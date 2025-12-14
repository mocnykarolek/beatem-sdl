#include "logic.hh"

void n() {

	printf("n\n");
	
	
}

Player::Player(double x, double y, int h, int w, double speed) {
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
	this->speed = speed;

}

void Player::drawPlayer(Scr* s, int color_i, int color_o) {

	s->DrawRectangle(s->screen, this->x, this->y, this->w, this->h, color_i, color_o);

}

void Player::updatePosition(int direction, double delta) {
	if (direction == UP) {
		this->y -= this->speed * delta;
		printf("ruch do gory\n");
	}
	if (direction == DOWN) {
		this->y += this->speed * delta;
		printf("ruch na dol\n");
	}
	if (direction == LEFT) {
		this->x -= this->speed * delta;
		printf("ruch w lewo\n");
	}
	if (direction == RIGHT) {
		this->x += this->speed * delta;
		printf("ruch w prawo\n");
	}
}

void Player::borderCollision(int screen_width, int screen_height) {

	// gora 
	if (this->y < 0.1) {
		this->y = 0;
		printf("top border reached\n");
		
	}
	// dol
	if (this->y + this->h > screen_height - 0.1) {
		this->y = (screen_height) - this->h;
		printf("bottom border reached\n");
		
	}

	// lewo
	if (this->x < 0.1) {
		this->x = 0;
		printf("left border reached\n");
		
	}
	// prawo
	if (this->x + this->w > screen_width -0.1) {
		this->x = (screen_width) - this->w;
		printf("right border reached\n");
		
	}
	

}

Enemy::Enemy(double x, double y, int w, int h, double speed) {
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
	this->speed = speed;
}

void Enemy::drawEnemy(Scr* s, int color_i, int color_o) {
	s->DrawRectangle(s->screen, this->x, this->y, this->w, this->h, color_i, color_o);
}