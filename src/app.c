#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"
#include "app.h"
#include "buf.h"
#include "disp.h"
#include "input.h"

AppInstance *app_self_ptr;

void app_Init(AppInstance *app, char *file_path) {
	app_self_ptr = app;

	app->font = LoadFontEx("resources/fonts/zed_mono.ttf", 64, NULL, 0);
	SetTextureFilter(app->font.texture, TEXTURE_FILTER_TRILINEAR);

	app->font_size = 32;

	app->text_win_w = 1920;
	app->text_win_h = 1200;

	app->open_buffers[0] = buf_FromFile(file_path);
	app->curr_buf = &app->open_buffers[0];

	display_Init(app);
}

void app_Close(AppInstance *app) {
	UnloadFont(app->font);
	*app = (AppInstance) {0};
}

void app_Update(AppInstance *app) {
	input_Update(input_GetInstance());
}

void app_Draw(AppInstance *app) {
	BeginDrawing();
	ClearBackground(BLACK);

	buf_Display(app->curr_buf);

	EndDrawing();
} 

AppInstance* app_GetInstance() {
	return app_self_ptr;
}

