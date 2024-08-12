#include "shop.h"

pthread_mutex_t mutex[SHOP_SIZE];
long long int shops[SHOP_SIZE], clients_data[CLIENT_SIZE];

int main()
{
    pthread_t clients[CLIENT_SIZE], loader;
    int clientNumber[CLIENT_SIZE];

    srand(time(0));

    for (int i = 0; i < SHOP_SIZE; i++)
    {
        shops[i] = rand() % (SHOP_BALANCE + 1);
        pthread_mutex_init(&mutex[i], NULL);
    }

    for (int i = 0; i < CLIENT_SIZE; i++)
    {
        clients_data[i] = rand() % (CLIENT_BALANCE + 1);
        clientNumber[i] = i;
    }

    for (int i = 0; i < CLIENT_SIZE; i++)
    {
        pthread_create(&clients[i], NULL, &shopVisit, &clientNumber[i]);
    }
    pthread_create(&loader, NULL, loadShop, NULL);

    for (int i = 0; i < CLIENT_SIZE; i++)
    {
        pthread_join(clients[i], NULL);
    }
    pthread_join(loader, NULL);

    exit(EXIT_SUCCESS);
}