#ifndef SDLGRAPHICSPROGRAM
#define SDLGRAPHICSPROGRAM

// ==================== Libraries ==================
// Depending on the operating system we use
// The paths to SDL are actually different.
// The #define statement should be passed in
// when compiling using the -D argument.
// This gives an example of how a programmer
// may support multiple platforms with different
// dependencies.

#include <SDL3/SDL.h>

// The glad library helps setup OpenGL extensions.
#include <glad/glad.h>

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
// Purpose:
// This class sets up a full graphics program using SDL
//
//
//
class SDLGraphicsProgram
{
public:
    // Constructor
    SDLGraphicsProgram(int w, int h);
    // Destructor
    ~SDLGraphicsProgram();
    // Setup OpenGL
    bool initGL();
    // Clears the screen
    void clear();
    // Flips to new buffer
    void flip();
    // Delay rendering
    void delay(int milliseconds);

    bool poll();
    // loop that runs forever
    void loop();

    bool isLeftPaddleUpKeyDown();

    bool isLeftPaddleDownKeyDown();

    bool isRightPaddleUpKeyDown();

    bool isRightPaddleDownKeyDown();
    // Get Pointer to Window
    SDL_Window *getSDLWindow();
    // Draw a simple rectangle
    void DrawRectangle(int x, int y, int w, int h);

    void DrawCircle(int x, int y, int radius);

private:
    // Screen dimension constants
    int screenHeight;
    int screenWidth;
    // The window we'll be rendering to
    SDL_Window *gWindow;
    // Our renderer
    SDL_Renderer *gRenderer;
    SDL_Rect leftPaddle;
    SDL_Rect rightPaddle;
    SDL_Rect ball;
    int ballVelX;
    int ballVelY;
};

// Initialization function
// Returns a true or false value based on successful completion of setup.
// Takes in dimensions of window.
SDLGraphicsProgram::SDLGraphicsProgram(int w, int h) : screenWidth(w), screenHeight(h)
{
    // Initialization flag
    bool success = true;
    // String to hold any errors that occur.
    std::stringstream errorStream;
    // The window we'll be rendering to
    gWindow = NULL;
    // Render flag

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        errorStream << "SDL could not initialize! SDL Error: " << SDL_GetError() << "\n";
        success = false;
    }
    else
    {
        // Create window
        gWindow = SDL_CreateWindow("Lab", screenWidth, screenHeight, SDL_WINDOW_OPENGL);

        // Check if Window did not create.
        if (gWindow == NULL)
        {
            errorStream << "Window could not be created! SDL Error: " << SDL_GetError() << "\n";
            success = false;
        }

        // Create a Renderer to draw on
        gRenderer = SDL_CreateRenderer(gWindow, NULL, SDL_RENDERER_ACCELERATED);
        // Check if Renderer did not create.
        if (gRenderer == NULL)
        {
            errorStream << "Renderer could not be created! SDL Error: " << SDL_GetError() << "\n";
            success = false;
        }
    }

    // If initialization did not work, then print out a list of errors in the constructor.
    if (!success)
    {
        errorStream << "SDLGraphicsProgram::SDLGraphicsProgram - Failed to initialize!\n";
        std::string errors = errorStream.str();
        SDL_Log("%s\n", errors.c_str());
    }
    else
    {
        SDL_Log("SDLGraphicsProgram::SDLGraphicsProgram - No SDL, GLAD, or OpenGL, errors detected during initialization\n\n");
    }
}

// Proper shutdown of SDL and destroy initialized objects
SDLGraphicsProgram::~SDLGraphicsProgram()
{
    // Destroy window
    SDL_DestroyWindow(gWindow);
    // Point gWindow to NULL to ensure it points to nothing.
    gWindow = NULL;
    // Quit SDL subsystems
    SDL_Quit();
}

// Initialize OpenGL
// Setup any of our shaders here.
bool SDLGraphicsProgram::initGL()
{
    // Success flag
    bool success = true;

    return success;
}

// clear
// Clears the screen
void SDLGraphicsProgram::clear()
{
    // Nothing yet!
    SDL_SetRenderDrawColor(gRenderer, 0x44, 0x44, 0x4, 0xFF);
    SDL_RenderClear(gRenderer);
}
// Flip
// The flip function gets called once per loop
// It swaps out the previvous frame in a double-buffering system
void SDLGraphicsProgram::flip()
{
    // Nothing yet!
    SDL_RenderPresent(gRenderer);
}

void SDLGraphicsProgram::delay(int milliseconds)
{
    SDL_Delay(milliseconds);
}

