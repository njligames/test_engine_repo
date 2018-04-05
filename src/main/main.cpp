#include "Engine.h"
int main(int argc, char *argv[])
{
#if (defined(__MACOSX__) && __MACOSX__)
    if (argc > 1)
    {
        //        setRunningPath(argv[1]);
        setScriptDir(argv[1]);
    }
#endif
    
    /* initialize SDL */
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) < 0)
    {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        return 1;
    }
    
    // Check for joysticks
    if (SDL_NumJoysticks() < 1)
    {
        printf("Warning: No joysticks connected!\n");
    }
    
#if !defined(__ANDROID__)
    SDL_GetDesktopDisplayMode(0, &gDisplayMode);
#endif
    
#if defined(__EMSCRIPTEN__)
    gDisplayMode.h = 725.0f;
    float div = gDisplayMode.h / 9.0;
    gDisplayMode.w = div * 16.0f;
    //      gDisplayMode.h = 600.0f;
#endif
    
#if defined(__EMSCRIPTEN__) || defined(__ANDROID__) || defined(__IPHONEOS__)
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
#endif
    
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
    
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    
#if defined(__MACOSX__)
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_EventState(SDL_DROPFILE, SDL_ENABLE);
#endif
    
    /* create window and renderer */
    gWindow =
    SDL_CreateWindow("NJLIGameEngine", SDL_WINDOWPOS_CENTERED,
                     SDL_WINDOWPOS_CENTERED, gDisplayMode.w, gDisplayMode.h,
                     SDL_WINDOW_OPENGL
#if defined(__MACOSX__)
                     | SDL_WINDOW_MAXIMIZED | SDL_WINDOW_ALWAYS_ON_TOP | SDL_WINDOW_UTILITY
#elif !defined(__EMSCRIPTEN__)
                     | SDL_WINDOW_FULLSCREEN
#endif
                     | SDL_WINDOW_RESIZABLE
#if !defined(__EMSCRIPTEN__)
                     | SDL_WINDOW_ALLOW_HIGHDPI
#endif
                     );
    
#if defined(__MACOSX__)
    createRenderer();
#endif
    
    // SDL_SetWindowSize(gWindow, 100, 100);
    
    int w, h;
    SDL_GetWindowSize(gWindow, &w, &h);
    SDL_Log("SDL_GetWindowSize #%d: current display mode is %dx%dpx", 0, w, h);
    
    //#if defined(__MACOSX__)
    //#if !(defined(NDEBUG))
    //        SDL_SetWindowSize(gWindow, w * 0.25f, h * 0.25f);
    //#endif
    //#endif
    
    SDL_GL_GetDrawableSize(gWindow, &w, &h);
    SDL_Log("SDL_GL_GetDrawableSize #%d: current display mode is %dx%dpx", 0, w,
            h);
    
    if (!gWindow)
    {
        printf("Could not initialize Window\n");
        return 1;
    }
    
#if (defined(__ANDROID__) && (__ANDROID__))
    SDL_SetWindowFullscreen(gWindow, SDL_TRUE);
#endif
    
    gGlContext = SDL_GL_CreateContext(gWindow);
    if (!njli::NJLIGameEngine::create(
                                      DeviceUtil::hardwareDescription().c_str()))
    {
        cerr << "Error initializing OpenGL" << endl;
        return 1;
    }
    
    gGraphics = unique_ptr<Graphics>(new Graphics(gWindow));
    
#if (defined(__IPHONEOS__) && __IPHONEOS__)
    SDL_AddEventWatch(EventFilter, NULL);
#endif
    
    int drawableW, drawableH;
    int screen_w, screen_h;
    float pointSizeScale;
    
    /* The window size and drawable size may be different when highdpi is
     * enabled,
     * due to the increased pixel density of the drawable. */
    SDL_GetWindowSize(gWindow, &screen_w, &screen_h);
    //    SDL_GL_GetDrawableSize(gWindow, &drawableW, &drawableH);
    drawableW = gDisplayMode.w;
    drawableH = gDisplayMode.h;
    
    /* In OpenGL, point sizes are always in pixels. We don't want them looking
     * tiny on a retina screen. */
    pointSizeScale = (float)drawableH / (float)screen_h;
    
    //#if defined(__MACOSX__)
    //    SDL_GetWindowSize(gWindow, &w, &h);
    //#else
    //    SDL_GL_GetDrawableSize(gWindow, &w, &h);
    //#endif
    //#if defined(__EMSCRIPTEN__)
    NJLI_HandleResize(drawableW, drawableH, gDisplayMode.format,
                      gDisplayMode.refresh_rate);
    //#endif
    
    gDone = (njli::NJLIGameEngine::start(argc, argv) == false) ? 1 : 0;
    
#if defined(__EMSCRIPTEN__)
    emscripten_set_main_loop(mainloop, 0, 0);
#else
    
    while (!gDone)
    {
#if defined(__IPHONEOS__) && __IPHONEOS__
        handleInput();
#else
        mainloop();
#endif
    }
    
    NJLI_HandleSurfaceDestroyed();
    
#endif
    
    return 0;
}
