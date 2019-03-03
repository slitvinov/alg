PREFIX = $(HOME)
ALG_CFLAGS = -Wall -Wextra -O2 -g

CO_S_CFLAGS = `co.conf --cflags s`
CO_D_CFLAGS = `co.conf --cflags d`

TRG = alg
L = libalg_s.a libalg_d.a

include make/hdr.mk
include make/obj.mk
include make/rules.mk
include make/dep.mk
