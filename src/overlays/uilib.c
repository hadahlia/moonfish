#include "uilib.h"

button_t new_button(float x, float y, float width, float height, char* text) {
	button_t this;

	this.x = x;
	this.y = y;
	this.height = width;
	this.height = height;
	this.text = text;

	return this;
}

tex_button_t new_tex_button(sprite_t *sprite, float x, float y, float width, float height, char* text) {
	tex_button_t this;

	this.sprite = sprite;
	this.x = x;
	this.y = y;
	this.height = width;
	this.height = height;
	this.text = text;

	return this;
}


//todo draw call? all ui in one