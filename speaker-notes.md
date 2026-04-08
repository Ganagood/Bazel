# Speaker Notes

## 1) Opening script
- Say: "Today we will do this in three steps: learn, see, do. First I explain Bazel, then I run the commands live, then you run the same flow in a container."
- Say: "Bazel is not just a build tool. It is a system for protecting developer time."

## 2) Audience engagement questions
- Ask: "Where do builds or tests slow your team down today?"
- Ask: "If one file changes, what should really rebuild?"
- Ask: "How often does CI fail because environment and not code changed?"
- Bridge line: "Keep those answers in mind. We will test whether Bazel addresses exactly those problems."

## 3) Mental model script
- Say: "Imagine your repository as a city. Targets are buildings. Dependencies are roads. Bazel is traffic control."
- Say: "When one street closes, traffic control reroutes only the affected roads. It does not rebuild the whole city."
- Say: "That is what selective rebuild means in practice."

## 4) Core concepts script
- Say: "There are three ideas to keep in mind: targets, explicit dependency graph, and caching."
- Say: "If inputs are unchanged, outputs are reused. That one sentence explains most of Bazel speedups."

## 5) Live demo script
- Use [demo-runbook.md](demo-runbook.md) as the exact command sequence.
- Before each command, ask: "What do you expect Bazel to reuse here?"
- After each command, explain one takeaway in one line.

### 5.1 Query
- Command: bazel query //...
- Say: "This is the map of build and test units Bazel understands."

### 5.2 First run
- Command: bazel run //app:demo_app
- Say: "First run does real work. This is the cold path."

### 5.3 Second run
- Command: bazel run //app:demo_app
- Say: "Now watch reuse. Same inputs, so Bazel reuses prior results."

### 5.4 Tests
- Command: bazel test //tests:math_utils_test
- Say: "Tests are first-class nodes in the same graph, not a separate toolchain."

### 5.5 Small code change
- Edit lib/math_utils.cc tax value from 0.07 to 0.08.
- Command: bazel run //app:demo_app
- Say: "Only impacted targets rebuild. This is the exact behavior we asked for at the beginning."

### 5.6 Dependency introspection
- Command: bazel query 'deps(//app:demo_app)'
- Say: "Now we can inspect impact before risky changes. This improves confidence in refactoring."

## 6) Optional advanced segment
- If room asks for deeper visibility, run:
	- bazel query 'rdeps(//..., //lib:math_utils)'
	- bazel aquery 'mnemonic("CppCompile", deps(//app:demo_app))'
- Say: "rdeps shows who is affected. aquery shows actions Bazel will execute."

## 7) Audience practice script
- Say: "Now your turn. You will run the same sequence in the same environment."
- Point audience to [README.md](README.md).
- Ask them to run from repo root: ./scripts/start_practice_container.sh
- Ask them to run inside container:
	- cd /workspace
	- bazel query //...
	- bazel run //app:demo_app
	- bazel test //tests:math_utils_test
- Ask them to apply the same math_utils edit and rerun app.
- Say: "If you can reproduce this yourself, you now understand the model and the workflow."

## 8) Closing script
- Say: "Bazel gives speed, correctness, and scalability from one explicit build graph."
- Say: "Start with one high-friction workflow, run side-by-side for two weeks, and compare measured outcomes."
- CTA: "What is one workflow in your team that should be the first Bazel pilot?"

## 9) Filler lines for transitions
- "Let us make a prediction before we run this command."
- "The graph explains the result we just saw."
- "Same inputs, same outputs, so reuse is expected."
- "This is where Bazel starts compounding value across teams."
