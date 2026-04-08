# Bazel Demo Audience Guide

This repository contains a small Bazel C++ demo and a practice container so everyone can run the same commands.

## What you will practice

- Discover targets in the workspace
- Run the demo app
- Run unit tests
- Make a small code change and observe targeted rebuild behavior

## Prerequisites

- Docker Desktop running (or any Docker daemon)
- Git installed

## Get the code

```bash
git clone git@github.com:Ganagood/Techtalk.git
cd Techtalk
```

If your environment does not support SSH clone, use HTTPS:

```bash
git clone https://github.com/Ganagood/Techtalk.git
cd Techtalk
```

## Start practice container

From the repository root:

```bash
./scripts/start_practice_container.sh
```

This opens an interactive shell in a container with Bazel preinstalled.
Your project is mounted at `/workspace`.

## Core practice flow

Inside the container:

```bash
cd /workspace
bazel query //...
bazel run //app:demo_app
bazel test //tests:math_utils_test
```

## Change one file and rerun

Edit `lib/math_utils.cc` and change tax rate in `ApplyTax` from `0.07` to `0.08`, then run:

```bash
bazel run //app:demo_app
bazel query 'deps(//app:demo_app)'
```

## Optional advanced commands

```bash
bazel query 'rdeps(//..., //lib:math_utils)'
bazel aquery 'mnemonic("CppCompile", deps(//app:demo_app))'
```

## Common issues

- Docker not running:
  - Start Docker Desktop, then rerun `./scripts/start_practice_container.sh`.
- Permission denied on script:
  - Run `chmod +x scripts/start_practice_container.sh` once.
- Slow first run:
  - Expected. Initial build does real work; follow-up runs are usually faster due to caching.

## Repository layout

- `demo-project/` Bazel demo source and build files
- `scripts/start_practice_container.sh` one-command container launcher

## Exit

- Type `exit` to leave the container shell.
