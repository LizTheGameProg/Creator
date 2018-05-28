#pragma once

namespace LSL
{
	//class String;
	class File
	{
	public:
		//--------------------------------
		// Constructors/Destructor
		//--------------------------------
		//File(String * fileName);
		~File();
		//void Write(String * toWrite);
		//void Write(char * toWrite);
		void ReadFile();
	private:
		File();


		//--------------------------------
		// Variables
		//--------------------------------
		//FILE	* file;
		//String	* fileName;
		//String	* fileContents;
		int		  fileSize;
	};
}