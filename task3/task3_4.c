#include <stdio.h>
#include <string.h>

#define N 256

int main()
{
    char str[N], substring[N];
    char *strPtr = NULL, *substrPtr = NULL, *savePtr = NULL;
    int match = 1;
    
    printf("Enter string: ");
    fgets(str, 256, stdin);
    str[strcspn(str, "\n")] = '\0';

    printf("Enter substring: ");
    fgets(substring, 256, stdin);
    substring[strcspn(substring, "\n")] = '\0';

    strPtr = str;
    substrPtr = substring;

    char *tempPtr = NULL;
    while (*strPtr != '\0')
    {
        substrPtr = substring;
        if (*strPtr == *substrPtr)
        {
            tempPtr = strPtr;
            while ((*substrPtr != '\0') && (*strPtr != '\0'))
            {
                if (*substrPtr == *strPtr)
                {
                    strPtr++;
                    substrPtr++;
                }
                else
                {
                    match = 0;
                    break;
                }
            }
            if (match == 0)
            {
                match = 1;
                strPtr = tempPtr;
                strPtr++;
                tempPtr = NULL;
            }
            else
            {
                if ((*strPtr == '\0') && (*substrPtr != '\0'))
                {
                    tempPtr = NULL;
                    break;
                }
                else break;
            }
        }
        else strPtr++;
    }
    printf("Begin pointer of substring: %p", tempPtr);
    
    // printf("\nString: %s\n", str);
    

    return 0;
}