install: $L $H
	co.install $L $(PREFIX)/lib
	co.install $H $(PREFIX)/include

libalg_s.a: $O $(O_S); ar rv $@ $O $(O_S) && ranlib $@
libalg_d.a: $O $(O_D); ar rv $@ $O $(O_D) && ranlib $@
$O : $H $I

%.o:   %.c; $(CC) $(CFLAGS) $(ALG_CFLAGS) $(CO_S_CFLAGS) -c -o $@ $<
%.s.o: %.c; $(CC) $(CFLAGS) $(ALG_CFLAGS) $(CO_S_CFLAGS) -c -o $@ $<
%.d.o: %.c; $(CC) $(CFLAGS) $(ALG_CFLAGS) $(CO_D_CFLAGS) -c -o $@ $<

clean:; rm -f $O $(O_S) $(O_D) $L
test:

.PHONY: clean install test
