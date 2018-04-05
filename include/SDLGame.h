//
//  SDLGame.h
//  NJLIC
//
//  Created by James Folk on 4/5/18.
//

#ifndef SDLGame_h
#define SDLGame_h

class SDLGame
{
public:
    virtual bool start(int argc, char **argv){return false;}
    virtual bool create(){return false;}
    virtual void destroy(){}
    virtual void render(){}
    virtual void update(double timeStep){}
    virtual void lowMemory(){}
    virtual void quit(){}
    virtual void pause(){}
    virtual void resume(){}
    virtual void dropFile(const std::string &filename){}
    virtual void dropText(const std::string &text){}
    virtual void resize(int width, int height, int sdlFormat, float refreshRate){}
    virtual int padDown(int device_id, int keycode){return 0;}
    virtual int padUp(int device_id, int keycode){return 0;}
    virtual void joy(int device_id, int axis, float value){}
    virtual void hat(int device_id, int hat_id, int x, int y){}
    virtual void keyDown(const std::string &keycodeName, bool withCapsLock,
                         bool withControl, bool withShift, bool withAlt,
                         bool withGui){}
    virtual void keyUp(const std::string &keycodeName, bool withCapsLock,
                       bool withControl, bool withShift, bool withAlt,
                       bool withGui){}
    virtual void keyboardFocusLost(){}
    //    virtual void keyboardFinish(const unsigned char *state, int numStates){}
    virtual void mouse(int button, int eventType, float x, float y, int clicks){}
    
    virtual void touch(int touchDevId, int pointerFingerId, int eventType,
                       float x, float y, float dx, float dy, float pressure){}
    virtual void finishTouches(){}
    
    virtual void accel(float x, float y, float z){}
    //    virtual void surfaceChanged(){}
    //    virtual void surfaceDestroyed(){}
    virtual int addJoystick(int device_id, const std::string &name,
                            int is_accelerometer, int nbuttons, int naxes,
                            int nhats, int nballs){return 0;}
    virtual int removeJoystick(int device_id){return 0;}
    virtual std::string getHint(const std::string &name){return std::string();}
    
    virtual void commitText(const std::string &text, int newCursorPosition){}
    virtual void setComposingText(const std::string &text, int newCursorPosition){}
    virtual void didEnterBackground(){}
    virtual void willTerminate(){}
    virtual void willEnterForeground(){}
    
};

#endif /* SDLGame_h */
