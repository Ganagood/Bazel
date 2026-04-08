# Stack Adaptation Guide (Java, Go, Python, JS/TS)

Use this to tailor the same Bazel story to your org stack.

## Universal Story Arc
- Pain: slow local loop + expensive CI + inconsistent tooling
- Bazel value: one graph, one cache strategy, one reproducible model
- Pilot: one workflow, two weeks, measured results

## Java Teams
What they care about:
- Incremental compile reliability
- Test stability in CI

Bazel talking points:
- `java_library`, `java_binary`, `java_test`
- Explicit deps reduce classpath drift

Starter target shape:
```python
java_library(
    name = "core",
    srcs = glob(["src/main/java/**/*.java"]),
    visibility = ["//visibility:public"],
)
```

## Go Teams
What they care about:
- Fast tests and deterministic module behavior

Bazel talking points:
- `go_library`, `go_binary`, `go_test`
- Predictable dependency graph in monorepos

Starter target shape:
```python
go_library(
    name = "core",
    srcs = ["core.go"],
    importpath = "example.com/project/core",
    visibility = ["//visibility:public"],
)
```

## Python Teams
What they care about:
- Environment drift and flaky CI

Bazel talking points:
- `py_library`, `py_binary`, `py_test`
- Reproducible dependency lock + hermetic test execution

Starter target shape:
```python
py_library(
    name = "core",
    srcs = ["core.py"],
    visibility = ["//visibility:public"],
)
```

## JS/TS Teams
What they care about:
- Build/test fragmentation across tools

Bazel talking points:
- Standardized build graph across apps and packages
- Better CI parallelization and cache reuse

Starter target shape (conceptual):
```python
# Example macro usage depends on selected ruleset (e.g., rules_js/rules_ts)
# Keep one target per package/module and wire explicit deps.
```

## Conversion Angle by Team Type
- Platform: "Bazel gives policy + consistency across all services."
- Feature teams: "Faster inner loop and fewer CI surprises."
- Leadership: "Measured reduction in wait time and CI spend."

## Pilot KPI Template (copy/paste)
- Baseline local build p50: ____
- Baseline local test p50: ____
- Baseline CI duration p50: ____
- Baseline flaky rate: ____
- After 2 weeks delta: ____%

## Recommended Next Step Per Stack
- Java: migrate one shared module + tests
- Go: migrate one service package + critical tests
- Python: migrate one flaky test suite
- JS/TS: migrate one package build + unit tests
