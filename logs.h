#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#pragma warning(disable:4996)

void initializeLogs() {
	FILE* fp = fopen("logs.bin", "r");
	if (fp == NULL) {
		printf("Initialize new file logs\n");

		// File doesn't exist, create it
		fp = fopen("logs.bin", "w");
		if (fp == NULL) {
			printf("Error creating file\n");
			return;
		}
	}
	else {
		printf("Loading existing logs file\n");
		// Read data from file and add it to the tree
	}
}

void logMessage(char* log) {
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	char time[32];
	strftime(time, sizeof(time), "%c - ", &tm);
	char logAndTime[150];
	sprintf(logAndTime, "%s %s", time, log);

	FILE* fp = fopen("logs.bin", "a");
	if (fp == NULL) {
		printf("Error opening file\n");
		return;
	}
	fprintf(fp, "%s\n", logAndTime);
	fclose(fp);
}
