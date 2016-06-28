#include "main.h"
//#include <unistd.h> // this should take the sleep command in seconds

/* MACROS */
#define MAX_ENEMY_INVENTORY 5

/* gSTRUCTS */
typedef struct {
	//int ID; if i have an ID in the structure, how will I call it with the RNG. I think I need an enumerated list.
	int level;
	// where should I allocate the memory for this? DONE IN INDIVIDUAL DECLARATIONS FOR NOW
	char *name;
	int hp;
	int def;
	int gold;
	int atk;
	int enemy_incoming_damage;
	//gear enemy_inventory[MAX_ENEMY_INVENTORY];
} enemy;



/* Function that will ask the user for his name and return this information to main */
enemy enemies ();

/* Function to determine enemy damage reduction */
void enemyBattleParams (enemy selected_enemy);

/* OK, so I need to be able to reference enemies by some kind of ID so they are randomly selected, otherwise I'll have to manually pick each one and customizing the output of the battle to the specific enemy will be ridiculous.

Ok one thing we can do is physically enumerate each struct with an ID OUTSIDE OF THE STRUCT, like
enemy bacon_sandwich; // declare enemy of type enemy struct
int bacon_sandwich_ID = 1; 
int cheese_taco_ID = 2;
*/


