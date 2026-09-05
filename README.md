# everyday

My personal CLI tool that does some tasks I do all the time.

## Usage

- `everyday package`: `<stage directory> <package version> <package name> [--pre-url=...]`
  - Description: Create a Car package archive and a Car package list entry.
  - Example: `make install DESTDIR=$PWD/stage && everyday stage 1.0 my-awesome-package`
  - Note: `--pre-url`: The URL where your package files are, for example: `--pre-url=https://smth.org/pkg/`
- `everyday gnuftp`: `<package name> <package version> <file extension>`
  - Description: Generate a GNU FTP url to a package.
  - Note: A trailing dot on the left side in the file extension will be automatically removed.
  - Example: With shell expansion: `wget $(everyday gnuftp binutils 2.47 .tar.zst)` 

## Compilation

To compile, as always:

```bash
make -j$(nproc)
```

## Installation

Same as usual, but `PREFIX` is set to `/usr` by default.

```bash
make install
# make install PREFIX=/usr/local
# make install DESTDIR=$(pwd)/../stuff PREFIX=/ BINDIR=Apps/
```
