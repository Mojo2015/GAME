/**********************************************************************************************************
 * Game/hero.c
 * Simple function to collect user information (name, )
 **********************************************************************************************************/

#include "main.h"
#include "hero.h"
#include "gear.h"
#include "inventory.h"

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
	
	light_potion.pot_stack += 2;	// set to start with 5 potions
	
	playerInventory.space[1] = light_potion;	// you'll have to remove this and have a parameter to add potions to inventory if >0 if you want to go with this stacking method.
	playerInventory.space[2] = don_custom;
	
	//playerInventory.space[2] = light_potion;
	//playerInventory.space[3] = light_potion;
	//playerInventory.space[4] = light_potion;
	
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
	
	player.current_hp = player.total_hp;	
	player.current_mp = player.total_mp;
	
	
	
	//initPlayerGear(); // run this function from main from now (as well as playerStatUpdate and init)
 
	
}

/*********************************************************************************
 * FUNCTION TO INITIALIZE THE PLAYERS STARTING GEAR - ONE TIME ONLY FUNCTION
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



/* ITEMS FROM HERE TO heroStats are being moved to inventory.c */
	

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
	
	playerBattleParams();	// obviously that function needs to be called to modify this stat
	printf ("DAMAGE TAKEN : %i%%\n", player.incoming_damage);
	
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
			
			
void playerBattleParams (void)
{
	/* NOTE: Calculations of incoming damage will be determined in another function, this one is simply going to REDUCE that incoming damage. So calculate a percentage of
	 * damage 0-200% based on level difference and use that value with this to establish total damage taken */
	int dr_per_xdef = 1;	// every 1 defense equates to a damage reduction of .2%, so every 10 armor = 2% DR.
	float player_dr   = (float)player.total_def / dr_per_xdef; // store amount of times player gets the reduction
	float damage_reduction = .002; // percent of damage that will be removed for each dr achieved by armor.
	
	
	/* Ok this is the function that will reduce incoming damage based on our defense, reduce fire damage based on fire defense, etc. */
	
	/* For now, i'm simply setting it up so that every 10 defense is equal to a reduction of 2% of enemy damage up to a limit of a 75% reduction */
	player.incoming_damage = 100 - (player_dr * damage_reduction);
	
								
	
}
			
			
			
			
			
			
	
	

 
	
