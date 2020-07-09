#include "FileCallback.h"
#include "SoundManager.h"

FileCallback::FileCallback()
	:pWaveName("Uninitialized")
{
}

FileCallback::~FileCallback()
{
}

void FileCallback::Set(const char* const pName)
{
	assert(pName != nullptr);

	memcpy_s(this->pWaveName, 256u, pName, strlen(pName));
	
}

void FileCallback::Execute()
{
	//print name of file loaded
	Trace::out("Loaded %s\n\n", this->pWaveName);


	SoundManager::CreateScript(SoundId::BEETHOVEN_ID);
	SoundManager::AddToScriptFront(SoundId::BEETHOVEN_ID, SoundId::BEETHOVEN_ID);

	Sound* SndC = SoundManager::CreateSound(SoundId::BEETHOVEN_ID);

	Handle::Status Status;
	Status = SndC->NewVolume(0.5f, Time());
	assert(Handle::Status::SUCCESS == Status);

	Status = SndC->Play(Time());
	assert(Handle::Status::SUCCESS == Status);

	//Stop Electro
	Sound* SndA = SoundManager::FindSound(SoundId::ELECTRO_ID);

	Status = SndA->Stop(Time());
	assert(Handle::Status::SUCCESS == Status);


	Status = SndC->Stop(Time(Duration::TIME_ONE_MINUTE));
	assert(Handle::Status::SUCCESS == Status);
}

//void FileCallback::OnFileLoaded()
//{
//	//print name of file loaded
//	Trace::out("Loaded %s\n", this->pWaveName);
//	
//
//	SoundManager::CreateScript(SoundId::BEETHOVEN_ID);
//	SoundManager::AddToScriptFront(SoundId::BEETHOVEN_ID, SoundId::BEETHOVEN_ID);
//
//	Sound* pSound = SoundManager::CreateSound(SoundId::BEETHOVEN_ID);
//
//	Handle::Status Status;
//	Status = pSound->NewVolume(0.5f, Time());
//	assert(Handle::Status::SUCCESS == Status);
//
//	Status = pSound->Play(Time());
//	assert(Handle::Status::SUCCESS == Status);
//
//	//Stop Electro
//
//	Status = pSound->Stop(Time(Duration::TIME_ONE_MINUTE));
//	assert(Handle::Status::SUCCESS == Status);
//}
