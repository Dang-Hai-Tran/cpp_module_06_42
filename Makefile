ALL_DIRS := $(shell find ./ -type d -name 'ex*')

all: $(ALL_DIRS)
	for dir in $(ALL_DIRS); do \
		make -C $$dir; \
	done

fclean: $(ALL_DIRS)
	for dir in $(ALL_DIRS); do \
		make fclean -C $$dir; \
	done
