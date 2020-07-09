#include "XAudio2Manager.h"
#include "VoiceCallback.h"
#include "AudioVoice.h"
#include "X3DAUDIO.H"


void XAudio2Manager::Create() {

    const XAudio2Manager* pInst = XAudio2Manager::GetInstance();
    assert(pInst);
}

void XAudio2Manager::Destroy()
{
    const XAudio2Manager* pInst = XAudio2Manager::GetInstance();
    assert(pInst);

    pInst->pMasterVoice->DestroyVoice();
    pInst->pXAudio2Engine->Release();

    //uninit COM interface
    CoUninitialize();
}

XAudio2Manager* XAudio2Manager::GetInstance() {

    static XAudio2Manager XAudioMan;
    return &XAudioMan;
}

XAudio2Manager::XAudio2Manager() {

    this->Init();
}

XAudio2Manager::~XAudio2Manager() {

    
}

void XAudio2Manager::Init() {

    HRESULT hr;

    //init COM interface
    hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
    assert(S_OK == hr);

    //Create XAudio2 Engine
    hr = XAudio2Create(&this->pXAudio2Engine, 0, XAUDIO2_DEFAULT_PROCESSOR);
    assert(S_OK == hr);

    //Create Master Voice for Engine
    hr = pXAudio2Engine->CreateMasteringVoice(&this->pMasterVoice);
    assert(S_OK == hr);

    
}

void XAudio2Manager::LoadWaveFile(const char* FileName, AudioBuffer& audioBuffer) {

    //Get Engine Instance
    XAudio2Manager* pAudioEngine = XAudio2Manager::GetInstance();
    assert(pAudioEngine != nullptr);

    // Open the file
    HANDLE FileHandle;
    FileError ferror = File::open(FileHandle, FileName, FileMode::FILE_READ);
    assert(ferror == FILE_SUCCESS);

    //seek to beginning of file
    ferror = File::seek(FileHandle, FileSeek::FILE_SEEK_BEGIN, 0);
    assert(ferror == FILE_SUCCESS);

    DWORD dwChunkSize;
    DWORD dwChunkPosition;

    //Check that the file type is a WAVE file
    pAudioEngine->FindChunk(FileHandle, fourccRIFF, dwChunkSize, dwChunkPosition);
    DWORD filetype;
    pAudioEngine->ReadChunkData(FileHandle, &filetype, sizeof(DWORD), dwChunkPosition);
    assert(filetype == fourccWAVE);


    

    //---read the format---
    //get size and pointer to chunk format header?
    pAudioEngine->FindChunk(FileHandle, fourccFMT, dwChunkSize, dwChunkPosition);
    //store format in wfx
    pAudioEngine->ReadChunkData(FileHandle, &audioBuffer.GetFormat(), dwChunkSize, dwChunkPosition);

    //---read the audio data---
    //get size and pointer to chunk
    pAudioEngine->FindChunk(FileHandle, fourccDATA, dwChunkSize, dwChunkPosition);
    //allocate an audio buffer to chunk size
    BYTE* pDataBuffer = new BYTE[dwChunkSize];
    //store audio data in audio buffer
    pAudioEngine->ReadChunkData(FileHandle, pDataBuffer, dwChunkSize, dwChunkPosition);

    //fill the engine audio buffer header
   

    audioBuffer.GetXAudio2Buffer().AudioBytes = dwChunkSize; //size of audio buffer in bytes
    audioBuffer.GetXAudio2Buffer().pAudioData = pDataBuffer; //buffer containing audio data
    audioBuffer.GetXAudio2Buffer().Flags = XAUDIO2_END_OF_STREAM; //flag tells source voice that its at the end of data 

    //close the file here
    CloseHandle(FileHandle);
    
}

