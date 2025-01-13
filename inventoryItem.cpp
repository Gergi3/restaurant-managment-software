const unsigned MAX_NAME_SIZE = 32;

struct InventoryItem
{
	char name[MAX_NAME_SIZE];
	unsigned quantity = 0;
};