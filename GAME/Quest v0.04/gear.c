/* This file will contain all of the usable gear in the game 
 * if it becomes too long, break it into separate functions for each type
 *  UNTIL I LEARN HOW TO DEAL WITH ALL THESE HEADERS WITHOUT ERRORS AND CONFLICTS
 *   MOVING THIS TO THE BOTTOM OF hero.h UNFORTUNATELY. */
 
 /* FIND OUT IF malloc() is necessary for all of this. Anything you allocate has to be freed so that will get tricky */
 /* OK THE ARMOR TYPES NEED TO BE DECLARED IN THE HEADER FILE PERIOD, BUT THE VALUES CAN BE INITIALIZED HERE. SO MOVE THINGS LIKE "armor soj;" to gear.h and this will work. */
 
 #include "main.h" // gear struct global variable is contained here. Do not remove.
 #include "hero.h"
 #include "gear.h" // all item names defined here
 
 /* This is a function that needs to actually be run if you expect these values to be defined */
void gameGear (void)
{
	
	/* REFERENCE SO YOU KNOW WHAT TO INCLUDE IN GEAR 
	 * typedef struct {
		char *itemName;
		char *itemType; 	// item type will be things like "Boots" or "Helm" and you'll need to make sure they can only occupy their matching slot in the gear struct.
		int damage;
		int defense;
			// resists
		int cold;
		int fire;
		int light;
		int psn; 
		int all; // all resists
		
			// other stats
		int ar;	// attack rating
		int vit; // increase to vitality
		int mp;  // increase to mana
		int luck; // increase to luck
		int exp;  // increase % of exp gain
	} armor, weapon; 
	*/ 
	
	/* Note, find some way to only init these items if the player is either carrying, has them equipped, or one drops. This is going to cause a major memory leak tbh. */
	
/* ITEM ID TABLE: 
 * 100000 - 110000 = gloves
 * 9xxxx = rings
 * 8xxxx = belts
 * 7xxxx = chest armor
 * 6xxxx = weapons
 * 5xxxx = shields
 * 4xxxx = boots
 * 3xxxx = helms
 * 2xxxx = legendary weapons
 * 1xxxx = legendary armor (all types)
 * 		10000 - 10999 = legendary chest
 * 		11000 - 11999 = legendary helms
 * 		12000 - 12999 = legendary boots
 * 		13000 - 13999 = legendary shields
 * 		14000 - 14999 = legendary belts 
 * 		15000 - 15999 = legendary rings
 * 		16000 - 16999 = legendary gloves
 * 		17000 - 19999 = reserved just incase.
 * 10-90 = consumables
 * 0	 = no item (nude)
 * 
 * */
 
 /*********************************************************************************
 * NUDE ITEM FOR WEARING NOTHING
 *********************************************************************************/
		null_item.itemID = 0;	// simple way to remove gear is to replace with nude, has no stats. 
		null_item.itemType = "Nothing";
 
 
 
 
 /*********************************************************************************
 * GLOVES
 *********************************************************************************/
	/* LEATHER GLOVES */
	leather_gloves.itemID = 100000;
	leather_gloves.itemType = "Gloves";
	leather_gloves.itemName = "Leather Gloves";
	leather_gloves.defense  = 2;
 
 
/*********************************************************************************
 *		EQUIPPABLE RINGS 
 *********************************************************************************/
	
		/* STONE OF JORDAN */
		soj.itemID   = 90000;
		soj.itemName = "Stone of Jerr-dan";
		soj.itemType = "Ring";
		soj.all = 10;
		soj.vit = 10;
		soj.luck = 5;
		soj.exp = 5;
		soj.gold_value = 50;
		
		/* JoHameds FaggiTaim Band Ring */
		joh.itemID   = 90001;
		joh.itemName = "Johamed's Faggitaim Band Ring";
		joh.itemType = "Not Bul Katho's";
		joh.luck     = 69;
		joh.l9aura   = 50;	// chance to cast level 9 aura. this is just for fun.
		joh.gold_value = 50;
		
		foa.itemID   = 90002;
		foa.itemName = "Heavenly Angus";
		foa.itemType = "Ring of Pure Beef";
		foa.l10aura  = 1;
		foa.vit 	 = -76;
		foa.gold_value = 50;
		
		
/*********************************************************************************
 *		EQUIPPABLE BELTS
 *********************************************************************************/
	
		/* LE CRACKED SASH */
		c_sash.itemID   = 80000;
		c_sash.itemName = "Le Cracked Sash";
		c_sash.itemType = "Belt";
		c_sash.defense  = 1;
		c_sash.gold_value = 1;
		
		/* LEATHER BELT */
		leather_belt.itemID = 80001;
		leather_belt.itemName = "Leather Belt";
		leather_belt.itemType = "Belt";
		leather_belt.defense  = 3;
		leather_belt.gold_value = 2;
		
		
		
/*********************************************************************************
 *		EQUIPPABLE CHEST ARMOR 
 *********************************************************************************/
	
		/* QUILTED VEST */
		//quilt.itemName = malloc(sizeof(char) * 50);
		quilt.itemID   = 70000;
		quilt.itemName = "Quilted Armor";
		quilt.itemType = "Chest";
		quilt.defense  = 8;
		quilt.gold_value = 5;
		
		leather_chest.itemID = 70001;
		leather_chest.itemName = "Leather Vest";
		leather_chest.itemType = "Chest";
		leather_chest.defense  = 10;
		leather_chest.gold_value = 8;
		
		studded_chest.itemID = 70002;
		studded_chest.itemName = "Studded Leather";
		studded_chest.itemType = "Chest";
		studded_chest.defense  = 15;
		studded_chest.gold_value = 12;

		
		
/*********************************************************************************
 *  	EQUIPPABLE WEAPONS
 ********************************************************************************/
 
	/* SWORDS */
		//short_sword.itemName = malloc(15);
		//SHORT SWORD
		short_sword.itemID   	= 60000;
		short_sword.itemName 	= "Short Sword";
		short_sword.itemType 	= "Sword";
		short_sword.damage   	= 3; 
		short_sword.gold_value  = 1;
		
		//LONG SWORD
		long_sword.itemID    	= 60001;
		long_sword.itemName  	= "Long Sword";
		long_sword.itemType  	= "Sword";
		long_sword.damage   	= 5;
		long_sword.luck			= 1;
		long_sword.mp		 	= 5;
		long_sword.gold_value   = 3;
		
		//BASTARD SWORD
		bastard_sword.itemID	= 60002;
		bastard_sword.itemName	= "Bastard Sword";
		bastard_sword.itemType  = "Sword";
		bastard_sword.damage    = 8;
		bastard_sword.hp		= 5;
		bastard_sword.gold_value = 5;
		
		//psn dagger
		dagger.itemID			= 60003;
		dagger.itemName			= "Newt Eye Dagger";
		dagger.itemType			= "Sword";
		dagger.damage			= 3;
		dagger.psndm			= 5;		// poison damage per second. 
		dagger.gold_value		= 10;
		dagger.story			= "Double, double toil and trouble\n"
								  "Fire burn, and cauldron bubble....\n"
								  "Round about the cauldron go\n"
								  "In the poison'd entrails throw.\n";
	
		
/*********************************************************************************
 *  	EQUIPPABLE SHIELDS
 ********************************************************************************/
		
	/* TOWER SHIELDS */
		//hoz.itemName = malloc(25);
		hoz.itemID   = 50000;
		hoz.itemName = "Herald of Zakapwn";
		hoz.itemType = "Shield";
		hoz.defense  = 10;
		hoz.damage   = 4; 	// only if its used to attack. DO NOT ADD THIS TO CHARS BASE
		hoz.all		 = 5;
		hoz.gold_value = 25;
		
		small_shield.itemID	= 50001;
		small_shield.itemName = "Small Shield";
		small_shield.itemType = "Shield";
		small_shield.defense  = 2;
		small_shield.damage   = 1;
		small_shield.gold_value = 1;
		
		large_shield.itemID = 50002;
		large_shield.itemName = "Large Shield";
		large_shield.itemType = "Shield";
		large_shield.defense = 4;
		large_shield.damage = 2;
		large_shield.fire	= 5;
		large_shield.gold_value = 3;
		
		tower_shield.itemID	= 50003;
		tower_shield.itemName = "Tower Shield";
		tower_shield.itemType = "Shield";
		tower_shield.defense  = 7;
		tower_shield.damage   = 5;
		tower_shield.all	  = 3;
		tower_shield.gold_value = 5;
		
/*********************************************************************************
 *  	EQUIPPABLE BOOTS
 ********************************************************************************/
		
		/* LEATHER BOOTS */
		leather_boots.itemID   = 40000;
		leather_boots.itemName = "Leather Boots";
		leather_boots.itemType = "Boots";
		leather_boots.defense  = 2;
		leather_boots.gold_value = 1;
		
/*********************************************************************************
 * HELMS
 *********************************************************************************/
		leather_hat.itemID   = 30000;
		leather_hat.itemName = "Leather Hat";
		leather_hat.itemType = "Helm";
		leather_hat.defense  = 2;
		leather_hat.gold_value = 1;
		
/*********************************************************************************
 * Legendary Weapons
 *********************************************************************************/
	
		frank_custom.itemID   = 20000;
		frank_custom.itemName = "THE WEAVE";
		frank_custom.itemType = "Sword";
		frank_custom.story	  = "THE END OF ALL ENDS. DESTRUCTION\nEXPLOSION AT THE END OF A LEFT AFTER\nEXECUTING A PERFECT BOB AND A WEAVE\nINTO A LEFT HOOK\n END.\n";
		frank_custom.damage   = 25;
		frank_custom.all	  = 20; 	// all resists
		frank_custom.hp	      = 100;	// +100 hp
		frank_custom.gold_value = 99;

		momo_custom.itemID    = 20001;
		momo_custom.itemName  = "Mohamed's Entropy";
		momo_custom.itemType  = "Balrog Blade";
		momo_custom.story 	  = "The infernal hellfires embrace the core\nof this sword unleashing a fiery crack\nupon every impact\nimpaling and revealing the\nentrails of all in its path.\n";
		momo_custom.damage	  = 25;
		momo_custom.all		  = 25;
		momo_custom.firedm	  = 10;
		momo_custom.gold_value = 100;
		
		don_custom.itemID	  = 20002;
		don_custom.itemName   = "The Immortal SoulSlayer";
		don_custom.itemType   = "Hellfire Scythe";
		don_custom.story	  = "The trouble is\n"
								"You think you have time.\n";
		don_custom.damage	  = 45;
		don_custom.bleed	  = 100;
		don_custom.all		  = 25;
		don_custom.gold_value = 69;
		
/*********************************************************************************
 * CONSUMABLES ** These may not continue using the gear struct
 *********************************************************************************/
		light_potion.itemID   = 10;
		light_potion.itemName = "Light Potion";
		light_potion.itemType = "Consumable";
		light_potion.hp_heal  = 15; 	// heals 20 hitpoints. more thought is needed here. 
		light_potion.pot_stack += 1;		// stack used to allow user to hold more than one potion to a single slot.
		light_potion.gold_value = 1;






// printf ("All gear has been initialized\n"); was just using this to debug, remove if no longer necessary
}
		
		
		
