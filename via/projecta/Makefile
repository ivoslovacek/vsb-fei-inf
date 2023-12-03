LESS_FILES := $(shell find . -type f -name '*.less')
CSS_FILES := $(patsubst %.less, %.css, $(LESS_FILES))

all: $(CSS_FILES)

%.css: %.less
	lessc $< $@

clean:
	rm -f $(CSS_FILES)

.PHONY: all clean
