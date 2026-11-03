#include "common/nums.h"

#ifndef INPUT_H_
#define INPUT_H_

enum INPUT_MODES : u8 {
	MODE_NORMAL,
	MODE_INSERT,
	VISUAL_LINE,
	VISUAL_BLOCK,
	MODE_COMMAND,
}; 

typedef struct {
	char field[1024];
	int field_len;

	char *r_field;
	int *r_len;

	int key_pressed;
	char char_pressed;

	u8 mode;

} InputState;

InputState* input_GetInstance();

void input_Update(InputState *inst);

void input_ModeNormal(InputState *inst);
void input_ModeInsert(InputState *inst);
void input_ModeVisualLine(InputState *inst);
void input_ModeVisualBlock(InputState *inst);
void input_ModeCommand(InputState *inst);

void input_MoveCursor(InputState *inst);

#endif
