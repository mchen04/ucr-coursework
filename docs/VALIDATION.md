# Workflow checks and limitations

Checks ran on mbp-old with Apple Clang 21, Python 3.12.13 and OpenJDK 26.0.1. Exact argv/cwd/stdin, stdout/stderr and results are retained outside this repo at `/Users/michaelchen/GoalRuns/ucr-coursework/t_d6be2f50/receipts.jsonl` and its `logs/`. Supplementary verification receipts, including the isolated SQL/JDBC exercise, are in that evidence directory’s `verify-1/`; `verify-1/VERIFY.md` records the results and limits. Build/test output, environments and tools are isolated there. No source/runtime behavior was changed.

| Workflow | Evidence result | Practical limit |
| --- | --- | --- |
| CS010B standalone C++ groups | 20 of 23 wildcard builds compile; file sum 286, character count 1, head/tail swap correct for supplied case 0 | Historical failures: ShoppingCart declarations, Time `_appm` typo, incomplete misc IntList; other runtime paths not exhaustively tested |
| CS010C standalone C++ groups | 13 of 15 wildcard builds compile; expression output correct; hash review compiles/runs with its existing embedded driver selected | `4.12` stack ambiguity; `8.11` wildcard duplicate main. All source preserved. Other runtime paths not exhaustive |
| CS061 | All 31 inputs assemble; Assignment 1 simulator shows R3=72 before HALT | External tool required evidence-only ARM64 fix; later interactive/trap workflows not fully simulated |
| CS111 HW2 | Compiles; synthetic RSA input decodes AB-space; invalid exponent prints invalid-key result | Historical integer/input limits unchanged; exit 0 alone does not imply valid key |
| CS166 | Both Java sources compile; nine scripts pass `bash -n`; six CSV counts captured. Disposable PostgreSQL/JDBC exercise loads original phase-2 DDL/indexes and all six CSVs, checks a 1000-row join, and confirms one synthetic CLI insert plus queries 6–10 | Evidence helper loads CSVs through JDBC; phase-1 SQL, literal psql/start/deploy wrappers, Swing, UCR/NetID, data regeneration, concurrency and other writes untested |
| CS170 relocation | Solver depth 2 / 5 expanded; forward selection {3,5} / 92% on small data | Reuses prior unchanged-blob evidence; unsolvable UCS/benchmark TypeError and 91%-vs-89% diagnostic retained; full large search/GUI plots not repeated |
| CS180 | Both supplied coverage examples execute without warnings and mark lines | Tracer catches failures/timeouts and can exit 0; no new edge-case test suite |
| Word Hunt | Original 31 tests / five suites pass with exact GoogleTest gitlink | CMake GUI config stops at absent SFML; case-sensitive Piece.cpp/piece.cpp issue and other original graphics assumptions remain; original tests embed stand-ins |
| Local note snapshots | All 28 files retain original bytes/hashes; linked by course indexes | Surrounding vault and referenced readings/submissions are external; historical factual claims not independently revalidated |

Broader accepted CS170 receipts are at `/Users/michaelchen/GoalRuns/course-consolidation/t_15ed254c/`. No AI Club build/import was repeated. No paid service, Michael account, browser/personal-app interaction, deployment or original repository mutation was used for testing. Source/data hashes, current tree reconciliation and privacy scope are recorded separately in root manifests/history guidance. The archive does not claim all historical assignments pass or all integrations remain available.
