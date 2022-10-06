/**
 * Displays the maze and the dots
 */
function afficherTableau() {
    for (let lg = 0; lg < RAW_MAZE.table.length; lg++) {
        for (let col = 0; col < RAW_MAZE.table[lg].length; col++) {
            if (RAW_MAZE.table[lg][col] == 0) {
                $("<span>", {
                    id: `${lg}-${col}`,
                }).appendTo("#cadre");
            } else if (RAW_MAZE.table[lg][col] == 1) {
               // console.log(`${15 * lg}px`,)
                $("<span>", {
                    id: `${lg}-${col}`,
                    class: "wall"
                }).css({
                    top: `${15 * lg}px`,
                    left: `${15 * col}px`,
                }).appendTo("#cadre");
            } else if (RAW_MAZE.table[lg][col] == 2) {
                $("<span>", {
                    id: `${lg}-${col}`,
                    class: "pac-dot"
                }).css({
                    top: `${15 * lg}px`,
                    left: `${15 * col}px`,
                }).appendTo("#cadre");
            }
        }
    }
}