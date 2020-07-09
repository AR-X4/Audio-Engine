#include "VoiceCallback.h"



VoiceCallback::VoiceCallback()
	:finished(false)
{}

//VoiceCallback::VoiceCallback(CircularData* _pOut)
//{
//	assert(_pOut);
//	this->pOut = _pOut;
//	this->finished = false;
//}

VoiceCallback::~VoiceCallback()
{
	
}


void VoiceCallback::Reset() {
	this->finished = false;
}

void STDMETHODCALLTYPE VoiceCallback::OnStreamEnd()
{
	this->finished = true;
	
}

void STDMETHODCALLTYPE VoiceCallback::OnBufferEnd(void*) {  

	//this->finished = true;
}



void STDMETHODCALLTYPE VoiceCallback::OnVoiceProcessingPassEnd() { }
void STDMETHODCALLTYPE VoiceCallback::OnVoiceProcessingPassStart(UINT32) {  }

void STDMETHODCALLTYPE VoiceCallback::OnBufferStart(void*) {  }
void STDMETHODCALLTYPE VoiceCallback::OnLoopEnd(void*) {  }
void STDMETHODCALLTYPE VoiceCallback::OnVoiceError(void*, HRESULT) {  }



