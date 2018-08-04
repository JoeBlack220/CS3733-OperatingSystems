//Sort a list of numbers using two separate threads
//by sorting half of each list separately then
//recombining the lists
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUMBER_OF_THREADS 3
void *sorter(void *params);    /* thread that performs basic sorting algorithm */
void *sorter2(void *params);    /* thread that performs basic sorting algorithm */
void *merger(void *params);    /* thread that performs merging of results */
void sort();
int *list;
int *list2;
int *result;
int *SIZE2;
int SIZE;
typedef struct{
    int from_index;
    int to_index;
} parameters;
int main (int argc, const char * argv[]){
    srand(time(NULL));
    int i;
    SIZE = atoi(argv[1]);
    list = malloc(sizeof(*list) * SIZE);
    list2 = malloc(sizeof(*list2) * SIZE);
    result = malloc(sizeof(*list) * SIZE);
    SIZE2 = malloc(sizeof(*SIZE2));
    SIZE2 = SIZE;
    for (i = 0; i < SIZE; i++) {
      list[i] = rand() % 101;
      list2[i] = rand() % 101;
      //printf("%i\n", list[i]);
    }
    pthread_t workers[NUMBER_OF_THREADS];

    long timedif;
    struct timeval tpend;
    struct timeval tpstart;

    /* establish the first sorting thread */
    parameters *data = (parameters *) malloc (sizeof(parameters));
    data->from_index = 0;
    data->to_index = (SIZE/2) - 1;
    if (gettimeofday(&tpstart, NULL)) {
       fprintf(stderr, "Failed to get start time\n");
       return 1;
    }
    pthread_create(&workers[0], 0, sorter, data);

    /* establish the second sorting thread */
    data = (parameters *) malloc (sizeof(parameters));
    data->from_index = (SIZE/2);
    data->to_index = SIZE - 1;
    pthread_create(&workers[1], 0, sorter, data);
    if (gettimeofday(&tpend, NULL)) {
       fprintf(stderr, "Failed to get end time\n");
       return 1;
    }
    timedif = tpend.tv_usec - tpstart.tv_usec;
    printf("sorting is done in %ld microseconds\n", timedif);
    /* now wait for the 2 sorting threads to finish */
    for (i = 0; i < NUMBER_OF_THREADS - 1; i++)
        pthread_join(workers[i], NULL);
    /* establish the merge thread */
    data = (parameters *) malloc(sizeof(parameters));
    data->from_index = 0;
    data->to_index = (SIZE);
    pthread_create(&workers[2], 0, merger, data);
    /* wait for the merge thread to finish */
    pthread_join(workers[2], NULL);

    /* output the sorted array */
    if (gettimeofday(&tpstart, NULL)) {
       fprintf(stderr, "Failed to get start time\n");
       return 1;
    }

    data = (parameters *) malloc(sizeof(parameters));
    data->from_index = 0;
    data->to_index = (SIZE);
    pthread_create(&workers[2], 0,sorter2  , data);

    if (gettimeofday(&tpend, NULL)) {
       fprintf(stderr, "Failed to get end time\n");
       return 1;
    }
    timedif = tpend.tv_usec - tpstart.tv_usec;
    printf("sorting is done in %ld microseconds\n", timedif);

    return 0;
}
void *sorter(void *params){
    parameters* p = (parameters *)params;
    //SORT
    int begin = p->from_index;
    int end = p->to_index+1;
    int z;
    for(z = begin; z < end; z++){
        //printf("The array recieved is: %d\n", list[z]);
    }
    //printf("\n");
    int i,j,t,k;
    for(i=begin; i< end; i++){
        for(j=begin; j< end-i-1; j++){
            if(list[j] > list[j+1]){
                t = list[j];
                list[j] = list[j+1];
                list[j+1] = t;
            }
        }
    }
    for(k = begin; k< end; k++){
            //printf("The sorted array: %d\n", list[k]);
    }
    int x;
    for(x=begin; x<end; x++){
            result[x]=list[x] ;
    }
    //printf("\n");
    pthread_exit(0);
}
void *merger(void *params){
    parameters* p = (parameters *)params;
   //MERGE
    int begin = p->from_index;
    int end = p->to_index+1;
    int i,j,t;
    for(i=begin; i< end; i++){
        for(j=begin; j< end-i; j++){
            if(result[j] > result[j+1]){
                t = result[j];
                result[j] = result[j+1];
                result[j+1] = t;
            }
        }
    }
    int d;
    for(d=0; d<SIZE2; d++){
        //printf("The final resulting array is: %d\n", result[d+2]);
    }
    pthread_exit(0);
}
void *sorter2(void *params){
    parameters* p = (parameters *)params;
    //SORT
    int begin = p->from_index;
    int end = p->to_index+1;
    int z;
    for(z = begin; z < end; z++){
        //printf("The array recieved is: %d\n", list[z]);
    }
    //printf("\n");
    int i,j,t,k;
    for(i=begin; i< end; i++){
        for(j=begin; j< end-i-1; j++){
            if(list2[j] > list2[j+1]){
                t = list2[j];
                list2[j] = list2[j+1];
                list2[j+1] = t;
            }
        }
    }
    for(k = begin; k< end; k++){
            //printf("The sorted array: %d\n", list[k]);
    }
    int x;
    for(x=begin; x<end; x++){
            result[x]=list[x] ;
    }
    //printf("\n");
    pthread_exit(0);
}
