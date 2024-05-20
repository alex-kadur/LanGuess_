# LanGuess_

---

## Ein Worträtselspiel

LanGuess_ ist ein Worträtselspiel vergleichbar mit 'Wordle'. Spieler versuchen, ein Wort innerhalb einer begrenzten Anzahl von Versuchen zu erraten. Das Spiel wurde ursprünglich als Lösung für eines der Problemsets von [CS50’s Introduction to Computer Science](https://cs50.harvard.edu/x/2023/psets/2/wordle50/) erstellt. Das Spiel wurde von mir jedoch stark modifiziert/erweitert und aehnelt der urspruenglichen Loesung nur noch in geringem Masse.

Es wurden alle unnoetigen Abhängigkeiten entfernt, die Spiellogik deutlich verfeinert und neue Funktionalitäten zur individuellen Anpassung und Verwaltung von Inhalten hinzuzufügen. Diese README enthält Informationen zur Verwendung des Programms, seiner Struktur und der Logik hinter verschiedenen Funktionalitäten.

## Inhaltsverzeichnis

- [Ubersicht](#ubersicht)
- [Installation](#installation)
- [Verwendung](#verwendung)
- [Funktionalität](#funktionalität)
- [Spiellogik](#spiellogik)
- [Autor](#autor)
- [Danksagung](#danksagung)
- [Lizenz](#lizenz)

---

## Ubersicht

Das Programm ist in C geschrieben und besteht aus mehreren Dateien:

- `main.c`: Enthält die Hauptlogik des Spiels.
- `utilities.c` + `utilities.h`: Enthält Hilfsfunktionen, die für verschiedene nicht programmspezifische Aufgaben verwendet werden.
- `ui.c` + `ui.h`: Enthält Funktionen, die für die Benutzeroberfläche und -interaktion verantwortlich sind.
- `game.c` + game.h`: Enthält Funktionen, die für die Spiellogik und -mechanik verantwortlich sind.
- `data_operations.c` + `data_operations.h`: Enthält Funktionen, die für die Verarbeitung von Daten verantwortlich sind.
- `globals.c` + `globals.h`: Enthält globale Variablen und Konstanten, die im gesamten Programm verwendet werden.
- `data_structures.h`: Enthält benutzerdefinierte Datenstrukturen, die im Programm verwendet werden.
- `constants.h`: Enthält Konstanten, die im gesamten Programm verwendet werden.
- `colors.h`: Enthält Farbdefinitionen, die im Programm verwendet werden.
- `files/`: Ein Verzeichnis, das Textdateien (`optionen_5.txt`, `optionen_6.txt`, `optionen_7.txt`, `optionen_8.txt`) enthält, ...
- ... die jeweils Listen von Wörtern mit in den Dateinamen angegebenen Längen enthalten.

---

## Installation

Um das Programm zu kompilieren und auszuführen, befolgen Sie die folgenden Schritte (Linux):

1. Klonen Sie das Repository: `git clone <https://github.com/alex-kadur/LanGuess_.git>`
2. Navigieren Sie zum Verzeichnis: `cd LanGuess_`
3. Kompilieren Sie das Programm: gcc `gcc -Iinclude/ src/main.c src/utilities.c src/ui.c src/globals.c src/game.c src/data_operations.c -o languess`
4. Führen Sie die Datei aus: `./languess`

---

## Verwendung

Das eigentliche Spiel läuft entsprechend der nachfolgenden Schritte ab:

1. Erraten Sie ein Wort mit der angegebenen Länge.
2. Das Programm gibt Rückmeldung zu jedem Versuch:
   - Richtige Buchstaben an der richtigen Position sind grün markiert.
   - Richtige Buchstaben an der falschen Position sind gelb markiert.
   - Falsche Buchstaben sind rot markiert.
3. Fahren Sie mit dem Raten solange fort, bis Sie entweder das Wort richtig erraten oder keine Versuche mehr übrig sind.

---

## Funktionalität

Die Funktionalität des Programms ergibt sich aus den oben genannten Dateien und Funktionen.

### Einstiegspunkt

- `main.c` enthält die Hauptfunktion, in der die Spielausführung beginnt.

### Spiel

- `game.c` definiert Funktionen, die für die Kernspielmechanik verantwortlich sind, einschließlich:

  - Verarbeitung der Benutzereingabe und Bereitstellung von Rückmeldungen zu Vermutungen.
  - Feststellen, ob der Spieler gewonnen oder verloren hat.

### Benutzeroberfläche

- `ui.c` definiert Funktionen, die für die Benutzeroberfläche und -interaktion verantwortlich sind, einschließlich:

  - Titelbildschirm anzeigen.
  - Ausgabe der Menues, Submenues und Optionen.
  - Verarbeiten von Benutzereingaben.
  - Anzeigen von Rückmeldungen.

### Datenverarbeitung

- `data_operations.c` definiert Funktionen, die für die Verarbeitung von Daten verantwortlich sind, einschließlich:

  - Laden von Wörterlisten aus Dateien.
  - Verarbeiten von Benutzereingaben.
  - Bereitstellen zufälliger Wörter für das Spiel.
  - Ausgabe und Bearbeitung der Wörterlisten.
  - Speichern aktualisierter Wörterlisten in Dateien.

### Hilfsfunktionen

- `utility_functions.h` definiert Hilfsfunktionen, die für verschiedene nicht programmspezifische Aufgaben verwendet werden:
  - Bildschirm leeren.
  - Behandlung von Benutzereingaben.
  - Konvertierung von Eingaben.
  - Pausieren des Programms.

---

## Spiellogik

Die Spiellogik dreht sich um folgende Schritte:

1. **Wortauswahl**: Das Programm wählt ein zufälliges Wort der gesetzten Länge aus der entsprechenden Wortlisten aus.
2. **Raten**: Der Spieler gibt eine Wortvermutung der angegebenen Länge ein.
3. **Rückmeldung**: Das Programm vergleicht die Vermutung mit dem ausgewählten Wort und gibt eine Rückmeldung:
   - Richtige Buchstaben an der richtigen Position sind grün markiert.
   - Richtige Buchstaben an der falschen Position sind gelb markiert.
   - Falsche/nicht vorkommende Buchstaben sind rot markiert.
4. **Gewinnfeststellung**: Das Spiel geht weiter, bis der Spieler das Wort richtig geraten hat oder keine Versuche mehr übrig sind.

---

## Autor

LanGuess_ wurde von Alexander Kadur erstellt.

---

## Danksagung

Ich möchte dem Team hinter [CS50’s Introduction to Computer Science](https://cs50.harvard.edu/x/2023/) meinen Dank und meine Anerkennung aussprechen.

Darüber hinaus möchte ich den Autoren und Beitragenden der Module und Bibliotheken, die für die Erstellung dieser Anwendung verwendet wurden, meine Dankbarkeit zeigen.

Zuletzt gilt meine Dankbarkeit allen engagierten Lehrenden um Rahmen meiner Umschulung zum Fachinformatiker fuer Anwendungsentwicklung.

---

## Lizenz

Dieses Projekt steht unter der MIT-Lizenz.

Copyright 2024 Alexander Kadur

---
