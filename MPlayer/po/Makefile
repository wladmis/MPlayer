HELP_FILES = $(wildcard ../help/help_mp-*.h)
LANGS = $(filter-out en,$(basename $(subst help_mp-,,$(notdir $(HELP_FILES)))))
PO_FILES = $(addsuffix .po,$(LANGS))
MO_FILES = $(addsuffix .gmo,$(LANGS))

all: $(MO_FILES)

%.gmo: %.po
	msgfmt -o $@ $<

en.msg: ../help/help_mp-en.h
	gawk -f ./mp_help2msg.awk $< > $@

$(PO_FILES): en.msg $(HELP_FILES)
	gawk -f ./mp_help2msg.awk ../help/help_mp-$(basename $@).h | awk -f ./mp_msg2po.awk en.msg > $@
