default: main
.PHONY: default

CFLAGS = -O0 -g3

include $(PUREC_DIR)/mk/target.mk

main: .spago

$(eval $(call purs_mk_target,main,Test.Main,src test))

check: main_leakcheck
.PHONY: check
