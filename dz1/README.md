# HW 1 (C)

Programs:

- `task1_swap.c`: swap two integers and print swapped values.
- `task2_reverse_array.c`: allocate array, reverse, print, free.
- `task3_transpose_matrix.c`: allocate matrix and transposed matrix, transpose, print, free.
- `task4_reverse_list.c`: build singly-linked list until `0`, reverse, print, free.

Build all:

```bash
make
```

Run by one command per task:

```bash
./run_task_swap
./run_task_reverse_array
./run_task_transpose_matrix
./run_task_reverse_list
```

Or directly with `make` (each command compiles the needed task and then runs it):

```bash
make run_task_swap
make run_task_reverse_array
make run_task_transpose_matrix
make run_task_reverse_list
```

Alternative command names:

```bash
./run_task_task1_swap
./run_task_task2_reverse_array
./run_task_task3_transpose_matrix
./run_task_task4_reverse_list
```

Alternative via Makefile targets:

```bash
make run_task_task1_swap
make run_task_task2_reverse_array
make run_task_task3_transpose_matrix
make run_task_task4_reverse_list
```

Run all tasks (build only):

```bash
make all
```

Clean:

```bash
make clean
```
