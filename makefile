# source directory		DS implementations
S=source
# include directory		General headers and error code headers
I=include
# tools directory    	Contains all tools for macro conversion
T=scripts
# build directory		The output of the build
B=build
# generic builds		The output of generic-type builds inside Build directory
G=generic
# void builds			The output of void-type builds inside Build directory
V=void

OBJS = \
	binary_tree \
	heap \
	linked_list \
	priority_queue \
	queue \
	stack \

.PHONY: all-g all-v all

all: all-g all-v

all-g:
	for obj in $(OBJS); do \
		python3 $T/convert.py -s "$(S)/__t_$$obj.c" -o "$(B)/$(G)/__t_$$obj.h" -t generic ; \
	done

all-v:
	for obj in $(OBJS); do \
		python3 $T/convert.py -s "$(S)/__t_$$obj.c" -o "$(B)/$(V)/$$obj.c" -t void ; \
	done

clean:
	rm -fr "$(B)"

clean-g:
	rm -fr "$(B)/$(G)"

clean-v:
	rm -fr "$(B)/$(V)"
