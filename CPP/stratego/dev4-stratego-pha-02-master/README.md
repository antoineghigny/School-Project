# **Projet dev4 Startego**

## Group

- Leong Paeg-Hing(56133)
- Akturk Yohan(56514)
- Ghigny Antoine(56359)

## Arborescence des fichiers
```bash
├───Stratego
│   │   config.pri
│   │   Doxyfile
│   │   Stratego.pro
│   │   Stratego.pro.user
│   │
│   ├───libs
│   │   └───catch2
│   │           catch.hpp
│   │
│   ├───src
│   │   ├───Console
│   │   │       colors.h
│   │   │       Console.pro
│   │   │       Controller.cpp
│   │   │       Controller.h
│   │   │       main.cpp
│   │   │       Observer.h
│   │   │       ViewConsole.cpp
│   │   │       ViewConsole.h
│   │   │
│   │   └───StrategoCore
│   │           Board.cpp
│   │           Board.h
│   │           Deck.cpp
│   │           Deck.h
│   │           Duel.h
│   │           Game.cpp
│   │           Game.h
│   │           GameResult.h
│   │           Graveyard.cpp
│   │           Graveyard.h
│   │           Model.h
│   │           Observable.h
│   │           Pawn.cpp
│   │           Pawn.h
│   │           Player.cpp
│   │           Player.h
│   │           Position.cpp
│   │           Position.h
│   │           SentryPawn.h
│   │           State.h
│   │           StrategoCore.pri
│   │           StrategoCore.pro
│   │           Team.h
│   │           test_position.cpp
│   │
│   └───Tests
│           main.cpp
│           Tests.pro
│           tst_model.cpp
│
└───TestFile
        formation1.txt
        formation2.txt
        formation3.txt
        formation4.txt
        formation5.txt
        formation6.txt
        formation7.txt

```

## Rules of the game

- Stratego is played with 2 players, each player has 40 pawns.
- At the start of the game, each player arranges his pieces as he sees fit in his first four rows.
- Each player moves a piece one square per turn: left, right, forward or backward.
- An attack occurs when the player moves his piece onto a square already occupied by the opponent.
- Each player then shows his piece to the opponent.
- The strongest piece remains in play, the other is eliminated; in case of a tie, both are eliminated.

<p float="left">
  <img src="https://media.discordapp.net/attachments/934924497767792671/956627727891439627/unknown.png" width="297" />
  <img src="https://media.discordapp.net/attachments/934924497767792671/956627834867179560/unknown.png" width="207" /> 
  <img src="https://media.discordapp.net/attachments/934924497767792671/956628151604248656/unknown.png" width="196" />
</p>

- Here are the coins ranked from strongest to weakest (strength in parentheses)

![alt text](https://media.discordapp.net/attachments/934924497767792671/956628981006860308/unknown.png)

## Delivery 1 (Headers & UML)
Modeling of business classes: Documented headers and diagrams have been submitted.

![alt text](https://media.discordapp.net/attachments/934924497767792671/956631009431011369/unknown.png?width=710&height=360)
![alt text](https://media.discordapp.net/attachments/934924497767792671/956631187877691472/unknown.png?width=710&height=287)


## Delivery 2 (Console)
This work consisted of delivering a fully implemented project with console interface. It is possible for each player to place their pawns interactively but also via a file.

During each phase of the game, it displays the board on the standard output, asks the user what he wishes to do.

Initially, the game welcomes us and then asks if we want to play in easy mode or not. Then, each player must import his board. Once done. The game can begin and each player can move their pawns 1 by 1 until capturing the flag of one of the players. This will be named the winner. Players will have the option to restart the game with the previous board or not.


### For importing the board via a file, the different symbols and their quantities are available below.

| Pawn        | Symbol | Quantities |
|-------------|--------|------------|
| Marshal     | 10     | 1          |
| General     | 9      | 1          |
| Colonels    | 8      | 2          |
| Major       | 7      | 3          |
| Commanders  | 6      | 4          |
| Lieutenants | 5      | 4          |
| Sergeants   | 4      | 4          |
| Deminer     | 3      | 5          |
| Scouts      | 2      | 8          |
| Spy         | 1      | 1          |
| Flag        | F      | 1          |
| Bomb        | B      | 6          |

10 9 F 6 6 7 7 7 8 8  
1 5 4 4 6 6 4 4 5 5  
2 2 2 3 3 3 3 2 2 2  
B B B 2 3 5 2 B B B  

### <u>Some images of the console view</u>
- It is possible to import interactively via a file

![alt text](https://media.discordapp.net/attachments/934924497767792671/956639858053480458/unknown.png?width=932&height=671)

---

- But also to position pawn by pawn in the board.

![alt text](https://media.discordapp.net/attachments/934924497767792671/956643873722097704/unknown.png?width=960&height=301)

---

### A few small features

- After having selected a pawn to move, it is possible to replace this pawn in its initial position in order to select another one.
- The board is displayed 2x, once for the red player and once for the blue player
- The main player's graveyard is always above the other player's graveyard.
- If a player decides to take a file to import his board, if he does not indicate anything, he will have the possibility of placing his pawns 1 by 1.
