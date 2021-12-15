#include <vd2/VDXFrame/VideoFilter.h>
#include <FrameAccuFilter.h>

VDXFilterDefinition filterDef_frameAccu = VDXVideoFilterDefinition<FrameAccuFilter>("Steve Grogorick", "Frame Accumulation filter", "Accumulate frame, e.g. for firework recordings.");

VDX_DECLARE_VIDEOFILTERS_BEGIN()
	VDX_DECLARE_VIDEOFILTER(filterDef_frameAccu)
VDX_DECLARE_VIDEOFILTERS_END()

VDX_DECLARE_VFMODULE()