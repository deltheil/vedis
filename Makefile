LIB=vedis
LIBNAME=lib$(LIB).a
DIR=build

all: lib

lib: $(DIR)/$(LIBNAME)

$(DIR)/%.o: %.c vedis.h
	install -d $(DIR)
	$(CC) -c -I. $(CFLAGS) $< -o $@

$(DIR)/$(LIBNAME): $(DIR)/vedis.o
	install -d $(DIR)
	rm -f $@
	$(AR) cq $@ $(DIR)/vedis.o

demo: $(DIR)/hello
	@./$(DIR)/hello

$(DIR)/hello: $(DIR)/hello.o
	$(CC) -L$(DIR) -l$(LIB) $< -o $@

$(DIR)/hello.o: hello.c $(DIR)/$(LIBNAME)

check: lib
	$(MAKE) -C tests clean
	$(MAKE) -C tests check

clean:
	rm -rf $(DIR)

.PHONY: all lib clean
