/*  
	This program is an analog of ls -la command in Linux terminal 
    As an argument, it takes the name of the directory whose information needs to be displayed
	example:
	input:  /media/Gl_test/
	output: drwxrwx--- 1 root vboxsf  4096 May 22 11:39 .
			-rwxrwx--- 1 root vboxsf   229 May 22 11:09 steps.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <stdio.h>
#include <curses.h>


void print_mode(mode_t* mode) {	
	printf(S_ISREG(*mode) ? "-" : "d");		//Test for a regular file.
	printf((*mode & S_IRUSR) ? "r" : "-");	//permission, owner.
    printf((*mode & S_IWUSR) ? "w" : "-");	//Write permission, owner.
    printf((*mode & S_IXUSR) ? "x" : "-");	//Execute/search permission, owner.
    printf((*mode & S_IRGRP) ? "r" : "-");	//Read permission, group.
    printf((*mode & S_IWGRP) ? "w" : "-");	//Write permission, group.
    printf((*mode & S_IXGRP) ? "x" : "-");	//Execute/search permission, group.
    printf((*mode & S_IROTH) ? "r" : "-");	//Read permission, others.
    printf((*mode & S_IWOTH) ? "w" : "-");	//Write permission, others.
    printf((*mode & S_IXOTH) ? "x" : "-");	//Execute/search permission, others.
}

void print_time(time_t *time) {
	char buf[100];
	struct tm* tm_info;	
	if((tm_info = localtime(time)) != NULL) {		
		strftime(buf, 100, "%b %d %H:%M", tm_info);  
		printf("%s ",buf);
	}
}

void output_names(uid_t* uid, gid_t* gid) {	
	struct group *grp;
	struct passwd *pwd;
	if((pwd = getpwuid(*uid)) != NULL) 
		printf("%s ",pwd->pw_name);	
	if((grp = getgrgid(*gid)) != NULL)
		printf("%s ",grp->gr_name);
}

int main(int argc, char* argv[]) {
	DIR *dir;
	struct dirent *file;
	struct stat file_stat;
	char buf[500]; 
	dir = opendir(argv[1]);
	while((file = readdir(dir)) != NULL)
	{
		sprintf(buf, "%s/%s", argv[1], file->d_name);	 //fill the buffer with the address
		stat(buf, &file_stat);	//get metadata
		print_mode(&file_stat.st_mode);	//access rights
		printf("%2zu ", file_stat.st_nlink);	//ammount of hard-links
		output_names(&file_stat.st_uid, &file_stat.st_gid);	//username and groupname
		printf("%5zu ", file_stat.st_size);
		print_time(&file_stat.st_mtime);
		printf(S_ISREG(file_stat.st_mode)   ? "\e[32;1m": "\e[34;1m");	// coloring: blue and tall for directories,
																		// green and tall for files
		printf("%s\n", file->d_name);
		printf ("\e[0m");
	}
	closedir(dir);
	return 0;
}
