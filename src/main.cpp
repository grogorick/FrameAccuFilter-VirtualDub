#include <vd2/VDXFrame/VideoFilter.h>
#include <BlackWhiteFilter.h>
#include <FrameAccuFilter.h>

VDXFilterDefinition filterDef_blackWhite = VDXVideoFilterDefinition<BlackWhiteFilter>("Shadwork", "Black White filter", "Example for VirtualDub Plugin SDK: Applies a Black White filter to video.");
VDXFilterDefinition filterDef_frameAccu = VDXVideoFilterDefinition<FrameAccuFilter>("Steve Grogorick", "Frame Accumulation filter", "Accumulate frame, e.g. for firework recordings.");

VDX_DECLARE_VIDEOFILTERS_BEGIN()
	VDX_DECLARE_VIDEOFILTER(filterDef_blackWhite)
	VDX_DECLARE_VIDEOFILTER(filterDef_frameAccu)
VDX_DECLARE_VIDEOFILTERS_END()

VDX_DECLARE_VFMODULE()