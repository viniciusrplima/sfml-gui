
OBJS = objs/main.o objs/SharedWindow.o objs/SFMLGui.o objs/SFMLObject.o\
       objs/SFMLBox.o objs/SFMLCaption.o objs/DOMFactory.o objs/SFMLTextInput.o\
       objs/SFMLSelectInput.o

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

clean:
	rm SFMLGuiTest $(OBJS)

run:
	./SFMLGuiTest
