#include "main.h"

/* Prototypes are moved to the bottom because some identifiers are declared below */

#define AR_MULTIPLIER 1.2 // Used for calculating damage (see hero.c player.dmg calculation)
#define MAX_INVENTORY 200 // absolute limit of the inventory size, cannot go beyond this no matter what gear or level.
#define MAX_POT_STACK 20

//extern int INVEN_CAP;	// http://stackoverflow.com/questions/1164167/variable-declaration-in-a-header-file Not using this anymore but thought i'd leave it here for knowledge.


/************************************************************************
 * HERO STATS 
 ************************************************************************/
	typedef struct {
		
		// PRIMARY STATS
		int 		level; // make sure there is an exp system added
		long long int 	exp;
		
		// SECONDARY STATS
		int				inven_cap;	// inventory max capacity

	    int 			dmg;		// PLAYERS CALCULATED DAMAGE OUTPUT
		/************************************************************************
		* BASE STATS - MODIFIED THROUGH LEVELS OR NAME CHANGE @ CHUCH
		************************************************************************/
		int 			base_def;
		int 			base_hp;
		int 			base_mp;
		int 			base_luck;
		int 			base_atk ;	// baseline attack, have equipped weapon ADD to this somehow but make sure that value is subtracted if weapon is removed 	
		int				base_vit ;
		int				base_ar;
	    char *			name;
	    
	    /************************************************************************
		* GEAR STAT TOTALS - TO BE ADDED TO BASE FOR ADJUSTED PLAYER VALUE 
		************************************************************************/
		int				bonus_def;
		int				bonus_hp;
		int				bonus_mp;
		int				bonus_luck;
		int				bonus_atk;
		int				resists	 ; //etc to add resist stats.
		int				bonus_vit; 
		int				bonus_ar;
		
		/************************************************************************
		* TOTAL STATS; BASE + GEAR - TO USE ON LIVE CHARACTER
		************************************************************************/
		int 			total_def;
		int 			total_hp;
		int 			total_mp;
		int 			total_luck;
		int 			total_atk ;
		int				total_vit;
		int				total_ar;
		
		/************************************************************************
		* CURRENT STATS: NECESSARY FOR TAKING DAMAGE OR USING MAGIC
		************************************************************************/
		int				current_hp;
		int				current_mp;
		// will add more if enemies have status effects that temporarily reduce stats.
		
		/* Damage reduction stats, all passive */
		int				incoming_damage; // see playerBattleParams in hero.c
	    
		// inventory stuff
		int				gold;
		// Figure out how to make a LIMITED SIZE inventory, i guess based on weight or total number of items.
		

		
	} NPC; // struct name

	// define a player of type NPC (above struct). This way we can reference it from multiple functions below.
	NPC player; // this is you
 
 
/***************************************************************************
 * It's an RPG right? Armor needs stats!!!  
 ***************************************************************************/
 
	typedef struct {
		int    itemID;		// Necessary for passing argument to change equipment
		char * itemName;
		char * itemType; 	// item type will be things like "Boots" or "Helm" and you'll need to make sure they can only occupy their matching slot in the gear struct.
		int damage;
		int defense;
			// resists
		int cold;
		int fire;
		int light;
		int psn; 
		int all; // all resists
		
		// elemental damage
		int firedm;
		int psndm;
		int lightdm;
		int colddm;
		int bleed;
		
			// other stats
		int ar;	// attack rating
		int vit; // increase to vitality
		int mp;  // increase to mana
		int hp;
		int luck; // increase to luck
		int exp;  // increase % of exp gain
		
		// bs for showcasing
		int l9aura;	// some kind of faggitaim aura. just for fun.
		int l10aura;
		
		// for legendaries
		char * story;
		
		// for consumables
		int pot_stack;			// this will be used to allow the user to hold multiple potions in a single item slot.
		int hp_heal;
		int mp_heal;
		
		// VALUE!
		int gold_value;
	} gear;	/* Note, gear is used in other structs below as well as function prototypes, messing up this order will break the program */
	
/***************************************************************************
* Players need an inventory. That should be a structure so.. lets try
***************************************************************************/
 
	/* ok so lets think about inventories. It can be by weight, by total items, or by total "blocks" where items take up x blocks or can stack like d2. 
	 * We can break the struct down into an order of like potions, weapons, misc. Or use arrays or structs? */
	typedef struct {
		int    capacity; // weight limit before the inventory stops accepting new items.
		gear   space[MAX_INVENTORY];	// array of gear structs, up to 200. now you can simply just have each space occupied by a copy of your item.
			
		
	
	
	
	
	} play_inventory;
	
	play_inventory playerInventory;	// this is our inventory 
	
	

/******************************************************************************
 * Gear being worn by the player 
 ******************************************************************************/

	typedef struct {
		gear lefthand;
		gear righthand;
		gear shield; // The player can either use a weapon (dual wield) or a shield in right hand) BUT NOT BOTH
		gear chest;
		gear legs;
		gear hands;
		gear belt;
		gear head;
		gear ring0;
		gear ring1;
		gear neck;
	} wearing;
	
	wearing playerGear;
	
	
	
	
	
	
	
/*********************************************************************************
 * FUNCTION PROTOTYPES, MOVE THESE TO A "main.h" or similar if possible. Or perhaps keep here sice they are organized hero files
 *********************************************************************************/
 
/* Function that will ask the user for his name and return this information to main */
void getName (void);

/* Function to init the players stats */
void playerStatGen (void);

/* Function to init the players gear */
void initPlayerGear (void);



/* Function to print out players current stats */
void heroStats (void);

/* Function to change equipped gear, argument is the itemID (which is the same as the items structure name) */
void changeGear(gear changeItem, int inventoryPOS);

/* Function to update players stats	*/
void playerStatUpdate (void);

/* Function to interpret players current stats for use in battle (reducing incoming damage, etc */
void playerBattleParams (void);



