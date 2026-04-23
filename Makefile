CC := gcc
CFLAGS := -Wall -Wextra -Werror -O2 -std=c11
BIN_DIR := bin

PROGRAMS := \
	task1_swap \
	task2_reverse_array \
	task3_transpose_matrix \
	task4_reverse_list

.PHONY: all clean run_all FORCE \
	run_task_swap run_task_reverse_array run_task_transpose_matrix run_task_reverse_list

all: $(PROGRAMS:%=$(BIN_DIR)/%)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(BIN_DIR)/%: %.c | $(BIN_DIR)
	$(CC) $(CFLAGS) $< -o $@

run_all: $(PROGRAMS:%=run_task_%)

FORCE:

run_task_%: FORCE
	$(MAKE) $(BIN_DIR)/$*
	./$(BIN_DIR)/$*

run_task_swap: run_task_task1_swap
run_task_reverse_array: run_task_task2_reverse_array
run_task_transpose_matrix: run_task_task3_transpose_matrix
run_task_reverse_list: run_task_task4_reverse_list

clean:
	rm -rf $(BIN_DIR)
