#include <windows.h>

#ifndef FILTER_VD_FRAME_DELAY_CONFIG
#define FILTER_VD_FRAME_DELAY_CONFIG

class FrameDelayFilterConfig {
public:
	FrameDelayFilterConfig()
		:mNumFrames(1)
	{
	}

public:
	uint8 mNumFrames;
};

#endif 