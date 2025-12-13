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

// narysowanie napisu txt na powierzchni screen, zaczynaj¹c od punktu (x, y)
// charset to bitmapa 128x128 zawieraj¹ca znaki
// draw a text txt on surface screen, starting from the point (x, y)
// charset is a 128x128 bitmap containing character images



// narysowanie na ekranie screen powierzchni sprite w punkcie (x, y)
// (x, y) to punkt œrodka obrazka sprite na ekranie
// draw a surface sprite on a surface screen in point (x, y)
// (x, y) is the center of sprite on screen



// rysowanie pojedynczego pixela
// draw a single pixel



// rysowanie linii o d³ugoœci l w pionie (gdy dx = 0, dy = 1) 
// b¹dŸ poziomie (gdy dx = 1, dy = 0)
// draw a vertical (when dx = 0, dy = 1) or horizontal (when dx = 1, dy = 0) line



// rysowanie prostok¹ta o d³ugoœci boków l i k
// draw a rectangle of size l by k



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

	Screen* screenObj = new Screen(SCREEN_WIDTH, SCREEN_HEIGHT);

	// tryb pe³noekranowy / fullscreen mode
//	rc = SDL_CreateWindowAndRenderer(0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP,
//	                                 &window, &renderer);
	
	
	
	


	// wy³¹czenie widocznoœci kursora myszy
	

	// wczytanie obrazka cs8x8.bmp


	eti = SDL_LoadBMP("./eti.bmp");
	if(eti == NULL) {
		printf("SDL_LoadBMP(eti.bmp) error: %s\n", SDL_GetError());
		screenObj->~Screen();
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

	while(!quit) {

		t2 = SDL_GetTicks();

		// w tym momencie t2-t1 to czas w milisekundach,
		// jaki uplyna³ od ostatniego narysowania ekranu
		// delta to ten sam czas w sekundach
		// here t2-t1 is the time in milliseconds since
		// the last screen was drawn
		// delta is the same time in seconds
		delta = (t2 - t1) * 0.001;
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
		screenObj->DrawRectangle(screenObj->screen, 4, 4, SCREEN_WIDTH - 8, 36, czerwony, niebieski);
		//            "template for the second project, elapsed time = %.1lf s  %.0lf frames / s"
		sprintf(text, "Szablon drugiego zadania, czas trwania = %.1lf s  %.0lf klatek / s", worldTime, fps);
		screenObj->DrawString(screenObj->screen, screenObj->screen->w / 2 - strlen(text) * 8 / 2, 10, text, screenObj->charset);
		//	      "Esc - exit, \030 - faster, \031 - slower"
		sprintf(text, "Esc - wyjscie, \030 - przyspieszenie, \031 - zwolnienie");
		screenObj->DrawString(screenObj->screen, screenObj->screen->w / 2 - strlen(text) * 8 / 2, 26, text, screenObj->charset);

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
