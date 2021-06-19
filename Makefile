CC = g++
INC_DIR = ./include
CFLAGS = -g -std=c++17 -I$(INC_DIR)/

OBJ_DIR = ./bin
_OBJS = main.o glad.o Shader.o Model.o tiny_obj_loader.o stb_image.o Texture.o Material.o 
OBJS = $(patsubst %,$(OBJ_DIR)/%, $(_OBJS))

SRC_DIR = ./src

SHARED_LIBRARIES = -L/usr/lib/x86_64-linux-gnu -L/usr/lib64
LIBS = -lGL -lGLEW -lglfw -lassimp -ldl

main : $(OBJS)
	$(CC) $(OBJS) -o main $(SHARED_LIBRARIES) $(LIBS)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) -c  $< -o $@

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c  $< -o $@

.PHONY: clean

clean:
	rm $(OBJ_DIR)/*.o 




