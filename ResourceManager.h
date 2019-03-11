/******************************************************************************************************************************************************************************************
File Name:  ResourceManager.h
Author(s):  Yohaan Mohan
         
All content © 2015 DigiPen (USA) Corporation, all rights reserved
******************************************************************************************************************************************************************************************/
#include "Advanced2D.h"
#pragma once

namespace GAM200
{
	typedef enum RESOURCE_TYPE
	{
		RESOURCE_NULL = 0,
		REOURCE_GRAPHIC = 1,
		RESOURCE_MOVIE = 2,
		RESOURCE_AUDIO = 3,
		RESOURCE_TEXT = 4,
	};

	//Resource class. Represents a resource object.
	//To be managed by a Resource Manager.
	//Should be overriden by other classes
	//and methods providing specific implementations
	//RenderManager
	class Resource : public cEngineObject
	{
		private:
		protected:
		public:
			unsigned int p_ResourceID;
			unsigned int p_Scope;
			std::string p_FileName;
			RESOURCE_TYPE p_Type;
			bool p_Loaded;

			//overloaded by derived classes

			virtual ~Resource() {};
			virtual void load() {};
			virtual void unload() {};

			inline Resource()
			{
				p_ResourceID = p_Scope = 0;
				p_Type = RESOURCE_NULL;
				p_Loaded = false;
			}
	};

	class ResourceManager
	{
		private:
		protected:
			static ResourceManager p_ResourceManger;

			//current resource scope
			unsigned int p_CurrentScope;

			//total number of resources, both loaded and unloaded
			unsigned int p_ResourceCount;

			inline ResourceManager()
			{
				p_CurrentScope = p_ResourceCount = 0;
			}

		public:
			static ResourceManager* getResourceManager();

			//STL map in the form <scope,resource list>
			//each scope element contains a list of resources for that scope
			std::map<unsigned int, std::list<Resource*> >p_Resources;

			//finds a resource by ID. Returns NULL if specified resource is not found
			Resource* findResourceByID(unsigned int UID);

			//clears all resources and all scopes
			void clear();

			//loads resources from an XML file
			bool loadFromXMLFile(std::string fileName);

			//sets the current scope. Depends on the scene currently loaded
			//call this function with a valid scene scope
			//to load and unload appropriate resources
			void setCurrentScope(unsigned int Scope);

			//returns the number of resources currently loaded
			const unsigned int getResourceCount() { return p_ResourceCount; }

	};
}