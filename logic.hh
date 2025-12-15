#pragma once
#include <stdio.h>
#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4
#include "draw.hh"
void n();

class Player {
	
	public:
		double x, y, speed;
		int w, h;
		double old_x, old_y;

		Player(double x, double y, int w, int h, double speed);
		void drawPlayer(Scr* s, int color_i, int color_o, double cam_x);
		void updatePosition(int direction, double delta, double* cam_x);
		void borderCollision(int screen_width, int screen_height);

};

class Enemy {
public:
	double x, y, speed;
	int w, h;

	Enemy(double x, double y, int w, int h, double speed);

	void drawEnemy(Scr* s, int color_i, int color_o, double cam_x);
		


};
void CheckEnemyPlayerCollision(Player* p, Enemy*e);