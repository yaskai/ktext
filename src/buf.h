#include "common/nums.h"
#include "common/arena.h"

#ifndef BUF_H_
#define BUF_H_

#define BUF_START_CAP		512
#define BUF_LINE_START_CAP 	2048

typedef struct {
	char *data;
	int len;
	int cap;

} BufLine;

typedef struct {
	BufLine *lines;	// Lines array
	char *path;		// File path string

	u32 num_lines;  // Line count
	u32 cap_lines;	// Lines array capacity

	int cursor_col;
	int cursor_row;

	int wish_col;

} Buffer;

Buffer buf_CreateNew();
Buffer buf_FromFile(char *path);

#endif

