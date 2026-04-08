# Bazel Demo Q&A: Anticipated Questions and Answers

A presenter resource with common questions and proven answers for the Bazel techtalk.

---

## Questions About Bazel Fundamentals

### Q1: How is Bazel different from make, gradle, or other build tools?

**Answer:**
"Make and gradle are imperative: you write commands, they run in order. Bazel is declarative: you describe what targets exist and what they depend on, then Bazel figures out the optimal build order.

More importantly, Bazel caches aggressively and can scale across machines. If 10,000 engineers build the same target, only one person pays the compute cost—Bazel reuses the cached result on everyone else's machine."

**Follow-up:** If they ask about specific tools (Maven, CMake, etc.), say: "Those work great for single languages. Bazel shines when you have Java, Python, C++, and JavaScript in the same repo—one graph, one cache, one mental model."

---

### Q2: Do we have to rewrite all our BUILD files by hand?

**Answer:**
"For new targets, yes, you write BUILD.bazel. But Bazel has migration tools. For Java, the buildifier tool can auto-generate BUILD files from pom.xml. For Go, there are gazelle tools.

Start with one package, write one BUILD.bazel by hand, get the win, then expand. Most teams don't migrate everything at once."

---

### Q3: Isn't Bazel the same as Blaze? I heard Google uses Blaze.

**Answer:**
"Blaze is Google's internal tool. Bazel is the open-source version Google released in 2015. They share the same philosophy: explicit dependency graph, caching, and correctness.

If you're not Google, you use Bazel. If you are Google, you probably use both."

---

### Q4: How large is the learning curve?

**Answer:**
"If you understand make or gradle, you can understand Bazel in a few hours. The mental model—targets, rules, labels, dependencies—is straightforward.

The hard part is not Bazel; it is declaring all your dependencies explicitly. That takes discipline, but it pays back in reliability."

---

## Questions About the Demo

### Q5: Why did the second run go so fast?

**Answer:**
"Same inputs, same outputs. The app didn't change, the libraries didn't change, so Bazel reused the build artifacts from the first run. No recompile, no relink, just execution.

After you deploy, if a teammate checks out the same code, their second run is also fast because we share the cache."

---

### Q6: When I edited math_utils.cc, why didn't the test rebuild?

**Answer:**
"Great question. The test only imports math_utils through these functions. Our change edited the implementation, not the header or the function signature. So the test binary doesn't need to rebuild—only the library does.

Bazel is precise about what actually changed. Make and scripts often rebuild too much."

---

### Q7: Can I run those query commands on my own project?

**Answer:**
"Yes, exactly. Once your targets are declared, bazel query and aquery are free introspection tools. 

Try it: bazel query 'deps(//your:target)' shows you the full chain. bazel query 'rdeps(//..., //some:lib)' shows who is affected by that lib. No guessing, no magic."

---

### Q8: What's the difference between deps() and rdeps()?

**Answer:**
"deps shows forward impact: if I build this, what do I need?

rdeps shows reverse impact: if I change this, what breaks?

Before a large refactor, run rdeps to see the blast radius. Then you know exactly which tests and targets to run before pushing."

---

## Questions About Adoption and Cost

### Q9: How much effort is the migration?

**Answer:**
"It depends on size. A small service: 1-2 weeks. A monorepo with 100 services: 2-3 months if you run it in parallel.

The key is: start with one service, get the win, then scale. Don't migrate everything at once."

---

### Q10: What if our build already works? Why change?

**Answer:**
"Fair question. Three reasons:

1. Speed: Incremental rebuilds compound across every engineer every day.
2. Confidence: Explicit dependencies catch bugs early and reduce flakiness.
3. Scale: As the codebase grows, your current build gets slower. Bazel linearizes this.

Pick one workflow—the one that is slowest or most flaky today—and run a 2-week side-by-side pilot. Measure before and after."

---

### Q11: Is Bazel expensive? Do we need special hardware?

**Answer:**
"Bazel is open-source and free. No licensing costs.

Hardware: A developer machine with 4+ cores is ideal. Bazel parallelizes work, so more cores help.

Remote cache and remote execution are optional. A basic remote cache is cheap and can save hours of CI time."

---

### Q12: What if we have legacy code Bazel can't handle?

**Answer:**
"Bazel can call external scripts and tools via the genrule or sh_binary rules. You can wrap legacy builds.

But the cleanest approach: start Bazel on new code, keep legacy code as-is for now, then migrate when you have momentum."

---

## Questions About Correctness and Reliability

### Q13: Why does Bazel reduce flaky tests?

