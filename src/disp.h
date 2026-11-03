#include "raylib.h"
#include "common/nums.h"
#include "buf.h"

#ifndef DISP_H_
#define DISP_H_

typedef struct {
	// Number of lines and collumns that can be shown on screen 
	u16 line_count, col_count;
	// Line number zone width
	float line_num_width;
	
} DisplayState;

typedef struct {
	char *data;

} DisplayString; 

void buf_Display(Buffer *buf);
void disp_DrawLineNumber(Buffer *buf, float pos_y, u32 line_idx);
void disp_DrawCursor(Buffer *buf);

Vector2 disp_MeasureLine(Buffer *buf, u32 line_idx);
Vector2 disp_MeasureChar(Buffer *buf, int col, int row);

#endif
