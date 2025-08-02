CC:=clang

SRC:=src/main.c
CORE_SRC:=src/core/c_main.c
APP_SRC:=src/app/*.c
RENDER_GL_SRC:=src/render/OpenGL/r_main.c
RENDER_VK_SRC:=src/render/Vulkan/r_main.c

BUILD_DIR:=bin
C_FLAGS=-g -Wall -Wextra
APP_INCLUDE=-I/opt/homebrew/Cellar/glfw/3.4/include -I/usr/local/include/
APP_INCLUDE+=-I/opt/homebrew/include
APP_LINK:=-L/opt/homebrew/Cellar/glfw/3.4/lib -lglfw -rpath /usr/local/lib/ -L/usr/local/lib/ -lvulkan.1 -framework Cocoa -framework OpenGl -framework IOKit
APP_LINK+=-L/opt/homebrew/lib -lepoxy
RENDER_LINK:=-L./bin/ -lbase -lapp
GAME_LINK:=-L./bin/ -lbase -lapp -lrender

.SILENT:

all:
	echo off
	$(MAKE) clean
	$(MAKE) core
	$(MAKE) app
	$(MAKE) render
	$(MAKE) game
	$(MAKE) run

gl:
	echo off
	$(MAKE) clean
	$(MAKE) core
	$(MAKE) app
	$(MAKE) render
	$(MAKE) sample
	$(MAKE) runs

core:
	$(CC) $(C_FLAGS) -o $(BUILD_DIR)/libbase.dylib -fPIC -shared $(CORE_SRC)

app:
	$(CC) $(C_FLAGS) -o $(BUILD_DIR)/libapp.dylib -fPIC -shared $(APP_SRC) $(APP_INCLUDE) $(APP_LINK)

render:
	$(CC) $(C_FLAGS) -o $(BUILD_DIR)/librender.dylib -fPIC -shared -D DEBUG $(RENDER_GL_SRC) $(APP_INCLUDE) $(APP_LINK) $(RENDER_LINK)

game:
	$(CC) $(C_FLAGS) -o $(BUILD_DIR)/game  $(SRC) $(APP_LINK) $(APP_INCLUDE) $(GAME_LINK)

sample:
	$(CC) $(C_FLAGS) -o $(BUILD_DIR)/sample  src/game/main.c $(APP_LINK) $(APP_INCLUDE) $(GAME_LINK)

runs:
	./$(BUILD_DIR)/sample

run:
	./$(BUILD_DIR)/game

clean:
	rm -rf bin/*
