# Gopher Drone Sim

Interactive 3D simulation of autonomous drone package delivery across the University of Minnesota campus. A C++ simulation engine talks to a Three.js frontend over WebSockets — schedule trips, watch drones fly the map, and export run stats.

[Watch the demo](https://youtu.be/94SR9GqrnaE) · [Run with Docker](#docker)

[![Demo](https://img.youtube.com/vi/94SR9GqrnaE/maxresdefault.jpg)](https://youtu.be/94SR9GqrnaE)

## Features

- **Campus-scale deliveries** — click two points on the 3D map to schedule a package pickup and drop-off
- **Shipping priorities** — Expedited, Standard, and No Rush queues; change priority until a drone claims the package
- **Pathfinding** — A\*, Dijkstra, BFS, and DFS routing over the campus graph
- **Leader / helper drones** — when a leader’s battery drops below 20%, it hands the package to the nearest free helper and returns to recharge
- **Weather** — a shared wind field that can push, damage, and eventually disable drones
- **Ops export** — write distance traveled and packages delivered to CSV
- **Live controls** — sim speed, entity camera follow, add humans/drones, show routes, notifications

## Stack

| Layer | Tech |
| --- | --- |
| Simulation | C++, Make, libwebsockets |
| Routing | OSM campus graph, A\* / Dijkstra / BFS / DFS |
| Frontend | TypeScript, Three.js, Vite |
| Run | Docker or local `make` |

The backend owns the world: entities, strategies, queues, weather, and handoff. The browser is a 3D view and control panel. They stay in sync over a WebSocket.

## Architecture

A few systems do the interesting work:

- **Priority queue** — each package carries a shipping state (Expedited / Standard / No Rush). Changing state reorders the queue; once a drone is committed, priority is locked.
- **Weather** — a single wind vector that every drone reads. Damage is layered on with a decorator so the base drone class stays unchanged.
- **Multi-drone handoff** — leader drones publish `HANDOFF_REQUEST`; helper drones subscribe and the nearest idle helper takes the package.
- **Data manager** — one process-wide collector for distance and delivery counts, with frontend notifications on export.

Entities (drones, robots, humans, helicopters, packages) are created through factories so new types plug in without rewriting the sim loop.

## Quick start

**Prereqs:** a C++ toolchain, Make, Node.js 20+, npm.

```bash
make -j
make run
```

Open [http://localhost:8081](http://localhost:8081).

Useful targets:

```bash
make run PORT=8090   # different port
make debug           # gdb
make docs            # Doxygen
make lint            # clang-format (Google style)
make clean
```

### Docker

```bash
docker pull prashantpilla/gopher-drone-sim
docker run --rm -p 8081:8081 prashantpilla/gopher-drone-sim
```

Or build this tree:

```bash
docker build -t gopher-drone-sim .
docker run --rm -p 8081:8081 gopher-drone-sim
```

Apple Silicon: uncomment the `FROM --platform=linux/amd64` line at the top of the `Dockerfile` if the default image fails to run.

## Using the sim

1. Drag to pan and zoom the campus map.
2. **Schedule Trip** — click pickup, then drop-off, name the package, pick a search strategy and shipping priority.
3. Watch the queue and notifications as drones claim, fly, and deliver.
4. **Manage Priorities** to reorder packages that have not been picked up yet (`name_package`).
5. **Add Drone** as Leader or Helper if you want more capacity; helpers only take handoffs.
6. **Send Stats to CSV** writes a local export of the run.

## Team

Built by [Prashant Pilla](https://github.com/prashant-pilla), Xander Hill, Casey Paulson, and Ryan Hale.

Originally a systems project at the University of Minnesota. This repo is the maintained personal copy.
