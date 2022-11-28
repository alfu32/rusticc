SOURCE=src
TARGET=build
all:
	rm -rf $(TARGET)
	mkdir $(TARGET)
	cd $(SOURCE)
	gcc $(SOURCE)/main.c -o $(TARGET)/main
	cd ..
clean:
	rm -rf $(TARGET)
test:
	make
	./$(TARGET)/main
source:
	gcc $(SOURCE)/main.c -E -o ./main.expanded.c