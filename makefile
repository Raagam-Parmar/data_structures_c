.PHONY: all linked_list stack queue queue_linked_list priority_queue

all: linked_list stack queue queue_linked_list priority_queue

clean: clean_linked_list clean_stack clean_queue clean_queue_linked_list clean_priority_queue


linked_list:
	python3 converter.py linked_list/int_linked_list.h 

clean_linked_list:
	rm -f linked_list/linked_list.h


stack:
	python3 converter.py stack/int_stack.h

clean_stack:
	rm -f stack/stack.h


queue:
	python3 converter.py queue/int_queue.h

clean_queue:
	rm -f queue/queue.h


queue_linked_list:
	python3 converter.py queue/int_queue_linked_list.h

clean_queue_linked_list:
	rm -f queue/queue_linked_list.h


priority_queue:
	python3 converter.py priority_queue/int_priority_queue.h

clean_priority_queue:
	rm -f priority_queue/priority_queue.h
	