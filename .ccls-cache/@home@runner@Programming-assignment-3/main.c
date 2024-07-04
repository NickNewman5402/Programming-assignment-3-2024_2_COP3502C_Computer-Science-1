#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct StoreData {
    char storeName[20];
    int x, y;
};

void displayStores(struct StoreData* store, int n) {
    for (int i = 0; i < n; i++)
        printf("\n\nStore name: %s\nx: %d\ny: %d\n\n", store[i].storeName, store[i].x, store[i].y);
}

void displayDist(float* distArry, int n) {
    for (int i = 0; i < n; i++)
        printf("\n\nDistance from store %d to store %d: %f\n\n", i, i + 1, distArry[i]);
}

void calcDistances(struct StoreData* store, int n, int combos) {
    // distance = sqrt((store[i+1].x - store[i].x)^2 + (store[i + 1].y - store[i].y)^2)
    float* distArry = calloc(sizeof(float), combos);
    for (int i = 0; i < n; i++)
        for(int j = 1; j < n; j++)
        distArry[i] = sqrt(pow(store[j].x - store[i].x, 2) + pow(store[j].y - store[i].y, 2));

    displayDist(distArry, combos);
}


int main(void) {

    int nRoads, nStores, testCases, combinations;

    scanf("%d", &testCases);


    for (int i = 0; i < testCases; i++) {

        scanf("%d", &nRoads);
        nStores = nRoads * 2;
        struct StoreData* store = malloc(nStores * sizeof(struct StoreData));

        for (int i = 0; i < nStores; i++) {
            scanf("%d" "%d", &store[i].x, &store[i].y);
            scanf("%s", store[i].storeName);

        }

        displayStores(store, nStores); // currently just used for debugging to ensure stores are vreated properly

        combinations = nStores * (nStores - 1) / 2; // to determine the number of combinations of stores to visit

        calcDistances(store, nStores, combinations); // to calculate the distance between each store and the other stores

    }


    return 0;
}