#include "File.h"
#include "String.h"

namespace LSL
{
	//File::File(String * a_fileName)
	//{
	//	// Copy over the fileName
	//	fileName = a_fileName;
	//
	//	// if there is an error
	//	errno_t error;
	//
	//	// Open the file for update
	//	error = fopen_s(&file, fileName->GetString(), "r+");
	//
	//	// If the file was not opened
	//	if(file == nullptr)
	//	{
	//		// then it's not there, let's create it
	//		error = fopen_s(&file, fileName->GetString(), "w+");
	//	}
	//
	//	fseek(file, 0, SEEK_END);
	//	fileSize = ftell(file);
	//	fseek(file, 0, SEEK_SET);
	//
	//	fileContents = new LSL::String();
	//	fileContents->Resize((unsigned int)fileSize);
	//}

	File::~File()
	{
		//fclose(file);
		//delete fileName;
		//if(fileContents != nullptr)
		//{
		//	delete fileContents;
		//	fileContents = nullptr;
		//}
	}

	File::File()
	{

	}

	void File::ReadFile()
	{
		//fread(fileContents->GetString(), sizeof(char), fileContents->GetLength(), file);
		//(*fileContents)[(unsigned int)fileSize] = 0;
	}
}