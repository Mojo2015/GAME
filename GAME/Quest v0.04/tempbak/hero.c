/**********************************************************************************************************
 * Game/hero.c
 * Simple function to collect user information (name, )
 **********************************************************************************************************/

#include "main.h"
#include "hero.h"
#include "gear.h"

void playerStatGen (void);

	
/**********************************************************
 FUNCTION TO GET PLAYERS NAME
**********************************************************/

void getName (void)
{
	
	/* Variables */ 
	int x = 0; 								 // for the input loop below
	char * hero = malloc(sizeof(char) * 50); // player name will be stored here, free this at end of function

	/* ask for name */
	printf ("\n\nHola. What is your name?\n\n NAME: ");

	/* Loop to the maximum size of the player name, avoid stack overflow. */
	for (x; x < 50; x++) {
		hero[x] = getchar();
		if (hero[x] == '\n') {		// this WILL STORE the \n, so replace it below with NULL
			break;
		}
	}
	
	printf ("\n\n");
	hero[x] = '\0';					// replace the newline \n with a string terminating NULL

	
	/* Temporary Welcome screen */
	printf ("Hello %s. Will you be the hero of the north? The savior of the fallen realms?\nDo you have what it takes to lead \
the norse to victory?\nOr will we succumb to the unending wrath of the tyrannical juden?\n\n", hero);

	/* Insert players name into the player struct (see hero.h) and free the memory occupied by the pointer (no longer needed) */
	player.name = hero;	
	//free (hero); // we shouldn't need that memory anymore, actually we do because player.name is a pointer. Freeing this throws it away.
	
}

/*********************************************************************************
 * FUNCTION TO INITIALIZE THE PLAYERS STATS 
 *********************************************************************************/
