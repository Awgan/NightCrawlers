DEPS = position.h point.h collision.h
DEPS_PIASKOWNICA = all_SDL.o cursor_picture.o obstacle_box_win.h all.o info_win.o point_container.o collision.o position.o point.o collision.o graph_prop.o main.cpp property.o comm_const.h read_file.h
DEPS_COMM = comm_const.h all.h
#%.o: %.c $(DEPS)
#	g++ -c -o $@ $< -I.
#
#'$@' --> name on the left side of ':'

graph_prop.o: graph_prop.cpp graph_prop.h comm_const.h
	g++ -c -o $@ graph_prop.cpp -I.

point.o: point.cpp point.h position.o property.o
	g++ -c -o $@ point.cpp -I.

point_container.o: point_container.cpp point_container.h point.o
	g++ -c -o $@ point_container.cpp -I.

position.o: position.cpp position.h comm_const.h
	g++ -c -o $@ position.cpp -I.

property.o: property.cpp property.h comm_const.h
	g++ -c -o $@ property.cpp -I.

info_win.o: info_win.cpp info_win.h point.o point_container.o
	g++ -c -o $@ info_win.cpp -I.

win_general.o: win_general.cpp win_general.h comm_const.h
	g++ -c -o $@ win_general.cpp -I.

obstacle_win.o: obstacle_win.cpp obstacle_win.h win_general.o
	g++ -c -o $@ obstacle_win.cpp -I.

all.o: all.cpp all.h comm_const.h point.o texture_cont.o obstacle_box_win.h point_container.o bullet.o gunpoint.o
	g++ -c -o $@ all.cpp -I.

cursor_picture.o: cursor_picture.cpp cursor_picture.h comm_const.h win_general.o
	g++ -c -o $@ cursor_picture.cpp -I.

all_SDL.o: all_SDL.cpp all_SDL.h comm_const.h texture_cont.o all.o
	g++ -c -o $@ all_SDL.cpp -I.

texture_cont.o: texture_cont.cpp texture_cont.h comm_const.h point.o
	g++ -c -o $@ texture_cont.cpp -I.

bullet.o: bullet.h bullet.cpp point.o comm_const.h
	g++ -c -o $@ bullet.cpp -I.

gunpoint.o: gunpoint.h gunpoint.cpp win_general.o comm_const.h
	g++ -c -o $@ gunpoint.cpp -I.

piaskownica: piaskownica.cpp
	g++ -O0 -o piaskownica piaskownica.cpp `sdl2-config --cflags --libs` -lSDL2_ttf -lSDL2  -L/usr/local/lib

main: gunpoint.o bullet.o texture_cont.o all_SDL.o cursor_picture.o obstacle_box_win.h all.o info_win.o point_container.o collision.o position.o point.o collision.o graph_prop.o main.cpp property.o comm_const.h read_file.h
	g++ -Wall -o main main.cpp bullet.o texture_cont.o all_SDL.o cursor_picture.o all.o info_win.o graph_prop.o point.o point_container.o position.o property.o win_general.o obstacle_win.o gunpoint.o `sdl2-config --cflags --libs` -lSDL2_ttf -lSDL2  -L/usr/local/lib
