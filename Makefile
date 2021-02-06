default: main
.PHONY: default

include $(PUREC_DIR)/mk/target.mk

main: .spago

$(eval $(call purs_mk_target,main,Test.Main,src test))

main_leackcheck: main
leakcheck: main_leackcheck
check: leakcheck
