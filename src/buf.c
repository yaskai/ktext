#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "buf.h"

Buffer buf_CreateNew() {
	Buffer buf = (Buffer) {0};

	return buf;
}

Buffer buf_FromFile(char *path) {
	Buffer buf = (Buffer) {0};

	buf.cap_lines = BUF_LINE_START_CAP; 
	buf.lines = calloc(buf.cap_lines, sizeof(BufLine));

	FILE *pF = fopen(path, "r");
	if(!pF) {
		// File wasn't found return empty buffer
		return buf;
	}

	char line[BUF_LINE_START_CAP];
	while(fgets(line, sizeof(line), pF)) {
		BufLine *curr_line = &buf.lines[buf.num_lines];
		curr_line->len = strlen(line);
		curr_line->cap = BUF_LINE_START_CAP;
		curr_line->data = calloc(curr_line->cap, 1);
		memcpy(curr_line->data, line, strlen(line));

		buf.num_lines++;
	}

	return buf;
}

