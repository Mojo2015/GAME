#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (void)
{

	char * bacon = "Gigantic Cocks";

	if (bacon == "Gigantic Cocks")
		printf ("I guess you were wrong bro\n");
	else
		printf ("I guess you were right broseidon of the seven seez\n");

/* Now, the reason this happens is obvious, bacon is a pointer so therefore there 
     is no string to reference but a simple memory location. You can reference it 
     by element number though as follows */

	if (bacon[0] == 'G')
		printf ("I'm always right\n");
	else
		printf ("Wrong again but I'm not wrong so this won't ever print\n");

/* So what can we do to compare the entire string? easy. Look for the null. */

int i;

// well this will at least print our string
for (i= 0; bacon[i] != '\0'; i++)
	printf ("%c", bacon[i]);

	printf ("\n"); 

/* I wonder if we can solve this dilemma with strcmp, come back to this plz. */

	return 0;
}