#include "AudioThread.h"
#include "FileThread.h"
#include "XAudio2Manager.h"
#include "SoundCallRegistry.h"
#include "BufferManager.h"
#include "PlaylistManager.h"
#include "ASoundManager.h"
#include "VoiceManager.h"
#include "ScriptManager.h"
#include "TimeEventManager.h"
#include "Message.h"
#include "SoundManager.h"


void Audio_Main(bool& KillSwitch)
{


	//---------------------------------------
	//----------Create Managers------------
	//---------------------------------------

	XAudio2Manager::  Create();
	ASoundManager::   Create();
	PlaylistManager:: Create();
	ScriptManager::	  Create();
	VoiceManager::	  Create();
	BufferManager::	  Create();
	TimeEventManager::Create();


	//Create File Thread
	std::thread FileThread(File_Main, std::ref(KillSwitch));
	FileThread.detach();

	//so waves can pre load in file thread
	std::this_thread::sleep_for(std::chrono::seconds(1));


	//-----------------------------------
	//----------Audio Main Loop----------
	//-----------------------------------
	while (KillSwitch) {
	

		Message* Msg;
		
		if (SoundManager::GetG2A()->PopFront(Msg))
		{
			TimeEventManager::Add(Msg, Msg->GetTriggerTime());
		}
		TimeEventManager::Update();
		ASoundManager::Update();// check callback for buffer switch

		
		std::this_thread::sleep_for(std::chrono::milliseconds(1));

	}

	//---------------------------------------
	//----------Destory Managers------------
	//---------------------------------------

	TimeEventManager::Destroy();
	ScriptManager::	  Destroy();
	VoiceManager::	  Destroy();
	PlaylistManager:: Destroy();
	BufferManager::	  Destory();
	ASoundManager::	  Destroy();
	XAudio2Manager::  Destroy();
	

	Trace::out("--->Audio Thread Killed\n\n");
}


