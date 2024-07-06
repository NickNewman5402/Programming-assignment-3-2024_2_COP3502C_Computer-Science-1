/*
Nick Newman
5295926
7/3/24
Comp Sci 1
Dr. Tanvir Ahmed
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_DISTANCE 28284.27

typedef struct StoreData {
    char storeName[20];
    int x, y;
}StoreData;

/* FUNCTION PROTOTYPES */
void findPerms(int*, int*, int, int, StoreData*, float*, int*);
void calcDistancesPerm(StoreData*, int*, int, float);




void findPerms(int* perm, int* used, int k, int n, StoreData* store, float* testDistance, int* bestPerm) {
    if (k == n) {
        float curDistance = 0;
        for (int i = 0; i < n; i += 2) {
            curDistance += sqrt(pow(store[perm[i + 1]].x - store[perm[i]].x, 2) + pow(store[perm[i + 1]].y - store[perm[i]].y, 2));
        }

        if (curDistance < *testDistance) {
            *testDistance = curDistance;
            for (int i = 0; i < n; i++) {
                bestPerm[i] = perm[i];
            }
        }
        return;
    }

    for (int i = 0; i < n; i++) {
        if (!used[i]) {
            used[i] = 1;
            perm[k] = i;
            findPerms(perm, used, k + 1, n, store, testDistance, bestPerm);
            used[i] = 0;
        }
    }
}

void calcDistancesPerm(StoreData* store, int* perm, int n, float curDistance) {
    float storeDistance = 0;

    printf("%0.3f", curDistance);
    for (int i = 0; i < n; i += 2) {
        storeDistance = sqrt(pow(store[perm[i + 1]].x - store[perm[i]].x, 2) + pow(store[perm[i + 1]].y - store[perm[i]].y, 2));
        printf("\n(%s, %s, %0.3f)", store[perm[i]].storeName, store[perm[i + 1]].storeName, storeDistance);
    }
    printf("\n");
}



int main(void) {

    int nRoads, nStores, testCases, combinations;
    float* testDistance = malloc(sizeof(float));


    scanf("%d", &testCases);


    for (int i = 0; i < testCases; i++) {

        scanf("%d", &nRoads);
        nStores = nRoads * 2;
        StoreData* store = malloc(nStores * sizeof(struct StoreData));

        for (int i = 0; i < nStores; i++) {
            scanf("%d" "%d", &store[i].x, &store[i].y);
            scanf("%s", store[i].storeName);

        }


        int* perm = calloc(sizeof(int), nStores);
        int* used = calloc(sizeof(int), nStores);
        int* bestPerm = calloc(sizeof(int), nStores);
        
        *testDistance = MAX_DISTANCE;
        findPerms(perm, used, 0, nStores, store, testDistance, bestPerm);
        calcDistancesPerm(store, bestPerm, nStores, *testDistance);


        free(store);
        free(perm);
        free(used);
        free(bestPerm);
    }

    free(testDistance);


    return 0;
}