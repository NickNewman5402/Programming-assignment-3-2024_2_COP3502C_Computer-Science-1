/*
Nick Newman
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
void displayStores(StoreData*, int);
void displayDist(float*, int);
void displayPerms(int*, int);
void findPerms(int*, int*, int, int, StoreData*, float*);
void calcDistances(StoreData*, int, int);
void calcDistancesPerm(StoreData*, int*, int, float*);
int factorial(int);



void displayStores(StoreData* store, int n) {
    for (int i = 0; i < n; i++)
         printf("\n\nStore name: %s\nx: %d\ny: %d\n\n", store[i].storeName, store[i].x, store[i].y);
}

void displayDist(float* distArry, int n) {
    for (int i = 0; i < n; i++)
        printf("\n\nDistance from store %d to store %d: %f\n\n", i, i + 1, distArry[i]);
}

void displayPerms(int* permArry, int n){
    for(int i = 0; i<n; i++)
        printf("%d ", permArry[i]);
        printf("\n");
}

void findPerms(int* perm, int* used, int k, int n, StoreData* store, float* testDistance){

    if (k==n){
        
        float curDistance = 0;
        for(int i = 0; i < n; i += 2){
            curDistance += sqrt(pow(store[perm[i+1]].x - store[perm[i]].x, 2) + pow(store[perm[i+1]].y - store[perm[i]].y, 2));
        }

        if(curDistance < *testDistance){
        displayPerms(perm, n);
        calcDistancesPerm(store, perm, n, testDistance);
        }
        
        return;
    }
    int i;
    for(i = 0; i < n; i++){
        if(!used[i]){
            used[i] = 1;
            perm[k] = i;
            findPerms(perm, used, k+1, n, store, testDistance);
            used[i] = 0;
        }
    }
}

void calcDistances(StoreData* store, int n, int combos) {
    // testDistance = sqrt((store[i+1].x - store[i].x)^2 + (store[i + 1].y - store[i].y)^2)
    float* distArry = calloc(sizeof(float), combos);
    for (int i = 0; i < n; i++)
        for(int j = 1; j < n; j++)
        distArry[i] = sqrt(pow(store[j].x - store[i].x, 2) + pow(store[j].y - store[i].y, 2));

    displayDist(distArry, combos);
}

void calcDistancesPerm(StoreData* store, int* perm, int n,float* testDistance){

    //float* distArry = calloc(sizeof(float*), n);
    

    float curDistance = 0, storeDistance = 0;

    for(int i = 0; i < n; i += 2){
        curDistance += sqrt(pow(store[perm[i+1]].x - store[perm[i]].x, 2) + pow(store[perm[i+1]].y - store[perm[i]].y, 2));
    }

    if(curDistance < *testDistance){
    printf("%0.3f\n", curDistance);
    for(int i = 0; i < n; i += 2){
        storeDistance = sqrt(pow(store[perm[i+1]].x - store[perm[i]].x, 2) + pow(store[perm[i+1]].y - store[perm[i]].y, 2));

        printf("(%s, %s, %0.3f)\n", store[perm[i]].storeName, store[perm[i+1]].storeName, storeDistance);
        *testDistance = curDistance;
    }
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

        //displayStores(store, nStores); // currently just used for debugging to ensure stores are vreated properly

        //combinations = nStores * (nStores - 1) / 2; // to determine the number of combinations of stores to visit

        int* perm = calloc(sizeof(int), nStores);
        int* used = calloc(sizeof(int), nStores);
        
        *testDistance = MAX_DISTANCE;
        findPerms(perm, used, 0, nStores, store, testDistance);
        
        //calcDistances(store, nStores, combinations); // to calculate the testDistance between each store and the other stores

    }



    return 0;
} 