---
tags:
  - project/coursework
  - project/cs166
  - topic/database
  - status/reference
created: 2026-02-18
updated: 2026-05-09
---

# CS 166 mechanics shop database

UCR CS 166 mechanics-shop / auto-repair schema project. Phase 1 (ER + relational schema), Phase 2 (Java/JDBC + Swing GUI), submitted Winter 2026.

## Workstreams

- [[cs166-mechanics-shop]] — earlier phase-oriented summary; treat this note as the canonical schema/JDBC/SQL truth.

## Schema (5 entities + 2 relationships)

- `Customer`, `Mechanic`, `Car` — entity tables.
- `Owns` — relationship table; `UNIQUE(car_vin)` enforces one-owner-per-car.
- `Service_Request` — open-state request (no status column).
- `Closed_Request` — close event with `UNIQUE(rid)`; presence of row = closed; carries mechanic + bill.
- `Mechanic` gains `specialty` in Phase 2; `Car.vin` is the natural primary key.

## Modeling decisions

- Open vs. closed determined by row presence in `Closed_Request`, not a status column.
- Mechanic does not attach to `Car`; closure records the mechanic-request interaction.
- `Closed_Request` is naturally weak/identifying in ER terms.
- State assumptions explicitly when the schema can't enforce them (one-owner-per-car, one-closure-per-request).
- Grading rewards cardinality/participation clarity over over-modeling.

## Phase 2 implementation shape

- Single `MechanicShopGUI.java` Swing app: top-aligned `JTabbedPane` with 10 tabs + bottom SQL log panel.
- Tabs: Add Customer / Add Mechanic / Add Car / New Request / Close Request / Bills < $100 / >20 Cars / Pre-1995 Cars / Top K Cars / Total Bills.
- PreparedStatement on write paths and the top-K query; reporting tabs 6/7/8/10 use plain `Statement` with hardcoded SQL.
- JDBC: `Class.forName("org.postgresql.Driver")`, `jdbc:postgresql://localhost:<port>/<dbname>`, helpers for `executeUpdate`, `executeQueryAndReturnResult`.
- ID generation: `SELECT MAX(id) + 1` (preferred over `COUNT(*) + 1` because of deletes).
- Validation surface (write paths): name length, phone format, VIN length, address length, year bounds, mechanic experience bounds, duplicate VIN rejection, date ordering on close, nonnegative bill, already-closed rejection.

## Phase 2 repo layout

- `phase2/`: `README.md`, `sql/create.sql`, `sql/create_ucr.sql`, `data/*.csv`, `java/src/{MechanicShop,MechanicShopGUI,TestGUI}.java`, `generate_data.py`, `start.sh`, `deploy_ucr.sh`, `ucr/*.sh`.
- Generated data volumes: 500 customers, 250 mechanics, 800 cars, 800 ownership rows, 1500 service requests, ~1000 closed requests.
- Phone format is `(###)#######` with **no dash** — validators expecting `(###)###-####` will fail.

## Reporting query set

- Closed requests with bill < $100 (date, comment, bill).
- Customers with > 20 cars (count from `Owns`).
- Pre-1995 cars with odometer < 50k (from service_requests).
- Top-K cars by open service-request count.
- Customers by total bill descending (aggregate across service_requests).

## Indexes (non-PK candidates)

- `Customer(lname)`, `Owns(customer_id)`, `Owns(car_vin)`, `Service_Request(customer_id)`, `Service_Request(car_vin)`, `Closed_Request(rid)`, `Closed_Request(mid)`, `Car(year)`.
- BTREE-on-PK indexes are redundant in PostgreSQL but expected as a grading artifact.

## Lab 6 server workflow

- SSH: `ssh <netid>@cs166.cs.ucr.edu` with UCR NetID.
- Setup: `scp -r` lab folder to server, then `source lab5/startPostgreSQL.sh`, `source lab5/createPostgreDB.sh`, `cp -a lab5/*txt $PGDATA/`, `cs166_psql $USER'_lab6_DB' < lab5/chapter5.sql`.
- Interactive: `cs166_psql $USER'_lab6_DB'`, run queries, save screenshots to `screenshot.pdf`, stop with `cs166_db_stop`.
- Query 6 input was treated as case-sensitive and exact-match for the part name.

## Verification anchors

- Phase 2 data verification script: all checks passed (headers, row counts, PK ranges, FK integrity, temporal ordering, value formats).
- ERDPlus JSON, SQL DDL, cross-check mapping, and assumptions doc all reported PASS in the late checklist.
- Outstanding submission caveats were format/notation only: export the ER diagram to PDF; decide whether `Closed_Request` should be drawn as weak/identifying if instructor expects that notation.
- Local toolchain check: macOS `/usr/bin/javac` is a shim and reports "Unable to locate a Java Runtime"; PostgreSQL JDBC jar not required for syntax review (driver loaded reflectively, not via import).
