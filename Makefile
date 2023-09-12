CC = g++
CFLAGS = -std=c++17 -Wall -Wextra -pedantic -Wno-unused-parameter -Werror=init-self
#LIBS = -lm -lSDL2 -lSDL2main -lSDL2_image -lSDL2_mixer -lSDL2_ttf -logg -lvorbis
#LIBS = -lSDL2 -lSDL2_mixer -lSDL2_image
LIBS = -I/usr/include/SDL2 -D_REENTRANT -lSDL2 -lSDL2_mixer -lSDL2_image -lSDL2_ttf

SRC_DIR=src
OBJ_DIR=obj
BIN_DIR=bin

SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))
DEP_FILES = $(OBJ_FILES:.o=.d)

DEBUG ?= 1
ifeq ($(DEBUG), 1)
    CFLAGS += -DDEBUG -g3
else
    CFLAGS += -DNDEBUG -O3 -mtune=native
endif

.PHONY: all
all: setup pinguim

.PHONY: setup
setup:
	mkdir -p $(BIN_DIR) $(OBJ_DIR)

pinguim: $(OBJ_FILES)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $(BIN_DIR)/$@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) -c -MMD -MP $< -o $@

-include $(DEP_FILES)

.PHONY: clean
clean:
	rm -rf $(OBJ_DIR)/* $(BIN_DIR)/*


