//#pragma once
//
//#ifdef STANDARD_EXPORTS
//#	define STANDARD_API __declspec(dllexport)
//#else
//#	define STANDARD_API __declspec(dllimport)
//#endif
//
//namespace LSL
//{
//	class STANDARD_API String
//	{
//	public:
//		// Constructor
//		String();
//		// Constructor that takes in a char array
//		String(char * string);
//		// Copy constructor
//		String(const String & other);
//		// Move constructor
//		String(String && other);
//		// Destructor
//		~String();
//		// Copy assignment: leaves a copy there
//		String & operator = (const String & other);
//		// Move assignment: moves the data from other
//		String & operator = (String && other);
//		// + operator: returns a string that contains the two strings
//		String operator + (const String & other) const;
//		// += operator: adds the other string to this string
//		String & operator += (const String & other);
//		// == operator: returns true if the two strings are the same
//		bool operator == (const String & other);
//		// != operator: returns true if the two strings are different
//		bool operator != (const String & other);
//		// [] operator: access a character at a certain index
//		char& operator[](const unsigned int index);
//
//		// Returns the current length of the String
//		const unsigned int GetLength() const;
//		// Returns the beginning of the string as a char pointer
//		char * GetString() const;
//
//		// Set the string
//		void SetString(const char * string);
//		// Resize the array
//		void Resize(const unsigned int size = 32);
//
//		// Get Input from the console window
//		void ReadFromConsole();
//		// Write out to the console
//		void WriteToConsole();
//
//		// Write out to the console
//		static void WriteToConsole(char * outPut);
//
//	private:
//		// Recalculate the length of the string
//		void UpdateLength();
//
//		void Copy(char * destination = nullptr, const unsigned int destinationSize = 0, const char * source = nullptr, const unsigned int sourceSize = 0);
//
//		char * m_charArray;
//
//		unsigned int m_length;
//	};
//}