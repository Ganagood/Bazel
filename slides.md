# Slide 1 - Bazel and Important Glossary

- Bazel: graph-based build and test system
- Target: buildable/testable unit (for example `//app:demo_app`)
- Dependency graph: explicit relationships between targets
- Cache: reuse outputs when inputs are unchanged

**Focus:** Core terms first.

---

# Slide 2 - Q&A Round 1

- Any questions on Bazel basics so far?
- Target, dependency graph, and cache are the key ideas
- If this is clear, we will move to a quick concept check

**Goal:** Quick clarity before demo.

---

# Slide 3 - Quick Check Questions


- If one file changes, should everything rebuild?
- What does `//app:demo_app` represent?
- What does Bazel reuse when inputs are unchanged?
- Which command shows dependencies of a target?

**Engagement:** Check understanding.

---

# Slide 4 - Simple Project Demo


- Use `app/`, `lib/`, and `tests/` to show target structure
- Run query, run, test, and small edit workflow
- Call out selective rebuild and cache behavior

**Approach:** Show it live.

---

# Slide 5 - Q&A Round 2


- Any questions from the live demo so far?
- We can revisit `deps` and `rdeps` if you want impact examples
- If this is clear, we will move to hands-on practice

**Goal:** Answer practical questions.

---

# Slide 6 - Audience Hands-On


- Clone `https://github.com/Ganagood/Techtalk.git` to your machine
- Open the repo locally and run the same Bazel commands
- Execute query, run, test, and one code edit
- Repeat the flow and see the rebuild behavior yourself

**Practice:** Audience runs it now.

---

# Slide 7 - Official Documentation Guide


- Main docs: `https://bazel.build`
- Query reference: `https://bazel.build/query/language`
- Bzlmod guide: `https://bazel.build/external/overview`
- Rules and ecosystem: `https://github.com/bazelbuild`

**Next:** Share official docs.

---

# Slide 8 - Fun Close


- Funny question: Is your build faster than your coffee machine?
- Funny question: How many times per day do we rebuild unchanged code?
- If no doubts remain, close the session with thanks

**Wrap-up:** Light close.

---

# Slide 9 - Live Demo Commands

- `bazel query //...` -> what exists
- `bazel run //app:demo_app` -> first run
- `bazel run //app:demo_app` -> cache reuse
- `bazel test //tests:math_utils_test` -> test run
- edit `lib/math_utils.cc` and rerun app
- `bazel query 'deps(//app:demo_app)'` -> dependency view

**Watch for:** reuse, rebuild scope, and dependency visibility.

---

# Slide 10 - Audience Practice Commands

- Clone with `git clone https://github.com/Ganagood/Techtalk.git`
- Open `Techtalk/demo-project`
- Run `bazel query //...`, `bazel run //app:demo_app`, and `bazel test //tests:math_utils_test`
- Repeat the `math_utils.cc` change and rerun the app

**Repo:** `https://github.com/Ganagood/Techtalk.git`

**Why this works:** Same environment, same files, same command flow.

---

# Slide 11 - Close

- Funny check: If Bazel saves 15 minutes per engineer per day, what is that worth in a month?
- If no more questions, thank the audience and close
- Continue learning with official Bazel docs

**Final line:** Bazel helps teams spend less time waiting and more time building.
