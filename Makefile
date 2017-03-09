glfw-3.2.1.bin.WIN32.zip:
	wget https://github.com/glfw/glfw/releases/download/3.2.1/glfw-3.2.1.bin.WIN32.zip

glfw-3.2.1.bin.WIN32: glfw-3.2.1.bin.WIN32.zip
	unzip glfw-3.2.1.bin.WIN32.zip && touch glfw-3.2.1.bin.WIN32.zip

Pathfinding.exe: glfw-3.2.1.bin.WIN32
	i686-w64-mingw32-g++-win32 \
-static-libgcc \
-static-libstdc++ \
-mwindows \
-Wpedantic \
-Wall \
-O3 \
-std=c++11 \
-oPathfinding.exe \
-Iinclude \
-Iglfw-3.2.1.bin.WIN32/include/ \
-Lglfw-3.2.1.bin.WIN32/lib-mingw-w64/ \
main.cpp src/*.cpp \
-lopengl32 \
-lglu32 \
-lglfw3
