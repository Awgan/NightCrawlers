DEPS = position.h point.h collision.h
DEPS_PIASKOWNICA = piaskownica.cpp win_general.o obstacle_win.o obstacle_box_win.h
DEPS_COMM = comm_const.h all.h
%.o: %.c $(DEPS)
	g++ -c -o $@ $< -I.

graph_prop.o: graph_prop.cpp graph_prop.h
	g++ -c -o graph_prop.o graph_prop.cpp -I.

point.o: point.cpp point.h position.h property.cpp property.h
	g++ -c -o point.o point.cpp -I.

point_container.o: point_container.h point_container.cpp
	g++ -c -o point_container.o point_container.cpp -I.

position.o: position.cpp position.h $(DEPS_COMM)
	g++ -c -o position.o position.cpp -I.

property.o: property.cpp property.h
	g++ -c -o property.o property.cpp -I.

collision.o: collision.cpp collision.h point.h
	g++ -c -o collision.o collision.cpp -I. -I/usr/local/lib/ -I/usr/local/inlude/SDL2/ -I. -I/usr/include/ -I/usr/local/include/ -I/usr/local/lib/

info_win.o: info_win.cpp info_win.h point.cpp point.h point_container.h point_container.cpp
	g++ -c -o info_win.o info_win.cpp -I.

win_general.o: win_general.cpp win_general.h 
	g++ -c -o win_general.o win_general.cpp -I.

obstacle_win.o: obstacle_win.cpp obstacle_win.h win_general.o 
	g++ -c -o obstacle_win.o obstacle_win.cpp -I.

all.o: all.cpp all.h comm_const.h point.cpp point.h
	g++ -c -o all.o all.cpp -I. -I/usr/local/inlude/SDL2/

cursor_picture.o: cursor_picture.cpp cursor_picture.h comm_const.h win_general.o
	g++ -c -o cursor_picture.o cursor_picture.cpp -I. -I/usr/local/inlude/SDL2/

all_SDL.o: all_SDL.h all_SDL.cpp comm_const.h property.cpp property.h
	g++ -c -o all_SDL.o all_SDL.cpp -I. -I/usr/local/inlude/SDL2/

piaskownica.o: $(DEPS_PIASKOWNICA)
	g++ -O0 -o piaskownica piaskownica.cpp win_general.o obstacle_win.o `sdl2-config --cflags --libs` -lSDL2 -I.

main: all_SDL.o cursor_picture.o obstacle_box_win.h all.o info_win.o point_container.o collision.o position.o point.o collision.o graph_prop.o main.cpp property.o comm_const.h read_file.h
	g++ -Wall -o main main.cpp all_SDL.o cursor_picture.o all.o info_win.o graph_prop.o point.o point_container.o position.o property.o win_general.o obstacle_win.o `sdl2-config --cflags --libs` -lSDL2_ttf -lSDL2  -L/usr/local/lib
