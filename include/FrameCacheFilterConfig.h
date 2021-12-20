#include <windows.h>

#ifndef FILTER_VD_FRAME_CACHE_CONFIG
#define FILTER_VD_FRAME_CACHE_CONFIG

class FrameCacheFilterConfig {
public:
	FrameCacheFilterConfig()
		:mMode(Load)
	{
	}

public:
	enum Mode { Load, Save } mMode;
};

#endif 