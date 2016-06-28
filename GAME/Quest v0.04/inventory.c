/* This file contains all functions relevant to the users inventory (outside of initial item placement ) */

#include "hero.h"
#include "gear.h"
#include "inventory.h"

/*********************************************************************************
 * FUNCTION TO VIEW AND EXAMINE USER EQUIPPED GEAR
 *********************************************************************************/

void inventory (void)
{
	
	int uinput; 	// for user input
	int loop = 0;   // bool value for loop below
	char buffer;	// temp for scanf buffer problems.
	gear SELECTED;  // will be use for outputting the item stats to the user
	
	printf ("What would you like to do?\n\n");
	printf ("1. View Currently Equipped Gear\n");
	printf ("2. View Inventory\n");
	printf ("CHOICE: ");
	
	scanf  ("%i%c", &uinput, &buffer);
	
	if 		(uinput == 1) {
				loop = 1;
	}			
		
	else if (uinput == 2) {
				viewInventory();	// will need a function for user to actually view what they are carrying
	}
	
	else {
			printf ("What is your foul intent with this bogus answer? I'm just ending the program then...\n");
			exit(1);
		}
	
	//TODO: HAVE EVERY ITEM TYPE AND ORGANIZE THEM BETTER (see ring0 and ring1 in stupid position)
	while (loop)
	{
		
	/* DISPLAY ITEMS PLAYER IS WEARING */
	printf ("You are currently wearing: \n");
	printf ("1. Chest     	: %s\n", playerGear.chest.itemName);
	printf ("2. Ring0     	: %s\n", playerGear.ring0.itemName);
	printf ("3. Belt      	: %s\n", playerGear.belt.itemName);
	printf ("4. Main hand 	: %s\n", playerGear.righthand.itemName);
	printf ("5. Off hand  	: %s\n", playerGear.shield.itemName);
	printf ("6. Boots     	: %s\n", playerGear.legs.itemName);
	printf ("7. Helm      	: %s\n", playerGear.head.itemName);
	printf ("8. Ring1      	: %s\n", playerGear.ring1.itemName);
	
	
	/* HAVE USER CHOOSE NEXT OPTION */
	printf ("\nEnter a value to print the items stats or enter 9 to quit: ");
	scanf  ("%i%c", &uinput, &buffer);
	//fflush (stdin);
	
	
	/* Assign user choice to buffer struct SELECTED and print its stats */	
	switch (uinput) {
		case 1: 
			SELECTED = playerGear.chest;
			printItemStats(SELECTED);
			break;
		case 2: 
			SELECTED = playerGear.ring0;
			printItemStats(SELECTED);
			break;
		
		case 3:
			SELECTED = playerGear.belt;
			printItemStats(SELECTED);
			break;
			
		case 4: 
			SELECTED = playerGear.righthand;
			printItemStats(SELECTED);
			break;
			
		case 5: 
			SELECTED = playerGear.shield;
			printItemStats(SELECTED);
			break;
		
		case 6: 
			SELECTED = playerGear.legs;
			printItemStats(SELECTED);
			break;
			
		case 7:
			SELECTED = playerGear.head;
			printItemStats(SELECTED);
			break;
			
		case 8:
			SELECTED = playerGear.ring1;
			printItemStats(SELECTED);
			break;
			
		case 9:
			loop = 0;	// set boolean to false to end the loop and exit function
			break;
			
		default: 
			break;
		}
		
	// end while loop
	}
		
		/* To do this seriously we're going to need some type of idea. We want to loop through the structs for the selected item and print all non-zero values. 
		 * I would like to do it without extreme redundancy, so it's going to need a variable like SELECTEDITEM.itemName etc. */
			
}

/*********************************************************************************
 * FUNCTION TO VIEW INVENTORY (ITEMS BEING CARRIED) - CONTINUATION OF inventory()
 *********************************************************************************/	
 
