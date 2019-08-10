#
# Makefile to generate build tools
#

STAMP = buildmk.stamp

ALWAYS = generated_lists

all: $(STAMP) $(ALWAYS)
	$(MAKE) -s -f build/build2.mk

generated_lists:
	@echo makefile_am_files = Zend/Makefile.am > $@
	@echo config_m4_files = sapi/*/config.m4 >> $@

$(STAMP): build/buildcheck.sh
	@build/buildcheck.sh $(STAMP)

.PHONY: $(ALWAYS)
