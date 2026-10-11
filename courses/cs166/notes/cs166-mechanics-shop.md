---
name: CS166 Mechanics Shop Database Project
description: Phase 1 ER design and relational schema (Winter 2026)
tags:
  - project/coursework
  - project/cs166
  - topic/database
  - status/historical
updated: 2026-05-06
---

# CS166 Mechanics Shop Database Project

## Retrieval note

- This is the earlier phase-oriented summary surface for the mechanics-shop project.
- Prefer [[cs166-mechanics-shop-database]] for the durable schema, JDBC implementation, query set, and submission-shape truth.

**Course:** CS 166, Winter 2026  
**Team Size:** 2 (same team for entire project)  
**Project Phases:** 
1. ER-model + relational schema design
2. JDBC implementation with 10 functions/queries  
3. Demo

## Phase 1: Schema Design (Submitted 2026-02-19)

### Core Schema (5 entities + 2 relationships)

**Entity Tables:**
- **Customer** — surrogate id (PK), fname/lname (VARCHAR 32), phone (CHAR 13), address (VARCHAR 256)
- **Mechanic** — surrogate id (PK/employee_id), fname/lname, experience (0-100 CHECK)
- **Car** — VIN (VARCHAR 16, PK — **natural key**), make/model (VARCHAR 32), year (1970-2026 CHECK)

**Relationship Tables:**
- **Owns** — ownership_id (PK), customer_id (FK), car_vin (FK, UNIQUE), one owner per car
- **Service_Request** — rid (PK), customer_id (FK), car_vin (FK), date, odometer (>0), complaint (TEXT)
- **Closed_Request** — wid (PK), rid (FK, UNIQUE), mid/mechanic (FK), date, comment (nullable), bill (numeric 10,2, >=0)

### Design Decisions (from assumptions.md)

| Decision | Rationale |
|----------|-----------|
| Owns is separate table | Spec says "ownership relation" in Query 7 → gave it entity status |
| Closed_Request separate | Open requests in Service_Request only, close creates new Closed_Request row → avoids nullable columns |
| Mechanic specialty omitted | Not in Phase 1 requirements, but Phase 2 "Add Mechanic" function lists it → defer to Phase 2 |
| VIN as natural PK for Car | Unique identifier in real world; other entities use surrogate IDs (no obvious natural keys) |
| Odometer on Service_Request | Not on Car table because same car has different readings each visit |

### Constraints Deferred to Application Layer (Phase 2)

1. **Closing date >= request date** — cross-table CHECK impossible; needs app validation
2. **Mechanic "works on single car at a time"** — concurrency rule, not static schema constraint
3. **Customer owns the car they bring in** — Service_Request has customer_id + car_vin but doesn't verify via Owns table; needs app-level ownership validation

### Code Conventions

**Comment Style:**
- Single-line `--` comments above relevant DDL
- Focus on "why" (design intent) rather than obvious facts
- Example: `-- separate table because spec says "ownership relation" in query 7`

**Naming:**
- Table names: PascalCase (Customer, Service_Request, Closed_Request)
- FK columns: `{table_singular}_{id|key}` (customer_id, car_vin, mid)
- Domain validation via CHECK constraints on bounded fields

**Structural Pattern:**
```sql
-- Comments explain intent
-- Drop in dependency order
-- Entities first, relationships after
-- FKs with explicit REFERENCES
-- UNIQUE for business rules (one-to-one)
-- CHECK for domain bounds
```

## Phase 2: Implementation Requirements (from project_description.md)

**Functions (5):**
1. Add Customer (validate inputs, insert)
2. Add Mechanic (includes specialty field — not in Phase 1 schema)
3. Add Car (VIN, make, model, year)
4. Initiate Service Request (search by last name, show cars, new car option)
5. Close Service Request (validate mechanic/request exist, check date ordering)

**Queries (5):**
6. Closed requests with bill < $100 (date, comment, bill)
7. Customers with >20 cars (count from Owns table)
8. Pre-1995 cars with <50k miles (from odometer in service_requests)
9. Top K cars by service request count (open requests only)
10. Customers by total bill descending (aggregate across service requests)

**Deliverables:**
- .sql files + .java files
- Dummy data in .csv
- Demo of working system

**Grading:** Phase 1 (30%), Phase 2 (60%), Demo (10%), Extra credit (10%)

## File Structure

```
cs166_project/
├── CS166_Project_Description.md
├── HotelManagement_Phase1.erdplus (old example)
├── phase1_research/
│   ├── assumptions_template.md
│   ├── er_diagram_guide.md
│   ├── grading_checklist.md
│   ├── prior_projects_analysis.md
│   └── relational_schema_guide.md
└── phase1_submission/
    ├── MechanicShop_Phase1.erdplus (ERD)
    ├── assumptions.md (design decisions)
    ├── assumptions.txt (same as .md)
    └── create_tables.sql (DDL)
```

**Location:** `/Users/michaelchen/Reserach_Container/cs166_project/`
