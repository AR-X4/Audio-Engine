#include "LoadWaveCommand.h"
#include "AudioBuffer.h"
#include "BufferManager.h"
#include "XAudio2Manager.h"
#include "SoundManager.h"

LoadWaveCommand::LoadWaveCommand(const char* const FileNameIn, SoundId Idin, FileCallback* pCallback)
	:FileName(FileNameIn), ID(Idin), pFileCallback(pCallback)
{
	
}

LoadWaveCommand::~LoadWaveCommand() {
	
	//do nothing
}

void LoadWaveCommand::Execute() {
	
	AudioBuffer* pBuff = BufferManager::CreateBuffer(this->ID);
	assert(pBuff != nullptr);
	
	XAudio2Manager::LoadWaveFile(this->FileName, *pBuff);

	if (this->pFileCallback != nullptr) {
		this->pFileCallback->Set(this->FileName);

		SoundManager::GetA2G()->PushBack(this->pFileCallback);

	}


}

