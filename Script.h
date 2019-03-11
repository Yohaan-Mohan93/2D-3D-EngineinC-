/******************************************************************************************************************************************************************************************
File Name:  Script.h
Author(s):  Yohaan Mohan
         
All content © 2015 DigiPen (USA) Corporation, all rights reserved
******************************************************************************************************************************************************************************************/
#include "Advanced2D.h"
#pragma once

namespace GAM200
{
	class Script
	{
		private:
			lua_State *luaState;
			static Script* pScript;
			const char* pFunctionName;
			int pFunctionNum;
			int pArgs;
			
			static int CallBack(lua_State* aLuaState);
			int RegisterFunction(const char* aFunctionName);

			int ScriptCalling(lua_State* aLuaState, int aFunctionNumber);
			void HandleReturns(lua_State* aLuaState, const char* aFunctionName);
		public:
			Script();
			Script(bool value);
			Script(std::string scriptFile);
			virtual ~Script();

			//running a script thorugh the Engine
			bool compileFile(const char* aFileName);
			bool selectScriptFunction(const char* aFunctionName);
			void addParam(bool value);
			void addParam(int value);
			void addParam(float value);
			void addParam(char* value);
			bool Go(int theReturns);
			union
			{
				bool pBool;
			};


			//indepent script and gets the value of variables in the script
			bool loadScript(std::string scriptFile);
			
			std::string getGlobalString(std::string name);
			void setGlobalString(std::string name, std::string value);

			double getGlobalNumber(std::string name);
			void setGlobalNumber(std::string name, double value);

			bool getGlobalBoolean(std::string name);
			void setGlobalBoolean(std::string name, bool value);

			void runFunction(std::string);
	};
}