void playerStatGen (void)
{
	
	/* XXX: FOR NOW, WE NEED TO RUN THE playerStatGen(); function OVER AGAIN if you expect the stats to be updated to reflect gear. Things need to be initialized in a loop in a game.
	 * Not to mention if the user unequips or equips new gear, we need the stats to reflect it IMMEDIATELY */
	/* Since the struct is globally defined in the hero.h header, we can simply adjust them now with no function i/o */
	
	/* We're going to need BASE values and "BONUS" values (the value of the BASE + BOOST from gear. Because we need to be able to alter base values with levels too. */
	
	// PRIMARY STATS
	player.level = 1;
	player.exp   = 0;

	// SECONDARY STATS
	player.dmg	 = (float) player.base_atk * AR_MULTIPLIER + playerGear.righthand.damage;	// calculate player damage
	
	/************************************************************************
	* BASE STATS - MODIFIED THROUGH LEVELS OR NAME CHANGE @ CHUCH
	************************************************************************/
	player.base_def  = 5;
	player.base_vit  = 5;
	player.base_hp   = 23;
	player.base_mp   = 0;
	player.base_luck = 0;
	player.base_atk  = 5;
	player.inven_cap = 20;	// 20 items in inventory to start
	
	
	// set the inventory limit
	
	/* This was my original idea for setting an inventory limit but it causes a segmentation fault :( */ 
	//playerInventory.capacity = player.inven_cap;	// two values for this is a bit redundant
	//playerInventory.carryID[playerInventory.capacity] = '\0';	// just to test. Setting the final value as NULL so we can determine where the end of inventory is
	
	/* NOTE: So player inventory works like a basic array. playerInventory.carryID[0] = integer value. use ITEMNAME.itemID (each items numbered ID). */
	
	// OTHER 
	player.gold  = 100;	// set inital gold to 100
	
	
	/************************************************************************
	* STARTING CHARACTER INVENTORY
	************************************************************************/
	/* We're not using element[0] because that looks dumb in game */
	playerInventory.space[1] = light_potion;
	playerInventory.space[2] = light_potion;
	playerInventory.space[3] = light_potion;
	playerInventory.space[4] = light_potion;
	
	//FOR TESTING, DON'T START A REAL GAME FILLING THEIR INVENTORY WITH GEAR
	playerInventory.space[5] = long_sword;
	playerInventory.space[6] = leather_chest;
	playerInventory.space[7] = leather_boots;
	playerInventory.space[8] = leather_gloves;
	playerInventory.space[9] = leather_hat;
	playerInventory.space[10] = quilt;
	playerInventory.space[11] = light_mana_potion;
	playerInventory.space[12] = momo_custom;
	
	/* NOTE THAT THE CHARACTER NEEDS TO BE INITIALIZED ONCE AND ONLY ONCE WITH HIS STATS AND STARTING GEAR AT THE BEGINNING
 *  OF THE GAME, THE BELOW SHOULD BE A STANDALONE FUNCTION BECAUSE IT WILL NEED TO BE RUN OFTEN AS THE GAME PROGRESSES
 *  IN THIS CURRENT STATE IT WOULD JUST RESET THE PLAYERS STATS TO LEVEL 1 EVERY TIME */
	
}
	
	
/************************************************************************
* FUNCTION TO UPDATE PLAYER STATS
*************************************************************************/	
void playerStatUpdate (void)
{
	

 
	/************************************************************************
	* GEAR STAT TOTALS - TO BE ADDED TO BASE FOR ADJUSTED PLAYER VALUE 
	************************************************************************/
	
	// BONUS DEFENSE, add all armor defense modifiers together:
	player.bonus_def = playerGear.belt.defense
					 + playerGear.chest.defense
					 + playerGear.hands.defense
					 + playerGear.head.defense
					 + playerGear.lefthand.defense
					 + playerGear.legs.defense
					 + playerGear.neck.defense
					 + playerGear.righthand.defense
					 + playerGear.ring0.defense
					 + playerGear.ring1.defense;
					 
					 
	player.bonus_hp  = playerGear.belt.hp
					 + playerGear.chest.hp
					 + playerGear.hands.hp
					 + playerGear.head.hp
					 + playerGear.lefthand.hp
					 + playerGear.legs.hp
					 + playerGear.neck.hp
					 + playerGear.righthand.hp
					 + playerGear.ring0.hp
					 + playerGear.ring1.hp;	 
					 
	player.bonus_mp  = playerGear.belt.mp
					 + playerGear.chest.mp
					 + playerGear.hands.mp
					 + playerGear.head.mp
					 + playerGear.lefthand.mp
					 + playerGear.legs.mp
					 + playerGear.neck.mp
					 + playerGear.righthand.mp
					 + playerGear.ring0.mp
					 + playerGear.ring1.mp;
					 
	player.bonus_luck  = playerGear.belt.luck
					   + playerGear.chest.luck
					   + playerGear.hands.luck
					   + playerGear.head.luck
					   + playerGear.lefthand.luck
					   + playerGear.legs.luck
					   + playerGear.neck.luck
					   + playerGear.righthand.luck
					   + playerGear.ring0.luck
					   + playerGear.ring1.luck;
					   
	player.bonus_ar  = playerGear.belt.ar
					 + playerGear.chest.ar
					 + playerGear.hands.ar
					 + playerGear.head.ar
					 + playerGear.lefthand.ar
					 + playerGear.legs.ar
					 + playerGear.neck.ar
					 + playerGear.righthand.ar
					 + playerGear.ring0.ar
					 + playerGear.ring1.ar;	 
	
	
	
	
	
	/************************************************************************
	* TOTAL STATS; BASE + GEAR - TO USE ON LIVE CHARACTER
	************************************************************************/
	player.total_def	= player.base_def  + player.bonus_def;
	player.total_mp		= player.base_mp   + player.bonus_mp;
	player.total_luck	= player.base_luck + player.bonus_luck;
	player.total_vit	= player.base_vit  + player.bonus_vit;
	player.total_ar    =  (player.base_atk * 10) + player.bonus_ar;	// attack rating, used to generate chance to hit
	
	// VITALITY * 3 is added to HP, so every point in vit will = 3 more hp
	player.total_hp     = player.base_hp   + player.bonus_hp + (player.total_vit * 3);
	
		/* Init all current stats to equal max character stats */
	//player.current_hp = player.total_hp;	/* *******PLEASE UNCOMMENT, STARTING WITH 0 HP WHILE I TEST CONSUMABLES */
	player.current_hp = 0;
	player.current_mp = player.total_mp;
	
	
	
	//initPlayerGear(); // run this function from main from now (as well as playerStatUpdate and init)
 
	
}

/*********************************************************************************
 * FUNCTION TO INITIALIZE THE PLAYERS STARTING GEAR
 *********************************************************************************/
