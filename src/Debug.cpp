#include "Debug.h"

// Initialize the static member variables of the class.
bool Debug::initiated = false;
ofstream Debug::_log;

// Constructor
Debug::Debug()
{
}

// Destructor
Debug::~Debug()
{
}

// Static method to initialize the logging functionality with a given file name.
// It opens the log file and sets the 'initiated' flag accordingly.
void Debug::init(string fileName)
{
	_log.open(fileName);		// Open the file with the provided 'fileName'
	initiated = _log.is_open(); // Update 'initiated' to indicate if the file was successfully opened.
}

// Static method to close the log file and clean up resources.
void Debug::close()
{
	_log.close();
}

// Static method to log a message (string) to the log file.
void Debug::Log(string logMessage)
{
	if (initiated)
	{
		_log << logMessage.data() << endl;	// Write the log message to the log file.
		_log.flush();						// Flush the output to ensure the message is written immediately.
	}
}

// Static method to log a message (wstring) to the log file.
void Debug::Log(wstring logMessage)
{
	if (initiated)
	{
		// Convert the std::wstring to UTF-8 encoded std::string
    	std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;
    	std::string utf8Message = converter.to_bytes(logMessage);

    	// Now you can write the UTF-8 encoded std::string to the std::wofstream
   		_log << utf8Message << std::endl;

		_log.flush();						// Flush the output to ensure the message is written immediately.
	}
}

// Static method to log a message (string) and an integer value to the log file.
void Debug::Log(string logMessage, int value)
{
	if (initiated) {
		_log << logMessage.data() << value << endl; // Write the log message and the integer value to the log file.
		_log.flush(); // Flush the output to ensure the message is written immediately.
	}
}

// Static method to log a message (string) and a floating-point value to the log file.
void Debug::Log(string logMessage, float value)
{
	if (initiated) {
		_log << logMessage.data() << value << endl; // Write the log message and the floating-point value to the log file.
		_log.flush(); // Flush the output to ensure the message is written immediately.
	}
}