#include "Demo.h"
#include "SoundManager.h"
#include "FileCallback.h"

void Demo1()
{
	//-----Part-A-----
	Sound* pFiddle = SoundManager::CreateSound(SoundId::FIDDLE_ID);
	Sound* pFiddle2 = SoundManager::CreateSound(SoundId::FIDDLE_ID);
	Sound* pFiddle3 = SoundManager::CreateSound(SoundId::FIDDLE_ID);

	Sound* pBassoon = SoundManager::CreateSound(SoundId::BASSOON_ID);
	Sound* pBassoon2 = SoundManager::CreateSound(SoundId::BASSOON_ID);
	Sound* pBassoon3 = SoundManager::CreateSound(SoundId::BASSOON_ID);
	Sound* pBassoon4 = SoundManager::CreateSound(SoundId::BASSOON_ID);
	Sound* pBassoon5 = SoundManager::CreateSound(SoundId::BASSOON_ID);
	
	Sound* pOboe = SoundManager::CreateSound(SoundId::OBOE2_ID);
	Sound* pOboe2 = SoundManager::CreateSound(SoundId::OBOE2_ID);
	Sound* pSongA = SoundManager::CreateSound(SoundId::SONGA_ID);
	Sound* pSongB = SoundManager::CreateSound(SoundId::SONGB_ID);

	////-----Part-B-----
	assert(Handle::Status::SUCCESS == pFiddle->NewPan(0.0f, Time()));
	pFiddle->Play(Time());

	assert(Handle::Status::SUCCESS == pFiddle2->NewPan(-1.0f, Time(Duration::TIME_ONE_SECOND) * 3));
	pFiddle2->Play(Time(Duration::TIME_ONE_SECOND) * 3);

	assert(Handle::Status::SUCCESS == pFiddle3->NewPan(1.0f, Time(Duration::TIME_ONE_SECOND) * 6));
	pFiddle3->Play(Time(Duration::TIME_ONE_SECOND) * 6);


	//-----Part-C-----
	assert(Handle::Status::SUCCESS == pBassoon->NewPan(-1.0f, Time(Duration::TIME_ONE_SECOND) * 10));
	assert(Handle::Status::SUCCESS == pBassoon->Play(Time(Duration::TIME_ONE_SECOND) * 10));

	float pan = -1.0f;
	for (int i = 1; i < 20; i++) {
		pan += 0.1f;
		assert(Handle::Status::SUCCESS == pBassoon->NewPan(pan, (Time(Duration::TIME_ONE_SECOND) * 10) + (Time(Duration::TIME_ONE_MILLISECOND) * (i*100))));
	}

	//-----Part-D-----
	assert(Handle::Status::SUCCESS == pOboe->NewVolume(0.0f, Time(Duration::TIME_ONE_SECOND) * 20));
	assert(Handle::Status::SUCCESS == pOboe->Play(Time(Duration::TIME_ONE_SECOND) * 20));

	float vol = 0.0f;
	for (int i = 1; i < 11; i++) {
		vol += 0.1f;
		assert(Handle::Status::SUCCESS == pOboe->NewVolume(vol, (Time(Duration::TIME_ONE_SECOND) * 20) + (Time(Duration::TIME_ONE_MILLISECOND) * (i * 200))));
	}

	assert(Handle::Status::SUCCESS == pOboe2->Play(Time(Duration::TIME_ONE_SECOND) * 25));
	for (int i = 1; i < 11; i++) {
		vol -= 0.1f;
		assert(Handle::Status::SUCCESS == pOboe2->NewVolume(vol, (Time(Duration::TIME_ONE_SECOND) * 25) + (Time(Duration::TIME_ONE_MILLISECOND) * (i * 200))));
	}

	//-----Part-E-----
	assert(Handle::Status::SUCCESS == pSongA->NewPan(-1.0f, Time(Duration::TIME_ONE_SECOND) * 30));
	assert(Handle::Status::SUCCESS == pSongA->Play(Time(Duration::TIME_ONE_SECOND) * 30));

	assert(Handle::Status::SUCCESS == pSongB->NewPan(1.0f, Time(Duration::TIME_ONE_SECOND) * 30));
	assert(Handle::Status::SUCCESS == pSongB->Play(Time(Duration::TIME_ONE_SECOND) * 30));

	assert(Handle::Status::SUCCESS == pSongA->PrintPlayTime(Time(Duration::TIME_ONE_SECOND) * 35));
	assert(Handle::Status::SUCCESS == pSongA->PrintPlayTime(Time(Duration::TIME_ONE_SECOND) * 38));
	assert(Handle::Status::SUCCESS == pSongA->PrintPlayTime(Time(Duration::TIME_ONE_MINUTE)));
	assert(Handle::Status::SUCCESS == pSongA->Stop(Time(Duration::TIME_ONE_MINUTE)));

	assert(Handle::Status::SUCCESS == pSongB->PrintPlayTime(Time(Duration::TIME_ONE_SECOND) * 72));
	assert(Handle::Status::SUCCESS == pSongB->Stop(Time(Duration::TIME_ONE_SECOND) * 72));

	//-----Part-F-----
	
	
	assert(Handle::Status::SUCCESS == pBassoon2->NewVolume(0.8f, (Time(Duration::TIME_ONE_SECOND) * 80)));
	assert(Handle::Status::SUCCESS == pBassoon2->NewPan(0.0f, (Time(Duration::TIME_ONE_SECOND) * 80)));
	assert(Handle::Status::SUCCESS == pBassoon2->Play(Time(Duration::TIME_ONE_SECOND) * 80));
	
	assert(Handle::Status::SUCCESS == pBassoon3->NewVolume(0.8f, (Time(Duration::TIME_ONE_SECOND) * 80) + Time(Duration::TIME_ONE_MILLISECOND) * 500));
	assert(Handle::Status::SUCCESS == pBassoon3->Play((Time(Duration::TIME_ONE_SECOND) * 80) + Time(Duration::TIME_ONE_MILLISECOND) * 500));
	
	assert(Handle::Status::SUCCESS == pBassoon4->NewVolume(0.8f, (Time(Duration::TIME_ONE_SECOND) * 81)));
	assert(Handle::Status::SUCCESS == pBassoon4->Play(Time(Duration::TIME_ONE_SECOND) * 81));

	assert(Handle::Status::SUCCESS == pBassoon5->NewVolume(0.8f, (Time(Duration::TIME_ONE_SECOND) * 81) + Time(Duration::TIME_ONE_MILLISECOND) * 500));
	assert(Handle::Status::SUCCESS == pBassoon5->Play((Time(Duration::TIME_ONE_SECOND) * 81) + Time(Duration::TIME_ONE_MILLISECOND) * 500));
	
	assert(Handle::Status::SUCCESS == pBassoon2->Stop((Time(Duration::TIME_ONE_SECOND) * 81) + Time(Duration::TIME_ONE_MILLISECOND) * 500));
	assert(Handle::Status::SUCCESS == pBassoon3->Stop((Time(Duration::TIME_ONE_SECOND) * 81) + Time(Duration::TIME_ONE_MILLISECOND) * 500));
	assert(Handle::Status::SUCCESS == pBassoon4->Stop((Time(Duration::TIME_ONE_SECOND) * 81) + Time(Duration::TIME_ONE_MILLISECOND) * 500));

}

