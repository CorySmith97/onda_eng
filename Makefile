CC:=clang

SRC:=src/main.m

BUILD_DIR:=bin
C_FLAGS=-g -Wall -Wextra -std=c23
C_FLAGS+=-Wno-unused-variable -Wno-missing-braces -Wno-unused-parameter
APP_INCLUDE=-I./src/thirdparty
APP_LINK:=-framework Cocoa -framework Metal -framework MetalKit -framework Foundation -framework QuartzCore 

.SILENT:

all:
	echo off
	$(MAKE) clean
	$(MAKE) core
	$(MAKE) render
	$(MAKE) game
	$(MAKE) run

gl:
	echo off
	$(MAKE) clean
	$(MAKE) core
	$(MAKE) render
	$(MAKE) sample
	$(MAKE) runs

core:
	$(CC) $(C_FLAGS) -o $(BUILD_DIR)/libbase.dylib -fPIC -shared $(CORE_SRC)

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
