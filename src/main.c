#include "raylib.h"
#include "app.h"

int main(int argc, char *argv[]) {
	SetTraceLogLevel(LOG_ERROR);

	AppInstance app = (AppInstance) {0};

	int ww = 1920, wh = 1200;
	InitWindow(ww, wh, "ktext");	
	SetWindowState(FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE);

	app_Init(&app, argv[1]);

	while( (!WindowShouldClose()) ^ (app.req_flags & REQ_EXIT) ) {
		app_Update(&app);
		app_Draw(&app);
	}

	CloseWindow();
	return 0;
}

