#include "bashFunc.h"

void enterCommandString(char* str)
{
    fgets(str, 256, stdin);
    str[strcspn(str, "\n")] = '\0';
}

int get_command(char * str) {

	int symbol;
  	int i = 0;
  	while ((symbol = getchar()) != '\n') {

    	if (i < STRSIZE - 1){
	      str[i] = symbol;
	      i++;
	    } else {

	     return 1;
	    }
	  }

	str[i]='\0';

	return 0;

}

void splitCommandString(char* str, char** splitStr)
{
    char* token = strtok(str, " ");
    int i = 0;

    while (token != NULL) {
        splitStr[i] = token;
        i++;
        token = strtok(NULL, " ");
    }
    splitStr[i] = NULL;
}

void clearCommandString(char* str, char** splitStr)
{
    str = NULL;
    for (int i = 0; splitStr[i] != NULL; i++) splitStr[i] = NULL;
}
