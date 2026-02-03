# JSnake – Pre-Git Development Versions

This directory contains early development milestones created
before this project was put under Git version control.

The files are kept in their original form and document the
evolution of the game logic step by step.

These versions are not complete programs:
- no main loop
- no rendering via Simple Draw in early stages
- may not compile

They are archived for historical and learning purposes.

---

## Version 0 – First Moving Square

First prototype featuring a single automatically moving square
that could be controlled by keyboard input.

This version established the basic idea of movement and input
handling.

---

## Version 1 – Performance Breakthrough

Still a single controllable square, but with a major performance
improvement.

Because Simple Draw is relatively slow, the full screen was no
longer redrawn every frame. Instead, only a single square was
drawn and overwritten in the next frame.

This optimization was a crucial breakthrough. Without it,
further development would not have been feasible.

---

## Version 2 – Logic vs. Animation Split

Introduction of a clear separation between:

- UpdateLogic
- UpdateAnimation

First attempts to represent the snake as an array.

The main challenge was handling two independent squares:
- the head
- the tail

The tail had to remember previous head positions and follow
them correctly to create a smooth snake animation.

---

## Version 3 – Collision and Growth Logic

Implementation of:
- collision detection with the game field boundaries
- snake growth logic

At this stage, snake segments were stored in structs and treated
almost like objects, carrying state and directional information.

The most difficult problem was the correct propagation of
direction data during growth. The tail often received direction
changes too early or too late, causing incorrect movement.

Solving this required extensive experimentation over several
days.

Additionally, an efficient block-drawing function was
introduced. Instead of drawing each square manually via loops,
all block rendering was unified into a single reusable function,
significantly improving code cleanliness.

---

## Version 4 – Near-Playable Prototype

Final documented pre-Git iteration.

This version was already close to a playable game. Core gameplay
was functional, but self-collision detection of the snake was
still missing.

Between this version and the first Git commit, several major
features were developed without intermediate snapshots:
- menu system
- functional buttons
- complete game flow

All of these features were implemented using Simple Draw only,
without additional libraries.

Due to missing intermediate recordings, this version represents
the last preserved milestone before the project was migrated
to Git.

