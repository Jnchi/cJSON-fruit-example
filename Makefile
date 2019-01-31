.PHONY: clean default

default: fruit

clean:
	@rm fruit

fruit: clean
	gcc -o fruit fruit.c cJSON.c -lm
