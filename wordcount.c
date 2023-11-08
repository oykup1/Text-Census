#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>

#define _ERROR -1
extern int errno;

int main (int argc, char *argv[]) {


//Checking we have correct number of arguments
if (argc != 2) {
printf("Error! Input txt file\n");
exit(-1);
}

//Opening file
int fd = open(argv[1], O_RDONLY);
if(fd == _ERROR) {
printf("Error number: %d, %s\n", errno, strerror(errno));
exit(-1);
}

int words = 0;
int charz = 0;
int lines = 0;
char prevChar = ' ';

//Creating buffer to store chars
char* buffer = (char*)malloc(sizeof(char));

int sz = 1;

while((sz = read(fd,buffer,sizeof(char))) == 1){

words = ((isspace(*buffer)) && !(isspace(prevChar))) ? words+1 : words;
lines = (*buffer == '\n') ? lines+1 : lines;
charz = charz + 1;
prevChar = *buffer;

}

if (sz == _ERROR) {
printf("Error number: %d, %s\n", errno, strerror(errno));
exit(-1);
}

if (sz == 0){
	if(isspace(prevChar) == 0) { // If last read character was a part of a word, then increment worrd
	words++;
	lines++; // Also make sure to consider last line since it wasn't denoted with \n	
	}
}

printf("%d %d %d %s\n", charz, words, lines, argv[1]);
return 0;
}
