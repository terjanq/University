/* Jan Góra
Problem biesiadujących filozofów
10/01/2018
*/


#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <time.h>


typedef char bool;
#define true 1
#define false 0

#define SHARED_BETWEEN_PROCESSES 1

int N = 10; //Number of Philosophes
int M = 30; //Number of dishes
bool turn_on_plates = true;
bool turn_on_thinking = true;
bool print_off = false;


//------------------------------------------------------------------------------

typedef struct {
  int dishesLeft;
  sem_t *stick;
  sem_t plates;
  sem_t eating;

} data;

void data_init(data* d) {
  d->stick = malloc(N * sizeof *d -> stick);
  for(int i=0; i<N; i++){
   sem_init(&d->stick[i], SHARED_BETWEEN_PROCESSES, 1);
  }
  sem_init(&d->plates, SHARED_BETWEEN_PROCESSES, 0);
  sem_init(&d->eating, SHARED_BETWEEN_PROCESSES, 0);
  d->dishesLeft = M;
}


void data_destroy(data* d) {
  for(int i=0; i<N; i++){
    sem_destroy(&d->stick[i]);
  }

  sem_destroy(&d->plates);
  sem_destroy(&d->eating);


}

//------------------------------------------------------------------------------
data *shared_data;


void start_race(){
  sem_post(&shared_data->eating);
  for(int i = 0; i < N - 1; i++) sem_post(&shared_data->plates);
}


bool eat(int *dishesEaten){
  sem_wait(&shared_data->eating);
    if(shared_data->dishesLeft == 0) {
      sem_post(&shared_data->eating);
      return 0;
    }
    if(shared_data->dishesLeft < 0){
      sem_post(&shared_data->eating);
      exit(-1);
    }
    
    (*dishesEaten)++;
    shared_data->dishesLeft--;
    
   
  sem_post(&shared_data->eating);
  return 1;
}

double think(){
  int sleep = rand()%N;
  usleep(sleep);
  return (double)sleep/1000;
}


void routine(int i){
  int dishesEaten = 0;
  double summaryThinkingTime = 0.0;

  bool isThereAnyFood = true;
  while(isThereAnyFood){
    if(turn_on_thinking) summaryThinkingTime = think();
    if(turn_on_plates) { sem_wait(&shared_data->plates);}
      sem_wait(&shared_data->stick[i]);
      sem_wait(&shared_data->stick[(i+1)%N]);

      isThereAnyFood = eat(&dishesEaten);

      sem_post(&shared_data->stick[(i+1)%N]);
      sem_post(&shared_data->stick[i]);
    if(turn_on_plates) sem_post(&shared_data->plates);
  }

  if(!print_off){
    printf("Philosoph No %d has eaten %d dishes ", i, dishesEaten);
    if(turn_on_thinking) printf("with summary thinking of %.3f ms", summaryThinkingTime);
    printf("\n");
  }
}


//------------------------------------------------------------------------------

int main(int argc, char *argv[]) {
  if(argc > 2){
    N = strtol(argv[1], NULL, 10);
    M = strtol(argv[2], NULL, 10);
    if(argc > 3){
      turn_on_plates = strtol(argv[3], NULL, 10);
      if(argc > 4){
        turn_on_thinking = strtol(argv[4], NULL, 10);
        if(argc > 5){
          print_off = strtol(argv[5], NULL, 10);
        }
      }
    }
  }

  printf("[N: %d, M: %d, turn_on_plates: %d, turn_on_thinking: %d]\n", N, M, turn_on_plates, turn_on_thinking);
  if(print_off) printf("[print_off: true]\n");
  srand(time(NULL));
  int fileDescriptor = shm_open("/data", O_CREAT | O_RDWR | O_TRUNC, S_IRUSR | S_IWUSR);
  ftruncate(fileDescriptor, sizeof(data));
  shared_data = mmap(NULL, sizeof(data), PROT_READ | PROT_WRITE, MAP_SHARED, fileDescriptor, 0);

  data_init(shared_data);

  for(int i=0; i<N; i++){
    if(fork() == 0){
       routine(i);
       break;
    }
    if(i==N - 1) start_race();
  }

  int status = 0;
  pid_t wpid;
  while ((wpid = wait(&status)) > 0);
  data_destroy(shared_data);
  shm_unlink("/data");
  return 0;
}