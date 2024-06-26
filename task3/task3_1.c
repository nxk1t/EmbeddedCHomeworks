#include <stdio.h>

void binaryRepresentation(int value)
{
    printf("Binary representation of integer: ");
    for (int i = 31; i >= 0; i--)
    {
        unsigned int temp = (value & (1 << i));
        temp >>= i;
        printf("%u", temp);
    }
    printf("\n");
}

int main()
{
    int value, swapValue;
    printf("Enter positive integer: ");
    scanf("%d", &value);
    if (value < 0)
    {
        printf("\nYou entered negative integer!");
        return -1;
    }

    printf("\nValue: %d\n", value);
    binaryRepresentation(value);

    printf("\n\nEnter swap-byte positive integer: ");
    scanf("%d", &swapValue);
    if (swapValue < 0)
    {
        printf("\nYou entered negative integer!");
        return -1;
    }

    printf("\nSwap value: %d\n", swapValue);
    binaryRepresentation(swapValue);

    char* valuePtr = (char*)&value;
    char* swapValPtr = (char*)&swapValue;

    valuePtr += 2;
    swapValPtr += 2;

    *valuePtr = *swapValPtr;

    printf("\n\nChanged value: %d", value);
    binaryRepresentation(value);

    return 0;
}