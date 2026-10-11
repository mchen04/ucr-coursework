# Source history and recovery

Original Git commit IDs, trees, blobs, authors and branch tips are retained without rewriting them. Empty bootstrap and history-anchor commits connect the source histories while keeping the anchor's current tree empty. The future consolidation squash is based on this anchor, so source ancestry survives. Source branch refs remain under `source-history/<original-name-lowercase>/<original-branch>`; all observed source heads/tags are accounted for in `SOURCES.json`.

In a full destination clone, use the source SHAs from the manifest:

```bash
git log <original-tip>
git ls-tree -r <original-tip>
git show <original-tip>:<academic-original-path>
```

For a shallow clone, use `git fetch --unshallow` first. Original paths appear in old commits; current paths appear in the manifest. CS170's completed collection already preserves the eight-puzzle and feature-selection original tips, and importing it once preserves those histories too. Its nested `SOURCES.json` still describes that earlier collection relative to `courses/cs170/`.

**Privacy:** CS010B raw history contains excluded home/history/editor/auth-like paths. They were classified from filenames/tree metadata only, not opened or scanned. Raw history may retain accidental sensitive material and most of the approximately 600 MB Git footprint. Do not browse those sensitive paths as coursework or make this repository public. Exact preservation has no known missing observed commit/tree/blob, but is not a security clearance for uninspected history. A future sanitized public export would be a separate decision and would lose original commit identities for rewritten material.

Local BIO/BUS/CS166 notes have snapshot hashes and original locations, with no source Git repository discovered. Their preexisting dates/reference pointers remain in the files; no earlier Git history is claimed for them. Source GitHub settings, issues/PR discussions, stars, permissions, external links and live resources were not migrated. Old repositories and checkout locations remain unchanged.
