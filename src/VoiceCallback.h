#ifndef VOICE_CALLBACK_H
#define VOICE_CALLBACK_H

#include "XAudio2Wrapper.h"
#include "CircularData.h"

//  Sample voice callback
class VoiceCallback : public IXAudio2VoiceCallback
{
public:

	//Big Four
	VoiceCallback();
	//VoiceCallback(CircularData* _pOut);
	VoiceCallback(const VoiceCallback& in) = delete;
	VoiceCallback& operator = (const VoiceCallback&) = delete;
	~VoiceCallback();

	void Reset();

	//Overridden Methods
	void STDMETHODCALLTYPE OnStreamEnd();
	void STDMETHODCALLTYPE OnBufferEnd(void*);
	
	//Not defined
	void STDMETHODCALLTYPE OnVoiceProcessingPassEnd();
	void STDMETHODCALLTYPE OnVoiceProcessingPassStart(UINT32);
	
	void STDMETHODCALLTYPE OnBufferStart(void*);
	void STDMETHODCALLTYPE OnLoopEnd(void*);
	void STDMETHODCALLTYPE OnVoiceError(void*, HRESULT);


	//Data
	bool finished;
	//CircularData* pOut;
};

#endif

// End of File 
