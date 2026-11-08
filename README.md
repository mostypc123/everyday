# everyday

My personal CLI tool that does some tasks I do all the time.

This is some of the worst code I ever wrote (It is bad, but reading this a few months later makes me think its not THAT bad).

## Usage

More info in `everyday --help` / `everyday help` / `everyday -h`.

- `everyday package`: `<stage directory> <package version> <package name> [--pre-url=...] [--push[=optional custom repo url]] [--update]`
- `everyday gnuftp`: `<package name> <package version> <file extension>`
- `everyday rrclone`: `<repo name>`
- `everyday <task name>`

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

## License

The Unlicense.
