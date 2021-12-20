#include <FrameDelayFilter.h>
#include <Tools.h>

uint32 FrameDelayFilter::GetParams() {
	if (g_VFVAPIVersion >= 12) {
		switch (fa->src.mpPixmapLayout->format) {
		case nsVDXPixmap::kPixFormat_XRGB8888:
			break;
		default:
			return FILTERPARAM_NOT_SUPPORTED;
		}
	}

	fa->dst.offset = 0;
	return FILTERPARAM_SWAP_BUFFERS;
}

void FrameDelayFilter::Start() {
	if (buffer) {
		delete[] buffer;
		buffer = nullptr;
	}
}

void FrameDelayFilter::Run() {
	if (g_VFVAPIVersion >= 12) {
		const VDXPixmap& pxdst = *fa->dst.mpPixmap;
		const VDXPixmap& pxsrc = *fa->src.mpPixmap;

		switch (pxdst.format) {
		case nsVDXPixmap::kPixFormat_XRGB8888:
			delayFrame(pxdst.data, pxdst.pitch, pxsrc.data, pxsrc.pitch, pxsrc.w, pxsrc.h);
			break;
		}
	}
	else {
		delayFrame(fa->dst.data, fa->dst.pitch, fa->src.data, fa->src.pitch, fa->dst.w, fa->dst.h);
	}
}

bool FrameDelayFilter::Configure(VDXHWND hwnd) {
	FrameDelayFilterDialog dlg(mConfig, fa->ifp);
	reset = dlg.Show((HWND)hwnd);
	return reset;
}

void FrameDelayFilter::delayFrame(void *dst0, ptrdiff_t dstpitch, const void *src0, ptrdiff_t srcpitch, uint32 w, uint32 h) {
	if (reset || !buffer) {
		reset = false;
		if (bufferCount != mConfig.mNumFrames || !buffer) {
			bufferCount = mConfig.mNumFrames;
			if (buffer) {
				delete[] buffer;
			}
			buffer = new uint32[w * h * bufferCount];
		}
		memset(buffer, 0, sizeof(uint32) * w * h * bufferCount);
	}

	ptrdiff_t bufferpitch = sizeof(uint32) * w;
	ptrdiff_t bufferIdxStep = w * h;

	uint32 *currentBuffer = buffer + (bufferIdx * bufferIdxStep);
	Tools::copyFrame(dst0, dstpitch, currentBuffer, bufferpitch, w, h);
	Tools::copyFrame(currentBuffer, bufferpitch, src0, srcpitch, w, h);

	bufferIdx = (bufferIdx + 1) % bufferCount;
}

VDXVF_BEGIN_SCRIPT_METHODS(FrameDelayFilter)
VDXVF_DEFINE_SCRIPT_METHOD(FrameDelayFilter, ScriptConfig, "ii")
VDXVF_END_SCRIPT_METHODS()

void FrameDelayFilter::GetSettingString(char *buf, int maxlen) {
	SafePrintf(buf, maxlen, " (%d Frame%s)", mConfig.mNumFrames, mConfig.mNumFrames == 1 ? "" : "s");
}

void FrameDelayFilter::GetScriptString(char *buf, int maxlen) {
	SafePrintf(buf, maxlen, "Config(%d)", mConfig.mNumFrames);
}

void FrameDelayFilter::ScriptConfig(IVDXScriptInterpreter *isi, const VDXScriptValue *argv, int argc) {
	mConfig.mNumFrames = argv[0].asInt();
}