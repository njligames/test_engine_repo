//
//  TestGame.h
//  NJLIC
//
//  Created by James Folk on 4/6/18.
//

#ifndef TestGame_h
#define TestGame_h

class TestGame : public SDLGame
{
public:
    virtual bool start(int argc, char **argv)override
    {
      printf("start\n");
        return true;
    }
    
    virtual bool create()override
    {
      printf("create\n");
        return true;
        
    }
    
    virtual void destroy()override
    {
      printf("destroy\n");
        
    }
    
    virtual void render()override
    {
      printf("render\n");

    }
    
    virtual void update(double timeStep)override
    {
      printf("update\n");
        
    }
    
    virtual void lowMemory()override
    {
      printf("lowMemory\n");
        
    }
    
    virtual void quit()override
    {
      printf("quit\n");
        
    }
    
    virtual void pause()override
    {
      printf("pause\n");

    }
    
    virtual void resume()override
    {
      printf("resume\n");

    }
    
    virtual void dropFile(const std::string &filename)override
    {
      printf("dropFile\n");
        
    }
    
    virtual void dropText(const std::string &text)override
    {
      printf("dropText\n");
        
    }
    
    virtual void resize(int width, int height, int sdlFormat, float refreshRate)override
    {
      printf("resize\n");
        
    }
    
    virtual int padDown(int device_id, int keycode)override
    {
      printf("padDown\n");
        return 0;
    }
    
    virtual int padUp(int device_id, int keycode)override
    {
      printf("padUp\n");
        return 0;
    }
    
    virtual void joy(int device_id, int axis, float value)override
    {
      printf("joy\n");
        
    }
    
    virtual void hat(int device_id, int hat_id, int x, int y)override
    {
      printf("hat\n");
        
    }
    
    virtual void keyDown(const std::string &keycodeName, bool withCapsLock,
                         bool withControl, bool withShift, bool withAlt,
                         bool withGui)override
    {
      printf("keyDown\n");
        
    }
    
    virtual void keyUp(const std::string &keycodeName, bool withCapsLock,
                       bool withControl, bool withShift, bool withAlt,
                       bool withGui)override
    {
      printf("keyUp\n");
        
    }
    
    virtual void keyboardFocusLost()override
    {
      printf("keyboardFocusLost\n");
        
    }
    
    virtual void mouse(int button, int eventType, float x, float y, int clicks)override
    {
      printf("mouse\n");
        
    }
    
    virtual void touch(int touchDevId, int pointerFingerId, int eventType,
                       float x, float y, float dx, float dy, float pressure)override
    {
      printf("touch\n");
    }
    
    virtual void finishTouches()override
    {
      printf("finishTouches\n");
        
    }
    
    virtual void accel(float x, float y, float z)override
    {
      printf("accel\n");
        
    }
    
    virtual int addJoystick(int device_id, const std::string &name,
                            int is_accelerometer, int nbuttons, int naxes,
                            int nhats, int nballs)override
    {
      printf("addJoystick\n");
        return 0;
    }
    
    virtual int removeJoystick(int device_id)override
    {
      printf("removeJoystick\n");
        return 0;
        
    }
    
    virtual std::string getHint(const std::string &name)override
    {
      printf("::\n");
        return std::string();
    }
    
    virtual void commitText(const std::string &text, int newCursorPosition)override
    {
      printf("commitText\n");
        
    }
    
    virtual void setComposingText(const std::string &text, int newCursorPosition)override
    {
      printf("setComposingText\n");
        
    }
    
    virtual void didEnterBackground()override
    {
      printf("didEnterBackground\n");
        
    }
    
    virtual void willTerminate()override
    {
      printf("willTerminate\n");
        
    }
    
    virtual void willEnterForeground()override
    {
      printf("willEnterForeground\n");
        
    }
};

#endif /* TestGame_h */
