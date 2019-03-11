/******************************************************************************************************************************************************************************************
File Name:  ErrorLogManager.cpp
Author(s):  Yohaan Mohan
         
All content © 2015 DigiPen (USA) Corporation, all rights reserved
******************************************************************************************************************************************************************************************/
#include "Advanced2D.h"

namespace GAM200
{
	cErrorLogManager cErrorLogManager::m_ErrorManager;

	//------------------------------------------------------------------------

	//cException

	//------------------------------------------------------------------------

	cException::cException(int ErrorNumber, std::string ErrorDesc, std::string SrcFileName, int LineNumber)
	{
		p_ErrorNumber = ErrorNumber;
		p_ErrorDesc = ErrorDesc;
		p_SrcFilename = SrcFileName;
		p_LineNumber = LineNumber;

		std::stringstream ErrStr;

		ErrStr << "Error Num: " << p_ErrorNumber << "\nError Desc: " << p_ErrorDesc << "\nSrc File: "
			<< p_SrcFilename << "\nLine Number: " << p_LineNumber << "\n";

		p_ErrText = ErrStr.str();
	}

	//------------------------------------------------------------------------

	const char* cException::what()
	{
		return p_ErrText.c_str();
	}

	//------------------------------------------------------------------------

	//cErrorLogManager

	//------------------------------------------------------------------------

	cErrorLogManager::cErrorLogManager()
	{
	}

	//------------------------------------------------------------------------

	cErrorLogManager* cErrorLogManager::GetErrorManager()
	{
		return &m_ErrorManager;
	}

	//------------------------------------------------------------------------

	//Opens log file
	void cErrorLogManager::create(std::string Filename)
	{
		p_LogFile.open(Filename.c_str());
	}

	//------------------------------------------------------------------------

	//Commits information to file and clears text cache
	void cErrorLogManager::flush()
	{
		p_LogFile << p_LogBuffer.str();
		p_LogFile.flush();
		p_LogBuffer.str("");
	}

	//------------------------------------------------------------------------

	//Close log file
	void cErrorLogManager::close()
	{
		p_LogFile.close();
	}

	//------------------------------------------------------------------------

	void cErrorLogManager::logException(cException e)
	{
		p_LogBuffer << getTimeString() << "\n" << e.what();
		flush();
	}

	//------------------------------------------------------------------------

	//Gets current time as string in the form: hours:mins:secs
	std::string cErrorLogManager::getTimeString()
	{
		std::stringstream TimeStr;

		struct tm *pTime;
		time_t ctTime; time(&ctTime);
		pTime = localtime(&ctTime);

		TimeStr << std::setw(2) << std::setfill('0') << pTime->tm_hour << ":";
		TimeStr << std::setw(2) << std::setfill('0') << pTime->tm_min << ":";
		TimeStr << std::setw(2) << std::setfill('0') << pTime->tm_sec;

		return TimeStr.str();
	}

	//------------------------------------------------------------------------
}
