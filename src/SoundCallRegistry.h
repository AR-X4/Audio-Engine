#ifndef SOUND_CALL_REGISTRY_H
#define SOUND_CALL_REGISTRY_H



enum class SoundId
{
	UNINITIALIZED,

	A_mono,
	AtoB_mono,
	B_mono,
	BtoC_mono,
	C_mono,
	CtoA_mono,
	End_mono,
	Intro_mono,

	SONGA_ID,
	SONGB_ID,

	STRINGS_ID,
	BASSOON_ID,
	BASSOON_ID2,
	BASSOON_ID3,
	BASSOON_ID4,
	FIDDLE_ID,
	OBOE2_ID,

	DEMO_1_ID,
	DEMO_2_ID,

	ELECTRO_ID,
	ALARM_ID,
	BEETHOVEN_ID,
	COMA_ID,
	DIAL_ID,
	MOON_PATROL_ID,
	SEQUENCE_ID,
	DONKEY_ID

};



enum class SoundStatus
{
	UNINITIALIZED,
	LOADING_WAVE,
	PLAYING,
	STOPING,
	PAUSING,
	UNPAUSING,

	SETTING_VOLUME,
	SETTING_PITCH,
	SETTING_PAN,
	SETTING_LOOPING,

	GETTING_VOLUME

};

#endif