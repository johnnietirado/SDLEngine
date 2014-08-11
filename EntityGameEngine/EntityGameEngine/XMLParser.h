#pragma once

#include "GameObject.h"
#include "HealthComponent.h"
#include "TransformComponent.h"
#include "RenderingComponent.h"
#include "PlayerControllerComponent.h"
#include "tinyxml.h"

class XMLParser
{
public:
	static XMLParser* Instance();

	GameObject* ParseGameObject(const char* goFile, GameObjectID id)
	{
		TiXmlDocument xmlDoc;
		const char* attr;
		if (!xmlDoc.LoadFile(goFile))
		{
			std::cout << xmlDoc.ErrorDesc() << std::endl;
			return NULL;
		}
		
		TiXmlElement* root = xmlDoc.FirstChildElement();
		if (root == NULL)
		{
			std::cout << "Failed to load File: No root element." << std::endl;
			xmlDoc.Clear();
			return NULL;
		}

		for (TiXmlElement* elem = root->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement())
		{
			std::string elemName = elem->Value();
			
			if (elemName == "Object")
			{
				GameObject* go = new GameObject();
				go->setID(id);
				std::cout << "Creating object with: \n";
				for (TiXmlElement* e = elem->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
				{
					elemName = e->Value();
					if (elemName == "Transform")
					{
						ParseTransformComponent(e, go);
					}
					else if (elemName == "Health")
					{
						ParseHealthComponent(e, go);
					}
					else if (elemName == "Renderer")
					{
						ParseRenderingComponent(e, go);
					}
					else if (elemName == "Controller")
					{
						ParseControllerComponent(e, go);
					}
				}
				return go;
			}
		}
		return NULL;
	}

	void LoadTexturesFromFile(const char* goFile, SDL_Renderer* renderer)
	{
		std::string filename = "";
		std::string id = "";

		TiXmlDocument xmlDoc;
		const char* attr;
		if (!xmlDoc.LoadFile(goFile))
		{
			std::cout << xmlDoc.ErrorDesc() << std::endl;
			return;
		}

		TiXmlElement* root = xmlDoc.FirstChildElement();
		if (root == NULL)
		{
			std::cout << "Failed to load File: No root element." << std::endl;
			xmlDoc.Clear();
			return;
		}

		for (TiXmlElement* elem = root->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement())
		{
			std::string elemName = elem->Value();
			std::string fileDir = ".\\Assets\\Images\\";
			if (elemName == "Texture")
			{
				filename = fileDir + elem->Attribute("Filename");
				id = elem->Attribute("TextureId");
				TextureManager::Instance()->Load(filename, id, renderer);
			}
		}
	}

private:
	void ParseTransformComponent(TiXmlElement* e, GameObject* go)
	{
		double x, y;
		const char* attr;
		TransformComponent* tc = new TransformComponent();
		tc->Initialize();
		tc->setOwner(go->GetID());
		
		e->Attribute("x", &x);
		e->Attribute("y", &y);

		tc->SetPosition((float)x, (float)y);
		go->AddComponent(ComponentID::Transform, tc);
		std::cout << "Transform Component\n";
	}
	
	void ParseHealthComponent(TiXmlElement* e, GameObject* go)
	{
		int health, maxHealth;
		HealthComponent* hc = new HealthComponent();
		hc->setOwner(go->GetID());
		hc->Initialize();
		e->Attribute("health", &health);
		e->Attribute("maxHealth", &maxHealth);
		hc->Load(health, maxHealth);
		go->AddComponent(ComponentID::Health, hc);
		std::cout << "Health Component\n";
	}

	void ParseRenderingComponent(TiXmlElement* e, GameObject* go)
	{
		AnimationID id;
		std::string texID;
		int width, height, animID;
		int rowStart = 0, colStart = 0, numFrames = 0, animationSpeed = 1;
		
		RenderingComponent* rc = new RenderingComponent();
		rc->setOwner(go->GetID());

		for (TiXmlElement* elem = e->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement())
		{
			std::string elemName = elem->Value();
			if (elemName == "Animation")
			{
				elem->Attribute("AnimationID", &animID);
				switch (animID)
				{
				case 1:
					id = AnimationID::IDLE;
					break;
				default:
					id = AnimationID::NONE;
					break;
				}

				texID = elem->Attribute("TextureID");
				elem->Attribute("width", &width);
				elem->Attribute("height", &height);
				elem->Attribute("rowStart", &rowStart);
				elem->Attribute("colStart", &colStart);
				elem->Attribute("numFrames", &numFrames);
				elem->Attribute("animationSpeed", &animationSpeed);

				Animation* anim = new Animation();
				anim->id = id;
				anim->texID = texID;
				anim->width = width;
				anim->height = height;
				anim->rowStart = rowStart;
				anim->colStart = colStart;
				anim->numFrames = numFrames;
				anim->currentFrame = 0;
				anim->animationSpeed = numFrames;

				rc->AddAnimation(id, anim);
			}
		}
		rc->Initialize();
		go->AddComponent(ComponentID::Renderer, rc);
		std::cout << "Rendering Component\n";
	}

	void ParseControllerComponent(TiXmlElement* e, GameObject* go)
	{
		PlayerControllerComponent* pc = new PlayerControllerComponent();
		pc->setOwner(go->GetID());
		pc->Initialize();
		go->AddComponent(ComponentID::Controller, pc);
		std::cout << "Constroller\n";
	}

private:
	static XMLParser* mInstance;
	XMLParser(){};
};