#include <iostream>

#include "main.h"

std::string sourceDirectory;
std::string targetDirectory;

void run()
{
	namespace fs = std::filesystem;

	// Casts path to string
	fs::path sourceFiles = sourceDirectory;
	fs::path targetLocation = targetDirectory;

	try // If you want to avoid exception handling, then use the error code overload of the following functions.
	{
		fs::create_directories(targetLocation); // Recursively create target directory if not existing.

		for (auto& p : fs::directory_iterator(sourceDirectory)) // Loop through each existing file from the source directory.
		{
			colorGreen;
			fs::copy(p.path(), targetLocation, fs::copy_options::overwrite_existing);
			printf_s("Copied %ls\n", p.path().c_str());
		}
	}
	catch (std::exception& e) // Not using fs::filesystem_error since std::bad_alloc can throw too.  
	{
		colorRed;
		printf("%s", e.what());
	}

	colorWhite;
}

int main(int argc, char* argv[], int, char**)
{
	// Loop through all console arguments
	for (int i = 0; i < argc; i++)
	{

		if (strncmp(argv[i], "-source=", 8) == 0)
		{
			std::string tmp = argv[i];
			int eqpos = tmp.find('=');
			sourceDirectory = tmp.substr(eqpos + 1);

			/* debug */
#ifndef NDEBUG
			printf_s("Source Directory: %s\n", sourceDirectory.c_str());
#endif
		}

		if (strncmp(argv[i], "-target=", 8) == 0)
		{
			std::string tmp = argv[i];
			int eqpos = tmp.find('=');
			targetDirectory = tmp.substr(eqpos + 1);

			/* debug */
#ifndef NDEBUG
			printf_s("Target Directory: %s\n\n", targetDirectory.c_str());
#endif
		}

		if (strcmp(argv[i], "-hide") == 0)
		{
			::ShowWindow(::GetConsoleWindow(), SW_HIDE);
		}

		if (strcmp(argv[i], "-build") == 0)
		{
			char buff[100];
			std::string buildDate = __DATE__;
			std::string buildTime = __TIME__;
			sprintf_s(buff, "built %s at %s.", buildDate.c_str(), buildTime.c_str());
			MessageBox(0, buff, "\n", MB_OK | MB_ICONINFORMATION);
			return 0;
		}
	}

	run();

	return 0;
}