//
//  TestGame.h
//  NJLIC
//
//  Created by James Folk on 4/6/18.
//

#ifndef TestGame_h
#define TestGame_h

#include "TestGame.h"
#include "treasure_hunt_renderer.hh"

class TestGame : public SDLGame
{
    gvr_context *_gvrContext;
    std::unique_ptr<TreasureHuntRenderer> _renderer;
public:
    virtual bool start(int argc, char **argv)override
    {
        return false;
    }
    
    virtual bool create()override
    {
        // Create GVR context.
        _gvrContext = gvr_create();
        
        // Create GVR Audio context.
//        std::unique_ptr<gvr::AudioApi> audio_context(new gvr::AudioApi);
//        audio_context->Init(GVR_AUDIO_RENDERING_BINAURAL_HIGH_QUALITY);
        
        // Initialize TreasureHuntRenderer.
//        _renderer.reset(new TreasureHuntRenderer(_gvrContext, std::move(audio_context)));
        _renderer.reset(new TreasureHuntRenderer(_gvrContext));
        _renderer->InitializeGl();
        return true;
        
    }
    
    virtual void destroy()override
    {
        
    }
    
    virtual void render()override
    {
        _renderer->DrawFrame();
    }
    
    virtual void update(double timeStep)override
    {
        
    }
    
    virtual void lowMemory()override
    {
        
    }
    
    virtual void quit()override
    {
        
    }
    
    virtual void pause()override
    {
        _renderer->OnPause();
    }
    
    virtual void resume()override
    {
        _renderer->OnResume();
    }
    
    virtual void dropFile(const std::string &filename)override
    {
        
    }
    
    virtual void dropText(const std::string &text)override
    {
        
    }
    
    virtual void resize(int width, int height, int sdlFormat, float refreshRate)override
    {
        
    }
    
    virtual int padDown(int device_id, int keycode)override
    {
        return 0;
    }
    
    virtual int padUp(int device_id, int keycode)override
    {
        return 0;
    }
    
    virtual void joy(int device_id, int axis, float value)override
    {
        
    }
    
    virtual void hat(int device_id, int hat_id, int x, int y)override
    {
        
    }
    
    virtual void keyDown(const std::string &keycodeName, bool withCapsLock,
                         bool withControl, bool withShift, bool withAlt,
                         bool withGui)override
    {
        
    }
    
    virtual void keyUp(const std::string &keycodeName, bool withCapsLock,
                       bool withControl, bool withShift, bool withAlt,
                       bool withGui)override
    {
        
    }
    
    virtual void keyboardFocusLost()override
    {
        
    }
    
    virtual void mouse(int button, int eventType, float x, float y, int clicks)override
    {
        
    }
    
    virtual void touch(int touchDevId, int pointerFingerId, int eventType,
                       float x, float y, float dx, float dy, float pressure)override
    {
        _renderer->OnTriggerEvent();
    }
    
    virtual void finishTouches()override
    {
        
    }
    
    virtual void accel(float x, float y, float z)override
    {
        
    }
    
    virtual int addJoystick(int device_id, const std::string &name,
                            int is_accelerometer, int nbuttons, int naxes,
                            int nhats, int nballs)override
    {
        return 0;
    }
    
    virtual int removeJoystick(int device_id)override
    {
        return 0;
        
    }
    
    virtual std::string getHint(const std::string &name)override
    {
        return std::string();
    }
    
    virtual void commitText(const std::string &text, int newCursorPosition)override
    {
        
    }
    
    virtual void setComposingText(const std::string &text, int newCursorPosition)override
    {
        
    }
    
    virtual void didEnterBackground()override
    {
        
    }
    
    virtual void willTerminate()override
    {
        
    }
    
    virtual void willEnterForeground()override
    {
        
    }
};

#endif /* TestGame_h */
