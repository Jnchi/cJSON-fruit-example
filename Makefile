.PHONY: clean default

default: fruit

clean:
	@rm fruit

fruit: 
	gcc -o fruit fruit.c cJSON.c -lm -ggdb
