#define TEXT_FIELD_MAX_SIZE 20

typedef struct 
{
	int id;
	const char* name[TEXT_FIELD_MAX_SIZE];
	const char* surname[TEXT_FIELD_MAX_SIZE];
    const char* address[TEXT_FIELD_MAX_SIZE];
	int phone;
} s_contact;

s_contact *create_contact(char* name, char* surname, char* address, int phone);
