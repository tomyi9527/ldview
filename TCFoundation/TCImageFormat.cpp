#include "TCImageFormat.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef WIN32
#include <unistd.h>
#endif // WIN32

TCImageFormat::TCImageFormat(void)
			  :name(NULL)
{
#ifdef _LEAK_DEBUG
	strcpy(className, "TCImageFormat");
#endif
}

TCImageFormat::~TCImageFormat(void)
{
}

void TCImageFormat::dealloc(void)
{
	TCObject::dealloc();
}

bool TCImageFormat::checkSignature(const char *filename)
{
	FILE *file = fopen(filename, "rb");
	bool retValue = false;

	if (file)
	{
		retValue = checkSignature(file);
		fclose(file);
	}
	return retValue;
}

bool TCImageFormat::loadFile(TCImage *image, const char *filename)
{
	FILE *file = fopen(filename, "rb");
	bool retValue = false;

	if (file)
	{
		retValue = loadFile(image, file);
		fclose(file);
	}
	return retValue;
}

bool TCImageFormat::saveFile(TCImage *image, const char *filename,
							 TCImageProgressCallback progressCallback,
							 void *progressUserData)
{
	FILE *file = fopen(filename, "wb");
	bool retValue = false;

	if (file)
	{
		retValue = saveFile(image, file, progressCallback, progressUserData);
		fclose(file);
		if (!retValue)
		{
			unlink(filename);
		}
	}
	return retValue;
}

bool TCImageFormat::callProgressCallback(TCImageProgressCallback
										 progressCallback,
										 CUCSTR message, float progress,
										 void *progressUserData)
{
	if (progressCallback)
	{
		return progressCallback(message, progress, progressUserData);
	}
	else
	{
		return true;
	}
}
