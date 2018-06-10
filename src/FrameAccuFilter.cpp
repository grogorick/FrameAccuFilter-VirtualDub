#include <FrameAccuFilter.h>

uint32 FrameAccuFilter::GetParams() {
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

void FrameAccuFilter::Start() {
	if (accu) {
		delete accu;
		accu = nullptr;
	}
}

void FrameAccuFilter::Run() {
	if (g_VFVAPIVersion >= 12) {
		const VDXPixmap& pxdst = *fa->dst.mpPixmap;
		const VDXPixmap& pxsrc = *fa->src.mpPixmap;

		switch (pxdst.format) {
		case nsVDXPixmap::kPixFormat_XRGB8888:
			accumulateFrame(pxdst.data, pxdst.pitch, pxsrc.data, pxsrc.pitch, pxsrc.w, pxsrc.h);
			break;
		}
	}
	else {
		accumulateFrame(fa->dst.data, fa->dst.pitch, fa->src.data, fa->src.pitch, fa->dst.w, fa->dst.h);
	}
}

bool FrameAccuFilter::Configure(VDXHWND hwnd) {
	FrameAccuFilterDialog dlg(mConfig, fa->ifp);
	return dlg.Show((HWND)hwnd);
}

void FrameAccuFilter::accumulateFrame(void *dst0, ptrdiff_t dstpitch, const void *src0, ptrdiff_t srcpitch, uint32 w, uint32 h) {
	if (!accu) {
		accu = new uint32[w * h];
		memset(accu, 0, sizeof(uint32) * w * h);
	}

	char *dst = (char *)dst0;
	const char *src = (const char *)src0;
	for (uint32 y = 0; y<h; ++y) {
		// Get scanline
		uint32 *srcline = (uint32 *)src;
		uint32 *dstline = (uint32 *)dst;
		uint32 *acculine = &accu[y * w];
		for (uint32 x = 0; x<w; ++x) {
			// Process pixels
			uint32 srcData = srcline[x];
			/*
			uint32 gray = uint32(0.299f * (srcData & 0x000000ff) + 0.587f * ((srcData & 0x0000ff00) >> 8) + 0.114f *((srcData & 0x00ff0000) >> 16));
			dstline[x] = gray | (gray << 8) | (gray << 16);
			/*/
			uint32 accuData = acculine[x];
			uint32 srcR = (srcData & 0x000000ff);
			uint32 srcG = (srcData & 0x0000ff00) >> 8;
			uint32 srcB = (srcData & 0x00ff0000) >> 16;
			uint32 accuR = (accuData & 0x000000ff);
			uint32 accuG = (accuData & 0x0000ff00) >> 8;
			uint32 accuB = (accuData & 0x00ff0000) >> 16;
			dstline[x] = (acculine[x] = max(srcR, accuR) | (max(srcG, accuG) << 8) | (max(srcB, accuB) << 16));
			/**/
		}
		src += srcpitch;
		dst += dstpitch;
	}
}

VDXVF_BEGIN_SCRIPT_METHODS(FrameAccuFilter)
VDXVF_DEFINE_SCRIPT_METHOD(FrameAccuFilter, ScriptConfig, "ii")
VDXVF_END_SCRIPT_METHODS()

void FrameAccuFilter::GetSettingString(char *buf, int maxlen) {
	SafePrintf(buf, maxlen, " (Mode:%d)", mConfig.mMode);
}

void FrameAccuFilter::GetScriptString(char *buf, int maxlen) {
	SafePrintf(buf, maxlen, "Config(%d)", mConfig.mMode);
}

void FrameAccuFilter::ScriptConfig(IVDXScriptInterpreter *isi, const VDXScriptValue *argv, int argc) {
	mConfig.mMode = FrameAccuFilterConfig::Mode(argv[0].asInt());
}