void viewInventory (void)
{
	 
	/* Ok, so in order to do this we need to define an actual hero_inventory structure and a stock of starting inventory for testing
	 * That will go in hero.h so it's accessible from other files, this way we can add items we find in battle to it later */
	 //playerInventory.space[0] = light_potion; INVENTORY SET UP
	int i, uChoice;
	char uReply;
	char buffer;
	int consumeReturn;	// value will be used to determine whether or not to delete item when used. 
	 
	printf ("CURRENT INVENTORY:\n");
	 
	/* Temporary loop to print items, this needs to be modified obviously or it will always just print 10 items */
	for (i = 1; i < MAX_INVENTORY; i++) {
		
		/* DON'T DISPLAY EMPTY ITEM SLOTS (null) */ 
		if (playerInventory.space[i].itemID > 0) {	
			
			// If item is not a potion
			if (playerInventory.space[i].itemID > 90) {
			printf ("%2i:	%s\n", i, playerInventory.space[i].itemName);
		}
			// if item is a potion, print its stacked amount.
		else if (playerInventory.space[i].itemID < 90) {
			printf ("%2i:	%s (%i)\n", i, playerInventory.space[i].itemName, playerInventory.space[i].pot_stack);
		}
			//printf ("%2i:	%s\n", i, playerInventory.space[i].itemName);	//	obviously change i to 1 and the starting inventory space to 1 for players.
		}
	}
	
	// Get user input and we'll print out the items stats
	printf ("Please select an item, or enter 99 to go back\n");
	printf ("Choice: ");
	scanf("%i%c", &uChoice, &buffer); // TEMP FIX, BUT IT WORKS, the \n gets dumped into buffer so we can move on. 
		
	
	// If choice is not a valid inventory item *** MODIFY THIS, users can pick null spaces***
	if (uChoice < 0 || uChoice > MAX_INVENTORY || uChoice == 99) {
		return;	// Yep, you can do this! 
	}
	
	else {
		printItemStats(playerInventory.space[uChoice]);
	}
	
	/* I really hate this method, but see pointerfun.c in the misc test files folder, you CANNOT reference a pointer with a string literal
	 * since the pointer is just going to contain a memory address, the following is an easy fix but it's ugly. Learn better */

	/*********************************************************************************
	* OPTIONS FOR CONSUMABLE ITEMS
	*********************************************************************************/	
	
	/* Check if the item is consumable, see notes on comparing string literals to pointers to fix the following dumb solution (so we can just use itemType)*/
	if (playerInventory.space[uChoice].itemID >= 10 && playerInventory.space[uChoice].itemID <= 90 ) {
		printf ("Would you like to use this item? (Y/N): ");
		scanf  ("%c%c", &uReply, &buffer);	// TEMP FIX, we're going to have to fix all stdin for this program
		
		/* Check reply, do the following if yes */
		if (uReply == 'y' || uReply == 'Y') {
		consumeReturn = consume(playerInventory.space[uChoice]);	// Function is just below this one, it returns 0 if item was used, 1 if not
		
		/* IF the item was a potion and the function returned 0 */
			if (playerInventory.space[uChoice].itemID >= 10 && playerInventory.space[uChoice].itemID < 90 && consumeReturn == 0) {
				printf ("Debug: You chugged a potion comma bro\n");
				playerInventory.space[uChoice].pot_stack -= 1;
				
				/* IF pot stack is reduced to zero, remove the item */
				if (playerInventory.space[uChoice].pot_stack == 0) {
					playerInventory.space[uChoice] = null_item;
				}
			}
		/* IF the item was used and not a potion, remove it, if not, don't remove it */
			if (playerInventory.space[uChoice].itemID > 90 && consumeReturn == 0) {
			playerInventory.space[uChoice] = null_item;
			}
			
		}
	
		/* Check reply, do the following if no */
		else if (uReply == 'n' || uReply == 'N') {
			printf ("Anything you say, returning\n");
			return;
		}
		
		/* Check reply, do the following if bad answer (make this a loop or just interpret as a no later */
		else {
			printf ("Here we go again with that fag talk\n"); 
			exit(1);
		}
	}
	
	/*********************************************************************************
	* OPTIONS FOR EQUIPPABLE ITEMS (Testing with just armor as this will be lots of work
	*********************************************************************************/	
	/* XXX TODO TODO: MODIFY THIS SECTION TO CONTAIN EACH ITEM TYPE, NOT JUST CHEST ARMOR, EASY WORK */
	
	/* Check if the item is an equippable item (just chest armor for tonight) */
	if (playerInventory.space[uChoice].itemID >= 10000 && playerInventory.space[uChoice].itemID < 110000 ) {
		
		/* Prompt user about changing gear */
		printf ("Do you want to equip the %s?\n" "Choose (Y/N): ", playerInventory.space[uChoice].itemName);
		scanf  ("%c%c", &uReply, &buffer);
		
		/* If the user says yes: */
		if (uReply == 'y' || uReply == 'Y') {
			changeGear(playerInventory.space[uChoice], uChoice);		// function to swap out gear, below in this source file
		}
		
		else if (uReply == 'n' || uReply == 'N') {
			printf ("Anything you say, returning\n");
			return;
		}
		
		/* Check reply, do the following if bad answer (make this a loop or just interpret as a no later */
		else {
			printf ("Here we go again with that fag talk\n"); 
			exit(1);
		}
		
		
	}
			
	
	
			
	
}

/*********************************************************************************
 * FUNCTION TO CONSUME ITEMS AND MODIFY THE PLAYERS STATS BASED ON THAT ITEM
 *********************************************************************************/	
int consume (gear CONSUMABLE)
{
	/* This function gets passed the struct of the item the player wishes to use
	 * Determine it's stat modifiers and use. NOTE: MAKE SURE HEALTH CANNOT GO ABOVE
	 * THE PLAYERS CURRENT LEVEL MAX!!! */
	int i = 0;
	int modifier;	// the amount of the stat to be changed will be copied here.
	
	printf ("Debug Print\n" "MAX HEALTH = %i\n" "CURRENT HEALTH = %i\n", player.total_hp, player.current_hp);
		
	/* If item has hp healing, pot stack is not zero (user has pots), run a loop and make sure it doesn't heal the user beyond max hp */
	if (CONSUMABLE.hp_heal && CONSUMABLE.pot_stack > 0 && player.current_hp < player.total_hp) {
		modifier = CONSUMABLE.hp_heal; // set modifier to equal the amount of hp the item heals
		
		
			while (modifier > 0) {	// loop will only run until hp maxes out
				player.current_hp += 1;
				i++;				// counter so we know how much health was healed
				modifier--;			// decrement modifier by 1 until it reaches zero
			
				if (player.current_hp == player.total_hp) {
					printf ("Health is maxed out!\n");
					return 0;
				}
			}
		
		
	}	
	else {
		printf ("Health is already at maximum, cannot use\n");
		return 1;
	}
	
	
	printf ("Ahh, %i health has been restored\n", i);	// would be nice if you could say how much, but need to have a for
	return 0;




	
}
