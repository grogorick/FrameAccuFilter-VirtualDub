#include <FrameCacheFilter.h>
#include <Tools.h>

uint32 *FrameCacheFilter::cache = nullptr;

uint32 FrameCacheFilter::GetParams() {
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

void FrameCacheFilter::Start() {
	if (cache) {
		delete[] cache;
		cache = nullptr;
	}
}

void FrameCacheFilter::Run() {
	if (g_VFVAPIVersion >= 12) {
		const VDXPixmap& pxdst = *fa->dst.mpPixmap;
		const VDXPixmap& pxsrc = *fa->src.mpPixmap;

		switch (pxdst.format) {
		case nsVDXPixmap::kPixFormat_XRGB8888:
			cacheFrame(pxdst.data, pxdst.pitch, pxsrc.data, pxsrc.pitch, pxsrc.w, pxsrc.h);
			break;
		}
	}
	else {
		cacheFrame(fa->dst.data, fa->dst.pitch, fa->src.data, fa->src.pitch, fa->dst.w, fa->dst.h);
	}
}

bool FrameCacheFilter::Configure(VDXHWND hwnd) {
	FrameCacheFilterDialog dlg(mConfig, fa->ifp);
	return dlg.Show((HWND)hwnd);
}

void FrameCacheFilter::cacheFrame(void *dst0, ptrdiff_t dstpitch, const void *src0, ptrdiff_t srcpitch, uint32 w, uint32 h) {
	if (!cache) {
		cache = new uint32[w * h];
		memset(cache, 0, sizeof(uint32) * w * h);
	}

	ptrdiff_t cachepitch = sizeof(uint32) * w;

	switch (mConfig.mMode) {
	case FrameCacheFilterConfig::Save:
		Tools::copyFrame(cache, cachepitch, src0, srcpitch, w, h);
	case FrameCacheFilterConfig::Load:
		Tools::copyFrame(dst0, dstpitch, cache, cachepitch, w, h);
		break;
	default: return;
	}
}

VDXVF_BEGIN_SCRIPT_METHODS(FrameCacheFilter)
VDXVF_DEFINE_SCRIPT_METHOD(FrameCacheFilter, ScriptConfig, "ii")
VDXVF_END_SCRIPT_METHODS()

void FrameCacheFilter::GetSettingString(char *buf, int maxlen) {
	switch (mConfig.mMode) {
	case FrameCacheFilterConfig::Save: SafePrintf(buf, maxlen, " (Save)"); break;
	case FrameCacheFilterConfig::Load: SafePrintf(buf, maxlen, " (Load)"); break;
	default: SafePrintf(buf, maxlen, " (Error)"); break;
	}
}

void FrameCacheFilter::GetScriptString(char *buf, int maxlen) {
	SafePrintf(buf, maxlen, "Config(%d)", mConfig.mMode);
}

void FrameCacheFilter::ScriptConfig(IVDXScriptInterpreter *isi, const VDXScriptValue *argv, int argc) {
	mConfig.mMode = FrameCacheFilterConfig::Mode(argv[0].asInt());
}