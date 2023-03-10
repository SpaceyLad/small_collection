
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>


int mage_points = 0, warrior_points = 0, ranged_points = 0,crit_count = 0;
int milliseconds = 0;

// Using unsigned int because all values except health will never go bellow 0.
// const is used because the variables will only be read when creating the characters.
// Using rand() is not optimal for 100% random battles because of the psudo random numbers,
// generated by time in C, but it is good enough for this case!

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
    printf("New player at %p\n", pNew);
  } else {
    printf("Error: Allocation pNew failed.\n");
  }
  return pNew;

}

void attack(struct player * attacker, struct player * target0, struct player * target1) {
  int accuracyCheck = rand() % 101;
  int attackMod = rand() % 601 - 300;
  int crit,final_attack;
  struct player *focus = NULL;

  final_attack = attackMod + attacker->attack;

while(1){
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

	if(accuracyCheck == 100){
	crit = final_attack * 3;
	focus -> health = focus -> health - crit;
	printf("%s attacked %s and it was a \033[0;31mCRIT!\033[0;37m Dealing 3 times more damage! Dealing %d, leaving the %s with %d health!\n",attacker->name,focus->name,crit,focus->name,focus->health);
	crit_count = crit_count + 1;
}
      focus -> health = focus -> health - final_attack;
      printf("%s attacked %s and dealt %d damage! %s has %d health left!\n", attacker -> name, focus -> name, final_attack,focus->name,focus -> health);
    } else {
      printf("%s tried to attack %s, but missed!\n", attacker -> name, focus -> name);
    }
  }

void init() {
  int id = 1, random_attacker = 0;

  printf("\nMaking new players..\n");

  struct player * magic = makeNewPlayer(1, "Mike", 3000, 1400, 100);
  struct player * warrior = makeNewPlayer(2, "Bjørn", 10000, 300, 80);
  struct player * ranged = makeNewPlayer(3, "Ragnhild", 6000, 1000, 60);

  printf("\nPlayers made!\n");

  printf("The mage %s! He has %d health and deals around %d damage each hit!\n", magic -> name, magic -> health, magic -> attack);
  printf("The warrior %s! He has %d health and deals around %d damage each hit!\n", warrior -> name, warrior -> health, warrior -> attack);
  printf("The ranged %s! She has %d health and deals around %d damage each hit!\n\n", ranged -> name, ranged -> health, ranged -> attack);

  while (1) {
    usleep(milliseconds * 1000);
    if (warrior -> health <= 0 && ranged -> health <= 0) {
      printf("\n\033[0;34mThe mage has won!\n");
      mage_points++;
      break;
    } else if (magic -> health <= 0 && ranged -> health <= 0) {
      printf("\n\033[0;31mThe warrior has won!\n");
      warrior_points++;
      break;
    } else if (warrior -> health <= 0 && magic -> health <= 0) {
      printf("\n\033[0;32mThe ranged has won!\n");
      ranged_points++;
      break;
    }
    while(1){
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
  printf("\033[0;37m");

  free(magic);
  free(warrior);
  free(ranged);

  magic = NULL;
  warrior = NULL;
  ranged = NULL;

  printf("\nMemory is free!\n");
}

void main(int argc, char * argv[]) {
  srand(time(NULL));
  int rounds = 0;
  if (argc < 2 || argc == 0) {
    printf("Please run the program like this: '%s <numbers of simulations>'\n", argv[0]);
    exit(1);
  }
  rounds = atoi(argv[1]);
  printf("We will run %d times!\n", rounds);

  for (int i = 0; i < rounds; i++) {
    init();
  }

  printf("\nThe score:\nMage: %d\nWarrior: %d\nRanged: %d\nCrits: %d\n", mage_points, warrior_points, ranged_points,crit_count);

}