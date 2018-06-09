#include <windows.h>

#ifndef FILTER_VD_FRAME_ACCU_CONFIG
#define FILTER_VD_FRAME_ACCU_CONFIG

class FrameAccuFilterConfig {
public:
	FrameAccuFilterConfig()
	{
		mMode = MAX;
	}

public:
	enum Mode { MAX } mMode;
};

#endif 