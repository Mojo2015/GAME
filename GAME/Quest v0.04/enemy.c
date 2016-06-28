/**********************************************************************************************************
 * Game/enemy.c
 * This is the file that will be used to generate enemies and their attributes
 **********************************************************************************************************/

#include "main.h"
#include "enemy.h"
#include "battle.h"



enemy enemies (void)
{
	enemy beta_phaggot, Undeadhamed, FaggiTaimFrankie, GeileyPoop, DonDiggie;
	
	beta_phaggot.level = 1;
	beta_phaggot.name = malloc(sizeof(char) * 50);
	beta_phaggot.name = "Beta Phaggot";
	beta_phaggot.hp = 10;
	beta_phaggot.def = 2; 	
	beta_phaggot.atk = 3;
	beta_phaggot.gold = 1;
	//beta_phaggot.enemy_inventory[0] = light_potion;
	//beta_phaggot.enemy_inventory[1] = short_sword;

	DonDiggie.level = 1;
	DonDiggie.name = malloc(sizeof(char) * 50 );
	DonDiggie.name = "Don Diggie";
	DonDiggie.hp = 6;
	DonDiggie.def = 2;
	DonDiggie.atk = 5;
	DonDiggie.gold = 2;
	//DonDiggie.enemy_inventory[0] = bastard_sword;
	//DonDiggie.enemy_inventory[1] = large_shield;
	

	/* REPLACE WITH RNG */
	int dothis;	
	char buffer;
	

	printf ("What enemy do you want to face?\n");
	printf ("1: Beta Phaggot\n");
	printf ("2: Don Diggie\n");
	printf ("Choice: ");
	
	scanf ("%i%c", &dothis, &buffer);
	

	// Will need to store the enemy name into another varibale
	enemy CURRENT;

	switch (dothis)
	{
		case 0:
			CURRENT = beta_phaggot;
			break;
		case 1: 
			CURRENT = DonDiggie;
			break;
		default:
			printf ("Bad Choice FGT");
			//exit(1);
	}			 
			


/**********************************************************************************************************************************************/
// CONTINUED:
	
	printf ("You chose to battle a %s\n", CURRENT.name);		
	battle(CURRENT);
}

/************************************************************************************************************
 FUNCTION TO DETERMINE AMOUNT OF DAMAGE TAKEN BY THE ENEMY WHEN HIT BY PLAYER
*************************************************************************************************************/
void enemyBattleParams (enemy selected_enemy)
{
	
	/* NOTE, SINCE IM USING ENEMY AND NOT SPECIFIC ENEMY NAMES LIKE DON_DIGGIE, IM NOT SURE THIS WILL WORK. IT WILL NEED TO BE TESTED */
	
	/* NOTE: Calculations of incoming damage will be determined in another function, this one is simply going to REDUCE that incoming damage. So calculate a percentage of
	 * damage 0-200% based on level difference and use that value with this to establish total damage taken */
	int dr_per_xdef = 1;	// every 1 defense equates to a damage reduction of .2%, so every 10 armor = 2% DR.
	float enemy_dr   = (float)selected_enemy.def / dr_per_xdef; // store amount of times player gets the reduction
	float damage_reduction = .002; // percent of damage that will be removed for each dr achieved by armor.
	
	
	/* Ok this is the function that will reduce incoming damage based on our defense, reduce fire damage based on fire defense, etc. */
	
	/* For now, i'm simply setting it up so that every 10 defense is equal to a reduction of 2% of enemy damage up to a limit of a 75% reduction */
	selected_enemy.enemy_incoming_damage = 100 - (enemy_dr * damage_reduction);
	
								
	
}



