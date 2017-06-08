typedef struct 
{
	int id;
	const char* name[20];
	const char* surname[20];
	int phoneNumber[10];
} s_contact;

s_contact *create_contact(char* name, char* surname, int phoneNumber);
