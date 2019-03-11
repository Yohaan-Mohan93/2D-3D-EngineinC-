/******************************************************************************************************************************************************************************************
File Name:  LogFile.h
Author(s):  Yohaan Mohan
Purpose: Create the window for 
         
All content © 2015 DigiPen (USA) Corporation, all rights reserved
******************************************************************************************************************************************************************************************/
#include "Advanced2D.h"
#pragma once

namespace GAM200
{
	class LogFile
	{
		public:
			LogFile();
			~LogFile();

			void Print(std::string s);
			void Print(char c[]);

			std::ofstream& operator<<(char c[]);
			std::ofstream& operator<<(std::string s);
			std::ofstream& operator<<(double d);
			std::ofstream& operator<<(float f);
			std::ofstream& operator<<(int i);
			std::ofstream& operator<<(bool b);
	};
}