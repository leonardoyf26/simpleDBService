# Mini Redis - Architecture

## Objective

This project aims to implement a simplified Redis-like database server written in C++.

The goal is to learn:

- database architecture
- storage engines
- network servers
- command parsing
- modular system design

The final system will behave as a service capable of receiving commands from clients via TCP.

---

# System Architecture

The system is divided into four main layers:

Client
  ↓
Server
  ↓
Parser
  ↓
Engine
  ↓
Storage

Each layer has a specific responsibility.

---

# Layers

## 1. Server Layer

Responsible for:

- accepting TCP connections
- receiving commands
- sending responses

This layer does NOT execute database logic.

---

## 2. Parser Layer

Responsible for converting raw text into commands.

Example:

Input:

SET name Leo

Output:

Command
type = SET
key = name
value = Leo

---

## 3. Engine Layer

Responsible for executing commands.

Example:

Command(SET name Leo)

Engine will call:

database.set("name", "Leo")

---

## 4. Storage Layer

Responsible for storing data.

The first implementation will use an in-memory hash table.

key -> value

Example:

name -> Leo
age -> 25

Future improvements may include:

- persistence
- snapshots
- append logs

---

# Initial Features

Version 1 will support the following commands:

SET key value
GET key
DEL key
EXISTS key
EXIT

---

# Data Flow

Client sends command:

SET name Leo

Flow inside the system:

Server receives text
↓
Parser creates Command
↓
Engine executes command
↓
Storage updates data
↓
Response returned to client

---

# Future Improvements

- TCP server
- persistence
- replication
- concurrency
- snapshots