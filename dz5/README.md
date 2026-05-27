# HW 5 (Processes)

Build from the repository root:

```bash
cmake -S . -B build
cmake --build build
```

Run:

```bash
./build/dz5/dz5_executer "ls -l /" "date"
```

The program runs each command through a pipe connected to `wc -c` and prints the byte size of each command output.

