# CS170 projects

Two assignments for CS 170, Introduction to AI, at UC Riverside, by Michael Chen and Tabito Sakamoto. Each project retains its own `src` tree, CLI, results documentation, and resources.

| Project | Standalone command, from the project directory | Dependencies and resources |
| --- | --- | --- |
| [01 · Eight-puzzle search](projects/01-eight-puzzle-search/README.md) | `python3 src/solver.py` | Python standard library; optional Matplotlib benchmark |
| [02 · Feature selection](projects/02-feature-selection/README.md) | `python3 src/main.py` | Python standard library; three included datasets in `data/` |

## Run independently

From this collection's root, choose one project:

```bash
cd projects/01-eight-puzzle-search
python3 src/solver.py
```

Or, from the collection root:

```bash
cd projects/02-feature-selection
python3 src/main.py
```

For feature selection, enter a filename such as `small-test-dataset.txt`, then choose forward selection, backward elimination, or KNN analysis. Its `data/` lookup is relative to the project directory. Do not run either project from the collection root or combine their `src` directories. Python 3.12 was used for the consolidation checks.

Both assignment CLIs run locally without downloads, accounts, API keys, or third-party packages. The puzzle benchmark needs Matplotlib; its README supplies a separate optional environment. The feature-selection README preserves the supplied script checks and their `PYTHONPATH=src` recipes.

## Retained limitations

The original puzzle UCS implementation returns `None` on unsolvable input, causing its CLI and benchmark to raise `TypeError`; this known issue is documented in the project README. The benchmark and CLI also use different “Very Easy” states. The implementation uses Euclidean distance, as the code and README describe.

Feature selection is computationally expensive on the large dataset and for repeated KNN searches. Its supplied checks print diagnostics rather than forming a strict automated test suite; the small-dataset LOOCV check reports 91% against its historical 89% expectation. These historical algorithms, prompts, timing characteristics, and reported results are preserved.

## Sources and attribution

[ATTRIBUTION.md](ATTRIBUTION.md) records the original repositories and contributors. [SOURCES.json](SOURCES.json) accounts for every imported file, including all three datasets and existing checks. Original histories are ancestors of this collection's `main`, surviving the consolidation PR's squash merge. In a full clone, use `git log <source-sha>` or `git show <source-sha>:<original-path>` to inspect the originals; unshallow a shallow clone first. Dataset names and contents are retained exactly; the sources supply no further dataset origin/license details, so none are invented. No collection-wide license has been added.
