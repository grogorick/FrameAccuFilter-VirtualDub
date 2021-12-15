#include <windows.h>

#ifndef FILTER_VD_FRAME_ACCU_CONFIG
#define FILTER_VD_FRAME_ACCU_CONFIG

class FrameAccuFilterConfig {
public:
	FrameAccuFilterConfig()
		:mOperation(Max)
	{
	}

public:
	enum Operation { Max, Add, Multiply } mOperation;
};

#endif 