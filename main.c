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
void findPerms(int*, int*, int, int, StoreData*, float*, int*, float, float**);// the last two float and float** were added by chatgpt
void calcDistancesPerm(StoreData*, int*, int, float);
float calcDistance(StoreData*, int, int, float**); // added by chatgpt*/



void findPerms(int* perm, int* used, int k, int n, StoreData* store, float* testDistance, int* bestPerm, float curDistance, float** memo) {
    //  float curDistance, float** memo added by chatGPT

    //*added by chatGPT
    if (curDistance >= *testDistance) {
        return; // Prune branches that exceed the current best distance
    }// finish GPT add */
    
    if (k == n) {
        /*float curDistance = 0;
        for (int i = 0; i < n; i += 2) {
            curDistance += sqrt(pow(store[perm[i + 1]].x - store[perm[i]].x, 2) + pow(store[perm[i + 1]].y - store[perm[i]].y, 2));
        }//*/

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
            //findPerms(perm, used, k + 1, n, store, testDistance, bestPerm);
            //* added by chatGPT
            if (k % 2 == 1) {
                float additionalDistance = calcDistance(store, perm[k], perm[k - 1], memo);
                findPerms(perm, used, k + 1, n, store, testDistance, bestPerm, curDistance + additionalDistance, memo);
            } else {
                findPerms(perm, used, k + 1, n, store, testDistance, bestPerm, curDistance, memo);
            }//*/ finish GPT add
            used[i] = 0;
        }
    }
}

//*added by GPT
float calcDistance(StoreData* store, int i, int j, float** memo) {
    if (memo[i][j] < 0) {
        memo[i][j] = sqrt(pow(store[j].x - store[i].x, 2) + pow(store[j].y - store[i].y, 2));
    }
    return memo[i][j];
}
//*/finish GPT add



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
        StoreData* store = malloc(nStores * sizeof(StoreData));

        for (int i = 0; i < nStores; i++) {
            scanf("%d" "%d", &store[i].x, &store[i].y);
            scanf("%s", store[i].storeName);

        }

        //added by GPT
        // Allocate and initialize memoization table
        float** memo = malloc(nStores * sizeof(float*));
        for (int j = 0; j < nStores; j++) {
            memo[j] = malloc(nStores * sizeof(float));
            for (int k = 0; k < nStores; k++) {
                memo[j][k] = -1.0; // Initialize to -1 to indicate that the value has not been calculated yet
            }
        }
        //finish GPT add

        int* perm = calloc(sizeof(int), nStores);
        int* used = calloc(sizeof(int), nStores);
        int* bestPerm = calloc(sizeof(int), nStores);
        
        *testDistance = MAX_DISTANCE;
        findPerms(perm, used, 0, nStores, store, testDistance, bestPerm, 0.0, memo);
        calcDistancesPerm(store, bestPerm, nStores, *testDistance);

        //added by GPT
        // Free memoization table
        for (int j = 0; j < nStores; j++) {
            free(memo[j]);
        }
        free(memo);
        //finish GPT add

        free(store);
        free(perm);
        free(used);
        free(bestPerm);
    }

    free(testDistance);


    return 0;
}