/*********************************************************************************
 * FUNCTION TO PRINT ITEM STATS, MUST BE CALLED WITH AN EXISTING ITEM PASSED AS ARG
 *********************************************************************************/
void printItemStats(gear SELECTED)
{
	char buffer;
	printf ("\n\n");
	// ONLY PRINT OUT NON ZERO VALUES
	
	//All items have a name and item type, no if needed
		
		
		printf ("Item Name			: %s\n", SELECTED.itemName);
	
		printf ("Item Type			: %s\n", SELECTED.itemType);

		
/* Since items have many possible stats, we'll run through each here and only print the nonzero values
 * this will have the net effect of printing the exact stats physically added to each item, the rest of
 * the struct contents are already zero, so they will simply not be displayed 							*/
 	
	if (SELECTED.damage && SELECTED.itemType == "Sword" || SELECTED.itemType == "Balrog Blade" || SELECTED.itemType == "Hellfire Scythe") // BUG ALERT, OTHER WEAPONS BESIDES SWORDS WONT DISPLAY, UPDATE AS NEEDED.
		printf ("Damage				: %i\n", SELECTED.damage);
		
	
	else if (SELECTED.damage && SELECTED.itemType == "Shield")
		printf ("Smite Damage     : %i\n", SELECTED.damage);
		
	if (SELECTED.defense)
		printf ("Defense          : %i\n", SELECTED.defense);
	if (SELECTED.cold)
		printf ("Cold Resist      : +%i\n", SELECTED.cold);
	if (SELECTED.fire)
		printf ("Fire Resist      : +%i\n", SELECTED.fire);
	if (SELECTED.light)
		printf ("Lightning Resist : +%i\n", SELECTED.light);
		
	if (SELECTED.psn)
		printf ("Poison Resist    : +%i\n", SELECTED.psn);
		
	if (SELECTED.all)
		printf ("Resist All			: +%i\n", SELECTED.all);
		
	if (SELECTED.bleed)
		printf ("%i%% Chance to Inflict Bleeding\n", SELECTED.bleed);
		
	if (SELECTED.ar)
		printf ("Attack Rating    : +%i\n", SELECTED.ar);
		
	if (SELECTED.vit)
		printf ("Vitality         : +%i\n", SELECTED.vit);
		
	if (SELECTED.mp)
		printf ("Mana             : +%i\n", SELECTED.mp);
		
	if (SELECTED.luck)
		printf ("Luck             : +%i\n", SELECTED.luck);
	if (SELECTED.exp)
		printf ("Experience       : +%i%%\n", SELECTED.exp);
	if (SELECTED.firedm)
		printf ("Adds %i fire damage\n", SELECTED.firedm);
		
		// this stuff is just bs for screen shots. 
	if (SELECTED.l9aura)
		printf ("Level 9 Aura of The Homogai");
	if (SELECTED.l10aura)
		printf ("Level 20 Fist of Thine Agnus");
	if (SELECTED.gold_value)
		printf ("value				: %i Gold\n", SELECTED.gold_value);
	if (SELECTED.story)
		printf ("\n%s\n", SELECTED.story);
	if (SELECTED.hp_heal)
		printf ("Heals %i hit points\n", SELECTED.hp_heal);
		

		
	//printf ("\npress enter to continue");
	//scanf  (" %c ", &buffer);

	printf ("\n\n");
	sleep(4);
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
}
