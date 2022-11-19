# J'ai choisit de créer une diagonale dans l'ordre croissant
1. Version en ligne sur Board Game Arena : Au début du jeu, chacun reçoit 4
tuiles qui sont placées automatiquement sur la diagonale dans l’ordre croissant.

- J'ai créé une méthode privée dans Game, qu prends un Integer en paramètre (ça va être le joueur actuel), crée une ArrayList qui ajoute des tuiles faces cachées en fonction de la taille du tableau. (si la taille du tableau est 4 -> pioche 4 tuiles faces cachées).

- Mélange la liste d'objet grace à "sort" dans Collections, mais comme il s'agit d'une liste d'objet, il faut indiquer sur quoi comparer pour trier les valeurs.

- Ajoute ensuite la liste dans la diagonale. 

-> Cette méthode est appelée en fonction du nombre de joueurs dans la partie et va créer une nouvelle liste et piocher à chaque fois dans les tuiles faces cachées.

```java
 private void placeDiagonale(int currentPlayerNumber) {

        ArrayList<Tile> tuilesRestantes = new ArrayList<Tile>();
        for (int k = 0; k < boards[currentPlayerNumber].getSize(); k++) {
            tuilesRestantes.add(pickFaceDownTile());
        }

        Collections.sort(tuilesRestantes, new Comparator<Tile>() {
            @Override
            public int compare(Tile o1, Tile o2) {
                return o1.getValue() - o2.getValue();
            }
        }
        );
        // afficher la liste triée
        for (int i = 0; i < tuilesRestantes.size(); i++) {
            System.out.println(tuilesRestantes.get(i));
        }

        for (int i = 0; i < getBoardSize(); i++) {
            boards[currentPlayerNumber].put(tuilesRestantes.get(i), new Position(i, i));
        }
    }
```
