//
//  SDLGameInterface.h
//  NJLIC
//
//  Created by James Folk on 4/6/18.
//

#ifndef SDLGameInterface_h
#define SDLGameInterface_h

#include "SDLGame.h"
#include <algorithm>

class SDLGameInterface
{
private:
    SDLGameInterface(){}
    SDLGameInterface(const SDLGameInterface&);
    static SDLGameInterface *sSDLGameInterface;
    
    std::vector<SDLGame*> mGames;
public:
    static SDLGameInterface *getInstance()
    {
        if(NULL == sSDLGameInterface)
            sSDLGameInterface = new SDLGameInterface();
        return sSDLGameInterface;
    }
    
    static void destroyInstance()
    {
        if(sSDLGameInterface)
            delete sSDLGameInterface;
        sSDLGameInterface = NULL;
    }
    
    void registerGame(SDLGame *game)
    {
        if(std::find(mGames.begin(), mGames.end(), game) == mGames.end())
        {
            mGames.push_back(game);
        }
    }
    
    bool start(int argc, char **argv)
    {
        bool ret = true;
        std::for_each(mGames.begin(),
                      mGames.end(),
                      [argc, argv, &ret](SDLGame *game) mutable {
                          bool r = game->start(argc, argv);
                          ret = ret && r;
                      });
        return ret;
    }
    
    bool create()
    {
        bool ret = true;
        std::for_each(mGames.begin(),
                      mGames.end(),
                      [&ret](SDLGame *game)  {
                          bool r = game->create();
                          ret = ret && r;
                      });
        return ret;
    }
    
    void destroy()
    {
        std::for_each(mGames.begin(), mGames.end(), [](SDLGame *game) {game->destroy();});
    }
    
    void render()
    {
        std::for_each(mGames.begin(), mGames.end(), [](SDLGame *game) {game->render();});
    }
    
    void update(double timeStep)
    {
        std::for_each(mGames.begin(), mGames.end(), [timeStep](SDLGame *game) {game->update(timeStep);});
    }
    
    void lowMemory()
    {
        std::for_each(mGames.begin(), mGames.end(), [](SDLGame *game) {game->lowMemory();});
    }
    
    void quit()
    {
        std::for_each(mGames.begin(), mGames.end(), [](SDLGame *game) {game->quit();});
    }
    
    void pause()
    {
        std::for_each(mGames.begin(), mGames.end(), [](SDLGame *game) {game->pause();});
    }
    
    void resume()
    {
        std::for_each(mGames.begin(), mGames.end(), [](SDLGame *game) {game->resume();});
    }
    
    void dropFile(const std::string &filename)
    {
        std::for_each(mGames.begin(), mGames.end(), [filename](SDLGame *game) {game->dropFile(filename);});
    }
    
    void dropText(const std::string &text)
    {
        std::for_each(mGames.begin(), mGames.end(), [text](SDLGame *game) {game->dropText(text);});
    }
    
    void resize(int width, int height, int sdlFormat, float refreshRate)
    {
        std::for_each(mGames.begin(), mGames.end(), [width, height, sdlFormat, refreshRate](SDLGame *game) {game->resize(width, height, sdlFormat, refreshRate);});
    }
    
    int padDown(int device_id, int keycode)
    {
        int ret = 1;
        std::for_each(mGames.begin(),
                      mGames.end(),
                      [device_id, keycode, &ret](SDLGame *game)  {
                          int r = game->padDown(device_id, keycode);
                          ret = ret && r;
                      });
        return ret;
    }
    
    int padUp(int device_id, int keycode)
    {
        int ret = 1;
        std::for_each(mGames.begin(),
                      mGames.end(),
                      [device_id, keycode, &ret](SDLGame *game) {
                          int r = game->padUp(device_id, keycode);
                          ret = ret && r;
                      });
        return ret;
    }
    
    void joy(int device_id, int axis, float value)
    {
        std::for_each(mGames.begin(), mGames.end(), [device_id, axis, value](SDLGame *game) {game->joy(device_id, axis, value);});
    }
    
    void hat(int device_id, int hat_id, int x, int y)
    {
        std::for_each(mGames.begin(), mGames.end(), [device_id, hat_id, x, y](SDLGame *game) {game->hat(device_id, hat_id, x, y);});
    }
    
