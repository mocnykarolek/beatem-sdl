#define _USE_MATH_DEFINES
#include<math.h>
#include<stdio.h>
#include<string.h>
#include "logic.hh"
#include "draw.hh"

extern "C" {
#include"./SDL2-2.0.10/include/SDL.h"
#include"./SDL2-2.0.10/include/SDL_main.h"
}

#define SCREEN_WIDTH	640
#define SCREEN_HEIGHT	480
#define nigga 3
#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4



// main
#ifdef __cplusplus
extern "C"
#endif
int main(int argc, char **argv) {
	int t1, t2, quit, frames;
	double delta, worldTime, fpsTimer, fps, distance, etiSpeed;

	SDL_Event event;
	SDL_Surface *eti;

	// okno konsoli nie jest widoczne, je¿eli chcemy zobaczyæ
	// komunikaty wypisywane printf-em trzeba w opcjach:
	// project -> szablon2 properties -> Linker -> System -> Subsystem
	// zmieniæ na "Console"
	// console window is not visible, to see the printf output
	// the option:
	// project -> szablon2 properties -> Linker -> System -> Subsystem
	// must be changed to "Console"
	printf("wyjscie printfa trafia do tego okienka\n");
	printf("printf output goes here\n");

	Scr* screenObj = new Scr(SCREEN_WIDTH, SCREEN_HEIGHT); // objekt ekranu


	eti = SDL_LoadBMP("./eti.bmp");
	if(eti == NULL) {
		printf("SDL_LoadBMP(eti.bmp) error: %s\n", SDL_GetError());
		screenObj->~Scr();
		SDL_Quit();
		return 1;
		};



	char text[128];
	int czarny = SDL_MapRGB(screenObj->GetFormat(), 0x00, 0x00, 0x00);
	int zielony = SDL_MapRGB(screenObj->GetFormat(), 0x00, 0xFF, 0x00);
	int czerwony = SDL_MapRGB(screenObj->GetFormat(), 0xFF, 0x00, 0x00);
	int niebieski = SDL_MapRGB(screenObj->GetFormat(), 0x11, 0x11, 0xCC);

	t1 = SDL_GetTicks();

	frames = 0;
	fpsTimer = 0;
	fps = 0;
	quit = 0;
	worldTime = 0;
	distance = 0;
	etiSpeed = 1;
	double cam_pos_x = 0;

	Player* gracz = new Player(SCREEN_WIDTH / 2, SCREEN_HEIGHT /2, 10, 10 ,100);
	Enemy* enemy1 = new Enemy(SCREEN_WIDTH /3,SCREEN_HEIGHT / 3, 20, 20 ,100);



	while(!quit) {

		

		t2 = SDL_GetTicks();
		
		//printf("Czas dt: %f\n", t2-t1);
		// w tym momencie t2-t1 to czas w milisekundach,
		// jaki uplyna³ od ostatniego narysowania ekranu
		// delta to ten sam czas w sekundach
		// here t2-t1 is the time in milliseconds since
		// the last screen was drawn
		// delta is the same time in seconds
		delta = (t2 - t1) * 0.001;
		//printf("Delta time: %f\n", delta);
		t1 = t2;

		worldTime += delta;

		distance += etiSpeed * delta;

		SDL_FillRect(screenObj->screen, NULL, czarny);

		screenObj->DrawSurface(screenObj->screen, eti,
		            SCREEN_WIDTH / 2 + sin(distance) * SCREEN_HEIGHT / 3,
			    SCREEN_HEIGHT / 2 + cos(distance) * SCREEN_HEIGHT / 3);



		fpsTimer += delta;
		if(fpsTimer > 0.5) {
			fps = frames * 2;
			frames = 0;
			fpsTimer -= 0.5;
			};

		// tekst informacyjny / info text
		screenObj->DrawRectangle(screenObj->screen, 4, 4, SCREEN_WIDTH - 8, 36, zielony, niebieski);
		//            "template for the second project, elapsed time = %.1lf s  %.0lf frames / s"
		sprintf(text, "Szablon drugiego zadania, czas trwania = %.1lf s  %.0lf klatek / s", worldTime, fps);
		screenObj->DrawString(screenObj->screen, screenObj->screen->w / 2 - strlen(text) * 8 / 2, 10, text, screenObj->charset);
		//	      "Esc - exit, \030 - faster, \031 - slower"
		sprintf(text, "Esc - wyjscie, \030 - przyspieszenie, \031 - zwolnienie");
		screenObj->DrawString(screenObj->screen, screenObj->screen->w / 2 - strlen(text) * 8 / 2, 26, text, screenObj->charset);

		sprintf(text, "nigger");
		screenObj->DrawString(screenObj->screen, SCREEN_WIDTH / 2 + sin(distance) * SCREEN_HEIGHT / 7, SCREEN_HEIGHT / 2 + cos(distance) * SCREEN_HEIGHT / 7, text, screenObj->charset);

		enemy1->drawEnemy(screenObj, czerwony, czerwony, cam_pos_x);

		gracz->drawPlayer(screenObj, zielony, niebieski, cam_pos_x);

		CheckEnemyPlayerCollision(gracz, enemy1);

		const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
		gracz->borderCollision(SCREEN_WIDTH, SCREEN_HEIGHT);
		if(currentKeyStates[SDL_SCANCODE_W]) gracz->updatePosition(UP, delta, &cam_pos_x);
		if (currentKeyStates[SDL_SCANCODE_S]) gracz->updatePosition(DOWN,delta, &cam_pos_x);
		if (currentKeyStates[SDL_SCANCODE_A]) gracz->updatePosition(LEFT, delta, &cam_pos_x);
		if (currentKeyStates[SDL_SCANCODE_D]) gracz->updatePosition(RIGHT, delta, &cam_pos_x);
		



		SDL_UpdateTexture(screenObj->scrtex, NULL, screenObj->screen->pixels, screenObj->screen->pitch);
//		SDL_RenderClear(renderer);
		SDL_RenderCopy(screenObj->renderer, screenObj->scrtex, NULL, NULL);
		SDL_RenderPresent(screenObj->renderer);
		

		

		// obs³uga zdarzeñ (o ile jakieœ zasz³y) / handling of events (if there were any)
		while(SDL_PollEvent(&event)) {
			switch(event.type) {
				case SDL_KEYDOWN:
					if (event.key.keysym.sym == SDLK_ESCAPE) quit = 1;
					else if (event.key.keysym.sym == SDLK_UP) etiSpeed = 2.0;
					else if (event.key.keysym.sym == SDLK_DOWN) etiSpeed = 0.3;
					else if (event.key.keysym.sym == SDLK_w) n();
					
					break;
				case SDL_KEYUP:

					etiSpeed = 1.0;
					break;
				case SDL_QUIT:
					quit = 1;
					break;
				};
			};
		frames++;
		};

	// zwolnienie powierzchni / freeing all surfaces
	

	SDL_Quit();
	return 0;
	};
