/**********************************************************************************************************
 * Game/main.c
 * Main project file, program starts here. 

Things we need to do: Learn how to minimize the amount of includes. Do I just use one main.h type of file globally? 
 I don't understand. But learn because I think this is bloating your program. I think what we should do is make a main.h
 And include all of the standard library needs within that, and simply include main.h in each program file. 
 *  NOTE: 6/28 -> Do not do a main.h with includes to other .h files. Simply include the headers needed by each function at this point, afaik
 *  mindlessly linking every file to one another annihilates the program and causes a wall of errors 

This project will need a GAME loop that runs until the user chooses to quit etc. Get a guide on the basics of games.

We're going to need some kind of graphics because a total text based game is too shitty. So I would like to incorporate
 ncurses and some kind of movement abilities to pretty up the game.

THINGS TO DO: 
	Create different types of armor, maybe have them generate with random stats (if that can be done easily).
	Make armor reduce amount of physical damage taken
	Make atk effect the amount of damage dealt
	Make weapons change the atk value
	Make armor (actual gear) change the armor value (change that to def because its confusing)
	Get rand() and srand() in this program so we can generate random values to randomize damage, enemy encounters, etc.
	by the way hurr durr, characters need levels and the game needs an exp system. Noob.
	Implement Ncurses (this will be a major overhaul if we make the game gigantic before doing it, so I suggest doing this in early development)

	Create a "main menu screen" With a logo
	Create some kind of story
	Create friendly NPCs, Merchants, add GOLD system to game (enemy.gold, chests, etc).
	Have enemies have a CHANCE to drop items (not just a single item, maybe one of a few).
	Speaking of the above, an inventory struct is going to be needed to make that have any point.
	change the hp stat to a vitality stat that increases hp and maybe something else like stam.
	
	Add ability to save and load
	Encrypt the save file so its not plain text, plain text is fucking ridiculous.
	Add a death screen, have penalty for death instead of losing entire game. That said, add churches to save!

	Ultimate: Learn SDL, make the entire game actually graphical. Keep this project small so that is possible first before expanding into a huge project.
 **********************************************************************************************************/



#include "main.h"
#include "hero.h"
#include "enemy.h"
#include "gear.h"
#include "inventory.h"



/* FUNCTION PROTOTYPES */

// Function to get characters name, see hero.c
void getName(void);

// Function to generate enemies, see enemy.c
enemy enemies (void);

// Function for doing battle, see battle.c, commented out because the fight is starting from enemy.c at this point
//void battle (enemy CURRENT, NPC player )

/*********************************************************************************
 *  MAIN FUNCTION: Very basic for now, welcome and present a few options.
 *********************************************************************************/
int main (void)
{
	int choice; 
	
	
	/* GREETING */
	printf ("\n\n\n\nWelcome to DonQuest ALPHA version 0.03, Still heavily in progress\n");
	printf ("The game is still in extremely basic form, text only, so chill out and enjoy\n");
	printf ("New Features in .03 ALPHA:\n"
			"Player now has a browseable inventory\n"
			"Player can now consume potions and change equipment\n"
			"Player stats are now functioning\n\nCOMING SOON: "
			"Equipment will reduce incoming damage, attack will increase damage taken by enemies\n"
			"More gear and enemies with exp and more readable formatting coming soon. Will actually be a playable game at that point\n");
	printf ("Pretty cool how it's coming so far, lots of work to go, come back!\n");
	//sleep(5);
			
	printf ("\n\nPress ENTER to continue...\n");
	
	while(getchar() != '\n');

		
	// You HAVE to initialize all the game gear before anything can be equipped!! ALSO NOTE: THIS IS RUN TWICE, THAT'S PROBABLY NOT NECESSARY NOW.
	gameGear();	
	/* Get player name and initialize stats and gear */	
	getName(); 
	playerStatGen();
	playerStatUpdate();
	initPlayerGear();
	
	
	
	sleep(2); // replace with ncurses
	
	
	/* BETA: Present choices for game testing */ 
	
	while (choice != 6)	// 4 is the current quit option
    {	
		
		/* Show the choices */
		printf ("\n\nWhat would you like to do?\n");
		
		printf ("1. Examine My Gear\n");
		printf ("2. View My Stats\n");
		printf ("3. Fight something (note, enter either 0 or 1 and you will just die\n");
		printf ("4. About The Game\n");
		printf ("5. Change Gear\n");
		printf ("6. Quit\n");
		
		/* Query user for input */
		printf ("\nChoice: ");
		scanf  ("%1i", &choice);

		/* Examine input and continue accordingly */
		switch (choice)
		{
			case 1: 
				inventory();
				sleep(3);
				break;
				
			case 2:
				heroStats();
				break;
			
			case 3:
				// get an enemy (that function will also initiate a fight)
				enemies();
				break;
				
			case 4:
				//development();
				printf ("Development function not yet created, sorry again\n");
				sleep(3);
				break;
				
			case 5:
				//changegear(); // we can't just call this without passing it an ID, so this will have to also communicate with an inventory selection first.
				break;
			case 6:
				return 0;
				break;
				
			default:
				printf ("well that was a shitty choice m7..\n");
				break;
		}
		
	// end while loop
	}
				
				
				
		
		
		

		
	
	
	


	
	//free (hero);
	return 0;
}
