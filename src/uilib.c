#include "uilib.h"

button_t new_button(float x, float y, float width, float height, char* text) {
	button_t this;

	this.x = x;
	this.y = y;
	this.width = width;
	this.height = height;
	this.text = text;

	return this;
}


tex_button_t new_tex_button(sprite_t *sprite, float x, float y, float scale, float width, float height, char* text, float text_offs_x, float text_offs_y) {
	// tex_button_t this;

	// this.sprite = sprite;
	// this.x = x;
	// this.y = y;
	// this.x_scale = this.y_scale = scale;
	// this.width= width * this.x_scale;
	// this.height = height * this.y_scale;
	// this.text = text;
	// this.text_offs_x = text_offs_x;
	// this.text_offs_y = text_offs_y;
	// this.visible = true;
	// this.angle = 0.f;

	tex_button_t button = (tex_button_t){
		.sprite = sprite,
		.x = x, .y = y, 
		.x_scale = scale, .y_scale = scale,
		.width = width * scale,
		.height = height * scale,
		.text = text,
		.text_offs_x = text_offs_x, .text_offs_y = text_offs_y,
		.visible = true,
		.angle = 0.f
	};

	//text offset?

	return button;
}

void draw_tex_button(tex_button_t *texbutt) {
	if(!texbutt->visible) return;
	//rdpq_mode_blender(RDPQ_BLENDER_MULTIPLY);
	float text_x = texbutt->x + texbutt->text_offs_x;
	float text_y = texbutt->y + texbutt->text_offs_y;
	

	//for(int i=0; i<MAX_SPRITES; i++) {
		//if(spriteActors[i] && spriteActors[i]->visible) {
	//surface_t surf = sprite_get_pixels(texbutt->sprite);
			// rdpq_tex_blit(&surf, spriteActors[i]->x,spriteActors[i]->y, &(rdpq_blitparms_t){
			// 	.cx = surf.width/2, .cy = surf.height/2,
			// 	.scale_x = spriteActors[i]->x_scale, .scale_y = spriteActors[i]->y_scale,
			// 	.theta = spriteActors[i]->angle
			// });

	//rdpq_set_prim_color(RGBA32(0xFF, 0xFF, 0xFF, 0xFF));
	
	rdpq_sprite_blit(texbutt->sprite, texbutt->x, texbutt->y, &(rdpq_blitparms_t){
		.cx = texbutt->sprite->width/2, .cy = texbutt->sprite->height/2,
		.scale_x = texbutt->x_scale, .scale_y = texbutt->y_scale,
		.theta = texbutt->angle
	});

	// ? text color? 
	// rdpq_set_prim_color(RGBA32(0xFF, 0xFF, 0xFF, 0xFF));
	//rdpq_text
	rdpq_text_printf(NULL, FONT_BUILTIN_DEBUG_MONO, text_x, text_y, texbutt->text);

	rdpq_set_mode_standard();
	//rdpq_set_prim_color(RGBA32(0xFF, 0xFF, 0xFF, 0xFF));
}



//todo draw call? all ui in one