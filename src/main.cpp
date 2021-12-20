#include <vd2/VDXFrame/VideoFilter.h>
#include <FrameAccuFilter.h>
#include <FrameDelayFilter.h>
#include <FrameCacheFilter.h>

VDXFilterDefinition filterDef_frameAccu = VDXVideoFilterDefinition<FrameAccuFilter>("Steve Grogorick", "Frame Accumulator", "Accumulate frames, e.g. for firework recordings.\ngrogorick.de");
VDXFilterDefinition filterDef_frameDelay = VDXVideoFilterDefinition<FrameDelayFilter>("Steve Grogorick", "Frame Delay", "Delay frames, e.g. get (n-th) last frame in addition to the current frame.\ngrogorick.de");
VDXFilterDefinition filterDef_frameCache = VDXVideoFilterDefinition<FrameCacheFilter>("Steve Grogorick", "Frame Cache", "Store and load frames, e.g. store the final output and combine it with the next frame.\ngrogorick.de");

VDX_DECLARE_VIDEOFILTERS_BEGIN()
	VDX_DECLARE_VIDEOFILTER(filterDef_frameAccu)
	VDX_DECLARE_VIDEOFILTER(filterDef_frameDelay)
	VDX_DECLARE_VIDEOFILTER(filterDef_frameCache)
VDX_DECLARE_VIDEOFILTERS_END()

VDX_DECLARE_VFMODULE()