void initPlayerGear (void)
{
	// run the gameGear function once to initialize all of the games armor types. Not sure how efficient this is. Later we should export that to a text
	// document and query it. This could be a huge waste of memory.
	

	//gameGear(); needs to be run to init all of the items in the game, but i have it set to run in the main function (program.c) so it should still be good
	//gameGear();
	
	
	/* EQUIP THE PLAYERS STARTING GEAR */
	playerGear.righthand = short_sword;
	playerGear.chest     = null_item;	// CURRENTLY_EQUIPPED.chest etc, this way we can pass it to other functions and it updates accordingly
	playerGear.ring0     = null_item;
	playerGear.ring1	 = null_item;
	playerGear.belt      = null_item;
	playerGear.lefthand  = null_item;
	playerGear.shield    = small_shield;
	playerGear.legs      = null_item;
	playerGear.head		 = null_item;
	// For testing purposes, within another function, try to print out shit about my chest armor now.
}

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
			printf ("%2i:	%s\n", i, playerInventory.space[i].itemName);	//	obviously change i to 1 and the starting inventory space to 1 for players.
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
		
		/* IF the item was used, remove it, if not, don't remove it */
			if (consumeReturn == 0) {
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
		
	/* If item has hp healing, run a loop and make sure it doesn't heal the user beyond max hp */
	if (CONSUMABLE.hp_heal && player.current_hp < player.total_hp) {
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
	

/*********************************************************************************
 * FUNCTION TO PRINT PLAYERS CURRENT STATS
 *********************************************************************************/			
void heroStats (void)
{
	
	/* I would like to add things like times killed, amount of enemies killed, total exp and exp to next level */
	playerStatGen();	// Because the stats are generated before the equipment in this program, we need to re-initialize to get the bonus from equipment.
	printf ("*************************************************\n");
	printf ("		STATS FOR %s\n					  \n", player.name);
	printf ("*************************************************\n");
	printf ("\n\n"												 );
	
	printf ("LEVEL  :		%i\n", player.level);
	printf ("EXP    :		%lli\n\n", player.exp);
	printf ("DEF    :		%i\n", player.total_def);
	printf ("MAX HP :		%i\n", player.total_hp);
	printf ("MAX MP :		%i\n", player.total_mp);
	printf ("LUCK   :		%i\n", player.total_luck);
	
	
	printf ("\n BATTLE STATISTITCS \n");
	printf ("----------------------\n");
	
	printf ("ATK			: %i\n", player.base_atk);
	printf ("Attack Rating	: %i\n", player.total_ar);
	printf ("DAMAGE			: %i\n", player.dmg);
	
	printf ("CURRENT HP     : %i\n", player.current_hp);
	printf ("CURRENT MP		: %i\n", player.current_mp);
	
	sleep(5);
	
}
	
/*********************************************************************************
 * FUNCTION TO CHANGE EQUIPPED GEAR, takes an inventory item and the position in the inventory array as args
 *********************************************************************************/
void changeGear(gear changeItem, int inventoryPOS)
{
	/* int inventoryPOS is the location in the inventory array the item in question is coming from, needed
	 * to do swaps. playerInventory.space[inventoryPOS] = old item being removed. Note that to do this we need
	 * a temporary gear item to store it in so nothing is lost in conversion. */
	
	int uInput;
	char uReply, buffer;
	gear temp_holder;
	
	/* OK, this is the function that will be called when the user wants to change currently equipped gear. Some requirements
	 * 1. Ability to REMOVE armor, so I would just pass the universal armor type nood as an argument and replace the armor with nood
	 * 2. Ability to change to a different armor. So the input char * will have to be the actual item name as stored in the program (like nood).
	 * 	  Think about how to automate this. May need to add one more var to the struct containing its exact name. */
	 
	/* on further review i've decided to just have this function take the gears entire struct. but wait. if we do that the items information
	 * is going to change to the struct name taken here no? lets test.
	 * 
	 * 1. We now have the item but its name will change from "frankie_custom" to changeItem. I guess that doesn't matter eh? irrelevant bug */
	 
	 // verify the item is going to be swapped with the piece, otherwise people can equip armor types anywhere they want.
	 
	/*********************************************************************************
	*  For each item type, prompt user, and swap gear and inventory spot if they say yes
	*********************************************************************************/
	/* Note: The swap is quite redundant, I wonder if we can call a reusable function to simplify the copy pasting 
	 * it can be done, create another function in which the args are the item struct and the location string literal like "head" and 
	 * have that function do the lifting. Just something that can be updated later to shrink the file size. 
	 * */
	 
	 
	 /* CHEST ARMOR */
	if (changeItem.itemID >= 70000 && changeItem.itemID < 80000) {
		
		/* VERIFY THEY WANT TO CHANGE */
		printf ("Are you sure you want to change your %s for the %s?\n CHOICE (Y/N): ", playerGear.chest.itemName\
																					  ,	changeItem.itemName);
		scanf  ("%c%c", &uReply, &buffer);
		
		/* If they say yes, do the following: */
		if (uReply == 'Y' || uReply == 'y') {
		
				/* PLACE OLD ITEM INTO A BUFFER */
			temp_holder = playerGear.chest;
			
				/* Equip new item */
			playerGear.chest = changeItem;
			playerStatUpdate();		// remember, the stats wont update until this function is called to run over the new gear.
			printf ("You are now equipped with the %s\n", playerGear.chest.itemName);
			
				/* PLACE OLD ITEM BACK IN SAME INVENTORY SPOT */
			playerInventory.space[inventoryPOS] = temp_holder;
		}
		
	}
	
	/* HELMS */
	if (changeItem.itemID >= 30000 && changeItem.itemID < 40000) {
		/* VERIFY THEY WANT TO CHANGE */
		printf ("Are you sure you want to change your %s for the %s?\n CHOICE (Y/N): ", playerGear.head.itemName\
																					  ,	changeItem.itemName);
		scanf  ("%c%c", &uReply, &buffer);
		
		if (uReply == 'Y' || uReply == 'y') {
			
			/* PLACE OLD ITEM INTO A BUFFER */
			temp_holder = playerGear.head;
			
			/* EQUIP NEW ITEM */
			playerGear.head = changeItem;
			playerStatUpdate();		// remember, the stats wont update until this function is called to run over the new gear.
			printf ("You are now equipped with the %s\n", playerGear.head.itemName);
			
			/* PLACE OLD ITEM BACK IN SAME INVENTORY SPOT */
			playerInventory.space[inventoryPOS] = temp_holder;
		}
	}
	
	/* BOOTS */
	if (changeItem.itemID >= 40000 && changeItem.itemID < 50000) {
		/* VERIFY THEY WANT TO CHANGE */
		printf ("Are you sure you want to change your %s for the %s?\n CHOICE (Y/N): ", playerGear.legs.itemName\
																					  ,	changeItem.itemName);
		scanf  ("%c%c", &uReply, &buffer);
		
		if (uReply == 'Y' || uReply == 'y') {
			
			/* PLACE OLD ITEM INTO A BUFFER */
			temp_holder = playerGear.legs;
			
			
			/* EQUIP NEW ITEM */
			playerGear.legs = changeItem;
			playerStatUpdate();		// remember, the stats wont update until this function is called to run over the new gear.
			printf ("You are now equipped with the %s\n", playerGear.legs.itemName);
			
			/* PLACE OLD ITEM BACK IN SAME INVENTORY SPOT */
			playerInventory.space[inventoryPOS] = temp_holder;
		}
	}
	
	/* SHIELDS */
	if (changeItem.itemID >= 50000 && changeItem.itemID < 60000) {
		/* VERIFY THEY WANT TO CHANGE */
		printf ("Are you sure you want to change your %s for the %s?\n CHOICE (Y/N): ", playerGear.shield.itemName\
																					  ,	changeItem.itemName);
		scanf  ("%c%c", &uReply, &buffer);
		
		if (uReply == 'Y' || uReply == 'y') {
			
			/* OLD ITEM IN BUFFER */
			temp_holder = playerGear.shield;
			
			/* EQUIP NEW ITEM */
			playerGear.shield = changeItem;
			playerStatUpdate();		// remember, the stats wont update until this function is called to run over the new gear.
			printf ("You are now equipped with the %s\n", playerGear.shield.itemName);
			
			/* Swap old into the inventory spot */
			playerInventory.space[inventoryPOS] = temp_holder;
		}
	}
	
	/* WEAPONS 60k-70k = standard, 20k-30k = legendary*/
	if ( (changeItem.itemID >= 60000 && changeItem.itemID < 70000) || (changeItem.itemID >= 20000 && changeItem.itemID < 30000) ) {
		/* VERIFY THEY WANT TO CHANGE */
		printf ("Are you sure you want to change your %s for the %s?\n CHOICE (Y/N): ", playerGear.righthand.itemName\
																					  ,	changeItem.itemName);
		scanf  ("%c%c", &uReply, &buffer);
		
		if (uReply == 'Y' || uReply == 'y') {
			
			/* Place old weapon into buffer */
			temp_holder = playerGear.righthand;
			
			/* Equip new weapon */
			playerGear.righthand = changeItem;
			playerStatUpdate();		// remember, the stats wont update until this function is called to run over the new gear.
			printf ("You are now equipped with the %s\n", playerGear.righthand.itemName);
			
			/* swap old weapon into inventory */
			playerInventory.space[inventoryPOS] = temp_holder;
		}
	}
	
	/* BELTS */
	if (changeItem.itemID >= 80000 && changeItem.itemID < 90000) {
		/* VERIFY THEY WANT TO CHANGE */
		printf ("Are you sure you want to change your %s for the %s?\n CHOICE (Y/N): ", playerGear.belt.itemName\
																					  ,	changeItem.itemName);
		scanf  ("%c%c", &uReply, &buffer);
		
		if (uReply == 'Y' || uReply == 'y') {
			
			temp_holder = playerGear.belt;
			
			playerGear.belt = changeItem;
			playerStatUpdate();		// remember, the stats wont update until this function is called to run over the new gear.
			printf ("You are now equipped with the %s\n", playerGear.belt.itemName);
			
			playerInventory.space[inventoryPOS] = temp_holder;
		}
	}
	
	/* RINGS - VERIFY WHICH FINGER TO PUT IT ON */
	if (changeItem.itemID >= 90000 && changeItem.itemID < 100000) {
		
		/* Determine which ring to change */
		printf ("Ring slot 0 or 1? CHOICE: ");
		scanf  ("%i%c", &uInput, &buffer);
		
		if (uInput == 0) {
			
			temp_holder = playerGear.ring0;
			
			playerGear.ring0 = changeItem;
			playerStatUpdate();		// remember, the stats wont update until this function is called to run over the new gear.
			printf ("You are now equipped with the %s\n", playerGear.ring0.itemName);
			
			playerInventory.space[inventoryPOS] = temp_holder;
		}
		
		if (uInput == 1) {
			
			temp_holder = playerGear.ring1;
			
			playerGear.ring1 = changeItem;
			playerStatUpdate();		// remember, the stats wont update until this function is called to run over the new gear.
			printf ("You are now equipped with the %s\n", playerGear.ring1.itemName);
			
			playerInventory.space[inventoryPOS] = temp_holder;
		}
		
		else {
			printf ("What a terrible answer, doing nothing instead how do you like that?\n");
			return;
		}
	}
	
	/* GLOVES */
	if (changeItem.itemID >= 100000 && changeItem.itemID < 110000) {
		/* VERIFY THEY WANT TO CHANGE */
		printf ("Are you sure you want to change your %s for the %s?\n CHOICE (Y/N): ", playerGear.hands.itemName\
																					  ,	changeItem.itemName);
		scanf  ("%c%c", &uReply, &buffer);
		
		if (uReply == 'Y' || uReply == 'y') {
			
			temp_holder = playerGear.hands;
			
			playerGear.hands = changeItem;
			playerStatUpdate();		// remember, the stats wont update until this function is called to run over the new gear.
			printf ("You are now equipped with the %s\n", playerGear.hands.itemName);
			
			playerInventory.space[inventoryPOS] = temp_holder;
		}
	}
		
}
			
			
		/*	
			
			player.level = 1;
	player.gold  = 100;	// set inital gold to 100
	player.def = 5;
	player.hp    =18;
	player.mp    = 0;
	player.luck  = 0;
	player.atk   = 5;
	
	//secondary stats
	player.ar    = player.atk * 100;
	player.dmg	 = player.atk * 1.2 + playerGear.righthand.damage;
	//player.name = hero;
			
			
			
			
			*/ 
			
			
			
			
			
			
			
	
	

 
	
