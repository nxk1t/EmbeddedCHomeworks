#include <stdio.h>

void binaryRepresentation(int value, int flag)
{
    int counter = value > 0 ? 0 : -1;
    printf("Binary representation of integer: ");
    for (int i = 31; i >= 0; i--)
    {
        unsigned int temp = (value & (1 << i));
        temp >>= i;
        printf("%u", temp);
        if (counter >= 0 && flag) counter += temp;
    }
    printf("\n");
    if (counter >= 0 && flag) printf("Number of ones: %d\n", counter);
}

void swapByte(int value, int swapValue)
{
    binaryRepresentation(swapValue, 0);
    int thirdByte = (swapValue >> 16) & 0xFF;
    value = (value & 0xFF00FFFF) | (thirdByte << 16);
    binaryRepresentation(value, 0);
}

int main()
{
    int value;
    printf("Enter positive or negative integer: ");
    scanf("%d", &value);

    binaryRepresentation(value, 1);

    if (value >= 0)
    {
        int swapValue;
        printf("Enter value to swap third byte: ");
        scanf("%d", &swapValue);
        swapByte(value, swapValue);
    }

    return 0;
}