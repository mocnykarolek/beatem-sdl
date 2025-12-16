#pragma once
#include <stdio.h>
#include <math.h>
#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4
#include "draw.hh"

void n();

struct Vector {
	float pos_x, pos_y;
	Vector(float x, float y) : pos_x(x), pos_y(y) {}

	Vector() {
		pos_x = 0;
		pos_y = 0;
	}


	void print() {

		printf("X: %f, Y: %f\n", pos_x, pos_y);
	}

};


class Entity {

	Entity(){}



};


class Player {
	
	public:
		double x, y, speed;
		int w, h;
		double old_x, old_y;
		int health;
		int playerState;
		


		Player(double x, double y, int w, int h, double speed, int health);
		void drawPlayer(Scr* s, int color_i, int color_o, double cam_x);
		void updatePosition(int direction, double delta, double* cam_x);
		void borderCollision(int screen_width, int screen_height);
		void attack(Enemy* enemies);
		Vector GetCenteredCordinates();
};

class Enemy {
public:
	double x, y, speed;
	int w, h;
	int visible;
	int health;
	Enemy(double x, double y, int w, int h, double speed, int health);

	Enemy();

	void drawEnemy(Scr* s, int color_i, int color_o, double cam_x);
		
	Vector GetCenterCordinates();

};

void CheckEnemyPlayerCollision(Player* p, Enemy*e);
