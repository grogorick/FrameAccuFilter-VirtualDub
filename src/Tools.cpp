#include <Tools.h>
#include <cstring>

void Tools::copyFrame(void *dst0, ptrdiff_t dstpitch, const void *src0, ptrdiff_t srcpitch, uint32 w, uint32 h) {
	char *dst = (char *)dst0;
	const char *src = (const char *)src0;
	for (uint32 y = 0; y < h; ++y) {
		// Copy scanline
		memcpy(dst, src, sizeof(uint32) * w);
		src += srcpitch;
		dst += dstpitch;
	}
}
