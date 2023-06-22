<div align="center">

# PL/Stupid Compiler

![GitHub](https://img.shields.io/github/license/d0p1s4m4/PLSc?logo=opensourceinitiative&style=flat-square)
[![Codecov](https://img.shields.io/codecov/c/gh/d0p1s4m4/PLSc?style=flat-square&logo=codecov&logoColor=codecov)](https://codecov.io/gh/d0p1s4m4/PLSc)
![GitHub Workflow Status (with event)](https://img.shields.io/github/actions/workflow/status/d0p1s4m4/PLSc/ci.yml?style=flat-square)


</div>


## Building

### Prerequisites:

**Mandatories**:
- a C compiler (gcc, clang, msvc....)
- GNU Make
- Git

**Optionals**:
- Inno Setup (:window: only)
- Python (:test_tube:)

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
