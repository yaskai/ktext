#include "raylib.h"
#include "common/nums.h"
#include "buf.h"

#ifndef APP_H_
#define APP_H_

#define REQ_EXIT	0x01

#define MAX_OPEN_BUFFERS 64

typedef struct {
	Font font;
	int font_size, font_spacing;

	int text_win_w, text_win_h;

	Buffer open_buffers[MAX_OPEN_BUFFERS];
	Buffer *curr_buf;

	// bit flags for requesting events 
	// eg. REQ_EXIT for shutting down
	u8 req_flags;

} AppInstance;

void app_Init(AppInstance *app, char *file_path);
void app_Close(AppInstance *app);

void app_Update(AppInstance *app);
void app_Draw(AppInstance *app);

void display_Init(AppInstance *app);

AppInstance* app_GetInstance();

#endif

