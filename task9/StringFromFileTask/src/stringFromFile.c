#include "stringFromFile.h"

int main()
{
    int fd;
    char writeBuf[] = "String from file", readBuf[strlen(writeBuf)], temp[SIZE] = "\0";

    fd = open("obj/output.txt", O_CREAT | O_RDWR, 0666);
    if(fd == 0) return 1;
    
    write(fd, writeBuf, strlen(writeBuf));

    int j = 0;
    
    for (int i = 0; i < strlen(writeBuf); i++)
    {
        lseek(fd, -i - 1, SEEK_END);
        read(fd, temp, 1);
        readBuf[j] = temp[0];
        j++;
    }

    printf("Содержимое файла output.txt: %s\n", readBuf); 
    
    close(fd);
    
    return 0;
    
}