HRESULT XAudio2Manager::FindChunk(HANDLE hFile, DWORD fourcc, DWORD& dwChunkSize, DWORD& dwChunkDataPosition)
{

    FileError ReadResult = FILE_SUCCESS;
    FileError SeekResult;
    DWORD dwChunkType;
    DWORD dwChunkDataSize;
    DWORD dwFileType;
    DWORD dwOffset = 0;

    //set pointer to beginning of file
    SeekResult = File::seek(hFile, FileSeek::FILE_SEEK_BEGIN, 0);
    assert(SeekResult == FILE_SUCCESS);

    while (ReadResult == FILE_SUCCESS)
    {
        //read file and set chunk type we're looking for... based on current file pointer
        ReadResult = File::read(hFile, &dwChunkType, sizeof(DWORD));
        assert(ReadResult == FILE_SUCCESS);
        
        //read file and set size of chunk we're looking for... based on current file pointer
        ReadResult = File::read(hFile, &dwChunkDataSize, sizeof(DWORD));
        assert(ReadResult == FILE_SUCCESS);
        assert(0 <= dwChunkDataSize);

        //Check if file is wave file
        if (fourccRIFF == dwChunkType) {

            dwChunkDataSize = 4;//why??

            //read file and set file type
            ReadResult = File::read(hFile, &dwFileType, sizeof(DWORD));
            assert(ReadResult == FILE_SUCCESS);
        }
        //else looking for format or data chunk... set pointer location to beginning of next chunk
        else {
            SeekResult = File::seek(hFile, FileSeek::FILE_SEEK_CURRENT, dwChunkDataSize);
            assert(SeekResult == FILE_SUCCESS);
        }

        dwOffset += sizeof(DWORD) * 2;

        //if we are pointing to the chunk we are looking for... set size and pointer location in file and break
        if (dwChunkType == fourcc)
        {
            dwChunkSize = dwChunkDataSize;
            dwChunkDataPosition = dwOffset;
            return S_OK;
        }

        dwOffset += dwChunkDataSize;
    }

    //should never get here.. will throw assertion in calling class after returning
    return S_FALSE;
}

HRESULT XAudio2Manager::ReadChunkData(HANDLE hFile, void* buffer, DWORD buffersize, DWORD bufferoffset)
{

    FileError FileResult = File::seek(hFile, FileSeek::FILE_SEEK_BEGIN, bufferoffset);
    assert(FileResult == FILE_SUCCESS);

    FileResult = File::read(hFile, buffer, buffersize);
    assert(FileResult == FILE_SUCCESS);

    return S_OK;
}

IXAudio2SourceVoice* XAudio2Manager::CreateVoice(WAVEFORMATEXTENSIBLE wfx, VoiceCallback* pCallback) {

    //Get Engine Instance
    XAudio2Manager* pAudioEngine = XAudio2Manager::GetInstance();
    assert(pAudioEngine != nullptr);

    //Create a voice
    IXAudio2SourceVoice* pSourceVoice;
    const HRESULT hr = pAudioEngine->pXAudio2Engine->CreateSourceVoice(&pSourceVoice, (WAVEFORMATEX*)&wfx, 0, XAUDIO2_MAX_FREQ_RATIO, pCallback); //voice needs the format
    assert(S_OK == hr);

    return pSourceVoice;
}

void XAudio2Manager::PlayVoice(AudioVoice* pVoiceIn) {

    assert(pVoiceIn != nullptr);

    //flush old data out of buffer
    HRESULT hr = pVoiceIn->GetXAudio2Voice()->FlushSourceBuffers();
    assert(S_OK == hr);

    ////Transfer the audio data from CPU to the XAudio2 Engine... buffer now in RAM... was just on CPU stack before?
    pVoiceIn->SubmitBuffer();

    //start voice from beginning of buffer
    hr = pVoiceIn->GetXAudio2Voice()->Start();
    assert(S_OK == hr);
}

void XAudio2Manager::PauseVoice(IXAudio2SourceVoice* InVoice) {
    assert(InVoice != nullptr);

    //stop voice and save position in buffer
    const HRESULT hr = InVoice->Stop();
    assert(S_OK == hr);
}

