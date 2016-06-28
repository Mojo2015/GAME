#include <stdio.h>

int main (void)
{

	int itemID = 47001;
	int i;
	int temp;

	while (itemID != 0) {
		itemID /= 10;	// this shaves off a digit iirc?
		printf ("ItemID is now %i\n", itemID); 
		if (itemID != 0)
			temp = itemID;
	}

	printf ("The first digit is %i\n", temp);
	return 0;


}

/* This is how we'll extract the first value of an itemID to verify that it is the correct type of armor for the position in which it is being equipped */ 
