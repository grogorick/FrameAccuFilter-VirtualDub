#include <vd2/VDXFrame/VideoFilter.h>
#include <vd2/VDXFrame/VideoFilterEntry.h>
#include <FrameAccuFilterDialog.h>

#ifndef FILTER_VD_FRAME_ACCU
#define FILTER_VD_FRAME_ACCU

extern int g_VFVAPIVersion;

class FrameAccuFilter : public VDXVideoFilter {
	public:
		virtual uint32 GetParams();
		virtual void Start();
		virtual void Run();
		virtual bool Configure(VDXHWND hwnd);
		virtual void GetSettingString(char *buf, int maxlen);
		virtual void GetScriptString(char *buf, int maxlen);
		VDXVF_DECLARE_SCRIPT_METHODS();
	protected:
		void accumulateFrame(void *dst, ptrdiff_t dstpitch, const void *src, ptrdiff_t srcpitch, uint32 w, uint32 h);
		FrameAccuFilterConfig mConfig;
		void ScriptConfig(IVDXScriptInterpreter *isi, const VDXScriptValue *argv, int argc);
};

#endif 