void XAudio2Manager::UnPauseVoice(IXAudio2SourceVoice* InVoice) {
    assert(InVoice != nullptr);

    //unpause voice from where it left off in buffer
    const HRESULT hr = InVoice->Start();
    assert(S_OK == hr);
}

void XAudio2Manager::StopVoice(IXAudio2SourceVoice* InVoice) {
    assert(InVoice != nullptr);

    //stop voice
    assert(S_OK == InVoice->Stop());

    //flush buffer
    //hr = InVoice->FlushSourceBuffers();
    //assert(S_OK == hr);

}

void XAudio2Manager::SetVolume(IXAudio2SourceVoice* InVoice, const float& volume) {
    assert(InVoice != nullptr);

    const HRESULT hr = InVoice->SetVolume(volume);
    assert(S_OK == hr);
}

void XAudio2Manager::SetPitch(IXAudio2SourceVoice* InVoice, const float& pitch) {
    assert(InVoice != nullptr);

    const HRESULT hr = InVoice->SetFrequencyRatio(pitch);
    assert(S_OK == hr);
}

void XAudio2Manager::SetLooping(bool bLoop, XAUDIO2_BUFFER& Buffer) {

    if (bLoop == true) {
        Buffer.LoopCount = XAUDIO2_LOOP_INFINITE;
    }
    else {
        Buffer.LoopCount = 0;
    }
}

void XAudio2Manager::SetPan(IXAudio2SourceVoice* InVoice, const float& pan) {

    //Get Engine Instance
    XAudio2Manager* pAudioEngine = XAudio2Manager::GetInstance();
    assert(pAudioEngine != nullptr);

    assert(InVoice != nullptr);
    assert(pAudioEngine->pMasterVoice != nullptr);
    assert(pan <= 1.0f);
    assert(pan >= -1.0f);

    //Get Speaker config
    DWORD dwChannelMask;
    pAudioEngine->pMasterVoice->GetChannelMask(&dwChannelMask);
    
    // pan of -1.0 indicates all left speaker, 
    // 1.0 is all right speaker, 0.0 is split between left and right
    const float left = 0.5f - pan / 2;
    const float right = 0.5f + pan / 2;

    //Create array for matrix output
    float outputMatrix[8] = { };
   
    switch (dwChannelMask)
    {
    case SPEAKER_MONO:
        outputMatrix[0] = 1.0;
        break;
    case SPEAKER_STEREO:
    case SPEAKER_2POINT1:
    case SPEAKER_SURROUND:
        outputMatrix[0] = left;
        outputMatrix[1] = right;
        break;
    case SPEAKER_QUAD:
        outputMatrix[0] = outputMatrix[2] = left;
        outputMatrix[1] = outputMatrix[3] = right;
        break;
    case SPEAKER_4POINT1:
        outputMatrix[0] = outputMatrix[3] = left;
        outputMatrix[1] = outputMatrix[4] = right;
        break;
    case SPEAKER_5POINT1:
    case SPEAKER_7POINT1:
    case SPEAKER_5POINT1_SURROUND:
        outputMatrix[0] = outputMatrix[4] = left;
        outputMatrix[1] = outputMatrix[5] = right;
        break;
    case SPEAKER_7POINT1_SURROUND:
        outputMatrix[0] = outputMatrix[4] = outputMatrix[6] = left;
        outputMatrix[1] = outputMatrix[5] = outputMatrix[7] = right;
        break;
    }


    XAUDIO2_VOICE_DETAILS VoiceDetails;
    InVoice->GetVoiceDetails(&VoiceDetails);

    XAUDIO2_VOICE_DETAILS MasterVoiceDetails;
    pAudioEngine->pMasterVoice->GetVoiceDetails(&MasterVoiceDetails);

    InVoice->SetOutputMatrix(NULL, VoiceDetails.InputChannels, MasterVoiceDetails.InputChannels, outputMatrix);
}


float XAudio2Manager::GetVolume(IXAudio2SourceVoice* InVoice) {
    
    assert(InVoice != nullptr);

    float out;
    InVoice->GetVolume(&out);
    return out;
}

