# FortuneDB

FortuneDB is a small Redis-inspired key-value database written in C. It runs as an interactive terminal program, keeps string keys and values in a custom hash map, and writes them back to a tiny snapshot file when you leave. No server process, no network layer, and—mercifully—no configuration ceremony: just a compact place to learn what sits underneath a dictionary and a database.

## Why I built this

I wanted to stop treating things such as Python dictionaries and Redis as polite magic. Building a small database from scratch was a practical way to get my hands on hash tables, collisions, linked lists, parsing, file I/O, pointers, and the particular brand of responsibility that comes with allocating memory in C.

It is deliberately a learning project, not an attempt to reproduce Redis feature for feature.

## Features

- Interactive REPL with an `exit` command.
- `SET`, `GET`, `DEL`, `EXIST`, and `COUNT` commands.
- Case-insensitive command names.
- Bare values and quoted strings, including strings with spaces.
- A 256-bucket hash map using the `djb2` hash function.
- Separate chaining with linked lists when keys land in the same bucket.
- Snapshot persistence: load a database on startup and save it on exit.
- Command validation for unknown commands and incorrect argument counts.

## How it works

Input passes through a small lexer and parser before being dispatched to the hash map. The map hashes a key into one of 256 buckets; collisions are kept in a linked list hanging off that bucket. `SET` updates an existing key or adds a new node, while the other commands look up, delete, count, or test for a key.

When the program starts, it reads the selected snapshot if one already exists. On a normal `exit`, it walks the hash map and writes the current contents back out. Simple on purpose, which is often the best kind of simple when you are trying to see the machinery clearly.

## Installation

You only need a C11-capable compiler and `make`. The provided build uses `gcc` by default and has no third-party dependencies.

Clone the repository and enter it:

```sh
git clone git@github.com:duckdoe/fortunedb.git
cd fortunedb
```

## Building

Build with:

```sh
make
```

The executable is written to `bin/fortunedb`.

To remove the compiled objects and executable:

```sh
make clean
```

## Usage

Pass a database name when starting the program. FortuneDB adds `.db` itself, so this command loads the included `data/fortune.db` snapshot:

```sh
./bin/fortunedb data/fortune
```

An example session:

```text
Welcome to fortunedb, type 'exit' to leave

> SET greeting "Hello world"
> GET greeting
Hello world
> EXIST greeting
YES
> COUNT
1 keys
> DEL greeting
> EXIST greeting
NO
> exit
Goodbye :)
Saving changes...
```

### Commands

| Command | What it does |
| --- | --- |
| `SET key value` | Creates a key or replaces its value. Values containing spaces must be quoted. |
| `GET key` | Prints a value, or an error when the key is absent. |
| `DEL key` | Deletes a key. |
| `EXIST key` | Prints `YES` or `NO` depending on whether the key exists. |
| `COUNT` | Prints the number of stored keys. |
| `exit` | Saves the database and closes the REPL. |

Keys are unquoted, whitespace-delimited identifiers. The command names themselves are case-insensitive, so `set`, `SET`, and `Set` all reach the same command.

## Persistence

Each database is a plain-text `.db` snapshot with one `key=value` entry per line. For example, `data/fortune.db` might look like this:

```text
greeting=Hello world
name=fortune
```

The snapshot is loaded when FortuneDB starts and rewritten when you leave with `exit`. There are no separate `SAVE` or `LOAD` commands; persistence is tied to the program lifecycle.

## Project structure

```text
.
├── src/         # C source files: REPL, parser, hash map, and storage
├── include/     # project header files
├── data/        # sample persisted database
├── bin/         # generated executable and object files (ignored by Git)
├── Makefile     # build instructions
└── README.md
```

## License

No license has been provided for this repository.