void Demo2()
{

	Sound* pDemo2Snd = SoundManager::CreateSound(SoundId::DEMO_2_ID, 0);
	assert(Handle::Status::SUCCESS == pDemo2Snd->Play(Time()));

	//Pan Center, Volume 80%
	assert(Handle::Status::SUCCESS == pDemo2Snd->NewVolume(0.8f, Time()));

	//Pan Right
	assert(Handle::Status::SUCCESS == pDemo2Snd->NewPan(1.0f, Time(Duration::TIME_ONE_SECOND) * 10));
	
	//Pan Left
	assert(Handle::Status::SUCCESS == pDemo2Snd->NewPan(-1.0f, Time(Duration::TIME_ONE_SECOND) * 20));
	
	//Pan Center
	assert(Handle::Status::SUCCESS == pDemo2Snd->NewPan(0.0f, Time(Duration::TIME_ONE_SECOND) * 30));
	
	//Pan Right
	assert(Handle::Status::SUCCESS == pDemo2Snd->NewPan(1.0f, Time(Duration::TIME_ONE_SECOND) * 40));
	

}

void Demo3()
{
	Handle::Status Status;

	//---Play sound A at 0 Sec---
	Sound* Snd_A = SoundManager::CreateSound(SoundId::COMA_ID, nullptr, 10);

	Status = Snd_A->NewVolume(0.1f, Time());
	assert(Handle::Status::SUCCESS == Status);

	Status = Snd_A->Play(Time());
	assert(Handle::Status::SUCCESS == Status);

	//---Play sound B at 0 Sec---
	Sound* Snd_B = SoundManager::CreateSound(SoundId::COMA_ID, nullptr, 50);

	Status = Snd_B->NewVolume(0.1f, Time());
	assert(Handle::Status::SUCCESS == Status);

	Status = Snd_B->Play(Time());
	assert(Handle::Status::SUCCESS == Status);

	//---Play sound C at 0 Sec---
	Sound* Snd_C = SoundManager::CreateSound(SoundId::COMA_ID, nullptr, 150);

	Status = Snd_C->NewVolume(0.1f, Time());
	assert(Handle::Status::SUCCESS == Status);

	Status = Snd_C->Play(Time());
	assert(Handle::Status::SUCCESS == Status);

	//---Print Priority Table---
	SoundManager::PrintPriority(Time());

	//---Play sound D at 1 Sec---
	Sound* Snd_D = SoundManager::CreateSound(SoundId::COMA_ID, nullptr, 50);

	Status = Snd_D->NewVolume(0.1f, Time(Duration::TIME_ONE_SECOND));
	assert(Handle::Status::SUCCESS == Status);

	Status = Snd_D->Play(Time(Duration::TIME_ONE_SECOND) );
	assert(Handle::Status::SUCCESS == Status);

	//---Print Priority Table---
	SoundManager::PrintPriority(Time(Duration::TIME_ONE_SECOND) + Time(Duration::TIME_ONE_MILLISECOND) * 10);

	//---Play sound E at 2 Sec---
	Sound* Snd_E = SoundManager::CreateSound(SoundId::COMA_ID, nullptr, 75);

	Status = Snd_E->NewVolume(0.1f, Time(Duration::TIME_ONE_SECOND) * 2);
	assert(Handle::Status::SUCCESS == Status);

	Status = Snd_E->Play(Time(Duration::TIME_ONE_SECOND) * 2);
	assert(Handle::Status::SUCCESS == Status);

	//---Print Priority Table---
	SoundManager::PrintPriority(Time(Duration::TIME_ONE_SECOND) * 2 + Time(Duration::TIME_ONE_MILLISECOND) * 10);

	//---Play sound F at 3 Sec---
	Sound* Snd_F = SoundManager::CreateSound(SoundId::COMA_ID, nullptr, 100);

	Status = Snd_F->NewVolume(0.1f, Time(Duration::TIME_ONE_SECOND) * 3);
	assert(Handle::Status::SUCCESS == Status);

	Status = Snd_F->Play(Time(Duration::TIME_ONE_SECOND) * 3);
	assert(Handle::Status::SUCCESS == Status);

	//---Print Priority Table---
	SoundManager::PrintPriority(Time(Duration::TIME_ONE_SECOND) * 3 + Time(Duration::TIME_ONE_MILLISECOND) * 10);

	//---Play sound G at 4 Sec---
	Sound* Snd_G = SoundManager::CreateSound(SoundId::COMA_ID, nullptr, 150);

	Status = Snd_G->NewVolume(0.1f, Time(Duration::TIME_ONE_SECOND) * 4);
	assert(Handle::Status::SUCCESS == Status);

	Status = Snd_G->Play(Time(Duration::TIME_ONE_SECOND) * 4);
	assert(Handle::Status::SUCCESS == Status);

	//---Print Priority Table---
	SoundManager::PrintPriority(Time(Duration::TIME_ONE_SECOND) * 4 + Time(Duration::TIME_ONE_MILLISECOND) * 10);

	//---Play sound H at 5 Sec---
	Sound* Snd_H = SoundManager::CreateSound(SoundId::COMA_ID, nullptr, 75);

	Status = Snd_H->NewVolume(0.1f, Time(Duration::TIME_ONE_SECOND) * 5);
	assert(Handle::Status::SUCCESS == Status);

	Status = Snd_H->Play(Time(Duration::TIME_ONE_SECOND) * 5);
	assert(Handle::Status::SUCCESS == Status);

	//---Print Priority Table---
	SoundManager::PrintPriority(Time(Duration::TIME_ONE_SECOND) * 5 + Time(Duration::TIME_ONE_MILLISECOND) * 10);

	//---Play sound I at 6 Sec---
	Sound* Snd_I = SoundManager::CreateSound(SoundId::COMA_ID, nullptr, 75);

	Status = Snd_I->NewVolume(0.1f, Time(Duration::TIME_ONE_SECOND) * 6);
	assert(Handle::Status::SUCCESS == Status);

	Status = Snd_I->Play(Time(Duration::TIME_ONE_SECOND) * 6);
	assert(Handle::Status::SUCCESS == Status);

	//---Print Priority Table---
	SoundManager::PrintPriority(Time(Duration::TIME_ONE_SECOND) * 6 + Time(Duration::TIME_ONE_MILLISECOND) * 10);

	//---Play sound J at 7 Sec---
	Sound* Snd_J = SoundManager::CreateSound(SoundId::COMA_ID, nullptr, 75);

	Status = Snd_J->NewVolume(0.1f, Time(Duration::TIME_ONE_SECOND) * 7);
	assert(Handle::Status::SUCCESS == Status);

	Status = Snd_J->Play(Time(Duration::TIME_ONE_SECOND) * 7);
	assert(Handle::Status::SUCCESS == Status);

	//---Print Priority Table---
	SoundManager::PrintPriority(Time(Duration::TIME_ONE_SECOND) * 7 + Time(Duration::TIME_ONE_MILLISECOND) * 10);

	//---Play sound K at 8 Sec---
	Sound* Snd_K = SoundManager::CreateSound(SoundId::COMA_ID, nullptr, 150);

	Status = Snd_K->NewVolume(0.1f, Time(Duration::TIME_ONE_SECOND) * 8);
	assert(Handle::Status::SUCCESS == Status);

	Status = Snd_K->Play(Time(Duration::TIME_ONE_SECOND) * 8);
	assert(Handle::Status::SUCCESS == Status);

	//---Print Priority Table---
	SoundManager::PrintPriority(Time(Duration::TIME_ONE_SECOND) * 8 + Time(Duration::TIME_ONE_MILLISECOND) * 10);

	//---Print Priority Table and stop active sounds at 13 sec
	SoundManager::PrintPriority(Time(Duration::TIME_ONE_SECOND) * 13);

	//stop all active sounds in table

	SoundManager::StopAllSounds(Time(Duration::TIME_ONE_SECOND) * 13);


	


}

