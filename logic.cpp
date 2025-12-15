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

void Player::drawPlayer(Scr* s, int color_i, int color_o, double cam_x) {
	double screen_position = this->x - cam_x;
	s->DrawRectangle(s->screen, screen_position, this->y, this->w, this->h, color_i, color_o);

}

void Player::updatePosition(int direction, double delta, double* cam_x) {

	if (direction == UP) {

		this->old_y = this->y;
		this->y -= this->speed * delta;
		printf("ruch do gory\n");
	}
	if (direction == DOWN) {
		this->old_y = this->y;
		this->y += this->speed * delta;
		printf("ruch na dol\n");
	}
	if (direction == LEFT) {
		*cam_x -= this->speed * delta;
		this->old_x = this->x;
		this->x -= this->speed * delta;
		printf("ruch w lewo\n");
	}
	if (direction == RIGHT) {
		this->old_x = this->x;
		*cam_x += this->speed * delta;
		this->x += this->speed * delta;
		printf("ruch w prawo\n");
	}
	printf("Kamera: %f\n", *cam_x);
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

void Enemy::drawEnemy(Scr* s, int color_i, int color_o, double cam_x) {
	double screen_position_x = this->x - cam_x;
	s->DrawRectangle(s->screen, screen_position_x, this->y, this->w, this->h, color_i, color_o);
}
void CheckEnemyPlayerCollision(Player* p, Enemy* e) {

	// hitbox gracza
	p->x + p->w;
	p->y + p->h;

	// hitbox przeciwnika

	e->x + e->w;
	e->y + e->h;

	if (p->x < e->x + e->w && p->x + p->w > e->x && p->y <e->y + e->h && p->y + p->h > e->y) {

		p->x = p->old_x;
		p->y = p->old_y;
		printf("Kolizja wykryta\n");
	}

	
}