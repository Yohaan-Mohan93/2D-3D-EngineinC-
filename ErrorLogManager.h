/******************************************************************************************************************************************************************************************
File Name:  ErrorLogManager.h
Author(s):  Yohaan Mohan 
         
All content © 2015 DigiPen (USA) Corporation, all rights reserved
******************************************************************************************************************************************************************************************/
#ifndef _ERRORLOGMANAGER_H
#define _ERRORLOGMANAGER_H

#include "Advanced2D.h"

#ifndef THROW_EXCEPTION
#define THROW_EXCEPTION(ErrorNum, ErrorDesc) throw cException(ErrorNum, ErrorDesc, __FILE__, __LINE__ );
#endif

namespace GAM200
{
	//Custom Exception Class

	class cException : public std::exception
	{
	public:
		int p_ErrorNumber;
		std::string p_ErrorDesc;
		std::string p_SrcFilename;
		int p_LineNumber;
		std::string p_ErrText;

		const char* what();
		cException(int ErrorNumber, std::string ErrorDesc, std::string SrcFileName, int LineNumber);
		~cException() throw() {}
	};

	//Singleton Logging Object

	class cErrorLogManager
	{
	public:
		static cErrorLogManager * GetErrorManager();
		cErrorLogManager();
		~cErrorLogManager() {}
		static cErrorLogManager m_ErrorManager;

	public:
		std::stringstream p_LogBuffer;
		void create(std::string Filename);
		void flush();
		void close();
		void logException(cException e);
		std::string getTimeString();
		std::ofstream p_LogFile;
	};
}

#endif
