# IFCC-H4232

IFCC is a C compiler coded in C++ that produces x86, ARM and MSP430 assembly code.

## Building

A makefile is provided to facilitate the build process.

### Building natively

Building on a Linux machine with antlr4 and the C++ runtime installed and configured.

```bash
make
```
or
```bash
make build
```

### Building with docker

Building on a machine with docker installed and configured

```bash
make build-docker
```

## Testing

The provided makefile is used to facilitate the testing process.

### Testing natively

Testing on a Linux machine with antlr4 and the C++ runtime installed and configured.

```bash
make test
```

### Testing with docker

Testing on a machine with docker installed and configured

```bash
make test-docker
```

## Usage

```bash
ifcc [OPTIONS] FILE 
```
### Options

`--target=<target>`
Selects the target architecture. Valid values are : `x86`, `arm`, `msp430`

## Examples

Standard - Compiles to x86 and outputs to stdout

```bash
ifcc my_program.c
```

With options - Compiles to ARM and outputs to file

```bash
ifcc --target=arm my_program.c > my_assembly.s
```

## License
[MIT](https://choosealicense.com/licenses/mit/)