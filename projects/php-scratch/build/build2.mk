include generated_lists

TOUCH_FILES = mkinstalldirs install-sh missing

config_h_in = main/php_config.h.in

targets = $(TOUCH_FILES) configure $(config_h_in)

PHP_AUTOCONF ?= 'autoconf'
PHP_AUTOHEAD ?= 'autoheader'

SUPPRESS_WARNINGS ?= 2>&1 | (egrep -v '(AC_PROG_CXXCPP was called before AC_PROG_CXX|defined in acinclude.m4 but never used)'||true)

all: $(targets)

$(config_h_in): configure
	@echo rebuilding $@
	@rm -f $@
	$(PHP_AUTOHEAD) $(SUPPRESS_WARNINGS)

$(TOUCH_FILES):
	touch $(TOUCH_FILES)

aclocal.m4: configure.ac acinclude.m4
	@echo rebuilding $@
	cat acinclude.m4 ./build/libtool.m4 > $@

configure: aclocal.m4 configure.ac $(config_m4_files)
	@echo rebuilding $@
	@rm -f $@
	$(PHP_AUTOCONF) -f $(SUPPRESS_WARNINGS)