void Demo4()
{
	Handle::Status Status;

	//I have the wave name hacked in here because I don't think callbacks should print the wave string name.
	//Most sounds have multiple waves associated to them so it doesn't make sense to print that info.
	UserCallback* pGameCallback_A = new UserCallback("../../MS2_AudioFiles/Dial_mono.wav");
	UserCallback* pGameCallback_B = new UserCallback("../../MS2_AudioFiles/MoonPatrol_mono.wav");
	UserCallback* pGameCallback_C = new UserCallback("../../MS2_AudioFiles/Sequence1_mono.wav");
	UserCallback* pGameCallback_D = new UserCallback("../../MS2_AudioFiles/Donkey_mono.wav");

	//Play Dial at 0 Sec
	Sound* SndA = SoundManager::CreateSound(SoundId::DIAL_ID, pGameCallback_A);
	Status = SndA->NewPan(-1.0f, Time());
	assert(Handle::Status::SUCCESS == Status);

	Status = SndA->Play(Time());
	assert(Handle::Status::SUCCESS == Status);

	//Play Moon Patrol at 0 Sec
	Sound* SndB = SoundManager::CreateSound(SoundId::MOON_PATROL_ID, pGameCallback_B);
	Status = SndB->NewPan(1.0f, Time());
	assert(Handle::Status::SUCCESS == Status);

	Status = SndB->Play(Time());
	assert(Handle::Status::SUCCESS == Status);

	//Play Sequence at 0 Sec
	Sound* SndC = SoundManager::CreateSound(SoundId::SEQUENCE_ID, pGameCallback_C);
	Status = SndC->NewPan(-1.0f, Time());
	assert(Handle::Status::SUCCESS == Status);

	Status = SndC->Play(Time());
	assert(Handle::Status::SUCCESS == Status);

	//Play Donkey at 3.5 sec
	Sound* SndD = SoundManager::CreateSound(SoundId::DONKEY_ID, pGameCallback_D);
	Status = SndD->NewPan(-1.0f, Time(Duration::TIME_ONE_MILLISECOND) * 3500);
	assert(Handle::Status::SUCCESS == Status);

	Status = SndD->Play(Time(Duration::TIME_ONE_MILLISECOND) * 3500);
	assert(Handle::Status::SUCCESS == Status);

}

