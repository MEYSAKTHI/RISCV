# Assembler & CPU Simulator

This project implements an assembler and CPU simulator for RISC-V-like instructions. It consists of an assembler that translates assembly code into machine instructions and a CPU simulator that executes these instructions in a pipeline. Additionally, a cache memory model is implemented for performance analysis.

## Features
- **Assembler**: Converts RISC-V-like assembly instructions to machine code.
- **CPU Simulator**: Implements a  pipeline-based CPU model with 5-stages.
- **Cache Simulator**: Simulates cache memory with hit/miss tracking and different memory access policies.

## Supported RISC-V Instructions
This simulator supports the following types of RISC-V instructions:

### R-Type (Register-Register Operations)
- ADD, SUB, SLL, XOR, SRL, SRA, OR, AND, MUL, REM

### I-Type (Immediate Operations)
- ADDI, SLLI, XORI, SRLI, SRAI, ANDI, JALR, LB, LH, LW, LBU, LHU

### S-Type (Store Instructions)
- SB, SH, SW

### B-Type (Branch Instructions)
- BEQ, BNE, BLT, BGE, BLTU, BGEU

### U-Type (Upper Immediate Instructions)
- LUI, AUIPC

### J-Type (Jump Instructions)
- JAL

## Files
- `assem_cpu.cpp` - Implements the assembler and CPU simulation.
- `cache_w.cpp` - Implements the cache memory simulator.
- `a.s`, `b.s` - Sample assembly code files.

## Usage
### Compile and Run the Assembler & CPU Simulator
```sh
 g++ assem_cpu.cpp -o simulator
 ./simulator
```

### Compile and Run the Cache Simulator
```sh
 g++ cache_w.cpp -o cache
 ./cache
```

## Output
- The assembler outputs binary instruction encoding.
- The CPU simulator executes the instructions and prints register/memory states.
- The cache simulator outputs hit/miss statistics and memory access behaviors.


