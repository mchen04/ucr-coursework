---
name: cs166-lab7
tags:
  - project/coursework
  - project/cs166
  - topic/database
  - status/reference
updated: 2026-05-06
---

# CS 166 Lab 7: Indexing

- Assignment focus: compare query performance with and without indexes in PostgreSQL.
- Required exercise deliverables: `queries.sql` with 6 queries, `create_indexes.sql` with targeted `DROP INDEX` / `CREATE INDEX` statements, and `lab7.pdf` with screenshots plus benchmark results.
- Query set:
  - count NYC parts with `on_hand > 70`
  - count total red parts across NYC + SFO
  - list suppliers with more total `on_hand` in NYC than SFO
  - list suppliers supplying NYC parts not supplied by anyone in SFO
  - `UPDATE part_nyc SET on_hand = on_hand - 10`
  - `DELETE FROM part_nyc WHERE on_hand < 30`
- Constraints to remember:
  - `part_number` is only unique within each part table, not across both.
  - red means `color_name = 'Red'` / `color = 0`.
  - benchmark on the same data before and after indexing.
  - run `measure.sh` at least 5 times and report averages.
- Setup/teardown flow:
  - `source startPostgreSQL.sh`
  - `source createPostgreDB.sh`
  - `source measure.sh`
  - `source stopPostgreSQL.sh`
