#include <stdio.h>
#include "raylib.h"
#include "input.h"
#include "app.h"

InputState input_state = (InputState) {0};

InputState* input_GetInstance() {
	return &input_state;
}

void input_Update(InputState *inst) {
	inst->char_pressed = GetCharPressed();
	inst->key_pressed = GetKeyPressed();

	/*
	if(inst->char_pressed) {

		if(!inst->field[inst->field_len])
			inst->field[inst->field_len++] = inst->char_pressed;
		else
			inst->field[++inst->field_len] = inst->char_pressed;
	}

	if(inst->key_pressed == KEY_BACKSPACE || IsKeyPressedRepeat(KEY_BACKSPACE)) {
		inst->field[inst->field_len--] = '\0';
		if(inst->field_len < 0) inst->field_len = 0; 
	}
	*/

	input_MoveCursor(inst);
}

void input_ModeNormal(InputState *inst) {
}

void input_ModeInsert(InputState *inst) {

}

void input_ModeVisualLine(InputState *inst) {

}

void input_ModeVisualBlock(InputState *inst) {

}

void input_ModeCommand(InputState *inst) {

}

void input_MoveCursor(InputState *inst) {
	int move_x = 0, move_y = 0;

	if(IsKeyPressed(KEY_H) || IsKeyPressedRepeat(KEY_H)) --move_x;
	if(IsKeyPressed(KEY_J) || IsKeyPressedRepeat(KEY_J)) ++move_y;
	if(IsKeyPressed(KEY_K) || IsKeyPressedRepeat(KEY_K)) --move_y;
	if(IsKeyPressed(KEY_L) || IsKeyPressedRepeat(KEY_L)) ++move_x;

	Buffer *buf = app_GetInstance()->curr_buf;
	int prev_x = buf->cursor_col, prev_y = buf->cursor_row;
	int targ_x = prev_x, targ_y = prev_y;

	if(inst->char_pressed == 'G')
		targ_y = buf->num_lines;

	targ_y += move_y;
	if(targ_y < 0) targ_y = 0;
	if(targ_y > buf->num_lines - 1) targ_y = buf->num_lines - 1;

	BufLine *line = &buf->lines[buf->cursor_row];

	if(inst->char_pressed == '$') 
		move_x = line->len - 2 - buf->cursor_col;

	if(inst->char_pressed == '^') 
		move_x = -buf->cursor_col;

	targ_x += move_x;
	if(targ_x > line->len - 2) targ_x = line->len - 2;
	if(targ_x < 0) targ_x = 0;

	// Candel x movement if no move is possible 
	if(prev_x == targ_x) move_x = 0;

	if(abs(move_x)) {
		buf->wish_col = targ_x;
	} else {
		if(buf->wish_col < line->len - 2) targ_x = buf->wish_col;
	}

	buf->cursor_col = targ_x;
	buf->cursor_row = targ_y;
}

