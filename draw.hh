#pragma once
extern "C" {
#include"./SDL2-2.0.10/include/SDL.h"
#include"./SDL2-2.0.10/include/SDL_main.h"
}
#include <stdio.h>
class Scr {
public:
	SDL_Texture* scrtex;
	SDL_Window* window;

	SDL_Renderer* renderer;
	SDL_Surface* charset;
	SDL_Surface* screen;
	Scr(int width, int heigh) {
		int rc = SDL_CreateWindowAndRenderer(width, heigh, 0,
			&window, &renderer);
		if (rc != 0) {
			SDL_Quit();
			printf("SDL_CreateWindowAndRenderer error: %s\n", SDL_GetError());
			exit(1);
		};

		SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
		SDL_RenderSetLogicalSize(renderer, width, heigh);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_SetWindowTitle(window, "Szablon do zdania drugiego 2017");
		screen = SDL_CreateRGBSurface(0, width, heigh, 32,
			0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
		scrtex = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
			SDL_TEXTUREACCESS_STREAMING,
			width, heigh);
		SDL_ShowCursor(SDL_DISABLE);
		charset = SDL_LoadBMP("./cs8x8.bmp");
		if (charset == NULL) {
			printf("SDL_LoadBMP(cs8x8.bmp) error: %s\n", SDL_GetError());
			SDL_FreeSurface(screen);
			SDL_DestroyTexture(scrtex);
			SDL_DestroyWindow(window);
			SDL_DestroyRenderer(renderer);
			SDL_Quit();
			exit(1);
		};
		SDL_SetColorKey(charset, true, 0x000000);
	}

	~Scr() {
		SDL_FreeSurface(charset);
		SDL_FreeSurface(screen);
		SDL_DestroyTexture(scrtex);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		printf("memory has been relested");
	}

	SDL_PixelFormat* GetFormat() {
		return screen->format;
	}

	

	void DrawString(SDL_Surface* screen, int x, int y, const char* text,
		SDL_Surface* charset) {
		int px, py, c;
		SDL_Rect s, d;
		s.w = 8;
		s.h = 8;
		d.w = 8;
		d.h = 8;
		while (*text) {
			c = *text & 255;
			px = (c % 16) * 8;
			py = (c / 16) * 8;
			s.x = px;
			s.y = py;
			d.x = x;
			d.y = y;
			SDL_BlitSurface(charset, &s, screen, &d);
			x += 8;
			text++;
			
		};
	};
	void DrawPixel(SDL_Surface* surface, int x, int y, Uint32 color) {
		int bpp = surface->format->BytesPerPixel;
		Uint8* p = (Uint8*)surface->pixels + y * surface->pitch + x * bpp;
		*(Uint32*)p = color;
	};
	void DrawLine(SDL_Surface* screen, int x, int y, int l, int dx, int dy, Uint32 color) {
		for (int i = 0; i < l; i++) {
			DrawPixel(screen, x, y, color);
			x += dx;
			y += dy;
		};
	};
	void DrawRectangle(SDL_Surface* screen, int x, int y, int l, int k,
		Uint32 outlineColor, Uint32 fillColor) {
		int i;
		DrawLine(screen, x, y, k, 0, 1, outlineColor);
		DrawLine(screen, x + l - 1, y, k, 0, 1, outlineColor);
		DrawLine(screen, x, y, l, 1, 0, outlineColor);
		DrawLine(screen, x, y + k - 1, l, 1, 0, outlineColor);
		for (i = y + 1; i < y + k - 1; i++)
			DrawLine(screen, x + 1, i, l - 2, 1, 0, fillColor);
	};
	void DrawSurface(SDL_Surface* screen, SDL_Surface* sprite, int x, int y) {
		SDL_Rect dest;
		dest.x = x - sprite->w / 2;
		dest.y = y - sprite->h / 2;
		dest.w = sprite->w;
		dest.h = sprite->h;
		SDL_BlitSurface(sprite, NULL, screen, &dest);
	};



};