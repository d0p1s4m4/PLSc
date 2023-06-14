<div align="center">

# PL/Stupid Compiler

![GitHub](https://img.shields.io/github/license/d0p1s4m4/PLSc?logo=opensourceinitiative&style=flat-square)

</div>


## Building

### Prerequisites:

**Mandatories**:
- a C compiler (gcc, clang, msvc....)
- GNU Make
- Git

**Optionals**:
- Inno Setup (:window: only)

### On UNIX-like OSes:

```
$ make
$ make check # if you want to run unit tests
```

and then as root:
```
# make install
```

### On NT-like OSes:

Install deps:
```
> winget import -i .\win32\winget-deps.json --accept-package-agreements
```

Building:

```
> make
```
