PREFIX = $(HOME)
ALG_CFLAGS = -Wall -Wextra -O2 -g

HE_S_CFLAGS = `he.conf --cflags s`
HE_D_CFLAGS = `he.conf --cflags d`

TRG = alg
L = libalg_s.a libalg_d.a

include make/hdr.mk
include make/obj.mk
include make/rules.mk
include make/dep.mk
