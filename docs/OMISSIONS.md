# Omitted current-tree artifacts

Every omitted original path, blob, mode and reason is recorded in the root `SOURCES.json`; this table summarizes it. Omissions affect only the new current tree. Original source history and originals are retained.

| Source | Omitted entries | Reason |
| --- | ---: | --- |
| CS010B | 4363 | Home/editor/cache artifacts (metadata-only), compiled output, empty placeholders |
| CS010C | 13 | Compiled/cache/editor metadata |
| CS061 | 0 | No current path omitted |
| CS111 | 3 | Compiled/cache/editor metadata |
| cs166-mechanic-shop-db | 0 | No current path omitted |
| cs170-projects | 0 | No current path omitted |
| cs180-statement-coverage | 1 | Compiled/cache/editor metadata |
| Modded-Word-Hunt | 2 | Compiled/cache/editor metadata |

Meaningful resources are retained even when historically generated: CS166 dummy CSVs and bundled JDBC jar, CS010B input data, CS010C word dictionary/movie reviews/sample ladder/DOT study diagrams, CS170 three datasets, Word Hunt media/fonts/dictionary/images and pinned GoogleTest dependency, and all discovered local academic notes. The extensionless `Final Study/midterm_badsort` and `Discussion1_Practice` were inspected as academic text and retained.

Metadata-only omissions in CS010B may contain accidental sensitive material. They are absent from the academic tree but still present in private unfiltered history; their contents were not read or scanned. There is no claimed disk reduction for that retained history. New command logs, tool clones, test-generated files, binaries, package environments, and recovery clones live outside the repository in the evidence directory.
