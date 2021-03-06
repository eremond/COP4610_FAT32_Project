#include "program.h"
#include "dirparse.h"
#include "utils.h"
#include "parse.h"
#include "ls.h"
#include "cd.h"
#include "rm.h"
#include "creat.h"
#include "size.h"
#include <stdio.h>
#include <string.h>
char* USER_INPUT[5];

void RunProgram(char* prompt) {
	while (1) {
		printf("%s> ", prompt);
		GetUserInput();
		if (strcmp(USER_INPUT[0], "exit") == 0) {
			break;
		}
		else if (strcmp(USER_INPUT[0], "ls") == 0) {
		  if (strcmp(USER_INPUT[1], ". . . . .") == 0) {
			list(GetCurrentDirectoryClusterNum());
		  }
		  else {
			ls(USER_INPUT[1]);
		  }
		}
		else if(strcmp(USER_INPUT[0], "info") == 0) {
		  PrintBootSector();
		}
		else if (strcmp(USER_INPUT[0], "cd") == 0) {
		  if (strcmp(USER_INPUT[1], ". . . . .") == 0) {
		    printf("Requires an argument for path name\n");
		  }
		  else if (strcmp(USER_INPUT[1], ".") == 0) {}
		  else {
		    cd(USER_INPUT[1]);
		  }										
		}
		else if (strcmp(USER_INPUT[0], "creat") == 0) {
		  if (strcmp(USER_INPUT[1],". . . . .") == 0) {
		    printf("Requires an argument for the file name\n");
		  }
		  else if (strcmp(USER_INPUT[1],".") == 0) {
			printf("Invalid file name\n");
		  }
		  else if (strcmp(USER_INPUT[1],"..") == 0) {
			printf("Invalid file name\n");
		  }
		  else {
			char parsedDir[USER_INPUT_BUFFER_LENGTH];
			strcpy(parsedDir, USER_INPUT[1]);
			ToFAT32(parsedDir);
			creat(parsedDir);
		  }
		}
		else if (strcmp(USER_INPUT[0], "mkdir") == 0) {
		  if (strcmp(USER_INPUT[1],". . . . .") == 0) {
		    printf("Requires an argument for the directory name\n");
		  }
		  else if (strcmp(USER_INPUT[1],".") == 0) {
			printf("Invalid directory name\n");
		  }
		  else if (strcmp(USER_INPUT[1],"..") == 0) {
			printf("Invalid directory name\n");
		  }	
		  else {
			char parsedDir[USER_INPUT_BUFFER_LENGTH];
			strcpy(parsedDir, USER_INPUT[1]);
			ToFAT32(parsedDir);
			mkdir(parsedDir);
		  }
		}
	        else if (strcmp(USER_INPUT[0], "size") == 0) {
		  if (strcmp(USER_INPUT[1], ". . . . .") == 0) {
		    printf("Requires a file name argument\n");
		  }
		  else {
		    size(USER_INPUT[1]);
		  }
		}
		else if (strcmp(USER_INPUT[0], "rm") == 0) {
		  if (strcmp(USER_INPUT[1],". . . . .") == 0) {
		    printf("Requires an argument for the file name\n");
		  }
		  else if (strcmp(USER_INPUT[1],".") == 0) {
		    printf("Invalid file name\n");
		  }
		  else if (strcmp(USER_INPUT[1],"..") == 0) {
		    printf("Invalid file name\n");
		  }	
		  else {
		    char parsedDir[USER_INPUT_BUFFER_LENGTH];
		    strcpy(parsedDir, USER_INPUT[1]);
		    ToFAT32(parsedDir);
		    rm(parsedDir);
		  }
		}
		else if (strcmp(USER_INPUT[0], "rmdir") == 0) {
                  if (strcmp(USER_INPUT[1],". . . . .") == 0) {
                    printf("Requires an argument for the directory name\n");
                  }
                  else if (strcmp(USER_INPUT[1],".") == 0) {
                    printf("Invalid dir name\n");
                  }
                  else if (strcmp(USER_INPUT[1],"..") == 0) {
                    printf("Invalid dir name\n");
                  }
                  else {
                    char parsedDir[USER_INPUT_BUFFER_LENGTH];
                    strcpy(parsedDir, USER_INPUT[1]);
                    ToFAT32(parsedDir);
                    rmdir(parsedDir);
                  }
                }
		else if (strcmp(USER_INPUT[0], "open") == 0) {
		  if (strcmp(USER_INPUT[1], ". . . . .") == 0 ||
		    strcmp(USER_INPUT[2], ". . . . .") == 0)
		  {
		    printf("Requires a file name argument followed by a mode argument\n");
		  }
		  else {
		    char parsedDir[USER_INPUT_BUFFER_LENGTH];
		    strcpy(parsedDir, USER_INPUT[1]);
		    ToFAT32(parsedDir);
		    open(parsedDir, USER_INPUT[2]);
		  }
		}
		else if (strcmp(USER_INPUT[0], "close") == 0) {
		  if (strcmp(USER_INPUT[1], ". . . . .") == 0) {
		    printf("Requires a file name argument\n");
		  }
		  else {
		    char parsedDir[USER_INPUT_BUFFER_LENGTH];
		    strcpy(parsedDir, USER_INPUT[1]);
		    ToFAT32(parsedDir);
		    close(parsedDir);
		  }
		}
	}
	int k = 0;
	while (k < 5) {
		free(USER_INPUT[k]);
		k++;
	}
}

void GetUserInput(void) {
	char tmp;
	int i = 0;
	while(i < 5) {
		if (USER_INPUT[i] != NULL) {
			free(USER_INPUT[i]);
		}
		USER_INPUT[i] = (char*)calloc(1, sizeof(char));
		USER_INPUT[i][0] = '\0';
		i++;
	}
	unsigned int userVecIndex = 0;
	do {
		tmp = fgetc(stdin);
		if (userVecIndex == 4) {
			if (tmp != '\"')
				printf("Expected quotes around last argument");
			tmp = fgetc(stdin);
			while (tmp != '\"') {
				USER_INPUT[userVecIndex] = DynStrPushBack(USER_INPUT[userVecIndex], tmp);
				tmp = fgetc(stdin);
			}
			// get the rest of the stream
			while (tmp != '\n' && tmp != '\0') {
				tmp = fgetc(stdin);
			}
		}
		else {
			while(tmp != ' ' && tmp != '\n' && tmp != '\0') {
				USER_INPUT[userVecIndex] = DynStrPushBack(USER_INPUT[userVecIndex], tmp);
				tmp = fgetc(stdin);
			}
		}
		userVecIndex++;
	}while (tmp != '\n' && tmp != '\0' && userVecIndex < 5);

	int j = userVecIndex;
	while (j < 5) {
		free(USER_INPUT[j]);
		USER_INPUT[j] = calloc(10, sizeof(char));
		strcpy(USER_INPUT[j], ". . . . .");
		j++;
	}
}
