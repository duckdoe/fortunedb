# Redis-Lite

> A miniature Redis-inspired in-memory key-value database written in C.

This project is part of my journey into systems programming. The goal is **not** to clone Redis feature-for-feature, but to understand how databases work under the hood by implementing one from scratch.

---

## Goals

- Learn hash tables by implementing my own.
    
- Build a command parser (REPL).
    
- Understand persistence.
    
- Practice manual memory management.
    
- Explore systems programming concepts before learning Rust.
    

---

## Features

### Core Commands

-  `SET key value`
    
-  `GET key`
    
-  `DEL key`
    
-  `EXISTS key`
    
-  `COUNT`
    
-  `CLEAR`
    

---

### Storage

-  Custom hash map implementation
    
-  Collision handling using linked lists
    
-  Dynamic memory allocation
    
-  String key/value support
    

---

### Persistence

-  Save database to disk on exit
    
-  Load database on startup
    
-  Simple snapshot file format
    

---

### REPL

-  Interactive shell
    
-  Command parsing
    
-  Helpful error messages
    
-  `HELP` command
    
-  `EXIT` command
    

---

## Stretch Goals

### Query Commands

-  `KEYS *`
    
-  `KEYS prefix*`
    
-  `SAVE`
    
-  `LOAD`
    

### Better Hash Map

-  Automatic resizing
    
-  Load factor calculation
    
-  Improved hash function experiments
    

### Advanced Features

-  Append-only log
    
-  Expiring keys (`EXPIRE`)
    
-  Basic transactions
    
-  Benchmark command
    

---

## Example Session

```text
> SET language C
OK

> SET project redis-lite
OK

> GET language
C

> EXISTS project
true

> COUNT
2

> DEL language
OK

> GET language
(nil)

> EXIT
Saving snapshot...
Goodbye!
```

---

# Project Structure

```
redis-lite/
│
├── src/
│   ├── main.c
│   ├── repl.c
│   ├── parser.c
│   ├── hashmap.c
│   ├── persistence.c
│   └── commands.c
│
├── include/
│   ├── hashmap.h
│   ├── parser.h
│   ├── persistence.h
│   └── commands.h
│
├── database.db
├── Makefile
└── README.md
```

---

## Architecture

```
User Input
     │
     ▼
   Parser
     │
     ▼
Command Dispatcher
     │
     ▼
 Hash Map
     │
     ▼
 Persistence
```

---

## Hash Map Design

The database uses a hash table for constant-time average lookups.

```
Buckets

0 ──► NULL

1 ──► ("language", "C")

2 ──► NULL

3 ──► ("name", "Fortune")
          │
          ▼
     ("project", "redis-lite")

4 ──► NULL
```

When two keys hash to the same bucket, collisions are handled using **linked lists (separate chaining).**

---

## Learning Objectives

By the end of this project I should understand:

- How hash tables work
    
- Why collisions happen
    
- How linked lists solve collisions
    
- How persistence works
    
- How command interpreters are built
    
- Memory allocation in C
    
- File I/O
    
- Pointer manipulation
    

---

## Development Roadmap

### Phase 1 — Hash Map

-  Hash function
    
-  Insert
    
-  Lookup
    
-  Delete
    

### Phase 2 — REPL

-  Read commands
    
-  Parse input
    
-  Execute commands
    

### Phase 3 — Persistence

-  Save snapshot
    
-  Load snapshot
    

### Phase 4 — Extra Commands

-  EXISTS
    
-  COUNT
    
-  KEYS
    

### Phase 5 — Polish

-  Error handling
    
-  Better parser
    
-  Cleaner code
    
-  Documentation
    

---

## Inspiration

- Redis
    
- CPython dictionaries
    
- The C Programming Language
    
- Writing software from first principles
    

---

## Why?

I wanted to understand what actually happens underneath data structures like Python's `dict` and databases like Redis instead of simply using them.

This project is my first step into systems programming.
