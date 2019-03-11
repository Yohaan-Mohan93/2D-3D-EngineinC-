/******************************************************************************************************************************************************************************************
File Name:  ResourceManager.cpp
Author(s):  Yohaan Mohan 
         
All content © 2015 DigiPen (USA) Corporation, all rights reserved
******************************************************************************************************************************************************************************************/
#include "Advanced2D.h"

namespace GAM200
{
	ResourceManager ResourceManager::p_ResourceManger;

	ResourceManager* ResourceManager::getResourceManager()
	{
		return &p_ResourceManger;
	}

	Resource* ResourceManager::findResourceByID(unsigned int UID)
	{
		std::map<unsigned int, std::list<Resource*>>::iterator it;

		//search through scopes
		for (it = p_Resources.begin(); it != p_Resources.end(); it++)
		{
			if (!(*it).second.empty())
			{
				std::list<Resource*>::iterator list_it;

				//search through the resources of the scope
				for (list_it = (*it).second.begin(); list_it != (*it).second.end(); it++)
				{
					//If it matches ID
					if ((*list_it)->p_ResourceID == UID)
						return (*list_it);
				}
			}
		}

		return nullptr;
	}

	void ResourceManager::clear()
	{
		std::map<unsigned int, std::list<Resource*>>::iterator it;

		//search through scopes
		for (it = p_Resources.begin(); it != p_Resources.end(); it++)
		{
			if (!(*it).second.empty())
			{
				std::list<Resource*>::iterator list_it;

				//Search through resources of scope
				for (list_it = (*it).second.begin(); list_it != (*it).second.end(); list_it++)
				{
					//Delete resource object
					(*list_it)->unload();
					SAFE_DELETE(*list_it);
				}

				(*it).second.clear();
			}
		}

		p_Resources.clear();
	}

	bool ResourceManager::loadFromXMLFile(std::string fileName)
	{
		TiXmlDocument doc(fileName.c_str());
		if (doc.LoadFile())
		{
			//find resource node
			TiXmlNode* ResourceTree = doc.FirstChild("resources");

			if (ResourceTree)
			{
				//enumerate resource objects
				for (TiXmlNode * child = ResourceTree->FirstChild(); child; child = child->NextSibling)
				{
					TiXmlElement *Element = child->ToElement();
					if (Element)
					{
						Resource *tempResource = NULL;
						tempResource = new Resource;

						for (TiXmlAttribute* ElementAttrib = Element->FirstAttribute(); ElementAttrib; ElementAttrib = ElementAttrib->Next())
						{
							//Examine resource object
							std::string AttribName = ElementAttrib->Name();
							std::string AttribValue = ElementAttrib->Value();

							//Detect resource type. Graphic? Audio? Text?
							if (AttribName == "type")
							{
								if (AttribValue == "graphic")
								{
									//Get singelton render manager

									//Load Graphics Resources. Implemented in later chapter.
									//cSDL2DRenderManager* g_RenderManager = cSDL2DRenderManager::GetSDL2DRenderManager();
									//Resource = g_RenderManager->loadResourceFromXML(Element);

									//Resource = new cResource();
								}

								if (AttribValue == "audio")
								{
									//Load Audio Resources. Implemented in later chapter.
									//cAudioManager* g_AudioManager = cAudioManager::GetAudioManager();
									//Resource = g_AudioManager->loadResourceFromXML(Element);
								}

								if (AttribValue == "text")
								{
									//Add a Config Manager to handle text?
									//Resource = g_ConfigManager->loadResourceFromXML(Element);

									//Resource = new cResource();
								}
							}

							if (tempResource)
							{
								p_Resources[tempResource->p_Scope].push_back(tempResource);
								p_ResourceCount++;
							}
						}
					}

					return true;
				}
			}
		}

		return false;
	}

	void ResourceManager::setCurrentScope(unsigned int Scope)
	{
		//Unload old scope, if not global scope.
		if (p_CurrentScope != 0)
		{
			std::list<Resource*>::iterator list_it;

			for (list_it = p_Resources[p_CurrentScope].begin(); list_it != p_Resources[p_CurrentScope].end(); list_it++)
				(*list_it)->unload();
		}

		p_CurrentScope = Scope;

		//Load new scope.
		std::list<Resource*>::iterator list_it;

		for (list_it = p_Resources[p_CurrentScope].begin(); list_it != p_Resources[p_CurrentScope].end(); list_it++)
			(*list_it)->load();
	}
}