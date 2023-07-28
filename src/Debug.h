#pragma once
#include <fstream>

using namespace std;

class Debug
{
public:
    // Constructor
    Debug();

    // Destructor
    ~Debug();

public:
    // Static method to initialize the logging functionality with a given file name.
    // Should be called before using the 'Log' methods.
    static void init(string fileName);

    // Static method to close the log file and clean up resources.
    // Should be called when logging is no longer needed.
    static void close();

    // Static method to log a message (string) to the log file.
    static void Log(string logMessage);

    // Static method to log a wide string message (wstring) to the log file.
    static void Log(wstring logMessage);

    // Static method to log a message (string) and an integer value to the log file.
    static void Log(string logMessage, int value);

    // Static method to log a message (string) and a floating-point value to the log file.
    static void Log(string logMessage, float value);

    // Static ofstream object to write to the log file.
    static ofstream _log;

    // Static boolean flag to keep track of whether the logging functionality has been initialized.
    static bool initiated;
};