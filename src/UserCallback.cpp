#include "UserCallBack.h"

UserCallback::UserCallback(char* WaveNameIn)
	:pSound(nullptr), pWaveName(WaveNameIn)
{
}

UserCallback::~UserCallback()
{
}

void UserCallback::Set(Sound* _pSnd)
{
	assert(_pSnd);
	this->pSound = _pSnd;
	
}

//void UserCallback::OnSoundEnd()
//{
//	assert(this->pSound);
//	assert(this->pWaveName);
//
//	Trace::out("------------------------------\n");
//	Trace::out("  UserCallback() \n");
//
//	SoundId id;
//	this->pSound->GetID(id);
//
//	Trace::out("      SndID: %d \n", id);
//
//	int timeInMS;
//	this->pSound->GetTimeInMS(timeInMS);
//	Trace::out("       Time: %d ms \n", timeInMS);
//
//	float pan;
//	this->pSound->GetPan(pan);
//	Trace::out("        Pan: %f  \n", pan);
//
//	Trace::out("       Wave: %s  \n", this->pWaveName);
//
//	Trace::out("------------------------------\n");
//}

void UserCallback::Execute()
{
	assert(this->pSound);
	assert(this->pWaveName);

	Trace::out("------------------------------\n");
	Trace::out("  UserCallback() \n");

	//SoundId id;
	//this->pSound->GetID(id);

	Trace::out("      SndID: %d \n", this->pSound->GetID());

	//int timeInMS;
	//this->pSound->GetTimeInMS(timeInMS);
	Trace::out("       Time: %d ms \n", this->pSound->GetPlayTime());

	float pan;
	this->pSound->GetPan(pan);
	Trace::out("        Pan: %f  \n", pan);

	Trace::out("       Wave: %s  \n", this->pWaveName);

	Trace::out("------------------------------\n");

	//kill sound
	this->pSound->Stop(Time());
}


