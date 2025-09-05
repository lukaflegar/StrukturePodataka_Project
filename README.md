# UNO Game in C programming language

[![Language](https://img.shields.io/badge/language-C-blue.svg)](https://en.wikipedia.org/wiki/C_(programming_language))
[![Status](https://img.shields.io/badge/status-completed-brightgreen.svg)]()
[![Course](https://img.shields.io/badge/course-Data%20Structures-orange.svg)]()

---

## 📌 About
This project was developed as part of the **Data Structures** course.

The project implements the card game **UNO** in C, focusing on **custom data structures**:
- 🔄 **Doubly circular linked list** → managing players in turn order.  
- 🃏 **Singly linked list** → storing each player's hand of cards.  
  ...

---

## 🚀 Features
- Add players (with name validation).  
- Each player starts with 7 cards.  
- Supports UNO special cards:
  - Skip ⏭️  
  - Reverse 🔁  
  - +2  
  - Normal number cards 🔢  
- 🂠 Draw a card when no valid moves exist.  
- 🤚 Automatic:
  - UNO call (when a player has 1 card left),  
  - Detecting when a player finishes,  
  - Declaring last player as loser.  
- 🧹 Proper memory management with dynamic allocation.  

---
- **Language:** C  
- **Focus:** Data Structures & Algorithms  
---

## 📷 Example Gameplay (console output)

Game begins!!!

The last played card is:
╔═╗
║5║
╚═╝

Player's turn:
Player's name: Luka
Number of remaining cards: 3
...
