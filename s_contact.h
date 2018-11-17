#define TEXT_FIELD_MAX_SIZE 20

typedef struct 
{
	unsigned int id;
	const char* name[TEXT_FIELD_MAX_SIZE];
	const char* surname[TEXT_FIELD_MAX_SIZE];
    const char* address[TEXT_FIELD_MAX_SIZE];
	unsigned int phone;
} s_contact;

s_contact *create_contact(unsigned int id, char* name, char* surname, char* address, unsigned int phone);