void Demo5()
{

	//Play Electro at 0 sec
	Sound* SndA = SoundManager::CreateSound(SoundId::ELECTRO_ID);

	Handle::Status Status;
	Status = SndA->NewVolume(0.3f, Time());
	assert(Handle::Status::SUCCESS == Status);

	Status = SndA->NewPan(-1.0f, Time());
	assert(Handle::Status::SUCCESS == Status);

	Status = SndA->Play(Time());
	assert(Handle::Status::SUCCESS == Status);


	//Play Alarm at 0 sec
	Sound* SndB = SoundManager::CreateSound(SoundId::ALARM_ID);

	Status = SndB->NewVolume(0.3f, Time());
	assert(Handle::Status::SUCCESS == Status);

	Status = SndB->NewPan(-1.0f, Time());
	assert(Handle::Status::SUCCESS == Status);

	Status = SndB->Play(Time());
	assert(Handle::Status::SUCCESS == Status);


	//Play Alarm at 5 sec
	Sound* SndB2 = SoundManager::CreateSound(SoundId::ALARM_ID);
	Status = SndB2->NewVolume(0.3f, Time(Duration::TIME_ONE_SECOND) * 5);
	assert(Handle::Status::SUCCESS == Status);

	Status = SndB2->NewPan(-1.0f, Time(Duration::TIME_ONE_SECOND) * 5);
	assert(Handle::Status::SUCCESS == Status);

	Status = SndB2->Play(Time(Duration::TIME_ONE_SECOND) * 5);
	assert(Handle::Status::SUCCESS == Status);

	//Play Alarm at 10 sec
	Sound* SndB3 = SoundManager::CreateSound(SoundId::ALARM_ID);
	Status = SndB3->NewVolume(0.3f, Time(Duration::TIME_ONE_SECOND) * 10);
	assert(Handle::Status::SUCCESS == Status);

	Status = SndB3->NewPan(-1.0f, Time(Duration::TIME_ONE_SECOND) * 10);
	assert(Handle::Status::SUCCESS == Status);

	Status = SndB3->Play(Time(Duration::TIME_ONE_SECOND) * 10);
	assert(Handle::Status::SUCCESS == Status);

	//Play Alarm at 15 sec
	Sound* SndB4 = SoundManager::CreateSound(SoundId::ALARM_ID);
	Status = SndB4->NewVolume(0.3f, Time(Duration::TIME_ONE_SECOND) * 15);
	assert(Handle::Status::SUCCESS == Status);

	Status = SndB4->NewPan(-1.0f, Time(Duration::TIME_ONE_SECOND) * 15);
	assert(Handle::Status::SUCCESS == Status);

	Status = SndB4->Play(Time(Duration::TIME_ONE_SECOND) * 15);
	assert(Handle::Status::SUCCESS == Status);

	//Play Alarm at 20 sec
	Sound* SndB5 = SoundManager::CreateSound(SoundId::ALARM_ID);
	Status = SndB5->NewVolume(0.3f, Time(Duration::TIME_ONE_SECOND) * 20);
	assert(Handle::Status::SUCCESS == Status);

	Status = SndB5->NewPan(-1.0f, Time(Duration::TIME_ONE_SECOND) * 20);
	assert(Handle::Status::SUCCESS == Status);

	Status = SndB5->Play(Time(Duration::TIME_ONE_SECOND) * 20);
	assert(Handle::Status::SUCCESS == Status);

	//Play Alarm at 25 sec
	Sound* SndB6 = SoundManager::CreateSound(SoundId::ALARM_ID);
	Status = SndB6->NewVolume(0.3f, Time(Duration::TIME_ONE_SECOND) * 25);
	assert(Handle::Status::SUCCESS == Status);

	Status = SndB6->NewPan(-1.0f, Time(Duration::TIME_ONE_SECOND) * 25);
	assert(Handle::Status::SUCCESS == Status);

	Status = SndB6->Play(Time(Duration::TIME_ONE_SECOND) * 25);
	assert(Handle::Status::SUCCESS == Status);


	//Create file callback
	FileCallback* pFileCallback = new FileCallback();
	//Load Beethoven..
	SoundManager::LoadWave("../../MS2_AudioFiles/Beethoven_stereo.wav", SoundId::BEETHOVEN_ID, pFileCallback);


}




