#ifndef USER_CALLBACK_H
#define USER_CALLBACK_H

#include "Sound.h"
#include "Message.h"

class UserCallback : public Message
{
public:

	UserCallback() = delete;
	UserCallback(char* WaveNameIn);
	UserCallback(const UserCallback&) = delete;
	UserCallback& operator = (const UserCallback&) = delete;
	~UserCallback();


	void Set(Sound* _pSnd);
	void Execute() override;

	//void OnSoundEnd();


private:
	Sound* pSound;
	char* pWaveName;
};

#endif


