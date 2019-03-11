/******************************************************************************************************************************************************************************************
File Name:  LogFile.cpp
Author(s):  Yohaan Mohan
         
All content © 2015 DigiPen (USA) Corporation, all rights reserved
******************************************************************************************************************************************************************************************/
#include "Advanced2D.h"

std::ofstream out("logfile.txt");

namespace GAM200
{
	LogFile::LogFile(){}

	LogFile::~LogFile()
	{
		if (out.good())
			out.close();
	}

	void LogFile::Print(std::string s)
	{
		out << s << std::endl;
	}

	void LogFile::Print(char c[])
	{
		out << c << std::endl;
	}

	std::ofstream& LogFile::operator<<(char c[])
	{
		out << c;
		return out;
	}

	std::ofstream& LogFile::operator<<(std::string s)
	{
		out << s;
		return out;
	}

	std::ofstream& LogFile::operator<<(double d)
	{
		out << d;
		return out;
	}

	std::ofstream& LogFile::operator<<(float f)
	{
		out << f;
		return out;
	}

	std::ofstream& LogFile::operator<<(int i)
	{
		out << i;
		return out;
	}

	std::ofstream& LogFile::operator<<(bool b)
	{
		if (b)
			out << "True";
		else
			out << "False";
		return out;
	}
}