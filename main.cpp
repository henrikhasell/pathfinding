#include <irrlicht/irrlicht.h>
#include <iostream>
#include "NodeMap.hpp"
#include "Vector.hpp"

const char TILEMAP_DATA[30 * 30] = {
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1,
    1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
};

using namespace irr;

class MyEventReceiver : public IEventReceiver
{
public:
	Navigation::NodeMap nodeMap;

    virtual bool OnEvent(const SEvent& event)
    {
		if (event.EventType == irr::EET_MOUSE_INPUT_EVENT)
		{
			switch(event.MouseInput.Event)
			{
			case EMIE_LMOUSE_PRESSED_DOWN:
				std::cout << "The left mouse button was pressed." << std::endl;
				mouseMode = SET_PATH_START;
				break;

			case EMIE_RMOUSE_PRESSED_DOWN:
				std::cout << "The right mouse button was pressed." << std::endl;
				mouseMode = SET_PATH_END;
				break;

			case EMIE_LMOUSE_LEFT_UP:
				std::cout << "The left mouse button was released." << std::endl;
				mouseMode = DO_NOTHING;
				break;

			case EMIE_RMOUSE_LEFT_UP:
				std::cout << "The right mouse button was released." << std::endl;
				mouseMode = DO_NOTHING;
				break;
			}

			core::position2d<s32> screenCoordinates(event.MouseInput.X, event.MouseInput.Y);
			core::line3d<f32> ray = collisionManager->getRayFromScreenCoordinates(screenCoordinates);
			core::plane3d<f32> plane(core::vector3d<f32>(0.0f, 0.0f, 0.0f), core::vector3d<f32>(0.0f, 1.0f, 0.0f));
			core::vector3d<f32> intersectionPoint;
			switch(mouseMode)
			{
				case SET_PATH_START:
					if(plane.getIntersectionWithLine(ray.start, ray.getVector(), intersectionPoint) == true)
					{
						pathStart.x = intersectionPoint.X;
						pathStart.y =-intersectionPoint.Z;
					}
					break;
			}
		}
    }
    
    MyEventReceiver(scene::ISceneCollisionManager* collisionManager) :
		collisionManager(collisionManager),
		nodeMap(30, 30, TILEMAP_DATA),
		pathStart(0.0f, 0.0f),
		pathFinish(0.0f, 0.0f),
		mouseMode(DO_NOTHING)
    {

    }
private:
	scene::ISceneCollisionManager* collisionManager;
	Navigation::Vector pathStart;
	Navigation::Vector pathFinish;
	enum { SET_PATH_START, SET_PATH_END, DO_NOTHING } mouseMode;
};

int main(int argc, char *argv[])
{

	IrrlichtDevice *device = createDevice(video::EDT_OPENGL);
	if(device)
	{
		device->setWindowCaption(L"Tower Defence Irrlicht");

		video::IVideoDriver* videoDriver = device->getVideoDriver();
		scene::ISceneManager* sceneManager = device->getSceneManager();
		scene::ISceneCollisionManager* collisionManager = sceneManager->getSceneCollisionManager();
		gui::IGUIEnvironment* guiEnvironment = device->getGUIEnvironment();

		MyEventReceiver receiver(collisionManager);


		device->setEventReceiver(&receiver);

		scene::IAnimatedMesh* turretMesh = sceneManager->getMesh("assets/meshes/turret.obj");
		scene::IAnimatedMesh* floorMesh = sceneManager->getMesh("assets/meshes/floor.obj");
		scene::IAnimatedMesh* wallMesh = sceneManager->getMesh("assets/meshes/wall.obj");

		sceneManager->setAmbientLight(video::SColorf(0.3,0.3,0.3,1));
		scene::ILightSceneNode *light =
			sceneManager->addLightSceneNode(0, core::vector3df(300, 500 ,-310), video::SColorf(0.2f, 0.2f, 0.2f, 0.0f), 500.0f);

		for(int i = 0; i < 30; i++)
		{
			for(int j = 0; j < 30; j++)
			{
				scene::ISceneNode *node = nullptr;

				switch(TILEMAP_DATA[i + j * 30])
				{
					case 0:
						node = sceneManager->addMeshSceneNode(floorMesh);
						break;
					case 1:
						node = sceneManager->addMeshSceneNode(wallMesh);
						break;
					case 2:
						node = sceneManager->addMeshSceneNode(turretMesh);
						break;
				}

				if(node)
				{
					//node->setMaterialFlag(video::EMF_LIGHTING, false);
					node->setPosition(core::vector3df(20.0f * i, 0.0f,-20.0f * j));
				}
			}
		}

		sceneManager->addCameraSceneNode(0, core::vector3df(300, 500,-310), core::vector3df(300, 0,-300));
		//sceneManager->addCameraSceneNodeFPS();

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
