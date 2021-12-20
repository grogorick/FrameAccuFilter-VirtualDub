#include <vd2/VDXFrame/VideoFilter.h>
#include <vd2/VDXFrame/VideoFilterEntry.h>
#include <FrameDelayFilterDialog.h>

#ifndef FILTER_VD_FRAME_DELAY
#define FILTER_VD_FRAME_DELAY

extern int g_VFVAPIVersion;

class FrameDelayFilter : public VDXVideoFilter {
	public:
		virtual uint32 GetParams();
		virtual void Start();
		virtual void Run();
		virtual bool Configure(VDXHWND hwnd);
		virtual void GetSettingString(char *buf, int maxlen);
		virtual void GetScriptString(char *buf, int maxlen);
		VDXVF_DECLARE_SCRIPT_METHODS();
	protected:
		void delayFrame(void *dst, ptrdiff_t dstpitch, const void *src, ptrdiff_t srcpitch, uint32 w, uint32 h);

		FrameDelayFilterConfig mConfig;
		void ScriptConfig(IVDXScriptInterpreter *isi, const VDXScriptValue *argv, int argc);

		uint32 *buffer = nullptr;
		uint8 bufferCount = 0;
		uint8 bufferIdx = 0;

		bool reset = true;
};

#endif 
