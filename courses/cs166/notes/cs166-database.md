---
tags:
  - project/coursework
  - project/cs166
  - topic/database
  - status/reference
aliases:
  - CS 166 Database Project
  - HotelManagement Phase1
updated: 2026-05-09
---

# CS 166 Database Project

## HotelManagement_Phase1
- Located at: `~/Reserach_Container/cs166_project/HotelManagement_Phase1.erdplus`
- Complex hotel management schema with 8 entities
- Includes weak entities (Room), ISA hierarchy (Manager subclass of Staff), identifying relationships
- Entities: Hotel, Room (weak), Customer, Booking, Staff, Manager (ISA), MaintenanceCompany, RoomRepairRequest

## Tools & References
- [[erdplus-format-reference]] — Complete .erdplus JSON format specification for programmatic diagram creation
- ERDPlus editor for visual design

## Current Work
- Understanding ERDPlus JSON structure to create new schemas programmatically
- Analyzed 2026-02-18: documented all format details including entity/attribute/relationship definitions, cardinality encoding, ISA relationships, edge structures, and coordinate system

## Durable anchor

- ERDPlus is the design surface; project is about programmatic schema creation, not application logic.
- HotelManagement_Phase1 is reference material in the mechanics-shop project tree, not the active CS 166 deliverable.
