[English](#_)

# LexiGuess_

## Ein Worträtselspiel

LexiGuess_ ist ein Worträtselspiel vergleichbar mit 'Wordle'. Spieler versuchen, ein Wort innerhalb einer begrenzten Anzahl von Versuchen zu erraten. Das Spiel wurde ursprünglich als Lösung für eines der Problemsets von [CS50’s Introduction to Computer Science](https://cs50.harvard.edu/x/2023/psets/2/wordle50/) erstellt. Das Spiel ähnelt dieser ursprünglichen Lösung noch teilweise, wurde jedoch stark modifiziert und erweitert, um Abhängigkeiten zu entfernen, die Spiellogik zu verfeinern und Funktionalitäten hinzuzufügen.

Diese README enthält umfassende Informationen zur Verwendung des Programms, seiner Struktur und der Logik hinter verschiedenen Funktionalitäten.

## Inhaltsverzeichnis

- [Übersicht](#Übersicht)
- [Installation](#installation)
- [Verwendung](#verwendung)
- [Funktionalität](#Funktionalität)
- [Spiellogik](#spiellogik)
- [Autor](#autor)
- [Danksagung](#Danksagungen)
- [Lizenz](#lizenz)

## Übersicht

Das Programm ist in C geschrieben und besteht aus mehreren Dateien:

- `main.c`: Enthält die Hauptlogik des Spiels.
- `core_functions.h`: Header-Datei mit den Kernfunktionen.
- `utility_functions.h`: Header-Datei mit Hilfsfunktionen.
- `files/`: Ein Verzeichnis, das Textdateien (`5.txt`, `6.txt`, `7.txt`, `8.txt`) enthält, die jeweils Listen von Wörtern mit in den Dateinamen angegebenen Längen enthalten.

## Installation

Um das Programm zu kompilieren und auszuführen, befolgen Sie die folgenden Schritte (Linux):

1. Klonen Sie das Repository: `git clone <repository-url>`
2. Navigieren Sie zum Verzeichnis: `cd LexiGuess_`
3. Kompilieren Sie das Programm: `gcc main.c -o LexiGuess`
4. Führen Sie die ausführbare Datei aus: `./LexiGuess`

## Verwendung

Das Spiel läuft entsprechend der nachfolgenden Schritte ab:

1. Geben Sie die Wortlänge für die aktuelle Runde ein (5, 6, 7 oder 8).
2. Raten Sie ein Wort mit der angegebenen Länge.
3. Das Programm gibt Rückmeldung zu jedem Versuch:
   - Richtige Buchstaben an der richtigen Position sind grün markiert.
   - Richtige Buchstaben an der falschen Position sind gelb markiert.
   - Falsche Buchstaben sind rot markiert.
4. Fahren Sie mit dem Raten fort, bis Sie entweder das Wort richtig erraten oder keine Versuche mehr übrig sind.

## Funktionalität

Die Funktionalität des Programms ist in Hauptfunktion, Kernfunktionen und Hilfsfunktionen unterteilt.

### Einstiegspunkt

- `main.c` enthält die Hauptfunktion, in der die Spielausführung beginnt.

### Kernfunktionen

- `core_functions.h` definiert Funktionen, die für die Kernspielmechanik verantwortlich sind, einschließlich:
  - Auswahl eines Worts aus der jeweiligen Wortliste.
  - Verarbeitung der Benutzereingabe und Bereitstellung von Rückmeldungen zu Vermutungen.
  - Feststellen, ob der Spieler gewonnen oder verloren hat.
- Die Kernfunktionen steuern den Spielverlauf und die Logik.

### Hilfsfunktionen

- `utility_functions.h` definiert Hilfsfunktionen, die für verschiedene nicht programmspezifische Aufgaben verwendet werden:
  - Bildschirm leeren.
  - Behandlung von Benutzereingaben.
  - Konvertierung von Eingaben in Kleinbuchstaben.

## Spiellogik

Die Spiellogik dreht sich um folgende Schritte:

1. **Wortauswahl**: Das Programm wählt ein zufälliges Wort der angegebenen Länge aus der entsprechenden Wortlisten-Datei aus.
2. **Raten**: Der Spieler gibt eine Wortvermutung der angegebenen Länge ein.
3. **Rückmeldung**: Das Programm vergleicht die Vermutung mit dem ausgewählten Wort und gibt eine Rückmeldung:
   - Richtige Buchstaben an der richtigen Position sind grün markiert.
   - Richtige Buchstaben an der falschen Position sind gelb markiert.
   - Falsche/nicht vorkommende Buchstaben sind rot markiert.
4. **Gewinnfeststellung**: Das Spiel geht weiter, bis der Spieler das Wort richtig geraten hat oder keine Versuche mehr übrig sind.

## Autor

LexiGuess_ wurde von Alexander Kadur erstellt.

## Danksagung

Ich möchte dem Team hinter [CS50’s Introduction to Computer Science](https://cs50.harvard.edu/x/2023/) meinen Dank und meine Anerkennung aussprechen.

Darüber hinaus möchte ich den Autoren und Beitragenden der Module und Bibliotheken, die für die Erstellung dieser Anwendung verwendet wurden, meine Dankbarkeit zeigen.

## Lizenz

Dieses Projekt steht unter der MIT-Lizenz.

Copyright 2024 Alexander Kadur

---

### _

# LexiGuess_

## A Word Guessing Game

LexiGuess_ is a word guessing game similar to 'Wordle'. Players try to guess a word within a limited number of attempts. The game was originally created as a solution for one of the problem sets of [CS50’s Introduction to Computer Science](https://cs50.harvard.edu/x/2023/psets/2/wordle50/]). The game still resembles this original solution to some extend but was later modified and extended to remove dependencies, refine the game logic and add functionality.

This README provides comprehensive information on how to use the program, its structure and the logic behind different functionalities.

## Table of Contents

- [Overview](#overview)
- [Installation](#installation)
- [Usage](#usage)
- [Functionality](#functionality)
- [Game Logic](#game-logic)
- [Author](#author)
- [Acknowledgements](#acknowledgements)
- [License](#license)

## Overview

The program is written in C and consists of several files:

- `main.c`: Contains the main logic of the game.
- `core_functions.h`: Header file containing core game functions.
- `utility_functions.h`: Header file containing utility functions.
- `files/`: A repository that holds text files (`5.txt`, `6.txt`, `7.txt`, `8.txt`) containing lists of words with lengths specified in the file names.

## Installation

To compile and run the program, follow these steps:

1. Clone the repository: `git clone <repository-url>`
2. Navigate to the directory: `cd LexiGuess_`
3. Compile the program: `gcc main.c -o LexiGuess`
4. Run the executable: `./LexiGuess`

## Usage

Once the program is running, follow these instructions to play the game:

1. Enter the word length for the current round (5, 6, 7, or 8).
2. Guess a word of the specified length.
3. The program will provide feedback on each guess:
   - Correct letters in the correct position are marked with green.
   - Correct letters in the wrong position are marked with yellow.
   - Incorrect letters are marked with red.
4. Continue guessing until you either guess the word correctly or run out of attempts.

## Functionality

The program's functionality is divided into core functions and utility functions.

### Entry Point

- `main.c` contains the main function where the game execution begins.

### Core Functions

- `core_functions.h` defines functions responsible for the core gameplay mechanics, including:
  - Selecting a word from the word list.
  - Processing user input and providing feedback on guesses.
  - Determining if the player has won or lost.
- The core functions handle the game flow and logic.

### Utility Functions

- `utility_functions.h` defines utility functions used throughout the program for tasks such as:
  - Clearing the screen.
  - Handling user input.
  - Converting input to lowercase.
- These functions assist in managing user interaction and maintaining the program's state.

## Game Logic

The game logic revolves around the following steps:

1. **Word Selection**: The program selects a random word of the specified length from the corresponding word list file.
2. **Guessing**: The player inputs a word guess of the specified length.
3. **Feedback**: The program compares the guess to the selected word and provides feedback:
   - Correct letters in the correct position are marked with green.
   - Correct letters in the wrong position are marked with yellow.
   - Incorrect letters are marked with red.
4. **Win/Loss Determination**: The game continues until the player guesses the word correctly or runs out of attempts.

## Author

LexiGuess_ was created by Alexander Kadur.

## Acknowledgements

I would like to express my thanks and appreciation to the team behind [CS50’s Introduction to Computer Science](https://cs50.harvard.edu/x/2023/).

Furthermore I want to show gratitude to the authors and contributors of the modules and libraries used for creating this application.

## License

This project is licensed under the MIT License.

Copyright 2024 Alexander Kadur