**Answer:**
"Flaky tests usually fail because:
- Different machine state (one engineer has an old cached library, another doesn't)
- Hidden dependencies (the test silently depends on a network call or local file)
- Race conditions (test order matters but shouldn't)

Bazel forces you to declare dependencies explicitly. Same machine state for everyone. That kills most flakiness."

---

### Q14: How does remote cache work?

**Answer:**
"Remote cache is a shared server (like S3 or gRPC cache) that stores build outputs.

Your machine builds target X. Instead of keeping the .o file locally, we upload it to cache. Your teammate on a different machine builds the same target, finds it in cache, and downloads instead of rebuilding.

Setup takes a day; payoff compounds across the team."

---

### Q15: Can I still use CI/CD with Bazel?

**Answer:**
"Yes. CI runs the same bazel commands your laptop does. The benefit is that CI is faster because it reuses cached results from your local builds.

Example: You pushed code. CI runs bazel test //... and gets cache hits from your local build. Instead of 30 minutes, it takes 5 minutes."

---

## Questions About Specific Use Cases

### Q16: We mostly do Python. Does Bazel help us?

**Answer:**
"Yes. Python's pain points are:
- Virtual environments drift (venv on one machine differs from another)
- Dependency conflicts
- Tests running in random order and interfering

Bazel forces hermetic Python environments. Everyone's Python path is identical. Tests run in order and isolation. Huge win for Python teams."

---

### Q17: We have a Java service. What's the benefit?

**Answer:**
"Java's pain: massive dependency trees, version conflicts, slow incremental rebuilds.

Bazel: explicit classpath per target, fine-grained incremental rebuilds, remote cache. A Java team we know cut build time from 8 minutes to 2 minutes."

---

### Q18: We use Docker for deployments. How does Bazel fit?

**Answer:**
"Bazel integrates well. You declare your app as a target, Bazel builds the binary, then rules_docker creates the container image.

Benefit: the same declarative graph covers source → binary → container. Reproducible deployments."

---

### Q19: Can we use Bazel with monorepos?

**Answer:**
"That is Bazel's sweet spot. Monorepos have:
- Shared dependencies (many services depend on common libs)
- Cross-language builds (Java services, Python data pipelines, Node frontends)
- Complex impact analysis (one change affects multiple teams)

Bazel handles all three elegantly. One graph, one cache, one mental model across the whole company."

---

## Objection Handling

### Q20: "This sounds like it will slow us down short-term."

**Answer:**
"You are right. The first 1-2 weeks will be slower as you learn and write BUILD files.

But after 2 weeks, every build is faster. After 2 months, you have saved more engineering time than you spent migrating. After a year, the compounding effect is massive.

That is why we recommend a pilot: one team, one workflow, 2 weeks. Prove the value before committing company-wide."

---

### Q21: "We don't have time to learn a new build system."

**Answer:**
"I hear that. You are busy. But consider: how much time do you spend waiting for builds? How many failed CI runs due to flakiness?

Bazel is an investment that pays back immediately. Start small. One afternoon workshop like this, then one team pilot. If it does not help, you can stop."

---

### Q22: "Our builds are already fast."

**Answer:**
"Great. Then Bazel will keep them fast and make them more reliable. Plus, you get one unified build across polyglot codebases.

But more importantly: scalability. Today your builds are fast because the codebase is small. Bazel is built for predictable performance as you grow to 1,000 engineers and thousands of targets."

---

### Q23: "Isn't Bazel used by big companies like Google and Stripe? Isn't it overkill for us?"

**Answer:**
"Google and Stripe use Bazel because it scales. But you don't need to be Google-scale to benefit.

Even a 50-person team with 3-4 services sees faster CI, fewer flaky failures, and cleaner dependency graphs. Start at small scale; it still helps."

---

## Deep Technical Questions

### Q24: How does Bazel differ from Nix or Buck?

**Answer:**
"All three are declarative builds with explicit graphs and caching.

Nix is a full system package manager, not just a build tool. Buck is Facebook's tool, similar to Bazel but less open community.

Bazel has the largest open community and the most language support. Pick Bazel unless you have a specific reason for Nix or Buck."

---

### Q25: Can Bazel work with our monolith that has complex implicit dependencies?

**Answer:**
"Not cleanly, at first. The pain point is declaring all those implicit dependencies.

But that is actually a good thing: it forces you to see what the monolith depends on. Usually you discover hidden couplings that slow development.

After you clean those up, Bazel becomes easy. And the codebase is healthier."

---

### Q26: What if we want to switch away from Bazel later?

**Answer:**
"Fair question. The output of Bazel is a normal link: and binary. You are not locked in.

If you decide to stop using Bazel, you still have your codebase. You convert to another build system. You have lost the build declarations, but not your code.

Compare that to: you are locked into a proprietary build system and cannot switch."

---

## Questions About the Demo Repository

### Q27: Can I use this demo project as a template for my own?

**Answer:**
"Absolutely. Clone it, modify the source code, update BUILD.bazel files, and you have your own project.

The pattern is the same: one package per folder, one BUILD.bazel per package, targets and rules inside."

---

### Q28: Where do I find more Bazel docs?

**Answer:**
"Start here:
- bazel.build - Official documentation
- rules_cc - C++ rules (what we used in the demo)
- GitHub: bazelbuild/bazel - Source and issues

For Python: rules_python
For Go: rules_go
For Java: Rules_java

Each has its own tutorial. Pick your language."

---

### Q29: How do I get help if I get stuck?

**Answer:**
"Three paths:
1. Bazel Slack community (very active, great people)
2. Stack Overflow tag [bazel]
3. GitHub issues on bazelbuild/bazel

I can also help. Pick one workflow, we run a pilot together, I help troubleshoot."

---

## Questions About Next Steps

### Q30: If we want to pilot Bazel, what is the first step?

**Answer:**
"Three steps:

1. Pick the highest-friction workflow (the one that is slowest or flakiest).
2. Clone the demo repo, adapt it to that workflow.
3. Run side-by-side with your current build for 2 weeks. Measure: build time, test time, CI reliability, team feedback.
4. Decide: scale or stay put.

I can help with steps 1-3."

---

## Handling Unknown Questions

### If asked something you don't know, say:

"That is a great question. I do not have the answer off the top of my head. Let me look it up and get back to you. In the meantime, check the Bazel documentation at bazel.build, or ask the Bazel community on Slack."

**Then:**
- Do not guess
- Do not pretend
- Follow up later with a real answer

---

## Pre-Demo Prep Checklist

- [ ] Read through all Q&As once
- [ ] Practice the first 10 Q&As out loud so answers feel natural
- [ ] Know how to navigate bazel.build docs quickly
- [ ] Have Bazel Slack community link ready
- [ ] Have contact info for follow-up conversations
- [ ] Keep this file open during Q&A for reference

---

End of Q&A Guide