bool SDLGraphicsProgram::poll()
{
    SDL_Event e;
    while (SDL_PollEvent(&e))
    {
        if (e.type == SDL_EVENT_QUIT)
        {
            SDL_Log("Quit the game");
            return true;
        }
    }
    return false;
}
// Loops forever!
void SDLGraphicsProgram::loop()
{
    // Main loop flag
    // If this is quit = 'true' then the program terminates.
    bool quit = false;
    // Event handler that handles various events in SDL
    // that are related to input and output
    SDL_Event e;
    // Enable text input
    SDL_StartTextInput();
    // While application is running
    while (!quit)
    {
        // Handle events on queue
        while (SDL_PollEvent(&e) != 0)
        {
            // User posts an event to quit
            // An example is hitting the "x" in the corner of the window.
            if (e.type == SDL_EVENT_QUIT)
            {
                quit = true;
            }
        } // End SDL_PollEvent loop.

        // Update screen of our specified window
        SDL_GL_SwapWindow(getSDLWindow());
    }

    // Disable text input
    SDL_StopTextInput();
}

bool SDLGraphicsProgram::isLeftPaddleUpKeyDown()
{
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    return state[SDL_GetScancodeFromKey(SDLK_w)] != 0;
}

bool SDLGraphicsProgram::isLeftPaddleDownKeyDown()
{
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    return state[SDL_GetScancodeFromKey(SDLK_s)] != 0;
}

bool SDLGraphicsProgram::isRightPaddleUpKeyDown()
{
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    return state[SDL_GetScancodeFromKey(SDLK_UP)] != 0;
}

bool SDLGraphicsProgram::isRightPaddleDownKeyDown()
{
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    return state[SDL_GetScancodeFromKey(SDLK_DOWN)] != 0;
}

// Get Pointer to Window
SDL_Window *SDLGraphicsProgram::getSDLWindow()
{
    return gWindow;
}

// Okay, render our rectangles!
void SDLGraphicsProgram::DrawRectangle(int x, int y, int w, int h)
{
    SDL_FRect rec = {static_cast<float>(x), static_cast<float>(y), static_cast<float>(w), static_cast<float>(h)};
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
    SDL_RenderRect(gRenderer, &rec);
}

void SDLGraphicsProgram::DrawCircle(int x, int y, int radius)
{
    int offsetx, offsety, d;
    int status;

    offsetx = 0;
    offsety = radius;
    d = radius - 1;
    status = 0;

    while (offsety >= offsetx)
    {
        status += SDL_RenderPoint(gRenderer, x + offsetx, y + offsety);
        status += SDL_RenderPoint(gRenderer, x + offsety, y + offsetx);
        status += SDL_RenderPoint(gRenderer, x - offsetx, y + offsety);
        status += SDL_RenderPoint(gRenderer, x - offsety, y + offsetx);
        status += SDL_RenderPoint(gRenderer, x + offsetx, y - offsety);
        status += SDL_RenderPoint(gRenderer, x + offsety, y - offsetx);
        status += SDL_RenderPoint(gRenderer, x - offsetx, y - offsety);
        status += SDL_RenderPoint(gRenderer, x - offsety, y - offsetx);

        if (status < 0)
        {
            status = -1;
            break;
        }

        if (d >= 2 * offsetx)
        {
            d -= 2 * offsetx + 1;
            offsetx += 1;
        }
        else if (d < 2 * (radius - offsety))
        {
            d += 2 * offsety - 1;
            offsety -= 1;
        }
        else
        {
            d += 2 * (offsety - offsetx - 1);
            offsety -= 1;
            offsetx += 1;
        }
    }
}

// Include the pybindings
#include <pybind11/pybind11.h>

namespace py = pybind11;

// Creates a macro function that will be called
// whenever the module is imported into python
// 'mygameengine' is what we 'import' into python.
// 'm' is the interface (creates a py::module object)
//      for which the bindings are created.
//  The magic here is in 'template metaprogramming'
PYBIND11_MODULE(mygameengine, m)
{
    m.doc() = "our game engine as a library"; // Optional docstring

    py::class_<SDLGraphicsProgram>(m, "SDLGraphicsProgram")
        .def(py::init<int, int>(), py::arg("w"), py::arg("h")) // our constructor
        .def("clear", &SDLGraphicsProgram::clear)              // Expose member methods
        .def("delay", &SDLGraphicsProgram::delay)
        .def("poll", &SDLGraphicsProgram::poll)
        .def("flip", &SDLGraphicsProgram::flip)
        .def("loop", &SDLGraphicsProgram::loop)
        .def("isLeftPaddleUpKeyDown", &SDLGraphicsProgram::isLeftPaddleUpKeyDown)
        .def("isLeftPaddleDownKeyDown", &SDLGraphicsProgram::isLeftPaddleDownKeyDown)
        .def("isRightPaddleUpKeyDown", &SDLGraphicsProgram::isRightPaddleUpKeyDown)
        .def("isRightPaddleDownKeyDown", &SDLGraphicsProgram::isRightPaddleDownKeyDown)
        .def("DrawPaddle", &SDLGraphicsProgram::DrawRectangle)
        .def("DrawBall", &SDLGraphicsProgram::DrawCircle);
    // We do not need to expose everything to our users!
    //            .def("getSDLWindow", &SDLGraphicsProgram::getSDLWindow, py::return_value_policy::reference)
}

#endif
