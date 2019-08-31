default:
	g++ -o jeu_linux main.cpp -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system -lpthread -lX11

	./jeu_linux

linux:
	g++ -o jeu_linux main.cpp -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system -lpthread -lX11


windows:
	cp main.cpp mainwin.cpp
	sed -i '/XInitThreads();/d' ./mainwin.cpp
	sed -i '/#include <X11\/Xlib.h>/d' ./mainwin.cpp
	x86_64-w64-mingw32-g++ -o jeu_windows.exe mainwin.cpp -I/home/jean/Téléchargements/SFML-2.4.2-windows-gcc-6.1.0-mingw-64-bit/SFML-2.4.2/include -L/home/jean/Téléchargements/SFML-2.4.2-windows-gcc-6.1.0-mingw-64-bit/SFML-2.4.2/lib -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system -lpthread
	rm -rf ./mainwin.cpp


all:
	g++ -o jeu_linux main.cpp -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system -lpthread -lX11
	cp main.cpp mainwin.cpp
	sed -i '/XInitThreads();/d' ./mainwin.cpp
	sed -i '/#include <X11\/Xlib.h>/d' ./mainwin.cpp
	x86_64-w64-mingw32-g++ -o jeu_windows.exe mainwin.cpp -I/home/jean/Téléchargements/SFML-2.4.2-windows-gcc-6.1.0-mingw-64-bit/SFML-2.4.2/include -L/home/jean/Téléchargements/SFML-2.4.2-windows-gcc-6.1.0-mingw-64-bit/SFML-2.4.2/lib -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system -lpthread
	rm -rf ./mainwin.cpp

