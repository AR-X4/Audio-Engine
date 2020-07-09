#ifndef LOAD_WAVE_COMMAND_H
#define LOAD_WAVE_COMMAND_H

#include "Message.h"
#include "SoundCallRegistry.h"
#include "FileCallback.h"

class LoadWaveCommand : public Message 
{
public:
	
	LoadWaveCommand(const char* const FileNameIn, SoundId Idin, FileCallback* pCallback = nullptr);
	~LoadWaveCommand();

	LoadWaveCommand() = delete;
	LoadWaveCommand(const LoadWaveCommand&) = delete;
	LoadWaveCommand& operator=(const LoadWaveCommand&) = delete;

	void Execute() override;

private:
	//Data
	const char* const FileName;
	SoundId ID;
	FileCallback* pFileCallback;

};

#endif