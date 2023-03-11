#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>


int mage_points = 0, warrior_points = 0, ranged_points = 0, crit_count = 0;
int milliseconds = 0, round_counter = 0;

sem_t sem;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

struct player {
  unsigned int id;
  int health;
  unsigned int attack;
  unsigned int accuracy;
  char name[16];
};

struct player * makeNewPlayer(const int idImport,
  const char pNameImport[16],
    const int healthImport,
      const int attackImport,
        const int accuracyImport) {
  struct player * pNew = NULL;
  pNew = malloc(sizeof(struct player));
  if (pNew != NULL) {
    pNew -> id = idImport;
    pNew -> health = healthImport;
    pNew -> attack = attackImport;
    pNew -> accuracy = accuracyImport;
    strcpy(pNew -> name, pNameImport);
  } else {
    printf("Error: Allocation pNew failed.\n");
  }
  return pNew;

}

void attack(struct player * attacker, struct player * target0, struct player * target1) {
  int accuracyCheck = rand() % 101;
  int attackMod = rand() % 601 - 300;
  int crit, final_attack;
  struct player * focus = NULL;

  // It must wait! Or else it will crash! A classic semaphore setup.
  sem_wait(&sem);

  final_attack = attackMod + attacker -> attack;

  while (1) {
    int random_target = rand() % 2;
    if (random_target == 0 && target0 -> health >= 0) {
      focus = target0;
      break;
    }
    if (random_target == 1 && target1 -> health >= 0) {
      focus = target1;
      break;
    }
  }
  if (attacker -> accuracy >= accuracyCheck) {

    if (accuracyCheck == 100) {
      crit = final_attack * 3;
      focus -> health = focus -> health - crit;
      crit_count = crit_count + 1;
    }
    focus -> health = focus -> health - final_attack;
  }
  sem_post( & sem);
}

void * init() {
  int id = 1, random_attacker = 0;
  

  struct player * magic = makeNewPlayer(1, "Mike", 3000, 1400, 100);
  struct player * warrior = makeNewPlayer(2, "Bjørn", 10000, 300, 80);
  struct player * ranged = makeNewPlayer(3, "Ragnhild", 6000, 1000, 60);

  while (1) {
    usleep(milliseconds * 1000);
    if (warrior -> health <= 0 && ranged -> health <= 0) {
      mage_points++;
      break;
    } else if (magic -> health <= 0 && ranged -> health <= 0) {
      warrior_points++;
      break;
    } else if (warrior -> health <= 0 && magic -> health <= 0) {
      ranged_points++;
      break;
    }
    while (1) {
      random_attacker = rand() % 3;

      if (ranged -> health >= 0 && random_attacker == 0) {
        attack(ranged, warrior, magic);
        break;
      }
      if (magic -> health >= 0 && random_attacker == 1) {
        attack(magic, warrior, ranged);
        break;
      }
      if (warrior -> health >= 0 && random_attacker == 2) {
        attack(warrior, ranged, magic);
        break;
      }
    }
  }

  free(magic);
  free(warrior);
  free(ranged);

  magic = NULL;
  warrior = NULL;
  ranged = NULL;
}

void main(int argc, char * argv[]) {
  srand(time(NULL));
  // The overclock will increase efficeny until the CPU will bottleneck, then it will run in normal speed.
  int rounds = 0,num_threads = 400;

  // Init the semaphore!
  sem_init(&sem, 0, 1);
  if (argc < 2 || argc == 0) {
    printf("Please run the program like this: '%s <numbers of simulations>'\n", argv[0]);
    exit(1);
  }

  rounds = atoi(argv[1]);

  pthread_t threads[num_threads];
  for (; round_counter <= rounds-1;) {
    for (int i = 0; i < num_threads; i++) {
	if(round_counter <= rounds){
        	pthread_create(&threads[i], NULL, init,NULL);
		round_counter = round_counter + 1;
  		printf("%d\n",round_counter);
	}
    }

     for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
     }

  }

  // Mutex lock to make sure all threads are done before summarizing the result.
  pthread_mutex_lock( & mutex);
  printf("\nThe score:\nMage: %d\nWarrior: %d\nRanged: %d\nCrits: %d\n", mage_points, warrior_points, ranged_points, crit_count);
  pthread_mutex_unlock( & mutex);
  sem_destroy(&sem);

}
