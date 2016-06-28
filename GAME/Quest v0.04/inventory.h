
/* Functions to view players current inventory / weared gear */
void inventory (void);
void viewInventory (void);

/* Function to use consumable items. Returns an integer to specify if item was used or not (so we know whether or not to remove it) */
int consume (gear CONSUMABLE);
