#ifndef _COMMANDS_H
#define _COMMANDS_H

typedef enum beo_address
{
	SOURCE_VIDEO = 0x00,
	SOURCE_AUDIO = 0x01,
	SOURCE_VIDEOTAPE = 0x05,
	SOURCE_ALL = 0x0F,
	SOURCE_SPDEMO = 0x1D,
	SOURCE_LIGHT = 0x1B,
	SOURCE_BEOVISION1 = 0xA0,
	SOURCE_BEOSOUND =0xA5,
	SOURCE_BEOVISION2= 0xA8,
	SOURCE_BEOSOUND2=0xAD,
	SOURCE_BEOVISION3 = 0xB0,
	SOURCE_BEOSOUND3 =0xB5
} beo_address;

typedef enum beo_command
{
	NUMBER_0 = 0x00,
	NUMBER_1 = 0x01,
	NUMBER_2 = 0x02,
	NUMBER_3 = 0x03,
	NUMBER_4 = 0x04,
	NUMBER_5 = 0x05,
	NUMBER_6 = 0x06,
	NUMBER_7 = 0x07,
	NUMBER_8 = 0x08,
	NUMBER_9 = 0x09,
	
	CLEAR = 0x0A,
	STORE = 0x0B,
	STANDBY = 0x0C,
	MUTE = 0x0D,
	INDEX = 0x0E,
	RESET = 0x0E,

	BACK = 0x14,

	PICTURE_OFF = 0x1C,
	P_UP = 0x1E,
	P_DOWN = 0x1F,
	TUNE = 0x20,
	Counter=0x20,
	
	CLOCK = 0x28,
	
	FORMAT = 0x2A,

	REWIND = 0x32,
	RETURN = 0x33,
	FORWARD = 0x34,
	PLAY = 0x35,
	GO = 0x35,
	STOP = 0x36,
	RECORD = 0x37,


	GUIDE = 0x40,
	SELECT = 0x3F,
	INFO = 0x43,
	SPEAKER = 0x44,

	TURN = 0x46,
	SOUND = 0x46,
	SLEEP = 0x47,
	LOUDNESS = 0x48,
		PICTURE = 0x4A,

	BASS = 0x4D,
	TREBLE = 0x4E,
	BALANCE = 0x4F,
	
	LIST = 0x58,
	
	MENU = 0x5C,
	
	VOLUME_UP = 0x60,
	VOLUME_DOWN = 0x64,
	
	LEFT_REPEAT = 0x70,
	RIGHT_REPEAT = 0x71,
	UP_REPEAT = 0x72,
	DOWN_REPEAT = 0x73,
	
	GO_REPEAT = 0x75,
	GREEN_REPEAT = 0x76,
	YELLOW_REPEAT = 0x77,
	BLUE_REPEAT = 0x78,
	RED_REPEAT = 0x79, 
	
	EXIT = 0x7F,
	TV = 0x80,
	RADIO = 0x81,
	VIDEO_AUX = 0x82,
	AUDIO_AUX = 0x83,
	HOME_MEDIA = 0x84, // Note uses address C0
	VIDEO_TAPE = 0x85,
	DVD = 0x86,
	CAMCORD = 0x87,
	TEXT = 0x88,
	SP_DEMO = 0x89,
	DIGITAL_TV = 0x8A,
	PC = 0x8B,
	WEB_MEDIA = 0x8C, // Note uses address C0
	
	DOOR_CAM = 0x8D,
	AUDIO_TAPE = 0x91,
	CD = 0x92,
	PHONO = 0x93,
	NETRADIO = 0x93,
	AUDIO_TAPE_2 = 0x94,
	N_MUSIC = 0x94,
	SPOTIFY = 0x96, // Note used address C0
	CD2 = 0x97,
	LIGHT = 0x9B,
		MORNING = 0xF,
		HOME =0x25,
		DINNER =0x26,
		CINEMA =0x27,
		BED_TIME = 0x39,
		NIGHT = 0x3A,
		WELCOME_HOME = 0x3B,
		GOODBYE = 0x3C,
	CONTROL =0x9C,
		WINDOW1 = 0xF,
		CURTAIN1 = 0x1A,
		ON_OFF1 = 0x25,
		SHADE1 = 0x3B,
	
	DIMENSION_2D = 0xAD,
	DIMENSION_3D = 0xAE,

	AV = 0xBF,
	TRACKING = 0xC8,
	
	HDMI1 = 0xCE, // Note uses address C0
	HDMI2 = 0x1CE, // Note uses address C0
	HDMI3 = 0x2CE, // Note uses address C0
	HDMI4 = 0x3CE, // Note uses address C0
	
	MATRIX1 = 0xCF, // Note uses address C0
	MATRIX2 = 0x1CF, // Note uses address C0

	CINEMA_ON = 0xDA,
	CINEMA_OFF = 0xDB,


	YELLOW = 0xD4,
	GREEN = 0xD5,
	BLUE = 0xD8,
	RED = 0xD9,

	HOME_CONTROL = 0xE3,

	P_AND_P = 0xFA,
	STAND = 0xF7,

	YOUTUBE = 0x18C, // Note uses address C0
	DEEZER = 0x196, // Note uses address C0
	PATTERN_PLAY = 0x1D3, // Note uses address C0
	BLUETOOTH = 0x283, // Note uses address C0
	BLGW_APP = 0x28C, // Note uses address C0
	Q_PLAY = 0x296, // Note uses address C0

} beo_command;

#endif