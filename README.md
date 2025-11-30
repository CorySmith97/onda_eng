# Onda engine (21/21)

C cory engine

This is intended to be a longer term project. But upon finishing a game, the debate will be up to start again from scratch or start again. HOWEVER profiler and core will be long term personal libraries that will stay with me. Platform may also stay longer term.

ZII

Everything should be zero initialized. Everything likewise should be String type. Platform layer should abstract that away. 

Separate backends.
Custom Utils library
Isometric RPGS

Dependencies:
- Steam networking flat header 
- Miniaudio
- Micro ui
- Sokol (backend)
- Glfw( for the moment. I’d like native implementations for each platform, windows.h, x11/wayland, cocoa.h)

Sprite editor using sprite alignment for rect selection 

Game that comes along with this engine.


- [ ] Updated Makefile for cross platform ease of building
- [ ] Build.zig for easy cross-compilation for those who wish.

## Profiler

- [ ] Macro system for section marking
- [ ] Prof dump to file

## Game

- [ ] Large world with a window system.
- [ ] Game design

## Platform 

- [ ] Miniaudio layer
- [ ] Implement Mouse handling
- [ ] The engine types should be macro defined to swap between backends.
- [ ] UI layout

## Core

- [ ] Traversal algorithms
- [ ] Sorting Algorithms
- [ ] Serialization/Deserialiaztion tooling
- [ ] String rewrite
- [ ] Generic ArrayHeader
- [ ] Generic Queue

## Engine 

- [ ] Internal engine console
- [ ] Sprite Handling
- [ ] Command Pallete
- [ ] MouseToWorldPos
- [ ] UI impl
