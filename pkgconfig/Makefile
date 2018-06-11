PREFIX = $(HOME)
TRG = alg
P = alg_s.pc alg_d.pc
SED = sed

install: $P
	mkdir -p -- "$(PREFIX)/share/pkgconfig"
	cp $P "$(PREFIX)/share/pkgconfig"

alg_s.pc: $(TRG).pc.in
	$(SED) "s,@PREFIX@,$(PREFIX),g; s,@PREC@,s,g" $< > $@
alg_d.pc: $(TRG).pc.in
	$(SED) "s,@PREFIX@,$(PREFIX),g; s,@PREC@,d,g" $< > $@

clean:; rm -f $P
test:

.PHONY: clean install test
