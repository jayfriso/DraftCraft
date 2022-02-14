/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "AppDelegate.h"
#include "UI/TitleScene.h"
#include "StaticData/TestStaticDataManager.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#include <Windows.h>
#endif

// #define USE_AUDIO_ENGINE 1

#if USE_AUDIO_ENGINE
#include "audio/include/AudioEngine.h"
using namespace cocos2d::experimental;
#endif

USING_NS_CC;


static cocos2d::Size DESIGN_RESOLUTION = cocos2d::Size(1920, 1080);
static double WINDOW_DESKTOP_SCALE{ 0.9 };

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate() 
{
#if USE_AUDIO_ENGINE
    AudioEngine::end();
#endif
}

// if you want a different context, modify the value of glContextAttrs
// it will affect all platforms
void AppDelegate::initGLContextAttrs()
{
    // set OpenGL context attributes: red,green,blue,alpha,depth,stencil,multisamplesCount
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8, 0};

    GLView::setGLContextAttrs(glContextAttrs);
}

// if you want to use the package manager to install more packages,  
// don't modify or remove this function
static int register_all_packages()
{
    return 0; //flag for packages manager
}

// Sets the given resolution based on the current desktops resolution
// Will also fit to the aspect ratio given
// Will scale value at the end by the scale given
// TODO : currently only works on windows
void setResolutionBasedOnDesktopSize(Rect& resolution, double scale, double aspectRatio)
{
    int desktopWidth{ 0 };
    int desktopHeight{ 0 };
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
    auto activeWindow = GetActiveWindow();
    HMONITOR monitor = MonitorFromWindow(activeWindow, MONITOR_DEFAULTTONEAREST);

    MONITORINFOEX monitorInfoEx;
    monitorInfoEx.cbSize = sizeof(monitorInfoEx);
    GetMonitorInfo(monitor, &monitorInfoEx);
    DEVMODE devMode;
    devMode.dmSize = sizeof(devMode);
    devMode.dmDriverExtra = 0;
    EnumDisplaySettings(monitorInfoEx.szDevice, ENUM_CURRENT_SETTINGS, &devMode);
    desktopWidth = devMode.dmPelsWidth;
    desktopHeight = devMode.dmPelsHeight;
#else
    desktopWidth = DESIGN_RESOLUTION.width;
    desktopHeight = DESIGN_RESOLUTION.height;
#endif

    double desktopRatio = (double)desktopWidth / desktopHeight;
    long width{ desktopWidth };
    long height{ desktopHeight };

    if (desktopRatio < aspectRatio)
    {
        height = width / aspectRatio;
    }
    else if (desktopRatio > aspectRatio)
    {
        width = height * aspectRatio;
    }

    resolution.setRect(0, 0, width * scale, height * scale);
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)

        Rect resolution{};
        setResolutionBasedOnDesktopSize(resolution, WINDOW_DESKTOP_SCALE, (double)DESIGN_RESOLUTION.width / DESIGN_RESOLUTION.height);
        glview = GLViewImpl::createWithRect("DraftCraft", resolution);

#else
        glview = GLViewImpl::create("DraftCraft");
#endif
        director->setOpenGLView(glview);
    }

#if _DEBUG
    director->setDisplayStats(true);
#endif

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0f / 60);

    // Set the design resolution
    glview->setDesignResolutionSize(DESIGN_RESOLUTION.width, DESIGN_RESOLUTION.height, ResolutionPolicy::SHOW_ALL);
    director->setContentScaleFactor(1);

    register_all_packages();

    // create a scene and run
    auto scene = TitleScene::createScene(m_appLifetimeResources, true);
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. Note, when receiving a phone call it is invoked.
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

#if USE_AUDIO_ENGINE
    AudioEngine::pauseAll();
#endif
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

#if USE_AUDIO_ENGINE
    AudioEngine::resumeAll();
#endif
}
