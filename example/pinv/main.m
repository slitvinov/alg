#!/usr/env/env octave

f = stdin();
d = fscanf(f, "%d", 1);
m = dlmread(f);
pinv(m)
