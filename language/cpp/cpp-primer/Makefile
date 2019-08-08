DIRS = ch01 ch07 ch08

all:
	$(foreach dir,$(DIRS),cd $(dir); make)

clean:
	$(foreach dir,$(DIRS),cd $(dir); make clean)

clobber:
	$(foreach dir,$(DIRS),cd $(dir); make clobber)
