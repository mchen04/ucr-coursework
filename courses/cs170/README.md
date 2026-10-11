# CS170 · Introduction to AI

Import of the completed `mchen04/cs170-projects` collection, once. Its original `projects/` subtree, datasets, checks, component READMEs, requirements, attribution and source manifest are retained. [Original collection README](README.original.md) and [original attribution](ATTRIBUTION.md) retain the previous consolidation context.

| Project | Run from this collection's root | Setup and limits |
| --- | --- | --- |
| [Eight-puzzle search](projects/01-eight-puzzle-search/README.md) | `cd courses/cs170/projects/01-eight-puzzle-search` then `python3 src/solver.py` | Standard library; optional benchmark uses its retained `requirements-benchmark.txt` |
| [Feature selection](projects/02-feature-selection/README.md) | `cd courses/cs170/projects/02-feature-selection` then `python3 src/main.py` | Standard library; included `data/` relative to project cwd |

Relocated representative runs: Very Easy UCS reaches depth 2, expanding 5 nodes; feature forward search on `small-test-dataset.txt` returns `{3, 5}` at 92%. Original source/data blobs match the prior accepted consolidation, whose broader command receipts remain applicable.

Known failures remain: unsolvable UCS returns `None`, so the original CLI/benchmark can raise `TypeError`; the LOOCV diagnostic prints 91% against its historical 89% expectation despite exiting 0. Full expensive large-dataset search and graphical plot presentation were not rerun. The two original repositories are accounted for through the completed collection's retained ancestry, without duplicate project copies.
