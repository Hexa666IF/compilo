# IFCC-H4232

IFCC is a C compiler coded in C++ that produces x86, ARM and MSP430 assembly code.

## 1. Building

A makefile is provided to facilitate the build process.

### 1.1 Building natively

Building on a Linux machine with antlr4 and the C++ runtime installed and configured.

```bash
make
```
or
```bash
make build
```

### 1.2 Building with docker

Building on a machine with docker installed and configured

```bash
make build-docker
```

## 2. Testing

The provided makefile is used to facilitate the testing process.

### 2.1 Testing natively

Testing on a Linux machine with antlr4 and the C++ runtime installed and configured.

```bash
make test
```

### 2.2 Testing with docker

Testing on a machine with docker installed and configured

```bash
make test-docker
```

## 3. Usage

```bash
ifcc [OPTIONS] FILE 
```
### 3. 1 Options

`--target=<target>`
Selects the target architecture. Valid values are : `x86`, `arm`, `msp430`

## 3. 2 Examples

Standard - Compiles to x86 and outputs to stdout

```bash
ifcc my_program.c
```

With options - Compiles to ARM and outputs to file

```bash
ifcc --target=arm my_program.c > my_assembly.s
```

## 4. License
[MIT](https://choosealicense.com/licenses/mit/)