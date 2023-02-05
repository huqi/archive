#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <windows.h> 

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

#define MAX_LENGTH (256)

#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")


struct tm *get_time_ptr(void) {
	time_t timep = {0};
	struct tm *p = NULL;
	
	time(&timep);
	p = gmtime(&timep);
	
	return p;
}

void get_date_str(char *buffer, int size) {
	struct tm *p = get_time_ptr();
	
	memset(buffer, 0, size);
	sprintf(buffer, "%d%02d%02d", 1900+p->tm_year, 1+p->tm_mon, p->tm_mday);
}

void get_file_name(char *buffer, int size, char *filepath) {
	char *p = NULL;
	
	memset(buffer, 0, size);
	
	p = strrchr(filepath, '\\');
	strncpy(buffer, p ? p+1 : filepath, size-1);
}

void get_dir_name(char *buffer, int size, char *filepath) {
	char *p = NULL;
	char t[MAX_LENGTH] = {0};
	
	memset(buffer, 0, size);
	strncpy(t, filepath, sizeof(t));
	
	p = strrchr(t, '\\');
	*p = '\0';
	
	strncpy(buffer, t, size);
}

void gen_dir_name(char *buffer, int size, char *path) {
	char date[MAX_LENGTH] = {0};

	memset(buffer, 0, size);
	get_date_str(date, sizeof(date));
	
	snprintf(buffer, size, "%s\\%s", path, date);
}

void check_and_create_dir(char *path) {
    DIR *dp = opendir(path);
	if(dp != NULL) {
		closedir(dp);
		return ;	
	}
	
	mkdir(path);
}


void moveFile(char *path, char *file) {
	char new_file[MAX_LENGTH] = {0};
	char filename[MAX_LENGTH] = {0};
	
	get_file_name(filename, sizeof(filename), file);
	snprintf(new_file, sizeof(new_file), "%s\\%s", path, filename);
	
	rename(file, new_file);
}

int main(int argc, char *argv[]) {
	char *filename = NULL;	
	char new_path[MAX_LENGTH] = {0};
	char path[MAX_LENGTH] = {0};
	
	if (argc != 2)
		return 1;
		
	filename = argv[1];

	get_dir_name(path, sizeof(path), filename);	
	gen_dir_name(new_path, sizeof(new_path), path);
	check_and_create_dir(new_path);
	moveFile(new_path, filename);

	return 0;
}
