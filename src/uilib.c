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


tex_button_t new_tex_button(sprite_t *sprite, float x, float y, float width, float height, char* text, float text_offs_x, float text_offs_y) {
	tex_button_t this;

	this.sprite = sprite;
	this.x = x;
	this.y = y;
	this.width= width;
	this.height = height;
	this.text = text;
	this.text_offs_x = text_offs_x;
	this.text_offs_y = text_offs_y;
	this.visible = true;


	//text offset?

	return this;
}

void draw_tex_button(tex_button_t *texbutt) {
	if(texbutt->visible == false) return;
	rdpq_mode_blender(RDPQ_BLENDER_MULTIPLY);
	//for(int i=0; i<MAX_SPRITES; i++) {
		//if(spriteActors[i] && spriteActors[i]->visible) {
			//surface_t surf = sprite_get_pixels(spriteActors[i]->sprite);
			// rdpq_tex_blit(&surf, spriteActors[i]->x,spriteActors[i]->y, &(rdpq_blitparms_t){
			// 	.cx = surf.width/2, .cy = surf.height/2,
			// 	.scale_x = spriteActors[i]->x_scale, .scale_y = spriteActors[i]->y_scale,
			// 	.theta = spriteActors[i]->angle
			// });

	float text_x = texbutt->x + texbutt->text_offs_x;
	float text_y = texbutt->y + texbutt->text_offs_y;

	rdpq_sprite_blit(texbutt->sprite, texbutt->x,texbutt->y, NULL); //&(rdpq_blitparms_t){

	// ? text color? 
	// rdpq_set_prim_color(RGBA32(0xFF, 0xFF, 0xFF, 0xFF));

	rdpq_text_printf(NULL, FONT_BUILTIN_DEBUG_MONO, text_x, text_y, texbutt->text);
			// 	.cx = surf.width/2, .cy = surf.height/2,
			// 	.scale_x = spriteActors[i]->x_scale, .scale_y = spriteActors[i]->y_scale,
			// 	.theta = spriteActors[i]->angle
			// });

			//rdp_draw_textured_rectangle(0);
		//}
	//}
}



//todo draw call? all ui in one