CC:=clang

SRC_MAC:=src/main.m

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

mac:
	$(CC) $(C_FLAGS) -o $(BUILD_DIR)/game  $(SRC_MAC) $(APP_LINK) $(APP_INCLUDE) $(GAME_LINK)

windows:
	$(CC) $(C_FLAGS) -o $(BUILD_DIR)/game  $(SRC)

clean:
	rm -rf bin/*
