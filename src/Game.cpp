

#include "AzulCore.h"
#include "Game.h"
#include "GameApp.h"
#include "InputTest.h"

#include "SoundManager.h"
//#include "Sound.h"
#include "Demo.h"

// Thread stuff
#include "ThreadHelper.h"



//-----------------------------------------AUDIO ENGINE DESIGN------------------------------------------
//
// Audio thread spins up instance of XAudio2 and manages low level sound functions
// Game thread creates sound objects... constructing them automatically assigns a handle and sound ID
//
// 
// 
//
// Commands are sent to the Audio thread from the game thread through a circular queue
//
//
// 
//
//-----------------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Game::Initialize()
//		Allows the engine to perform any initialization it needs to before 
//      starting to run.  This is where it can query for any required services 
//      and load any non-graphic related content. 
//-----------------------------------------------------------------------------
void Game::Initialize()
{ 
	// Game Window Device setup
	this->setWindowName("Audio Engine");
	this->setWidthHeight(400, 300);
	this->SetClearColor(0.74f, 0.74f, 0.86f, 1.0f);
}

//-----------------------------------------------------------------------------
// Game::LoadContent()
//		Allows you to load all content needed for your engine,
//	    such as objects, graphics, etc.
//-----------------------------------------------------------------------------
void Game::LoadContent()
{	
	glDisable(GL_DEBUG_OUTPUT);

	// Load up the demo application
	GameApp::LoadDemo(this->getWidth(), this->getHeight());

	// Name the current main thread
	ThreadHelper::SetCurrentThreadName("--- Game Main ---");
	ThreadHelper::DebugBegin(0);

	//---------------------------------------------------------------------------------------------------------
	// Launch Audio Thread
	//---------------------------------------------------------------------------------------------------------

	//Create Sound System
	SoundManager::Create();

	//--------------------------------
	//----------Load Waves--------
	//--------------------------------
	//Demo1
	SoundManager::LoadWave("../AudioFiles/Fiddle_mono.wav", SoundId::FIDDLE_ID);
	SoundManager::LoadWave("../AudioFiles/Bassoon_mono.wav", SoundId::BASSOON_ID);
	SoundManager::LoadWave("../AudioFiles/Oboe2_mono.wav", SoundId::OBOE2_ID);
	SoundManager::LoadWave("../AudioFiles/SongA.wav", SoundId::SONGA_ID);
	SoundManager::LoadWave("../AudioFiles/SongB.wav", SoundId::SONGB_ID);

	//Demo2
	SoundManager::LoadWave("../AudioFiles/Intro_mono.wav", SoundId::Intro_mono);
	SoundManager::LoadWave("../AudioFiles/A_mono.wav", SoundId::A_mono);
	SoundManager::LoadWave("../AudioFiles/AtoB_mono.wav", SoundId::AtoB_mono);
	SoundManager::LoadWave("../AudioFiles/B_mono.wav", SoundId::B_mono);
	SoundManager::LoadWave("../AudioFiles/BtoC_mono.wav", SoundId::BtoC_mono);
	SoundManager::LoadWave("../AudioFiles/C_mono.wav", SoundId::C_mono);
	SoundManager::LoadWave("../AudioFiles/CtoA_mono.wav", SoundId::CtoA_mono);
	SoundManager::LoadWave("../AudioFiles/End_mono.wav", SoundId::End_mono);

	//Demo3
	SoundManager::LoadWave("../../MS2_AudioFiles/Coma_mono.wav", SoundId::COMA_ID);

	//Demo 4
	SoundManager::LoadWave("../../MS2_AudioFiles/Dial_mono.wav", SoundId::DIAL_ID);
	SoundManager::LoadWave("../../MS2_AudioFiles/MoonPatrol_mono.wav", SoundId::MOON_PATROL_ID);
	SoundManager::LoadWave("../../MS2_AudioFiles/Sequence1_mono.wav", SoundId::SEQUENCE_ID);
	SoundManager::LoadWave("../../MS2_AudioFiles/Donkey_mono.wav", SoundId::DONKEY_ID);


	//Demo 5
	SoundManager::LoadWave("../../MS2_AudioFiles/Electro_mono.wav", SoundId::ELECTRO_ID);
	SoundManager::LoadWave("../../MS2_AudioFiles/Alert_mono.wav", SoundId::ALARM_ID);

	//--------------------------------
	//----------Load Scripts--------
	//--------------------------------
	SoundManager::CreateScript(SoundId::FIDDLE_ID);
	SoundManager::AddToScriptFront(SoundId::FIDDLE_ID, SoundId::FIDDLE_ID);

	SoundManager::CreateScript(SoundId::BASSOON_ID);
	SoundManager::AddToScriptFront(SoundId::BASSOON_ID, SoundId::BASSOON_ID);

	SoundManager::CreateScript(SoundId::OBOE2_ID);
	SoundManager::AddToScriptFront(SoundId::OBOE2_ID, SoundId::OBOE2_ID);

	SoundManager::CreateScript(SoundId::SONGA_ID);
	SoundManager::AddToScriptFront(SoundId::SONGA_ID, SoundId::SONGA_ID);

	SoundManager::CreateScript(SoundId::SONGB_ID);
	SoundManager::AddToScriptFront(SoundId::SONGB_ID, SoundId::SONGB_ID);

	SoundManager::CreateScript(SoundId::DEMO_2_ID);
	SoundManager::AddToScriptFront(SoundId::DEMO_2_ID, SoundId::End_mono);
	SoundManager::AddToScriptFront(SoundId::DEMO_2_ID, SoundId::CtoA_mono);
	SoundManager::AddToScriptFront(SoundId::DEMO_2_ID, SoundId::C_mono);
	SoundManager::AddToScriptFront(SoundId::DEMO_2_ID, SoundId::BtoC_mono);
	SoundManager::AddToScriptFront(SoundId::DEMO_2_ID, SoundId::B_mono);
	SoundManager::AddToScriptFront(SoundId::DEMO_2_ID, SoundId::AtoB_mono);
	SoundManager::AddToScriptFront(SoundId::DEMO_2_ID, SoundId::A_mono);
	SoundManager::AddToScriptFront(SoundId::DEMO_2_ID, SoundId::Intro_mono);
	
	SoundManager::CreateScript(SoundId::ELECTRO_ID);
	SoundManager::AddToScriptFront(SoundId::ELECTRO_ID, SoundId::ELECTRO_ID);

	SoundManager::CreateScript(SoundId::ALARM_ID);
	SoundManager::AddToScriptFront(SoundId::ALARM_ID, SoundId::ALARM_ID);

	SoundManager::CreateScript(SoundId::COMA_ID);
	SoundManager::AddToScriptFront(SoundId::COMA_ID, SoundId::COMA_ID);

	SoundManager::CreateScript(SoundId::DIAL_ID);
	SoundManager::AddToScriptFront(SoundId::DIAL_ID, SoundId::DIAL_ID);

	SoundManager::CreateScript(SoundId::MOON_PATROL_ID);
	SoundManager::AddToScriptFront(SoundId::MOON_PATROL_ID, SoundId::MOON_PATROL_ID);

	SoundManager::CreateScript(SoundId::SEQUENCE_ID);
	SoundManager::AddToScriptFront(SoundId::SEQUENCE_ID, SoundId::SEQUENCE_ID);

	SoundManager::CreateScript(SoundId::DONKEY_ID);
	SoundManager::AddToScriptFront(SoundId::DONKEY_ID, SoundId::DONKEY_ID);


}

