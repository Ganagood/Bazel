# Live Demo Runbook

Run commands from `demo-project/`.

## 1) Set up the room before commands
- Ask where builds or tests slow the team down today.
- Ask what they expect to rebuild when one file changes.
- Tell the room they will get a practice container after the walkthrough.

## 2) Verify Bazel
```bash
bazel version
```

If Bazel is not installed, install Bazelisk and retry.

## 3) Show project targets
```bash
bazel query //...
```

Talk track:
- "This is the graph of build/test units Bazel understands."

## 4) First run
```bash
bazel run //app:demo_app
```

Talk track:
- "First execution does real build work."

## 5) Second run
```bash
bazel run //app:demo_app
```

Talk track:
- "Notice the second run is much faster; Bazel reused prior work."

## 6) Run tests
```bash
bazel test //tests:math_utils_test
```

Talk track:
- "Tests are first-class targets in the same graph."

## 7) Make a tiny code change
Edit `lib/math_utils.cc` and change tax rate in `ApplyTax` from `0.07` to `0.08`.

Then run:
```bash
bazel run //app:demo_app
```

Talk track:
- "Only impacted targets rebuild. No full project rebuild."

## 8) Dependency introspection
```bash
bazel query 'deps(//app:demo_app)'
```

Talk track:
- "This is the exact dependency impact surface of the app target."

## 9) Audience practice in containers
- Prerequisite: Docker Desktop or another Docker daemon is running on attendee machines.
- From the repo root, ask attendees to run `./scripts/start_practice_container.sh`.
- Inside the container, have them run:

```bash
cd /workspace
bazel query //...
bazel run //app:demo_app
bazel test //tests:math_utils_test
```

- Ask them to repeat the `math_utils.cc` edit and rerun `bazel run //app:demo_app`.

## 10) Close with scale message
- Same concepts scale to large repos and CI
- Remote cache + remote execution can multiply gains

## Optional advanced extension
If the audience wants deeper graph visibility, run the advanced sequence in `../intermediate-wow-demo.md`.

## Tailor to your org stack
After the demo, use `../stack-adaptation-guide.md` to switch examples and migration entry points by language ecosystem.

## Optional backup commands
```bash
bazel clean
bazel build //...
```
