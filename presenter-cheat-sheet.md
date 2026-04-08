# Bazel Presenter Cheat Sheet

Use this as your on-desk cue card while presenting.

## Recommended Flow

## 1) Open with audience questions
- Ask: "Where do builds or tests slow your team down today?"
- Ask: "If one file changes, what should really rebuild?"
- Ask: "How often does CI fail because environments drift instead of code changes?"
- Line: "Bazel is an engineering leverage tool, not just another build tool."

## 2) Explain the mental model
- Metaphor: city = repo, buildings = targets, roads = deps, traffic controller = Bazel.
- Line: "Bazel rebuilds only the streets we changed, not the whole city."

## 3) Cover the core ideas
- Targets
- Explicit dependency graph
- Cache reuse (local + remote)
- Line: "No input change means no wasted rebuild."

## 4) Run the live demo core
Run from `demo-project/`:
```bash
bazel query //...
bazel run //app:demo_app
bazel run //app:demo_app
bazel test //tests:math_utils_test
```
Edit `lib/math_utils.cc` tax multiplier `1.07` -> `1.08`, then:
```bash
bazel run //app:demo_app
bazel query 'deps(//app:demo_app)'
```

- Before each command, ask: "What do you expect Bazel to reuse here?"
- After each command, connect the output back to the graph.

## 5) Go deeper if the room wants more
```bash
bazel query 'rdeps(//..., //lib:math_utils)'
bazel aquery 'mnemonic("CppCompile", deps(//app:demo_app))'
```
Line: "Now we can see exactly what rebuilds and why, before we change anything."

## 6) Let the audience practice
- Ask attendees to start Docker before this section.
- From the repo root, run `./scripts/start_practice_container.sh`.
- Inside the container, have them repeat `bazel query`, `bazel run`, and `bazel test`.
- Ask them to edit `lib/math_utils.cc` in the mounted workspace and rerun the app.

## 7) Close on adoption
- Start with one painful workflow
- Run two pipelines in parallel for 2 weeks
- Compare measured before/after

## 8) Close
- CTA: "Reply with one workflow candidate for a 2-week Bazel pilot."

## Backup If Demo Glitches
```bash
bazel clean
bazel build //...
bazel test //...
```

## Conversion One-Liners
- "Bazel scales confidence, not just builds."
- "A small local speedup compounds across every engineer-day."
- "The larger your codebase, the bigger Bazel's ROI."
