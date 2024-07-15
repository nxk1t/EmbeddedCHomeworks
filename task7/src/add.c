#include "calc.h"

long long int add()
{
    long long int first, second;
    printf("Введите первое целое число: ");
    scanf("%lld", &first);

    printf("Введите второе целое число: ");
    scanf("%lld", &second);

    return first + second;
}