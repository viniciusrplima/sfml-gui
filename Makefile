
OBJS = objs/main.o objs/SharedWindow.o objs/SFMLGui.o objs/SFMLObject.o\
       objs/SFMLBox.o objs/SFMLCaption.o objs/DOMFactory.o objs/SFMLTextInput.o\
       objs/SFMLSelectInput.o objs/SFMLImage.o objs/SFMLTextureHolder.o\
       objs/SFMLCircle.o

LIBS = -lstdc++ -lsfml-graphics -lsfml-window -lsfml-system

SFMLGuiTest: $(OBJS)
	gcc $(OBJS) $(LIBS) -o SFMLGuiTest

objs/main.o: main.cpp
	gcc -c main.cpp -o objs/main.o

objs/SharedWindow.o: src/SharedWindow.h src/SharedWindow.cpp
	gcc -c src/SharedWindow.cpp -o objs/SharedWindow.o

objs/SFMLGui.o: src/SFMLGui.h src/SFMLGui.cpp
	gcc -c src/SFMLGui.cpp -o objs/SFMLGui.o

objs/SFMLObject.o: src/SFMLObject.h src/SFMLObject.cpp
	gcc -c  src/SFMLObject.cpp -o objs/SFMLObject.o

objs/SFMLBox.o: src/SFMLBox.h src/SFMLBox.cpp
	gcc -c src/SFMLBox.cpp -o objs/SFMLBox.o

objs/SFMLCaption.o: src/SFMLCaption.h src/SFMLCaption.cpp
	gcc -c src/SFMLCaption.cpp -o objs/SFMLCaption.o

objs/DOMFactory.o: src/DOMFactory.h src/DOMFactory.cpp
	gcc -c src/DOMFactory.cpp -o objs/DOMFactory.o

objs/SFMLTextInput.o: src/SFMLTextInput.h src/SFMLTextInput.cpp
	gcc -c src/SFMLTextInput.cpp -o objs/SFMLTextInput.o

objs/SFMLSelectInput.o: src/SFMLSelectInput.h src/SFMLSelectInput.cpp
	gcc -c src/SFMLSelectInput.cpp -o objs/SFMLSelectInput.o

objs/SFMLImage.o: src/SFMLImage.h src/SFMLImage.cpp
	gcc -c src/SFMLImage.cpp -o objs/SFMLImage.o

objs/SFMLTextureHolder.o: src/SFMLTextureHolder.h src/SFMLTextureHolder.cpp
	gcc -c src/SFMLTextureHolder.cpp -o objs/SFMLTextureHolder.o

objs/SFMLCircle.o: src/SFMLCircle.h src/SFMLCircle.cpp
	gcc -c src/SFMLCircle.cpp -o objs/SFMLCircle.o

.PHONY: clean run compile build

clean:
	rm SFMLGuiTest $(OBJS)

run:
	./SFMLGuiTest

compile: 
	-mkdir objs
	make

build:
	-mkdir build
	-mkdir build/include
	-mkdir build/lib
	-mkdir build/resources
	cp src/*.h build/include/
	cp src/*hpp build/include/
	cp resources/*.ttf build/resources/
	make compile
	ar rcs build/lib/libsfmlgui.a $(OBJS)

