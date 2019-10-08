D = tool pkgconfig lib example/min example/eig

install: dir
test: dir
clean: dir
include make/dir.mk
hdr:; (cd lib; make hdr)
.PHONY: test install clean hdr
