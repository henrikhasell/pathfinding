#include <irrlicht/irrlicht.h>

using namespace irr;

int main(int argc, char *argv[])
{
	IrrlichtDevice *device = createDevice(video::EDT_OPENGL);

	if(device)
	{
		device->setWindowCaption(L"Tower Defence Irrlicht");

		video::IVideoDriver* videoDriver = device->getVideoDriver();
		scene::ISceneManager* sceneManager = device->getSceneManager();
		gui::IGUIEnvironment* guiEnvironment = device->getGUIEnvironment();

		while(device->run() == true)
		{
			videoDriver->beginScene();
			sceneManager->drawAll();
			guiEnvironment->drawAll();
			videoDriver->endScene();
		}

		device->drop();
	}

	return device ? 0 : -1;
}
