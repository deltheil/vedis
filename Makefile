LIBNAME=libvedis.a
DIR=build

all: lib

lib: $(DIR)/$(LIBNAME)

$(DIR)/vedis.o: vedis.c vedis.h
	install -d $(DIR)
	$(CC) -c $(CFLAGS) $< -o $@

$(DIR)/$(LIBNAME): $(DIR)/vedis.o
	install -d $(DIR)
	rm -f $@
	$(AR) cq $@ $(DIR)/vedis.o

clean:
	rm -rf $(DIR)

.PHONY: all lib clean
