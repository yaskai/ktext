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

	if(inst->char_pressed == 'G')
		buf->cursor_row = buf->num_lines; 

	buf->cursor_row += move_y;
	if(buf->cursor_row < 0) buf->cursor_row = 0;
	if(buf->cursor_row > buf->num_lines - 1) buf->cursor_row = buf->num_lines - 1;

	BufLine *line = &buf->lines[buf->cursor_row];

	buf->cursor_col += move_x;
	if(buf->cursor_col > line->len - 2) buf->cursor_col = line->len - 2;
	if(buf->cursor_col < 0) buf->cursor_col = 0;

	if(inst->char_pressed == '$') 
		buf->cursor_col = line->len;

	if(inst->char_pressed == '^')
		buf->cursor_col = 0;
}

