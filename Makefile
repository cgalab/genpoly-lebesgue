make_lebesgue: make_lebesgue.c
	$(CC) -O2 -Wall -o "$@" $<

clean:
	rm -f make_lebesgue

.PHONY: clean
