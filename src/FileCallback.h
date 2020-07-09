#ifndef USER_FILEBACK_H
#define USER_FILEBACK_H

//#include "Sound.h"
#include "Message.h"

class FileCallback : public Message
{
public:

	FileCallback();
	FileCallback(const FileCallback&) = delete;
	FileCallback& operator = (const FileCallback&) = delete;
	~FileCallback();


	void Set(const char* const pName);
	void Execute() override;

	//void OnFileLoaded();


private:
	char pWaveName[256u];
	
};

#endif