    void keyDown(const std::string &keycodeName, bool withCapsLock,
                 bool withControl, bool withShift, bool withAlt,
                 bool withGui)
    {
        std::for_each(mGames.begin(), mGames.end(), [keycodeName, withCapsLock, withControl, withShift, withAlt, withGui](SDLGame *game) {game->keyDown(keycodeName, withCapsLock, withControl, withShift, withAlt, withGui);});
    }
    
    void keyUp(const std::string &keycodeName, bool withCapsLock,
               bool withControl, bool withShift, bool withAlt,
               bool withGui)
    {
        std::for_each(mGames.begin(), mGames.end(), [keycodeName, withCapsLock, withControl, withShift, withAlt, withGui](SDLGame *game) {game->keyUp(keycodeName, withCapsLock, withControl, withShift, withAlt, withGui);});
    }
    
    void keyboardFocusLost()
    {
        std::for_each(mGames.begin(), mGames.end(), [](SDLGame *game) {game->keyboardFocusLost();});
    }
    
    void mouse(int button, int eventType, float x, float y, int clicks)
    {
        std::for_each(mGames.begin(), mGames.end(), [button, eventType, x, y, clicks](SDLGame *game) {game->mouse(button, eventType, x, y, clicks);});
    }
    
    void touch(int touchDevId, int pointerFingerId, int eventType,
               float x, float y, float dx, float dy, float pressure)
    {
        std::for_each(mGames.begin(), mGames.end(), [touchDevId, pointerFingerId, eventType, x, y, dx, dy, pressure](SDLGame *game) {game->touch(touchDevId, pointerFingerId, eventType, x, y, dx, dy, pressure);});
    }
    
    void finishTouches()
    {
        std::for_each(mGames.begin(), mGames.end(), [](SDLGame *game) {game->finishTouches();});
    }
    
    void accel(float x, float y, float z)
    {
        std::for_each(mGames.begin(), mGames.end(), [x, y, z](SDLGame *game) {game->accel(x, y, z);});
    }
    
    int addJoystick(int device_id, const std::string &name,
                    int is_accelerometer, int nbuttons, int naxes,
                    int nhats, int nballs)
    {
        int ret = 1;
        std::for_each(mGames.begin(),
                      mGames.end(),
                      [device_id, name, is_accelerometer, nbuttons, naxes, nhats, nballs, &ret](SDLGame *game) {
                          int r = game->addJoystick(device_id, name, is_accelerometer, nbuttons, naxes, nhats, nballs);
                          ret = ret && r;
                      });
        return ret;
    }
    
    int removeJoystick(int device_id)
    {
        int ret = 1;
        std::for_each(mGames.begin(),
                      mGames.end(),
                      [device_id, &ret](SDLGame *game) {
                          int r = game->removeJoystick(device_id);
                          ret = ret && r;
                      });
        return ret;
    }
    
    std::string getHint(const std::string &name)
    {
        std::string ret = "";
        std::for_each(mGames.begin(),
                      mGames.end(),
                      [name, &ret](SDLGame *game) {
                          std::string r = game->getHint(name);
                          ret = ret + r;
                      });
        return ret;
    }
    
    void commitText(const std::string &text, int newCursorPosition)
    {
        std::for_each(mGames.begin(), mGames.end(), [text, newCursorPosition](SDLGame *game) {game->commitText(text, newCursorPosition);});
    }
    
    void setComposingText(const std::string &text, int newCursorPosition)
    {
        std::for_each(mGames.begin(), mGames.end(), [text, newCursorPosition](SDLGame *game) {game->setComposingText(text, newCursorPosition);});
    }
    
    void didEnterBackground()
    {
        std::for_each(mGames.begin(), mGames.end(), [](SDLGame *game) {game->didEnterBackground();});
    }
    
    void willTerminate()
    {
        std::for_each(mGames.begin(), mGames.end(), [](SDLGame *game) {game->willTerminate();});
    }
    
    void willEnterForeground()
    {
        std::for_each(mGames.begin(), mGames.end(), [](SDLGame *game) {game->willEnterForeground();});
    }
};
SDLGameInterface *SDLGameInterface::sSDLGameInterface = NULL;

#endif /* SDLGameInterface_h */
