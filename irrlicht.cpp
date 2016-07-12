#include <stdio.h>
#include <irrlicht/irrlicht.h>

class addStaticText;
using namespace irr;

int main(int argc, char **argv)
{
    IrrlichtDevice *device = createDevice(video::EDT_OPENGL, core::dimension2d<u32>(640, 480));

    if(device != nullptr)
    {
        device->setWindowCaption(L"Basic Irrlicht Framework");

        // Fetch Important Objects
        video::IVideoDriver* driver = device->getVideoDriver();
        scene::ISceneManager *sceneManager = device->getSceneManager();
        gui::IGUIEnvironment *guiEnvironment = device->getGUIEnvironment();

        // Main Loop
        while(device->run() == true)
        {
            driver->beginScene();
            sceneManager->drawAll();
            driver->endScene();
        }

        device->drop();
    }

    return device != nullptr ? 0 : -1;
}
