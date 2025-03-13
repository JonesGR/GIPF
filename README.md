# Instrukcja obsługi aplikacji GIPF

## Wprowadzenie
Aplikacja GIPF jest implementacją gry planszowej, która umożliwia interakcję poprzez polecenia tekstowe oraz wizualizację planszy. Użytkownik może wprowadzać polecenia, aby sterować rozgrywką i analizować stan gry.

## Uruchamianie aplikacji
Aby uruchomić aplikację, skompiluj kod za pomocą kompilatora obsługującego SFML. Następnie uruchom plik wykonywalny.

## Interfejs aplikacji
Aplikacja obsługuje dwie główne metody interakcji:
1. **Polecenia tekstowe** – wpisywane w konsoli.
2. **Graficzna wizualizacja planszy** – generowana za pomocą biblioteki SFML.

## Obsługa poleceń
Podczas działania aplikacji możesz wprowadzać następujące komendy:

- `PRINT_GAME_BOARD` – wyświetla aktualny stan planszy.
- `PRINT_GAME_STATE` – pokazuje ogólny stan gry.
- `IS_GAME_OVER` – sprawdza, czy gra została zakończona.
- `LOAD_GAME_BOARD` – ładuje stan planszy
- `GEN_ALL_POS_MOV` – generuje wszystkie możliwe ruchy.
- `GEN_ALL_POS_MOV_EXT` – generuje wszystkie możliwe ruchy w trybie rozszerzonym.
- `GEN_ALL_POS_MOV_NUM` – generuje ruchy z numerami.
- `GEN_ALL_POS_MOV_EXT_NUM` – generuje rozszerzone ruchy z numerami.
- `WINNING_SEQUENCE_EXIST <N>` – sprawdza, czy istnieje zwycięska sekwencja o długości N.
- `SOLVE_GAME_STATE` – rozwiązuje aktualny stan gry.
- `DO_MOVE x y` – wykonuje ruch w pozycji `(x, y)`.
- `DO_MOVE x y P rStart rEnd` – wykonuje ruch oraz przechwytuje wskazane rzędy.

Wpisanie polecenia `CTRL+D` (EOF) powoduje zakończenie aplikacji.

## Wizualizacja planszy
Po wpisaniu `PRINT_GAME_BOARD` otwiera się okno wizualizacji planszy.
Elementy wizualizacji:
- Białe kwadraty – puste pola.
- Niebieskie kwadraty – pionki gracza 1.
- Czerwone kwadraty – pionki gracza 2.

## Wczytywanie planszy
Przykład:<br />
LOAD_GAME_BOARD<br />
4 4 15 15
1 2 B
   W _ _ B
  W B _ _ W
 B _ W _ B _
B _ W _ B B W
 W _ B _ W _
  _ W _ _ _
   W _ W B


## Obsługa okna gry
- Kliknięcie "X" zamyka okno gry.
- Plansza automatycznie aktualizuje stan po wykonaniu ruchu.

## Zakończenie gry
Gra kończy się, gdy komenda `IS_GAME_OVER` zwróci wartość oznaczającą koniec gry.

## Uwagi dodatkowe
- Aplikacja wymaga biblioteki SFML.


