# Bazel Demo Audience Guide

This repository contains a small Bazel C++ demo so everyone can clone the repo and run the same commands locally.

## What you will practice

- Discover targets in the workspace
- Run the demo app
- Run unit tests
- Make a small code change and observe targeted rebuild behavior

## Prerequisites

- Bazel installed locally
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

## Core practice flow

From your local machine:

```bash
cd Techtalk/demo-project
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

- Bazel not installed:
  - Install Bazel or Bazelisk first, then rerun the commands.
- Slow first run:
  - Expected. Initial build does real work; follow-up runs are usually faster due to caching.

## Repository layout

- `demo-project/` Bazel demo source and build files
- `scripts/start_practice_container.sh` optional container launcher if you want an isolated environment

## Exit

- Close the terminal or continue experimenting with more Bazel commands.
