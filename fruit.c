#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "cJSON.h"

#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0

char* load_file(char const* path)
{
	char* buffer = 0;
	long length;
	FILE * f = fopen (path, "rb"); //was "rb"
	int i;
	if (f)
	{
		fseek (f, 0, SEEK_END);
		length = ftell (f);
		fseek (f, 0, SEEK_SET);
		buffer = (char*)malloc ((length+1)*sizeof(char));
		if (buffer)
		{
			fread (buffer, sizeof(char), length, f);
		}
		fclose (f);
	}
	buffer[length] = '\0';
	return buffer;
}

int main()
{
	cJSON *fruit = NULL, *fruits = NULL, *fruit_j = NULL;
	char *fruits_list = load_file("fruits.json");

	printf("Fruit List: %s\n", fruits_list);

	fruit_j = cJSON_Parse(fruits_list);

	if(fruit_j == NULL)
	{
		printf("fruit_j is null\n");
		return EXIT_FAILURE;
	}

	fruits = cJSON_GetObjectItem(fruit_j, "fruit");
	if(fruits == NULL)
	{
		printf("fruits is null\n");
		return EXIT_FAILURE;
	}

	int fruitCnt = 0;
	cJSON_ArrayForEach(fruit, fruits)
	{
		printf("fruit: %s\n", cJSON_Print(fruit));
		fruitCnt++;
/*		if(cJSON_GetObjectItem(fruits, "banana"))
			printf("Banana\n");

		if(!cJSON_GetObjectItem(fruits, "apple"))
			printf("No Apples\n");*/
	}
	char *fruit_list[fruitCnt];
	printf("sizeof fruit_list: %ld\n", sizeof(fruit_list));
	printf("fruitCnt: %d\n", fruitCnt);

	printf("fruits: %s\n", cJSON_Print(fruits));

	fruitCnt = 0;
	cJSON_ArrayForEach(fruit, fruits)
	{
		printf("Start\n");
		printf("sizeof cJSON_Print(fruit): %ld\n", sizeof(cJSON_PrintUnformatted(fruit)));
		
		fruit_list[fruitCnt] = (char *) malloc(10*sizeof(cJSON_PrintUnformatted(fruit)));

		printf("sizeof fruit_list[fruitCnt]: %ld\n", sizeof(fruit_list[fruitCnt]));

	        printf("fruit: %s\n", cJSON_PrintUnformatted(fruit));

		char *string = cJSON_PrintUnformatted(fruit);
	        printf("fruit string: %s\n", string);
		strcpy(fruit_list[fruitCnt], string); 
		printf("fruit_list[fruitCnt]: %s\n", fruit_list[fruitCnt]);

		printf("fruitCnt %d\n", fruitCnt);
		fruitCnt++;
		printf("End\n");
	}

        printf("Fruits: %s\n", cJSON_Print(fruits));
	return EXIT_SUCCESS;
}
