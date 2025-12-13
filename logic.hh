#pragma once
#include <stdio.h>
#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4

void n();

class Player {
	public:
		double x, y, speed;
		int w, h;
		
		void updatePosition(int direction, double delta) {
			if (direction == UP) {
				this->y -= this->speed * delta;
				printf("ruch do gory\n");
			}
			if (direction == DOWN) {
				this->y += this->speed * delta;
				printf("ruch do gory\n");
			}
			if (direction == LEFT) {
				this->x -= this->speed * delta;
				printf("ruch do gory\n");
			}
			if (direction == RIGHT) {
				this->x += this->speed * delta;
				printf("ruch do gory\n");
			}
			
		}


};