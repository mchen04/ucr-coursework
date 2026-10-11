# Source history and recovery

Original Git commit IDs, trees, blobs, authors and branch tips are retained without rewriting them. The initial empty bootstrap/history anchor already survives in the published coursework main ancestry. Source branch refs remain under `source-history/<original-name-lowercase>/<original-branch>`; all observed source heads/tags are accounted for in `SOURCES.json`.

For the HomeBase addition, baseline-tree anchor `4de63f8ceba40663fd29ec85fc1905bc4cea09ad` has parents published main `a802a5021ff8678f4cf89d954a33c99897e332c3` and original HomeBase tip `21758cc0381ec3cef769d250d0e50091a3d46869`. Its current tree is exactly the existing coursework tree, rather than empty. Retain `history-anchor/homebase` and `source-history/homebase/main`, and fast-forward private default main to that unchanged-tree anchor before a later authorized content squash. A content squash alone would discard a merge parent's source ancestry. This method preserves all 134 HomeBase commits without rewriting or duplicating prior imports; the first build phase creates only local commits/refs. Original HomeBase paths exist in historical commits; its root README is byte-identical at `projects/homebase/README.original.md` in the current tree.

In a full destination clone, use the source SHAs from the manifest:

```bash
git log <original-tip>
git ls-tree -r <original-tip>
git show <original-tip>:<academic-original-path>
```

For a shallow clone, use `git fetch --unshallow` first. Original paths appear in old commits; current paths appear in the manifest. CS170's completed collection already preserves the eight-puzzle and feature-selection original tips, and importing it once preserves those histories too. Its nested `SOURCES.json` still describes that earlier collection relative to `courses/cs170/`.

**Privacy:** CS010B raw history contains excluded home/history/editor/auth-like paths. They were classified from filenames/tree metadata only, not opened or scanned. Raw history may retain accidental sensitive material and most of the approximately 600 MB Git footprint. Do not browse those sensitive paths as coursework or make this repository public. Exact preservation has no known missing observed commit/tree/blob, but is not a security clearance for uninspected history. A future sanitized public export would be a separate decision and would lose original commit identities for rewritten material.

Local BIO/BUS/CS166 notes have snapshot hashes and original locations, with no source Git repository discovered. Their preexisting dates/reference pointers remain in the files; no earlier Git history is claimed for them. Source GitHub settings, issues/PR discussions, stars, permissions, external links and live resources were not migrated. Old repositories and checkout locations remain unchanged.
