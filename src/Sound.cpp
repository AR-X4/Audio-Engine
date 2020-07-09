
#include "CircularData.h"
#include "SoundManager.h"
#include "Sound.h"

#include "PlaySoundCommand.h"
#include "StopSoundCommand.h"
#include "SetVolumeCommand.h"
#include "SetPanCommand.h"
#include "PrintPlayTimeCommand.h"
#include "TimeEventManager.h"


Sound::Sound()
	: ID(SoundId::UNINITIALIZED), pASound(nullptr), Volume(1.0f), 
	Pan(0.0f), Priority(0u), StartTime(Time(Duration::TIME_ZERO)), 
	pPriorityNext(nullptr), pPriorityPrev(nullptr), handle()
{

}

Sound::Sound(const Sound& tmp)

{
	this->ID = tmp.ID;
	this->pASound = tmp.pASound;
	this->Volume = tmp.Volume;
	this->Pan = tmp.Pan;

}

Sound& Sound::operator=(const Sound& tmp)
{
	// QUESTION: copy handle?  --> I say NO, its the data not the handle
	//           to prevent anyone, I deleted the copy operator in handle
	//           this->handle = r.handle;   <----- I say its a no no

	this->ID = tmp.ID;
	this->pASound = tmp.pASound;
	this->Volume = tmp.Volume;
	this->Pan = tmp.Pan;

	return *this;
}

Sound::~Sound()
{
	

}

const Handle::Status Sound::Play(Time TriggTime)
{
	Handle::Lock lock(this->handle);
	if (lock)
	{
		

		Message* pMsg = new PlaySoundCommand(this, TriggTime);

		SoundManager::SendAudioCommand(pMsg);
	
	}
	else {
		//assert(false);
	}
	return lock;
}

const Handle::Status Sound::Stop(Time TriggTime)
{
	Handle::Lock lock(this->handle);

	if (lock)
	{
		Message* pMsg = new StopSoundCommand(this, TriggTime);

		SoundManager::SendAudioCommand(pMsg);
	}
	return lock;
}

const Handle::Status Sound::SetVolume(const float VolumeIn)
{
	Handle::Lock lock(this->handle);

	if (lock)
	{
		this->Volume = VolumeIn;
	}
	return lock;
}

const Handle::Status Sound::SetPan(const float PanIn)
{
	Handle::Lock lock(this->handle);

	if (lock)
	{
		this->Pan = PanIn;
	}
	return lock;
}

const Handle::Status Sound::NewPan(const float PanIn, Time TriggTime)
{
	Handle::Lock lock(this->handle);
	if (lock)
	{
		Message* pMsg = new SetPanCommand(this, TriggTime, PanIn);

		SoundManager::SendAudioCommand(pMsg);
	}
	return lock;
	
}

const Handle::Status Sound::NewVolume(const float VolIn, Time TriggTime)
{
	Handle::Lock lock(this->handle);
	if (lock)
	{
		Message* pMsg = new SetVolumeCommand(this, TriggTime, VolIn);

		SoundManager::SendAudioCommand(pMsg);
	}
	return lock;
	
}

const Handle::Status Sound::PrintPlayTime(Time TriggTime)
{
	Handle::Lock lock(this->handle);
	if (lock)
	{
		Message* pMsg = new PrintPlayTimeCommand(this, TriggTime);

		SoundManager::SendAudioCommand(pMsg);
	}
	return lock;
}

SoundId& Sound::GetID()
{
	return this->ID;
}

const Handle::Status Sound::GetVolume(float& VolIn) {
	Handle::Lock lock(this->handle);

	if (lock)
	{
		VolIn = this->Volume;
	}
	return lock;
}

const Handle::Status Sound::GetPan(float& PanIn) {
	Handle::Lock lock(this->handle);

	if (lock)
	{
		PanIn = this->Pan;
	}
	return lock;
}

void Sound::SetASound(ASound* pIn)
{
	assert(pIn != nullptr);
	this->pASound = pIn;
}

int Sound::GetHandleID()
{

	return this->handle.GetID();
}

ASound* Sound::GetASound()
{
	assert(this->pASound != nullptr);
	return this->pASound;
}

void Sound::Set(SoundId IDIn, int SoundPriority)
{
	this->ID = IDIn;
	this->Priority = SoundPriority;
}

void Sound::Dump()
{
	Trace::out("   Name: %d (%p) \n", this->ID, this);
}

void Sound::Wash()
{
	this->ID = SoundId::UNINITIALIZED;
	this->pASound = nullptr;
	this->Volume = 1.0f;
	this->Pan = 0.0f;
	this->Priority = 0;
	this->StartTime = Time(Duration::TIME_ZERO);
	this->pPriorityNext = nullptr;
	this->pPriorityPrev = nullptr;

}





//Handle::Status Sound::GetTimeInMS(int& timeInMS)
//{
//	Handle::Lock lock(this->handle);
//	if (lock)
//	{
//		// table lock
//		Handle::Lock tableLock(SoundManager::table_handle);
//
//		// Check Priority table
//		if (tableLock)
//		{
//			bool status = false;
//			for (unsigned int i = 0; i < SoundManager::SOUND_PRIORITY_TABLE_SIZE; i++)
//			{
//				if (SoundManager::SoundPriorityTable[i].handleID == this->handle.GetID())
//				{
//					Time delta = (TimeEventManager::GetTimeCurrent()) - SoundManager::SoundPriorityTable[i].startTime;
//
//					timeInMS = Time::quotient(delta, Time(Duration::TIME_ONE_MILLISECOND));
//
//					status = true;
//					break;
//				}
//			}
//
//			if (!status)
//			{
//				assert(false);
//			}
//		}
//		else
//		{
//			assert(false);
//		}
//	}
//
//	return lock;
//}

void Sound::SetPriorityNext(Sound* pSoundIn)
{
	this->pPriorityNext = pSoundIn;
}

void Sound::SetPriorityPrev(Sound* pSoundIn)
{
	this->pPriorityPrev = pSoundIn;
}

Sound* Sound::GetPriorityNext()
{
	return this->pPriorityNext;
}

Sound* Sound::GetPriorityPrev()
{
	return this->pPriorityPrev;
}

void Sound::StartTimer()
{
	this->StartTime = TimeEventManager::GetTimeCurrent();
}

int Sound::GetPlayTime()
{
	Time CurrentTime = TimeEventManager::GetTimeCurrent() - this->StartTime;

	return Time::quotient(CurrentTime, Time(Duration::TIME_ONE_MILLISECOND));
}

unsigned int Sound::GetPriority() const
{
	return this->Priority;
}



// End of File 
