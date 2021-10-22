#include <stdbool.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

void *findprimenum(void *param) {
  int *num = (int *)param;
  for(int i = 2; i < *num; i++){
    if(i <= 2){
      printf("Prime number %d\n",i);
    }
    for(int j = 2; 2 <= i - 1; j++){
      if(i%j==0){
        break;
      }
      if(j == i - 1){
        printf("Prime number %d\n",i);
      }
    }
    }
}

int  main() {
    pthread_t tid;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    int num;
    printf("Please enter an integer number greater than 0:");
    scanf("%d", &num);
    pthread_create(&tid, NULL, findprimenum,(void *) &num);
    // Then join threads
    pthread_join(tid, NULL);
    system("pause");
	  return 0;
    
}