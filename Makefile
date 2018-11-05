D = tool pkgconfig lib example/min example/eig

install: dir
test: dir
clean: dir
include make/dir.mk

.PHONY: test install clean
