#include <vd2/VDXFrame/VideoFilter.h>

#ifndef FILTER_VD_FRAME_TOOLS
#define FILTER_VD_FRAME_TOOLS

namespace Tools {
	void copyFrame(void *dst0, ptrdiff_t dstpitch, const void *src0, ptrdiff_t srcpitch, uint32 w, uint32 h);
};

#endif 
