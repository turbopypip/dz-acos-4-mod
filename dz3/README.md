# HW 3 (Linking)

This task demonstrates:

- link-time interposition for `fred` and `john`;
- load-time interposition for `bill` and `sam`.

Build from the repository root:

```bash
cmake -S . -B build
cmake --build build
```

Run without preload:

```bash
./build/dz3/dz3_program
```

Run with preload on Linux:

```bash
LD_PRELOAD=./build/dz3/libdz3_preload.so ./build/dz3/dz3_program
```

Run with preload on macOS:

```bash
DYLD_INSERT_LIBRARIES=./build/dz3/libdz3_preload.dylib DYLD_FORCE_FLAT_NAMESPACE=1 ./build/dz3/dz3_program
```

