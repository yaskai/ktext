#include <math.h>
#include <string.h>
#include "raylib.h"
#include "app.h"
#include "disp.h"
#include "common/arena.h"
#include "input.h"

DisplayState d_state = (DisplayState) {0}; 
AppInstance *ptr_app;

Arena disp_arena = (Arena) {0};

void display_Init(AppInstance *app) {
	ptr_app = app;

	d_state.line_count = app->text_win_h / app->font_size;
	d_state.line_num_width = (app->font_size * 0.5f) * 4;  

	d_state.col_count = app->text_win_w / app->font_size;

	disp_arena = arena_Init(d_state.line_count * d_state.col_count);
}

void buf_DrawLineNumbers(Buffer *buf) {
	for(u32 i = 0; i < buf->num_lines; i++) {
		float y = i * (ptr_app->font_size + ptr_app->font_spacing);
		DrawTextEx(ptr_app->font, TextFormat("%d", i), (Vector2) { 0, y }, ptr_app->font_size, ptr_app->font_spacing, GRAY);
		DrawLine(0, y + ptr_app->font_size, 1920, y + ptr_app->font_size, GRAY);
	}
}

void buf_Display(Buffer *buf) {
	for(int i = 0; i < buf->num_lines; i++) {
		BufLine *curr_line = &buf->lines[i];

		// Get y coordiate for text rendering   
		float y = i * (ptr_app->font_size + ptr_app->font_spacing);

		disp_DrawLineNumber(buf, y, i);

		// Draw line's string
		DrawTextEx(ptr_app->font, curr_line->data, (Vector2) { d_state.line_num_width, y }, ptr_app->font_size, ptr_app->font_spacing, RAYWHITE);
	}

	// *TEST!
	// Draw input field 
	InputState *input = input_GetInstance();
	DrawTextEx(ptr_app->font, input->field, (Vector2) { d_state.line_num_width, 1100 }, ptr_app->font_size, ptr_app->font_spacing, RAYWHITE);

	disp_DrawCursor(buf);
}

void disp_DrawLineNumber(Buffer *buf, float pos_y, u32 line_idx) {
	Color color = (buf->cursor_row == line_idx) ? LIGHTGRAY : GRAY;

	DrawTextEx(
			ptr_app->font,
			TextFormat("%d", line_idx),
			(Vector2) { ptr_app->font_size * 0.5f, pos_y },
			ptr_app->font_size,
			ptr_app->font_spacing,
			color
			);
}

void disp_DrawCursor(Buffer *buf) {
	AppInstance *app = app_GetInstance();

	Vector2 pos;
	pos.x = d_state.line_num_width;
	pos.y = buf->cursor_row * (ptr_app->font_size + ptr_app->font_spacing);

	BufLine *hovered_line = &buf->lines[buf->cursor_row];
	Vector2 char_size = disp_MeasureChar(buf, buf->cursor_col, buf->cursor_row); 

	char temp[buf->cursor_col+1];
	memset(temp, '\0', buf->cursor_col+1);
	memcpy(temp, hovered_line->data, buf->cursor_col);
	
	bool empty = strlen(temp) == 0;
	if(empty) {
		char_size = MeasureTextEx(
			app->font,
			" ", 
			app->font_size, 
			app->font_spacing
			);
	}

	Vector2 size_left = MeasureTextEx(
			app->font,
			temp, 
			app->font_size, 
			app->font_spacing
			);

	Rectangle rec = (Rectangle) {
		.x = fmaxf(pos.x + size_left.x, pos.x),
		.y = pos.y,
		.width = char_size.x, 
		.height = char_size.y 
	};

	DrawRectangleLinesEx(rec, 1, RAYWHITE);
}

Vector2 disp_MeasureLine(Buffer *buf, u32 line_idx) {
	AppInstance *app = app_GetInstance();
	
	return MeasureTextEx(
			app->font, 
			buf->lines[line_idx].data,
			app->font_size, 
			app->font_spacing
			);	
}

Vector2 disp_MeasureChar(Buffer *buf, int col, int row) {
	AppInstance *app = app_GetInstance();

	return MeasureTextEx(
			app->font,
			TextFormat("%c", buf->lines[buf->cursor_row].data[buf->cursor_col]),
			app->font_size,
			app->font_spacing
			);
}

