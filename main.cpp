#define SDL_MAIN_HANDLED
#include "SDL.h"
#include <stdlib.h>
#include <fstream>
#include <iostream>

using namespace std;

const Uint32 fps = 60; //Set speed in fps (frames per second)
const Uint32 minframetime = 1000 / fps;

int main() {
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window* window = SDL_CreateWindow("Game Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1920, 1080, SDL_WINDOW_SHOWN); //Display window

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0); //Create renderer

    SDL_SetWindowFullscreen(window, 0);

    bool running = true;
    Uint32 frametime;
    SDL_Event event;

    int numLines = 0;
    int num = 0;
    int numX = 0;
    char character;

    ifstream fin;
    fin.open("map.txt", ios::in); //Open map file

    SDL_Rect walls[999];
    string color[999];

    while (!fin.eof()) {
        fin.get(character); //Get next character of map

        cout << character; //Display map in console

        if (character == 'X') { //Check if character is 'X'
            walls[num].x = numX * 100;
            walls[num].y = numLines * 100;
            walls[num].w = 100;
            walls[num].h = 100;
            color[num] = "black";
        } else if (character == 'R') { //Check if character is 'R'
            walls[num].x = numX * 100;
            walls[num].y = numLines * 100;
            walls[num].w = 100;
            walls[num].h = 100;
            color[num] = "red";
        } else if (character == 'G') { //Check if character is 'G'
            walls[num].x = numX * 100;
            walls[num].y = numLines * 100;
            walls[num].w = 100;
            walls[num].h = 100;
            color[num] = "green";
        } else if (character == 'B') { //Check if character is 'B'
            walls[num].x = numX * 100;
            walls[num].y = numLines * 100;
            walls[num].w = 100;
            walls[num].h = 100;
            color[num] = "blue";
        } else { //Check if character is anything else
            walls[num].x = -100;
            walls[num].y = -100;
            walls[num].w = 0;
            walls[num].h = 0;
        }
        if (character == '\n'){ //Check if character is a new line
            numX = -1;
            numLines++;
        }

        num++;
        numX++;
    }

    while (running) //This is called once per frame
    {
    	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); //Set background color

        SDL_SetWindowResizable(window, SDL_TRUE); //Make window resizable

        SDL_RenderClear(renderer); //Clear screen

        static bool fullScreen = true; //Is fullscreen
        static int windowWidth = 1000; 	//Get window width
        static int windowHeight = 700; //Get window height
        static int screenWidth = 1920;
        static int screenHeight = 1080;
        static int x = 0;
        static int y = 0;
        static int speed = 300;

        const Uint8* state = SDL_GetKeyboardState(NULL); //Store key state in variable

        if (state[SDL_SCANCODE_LEFT]) {
            x -= 1 * speed / fps;
        }
        if (state[SDL_SCANCODE_RIGHT]) {
            x += 1 * speed / fps;
        }
        if (state[SDL_SCANCODE_UP]) {
            y -= 1 * speed / fps;
        }
        if (state[SDL_SCANCODE_DOWN]) {
            y += 1 * speed / fps;
        }

        SDL_Rect square; //Create parameters for movable square

        square.x = x;
        square.y = y;
        square.w = 50;
        square.h = 50;

        for (int i = 0; i < num - 1; i++) {
            if (color[i] == "black") { //Check color of squares
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            } else if (color[i] == "red") {
                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            } else if (color[i] == "green") {
                SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
            } else if (color[i] == "blue") {
                SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
            }

            SDL_RenderFillRect(renderer, &walls[i]); //Render squares
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); //Set draw color of movable square

        SDL_RenderFillRect(renderer, &square); //Render movable square
 
        SDL_RenderPresent(renderer); //Draw everything
        
        frametime = SDL_GetTicks(); //Get frame time

        if (SDL_PollEvent(&event))
        {
            switch (event.type)
            {

            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_F11) { //Detect if F11 is pressed
                    if (fullScreen) {
                        SDL_SetWindowFullscreen(window, 0);
                        SDL_RestoreWindow(window);
                        SDL_SetWindowSize(window, windowWidth, windowHeight);
                        SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED); //Toggle fullscreen off

                        fullScreen = false;
                    }
                    else {
                        SDL_SetWindowSize(window, 1920, 1080);
                        SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN); //Toggle fullscreen on

                        fullScreen = true;

                        SDL_GetWindowSize(window, &screenWidth, &screenHeight);
                    }
                }
            }

            if (event.type == SDL_WINDOWEVENT) {
                switch (event.window.event) {
                case SDL_WINDOWEVENT_RESIZED:
                    SDL_GetWindowSize(window, &windowWidth, &windowHeight);
                }
            }

            if (SDL_QUIT == event.type) //Detect if user presses the x button
            {
                SDL_DestroyRenderer(renderer);
                SDL_DestroyWindow(window);

                break; //Quit game
            }
        }

        if (SDL_GetTicks() - frametime < minframetime) //Check if it is running at the right speed
            SDL_Delay(minframetime - (SDL_GetTicks() - frametime));

    }

	return 0;
}