//-----------------------------------------------------------------------------
// Game::Update()
//      Called once per frame, update data, tranformations, etc
//      Use this function to control process order
//      Input, AI, Physics, Animation, and Graphics
//-----------------------------------------------------------------------------
void Game::Update()
{
	// Update the demo application
	GameApp::UpdateDemo();
	SoundManager::Update();
	
	Keyboard* key = Keyboard::GetInstance();

	//-------Demo One------
	static bool OneKeyPressed = key->GetKeyState(AZUL_KEY::KEY_1);
	if (key->GetKeyState(AZUL_KEY::KEY_1) && OneKeyPressed == false)
	{
		Demo1();
		OneKeyPressed = true;
	}


	//-----Demo Two-------
	static bool TwoKeyPressed = key->GetKeyState(AZUL_KEY::KEY_2);
	if (key->GetKeyState(AZUL_KEY::KEY_2) && TwoKeyPressed == false)
	{ 
		Demo2();
		TwoKeyPressed = true;
	}

	//-----Demo Three-------
	static bool ThreeKeyPressed = key->GetKeyState(AZUL_KEY::KEY_3);
	if (key->GetKeyState(AZUL_KEY::KEY_3) && ThreeKeyPressed == false)
	{
		Demo3();
		ThreeKeyPressed = true;
	}

	//-----Demo Four-------
	static bool FourKeyPressed = key->GetKeyState(AZUL_KEY::KEY_4);
	if (key->GetKeyState(AZUL_KEY::KEY_4) && FourKeyPressed == false)
	{
		Demo4();
		FourKeyPressed = true;
	}

	//-----Demo Five-------
	static bool FiveKeyPressed = key->GetKeyState(AZUL_KEY::KEY_5);
	if (key->GetKeyState(AZUL_KEY::KEY_5) && FiveKeyPressed == false)
	{
		Demo5();
		FiveKeyPressed = true;
	}

}

//-----------------------------------------------------------------------------
// Game::Draw()
//		This function is called once per frame
//	    Use this for draw graphics to the screen.
//      Only do rendering here
//-----------------------------------------------------------------------------
void Game::Draw()
{
	// Draw the demo application
	GameApp::DrawDemo();

}

//-----------------------------------------------------------------------------
// Game::UnLoadContent()
//       unload content (resources loaded above)
//       unload all content that was loaded before the Engine Loop started
//-----------------------------------------------------------------------------
void Game::UnLoadContent()
{
	
	SoundManager::Destroy();

	ThreadHelper::DebugEnd(0);
}

// End of File 

