all:
	gcc -Iinclude/ -Iinclude/obj/include \
	src/app.c src/camera.c src/main.c src/scene.c src/texture.c src/utils.c \
	src/icecream.c src/donut.c src/flag.c src/skybox.c src/map.c src/rain.c \
	include/obj/src/draw.c include/obj/src/load.c include/obj/src/model.c include/obj/src/transform.c include/obj/src/info.c \
	-lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lopengl32 -lm \
	-o donut.exe -Wall -Wextra -Wpedantic

clean:
	del /Q donut.exe 2>NUL
	del /Q donut_game.exe 2>NUL

linux:
	gcc -Iinclude/ -Iinclude/obj/include \
	src/app.c src/camera.c src/main.c src/scene.c src/texture.c src/utils.c \
	src/icecream.c src/donut.c src/flag.c src/skybox.c src/map.c src/rain.c \
	include/obj/src/draw.c include/obj/src/load.c include/obj/src/model.c include/obj/src/transform.c include/obj/src/info.c \
	-lSDL2 -lSDL2_image -lGL -lm \
	-o donut -Wall -Wextra -Wpedantic
