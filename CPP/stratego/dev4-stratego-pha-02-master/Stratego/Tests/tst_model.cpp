#include <catch2/catch.hpp>
#include <Pawn.h>
#include <Deck.h>
#include <Graveyard.h>
#include <Board.h>
#include <Game.h>

TEST_CASE("The creation of the pawn", "[pawn]")
{
    SECTION("Creation of a pawn that can't move : bomb") {
        Pawn p {Role::BOMB, Team::BLUE};

        REQUIRE(Role::BOMB == p.getRole());
        REQUIRE(Team::BLUE == p.getTeam());
        REQUIRE(false == p.isMoveable());
    }

    SECTION("Creation of a pawn that can't move : flag") {
        Pawn p {Role::FLAG, Team::BLUE};

        REQUIRE(Role::FLAG == p.getRole());
        REQUIRE(Team::BLUE == p.getTeam());
        REQUIRE(false == p.isMoveable());
    }

    SECTION("Creation of a pawn that can't move : wall") {
        Pawn p {Role::WALL, Team::NONE};

        REQUIRE(Role::WALL == p.getRole());
        REQUIRE(Team::NONE == p.getTeam());
        REQUIRE(false == p.isMoveable());
    }

    SECTION("Creation of a pawn that can't move : empty") {
        Pawn p {};

        REQUIRE(Role::EMPTY == p.getRole());
        REQUIRE(Team::NONE == p.getTeam());
        REQUIRE(false == p.isMoveable());
    }

    SECTION("Creation of a pawn that can move : spy") {
        Pawn p {Role::SPY, Team::BLUE};

        REQUIRE(Role::SPY == p.getRole());
        REQUIRE(Team::BLUE == p.getTeam());
        REQUIRE(true == p.isMoveable());
    }

    SECTION("Creation of a pawn that can move : scout") {
        Pawn p {Role::SCOUT, Team::BLUE};

        REQUIRE(Role::SCOUT == p.getRole());
        REQUIRE(Team::BLUE == p.getTeam());
        REQUIRE(true == p.isMoveable());
    }

    SECTION("Creation of a pawn that can move : deminer") {
        Pawn p {Role::DEMINER, Team::BLUE};

        REQUIRE(Role::DEMINER == p.getRole());
        REQUIRE(Team::BLUE == p.getTeam());
        REQUIRE(true == p.isMoveable());
    }

    SECTION("Creation of a pawn that can move : sergeant") {
        Pawn p {Role::SERGEANT, Team::BLUE};

        REQUIRE(Role::SERGEANT == p.getRole());
        REQUIRE(Team::BLUE == p.getTeam());
        REQUIRE(true == p.isMoveable());
    }

    SECTION("Creation of a pawn that can move : lieutenant") {
        Pawn p {Role::LIEUTENANT, Team::BLUE};

        REQUIRE(Role::LIEUTENANT == p.getRole());
        REQUIRE(Team::BLUE == p.getTeam());
        REQUIRE(true == p.isMoveable());
    }

    SECTION("Creation of a pawn that can move : commander") {
        Pawn p {Role::COMMANDER, Team::BLUE};

        REQUIRE(Role::COMMANDER == p.getRole());
        REQUIRE(Team::BLUE == p.getTeam());
        REQUIRE(true == p.isMoveable());
    }

    SECTION("Creation of a pawn that can move : major") {
        Pawn p {Role::MAJOR, Team::BLUE};

        REQUIRE(Role::MAJOR == p.getRole());
        REQUIRE(Team::BLUE == p.getTeam());
        REQUIRE(true == p.isMoveable());
    }

    SECTION("Creation of a pawn that can move : colonel") {
        Pawn p {Role::COLONEL, Team::BLUE};

        REQUIRE(Role::COLONEL == p.getRole());
        REQUIRE(Team::BLUE == p.getTeam());
        REQUIRE(true == p.isMoveable());
    }

    SECTION("Creation of a pawn that can move : general") {
        Pawn p {Role::GENERAL, Team::BLUE};

        REQUIRE(Role::GENERAL == p.getRole());
        REQUIRE(Team::BLUE == p.getTeam());
        REQUIRE(true == p.isMoveable());
    }

    SECTION("Creation of a pawn that can move : marechal") {
        Pawn p {Role::MARECHAL, Team::BLUE};

        REQUIRE(Role::MARECHAL == p.getRole());
        REQUIRE(Team::BLUE == p.getTeam());
        REQUIRE(true == p.isMoveable());
    }
}

TEST_CASE("The function clear of the pawn", "[pawn]")
{
    Pawn p {Role::SCOUT, Team::BLUE};
    p.addMove(Position(1,1));
    p.addMove(Position(1,2));
    p.addMove(Position(1,3));
    p.clearMove();
}

TEST_CASE("Check back and forth", "[pawn]")
{
    SECTION("1 back and forth case") {
        Pawn p {Role::SCOUT, Team::BLUE};
        for(int i {}; i < 1; i++)
        {
            p.addMove(Position(1,1));
            p.addMove(Position(1,2));
        }

        REQUIRE(false == p.isBackAndForthTooMuch(Position(1,1)));
    }

    SECTION("2 back and forth case") {
        Pawn p {Role::SCOUT, Team::BLUE};
        for(int i {}; i < 2; i++)
        {
            p.addMove(Position(1,1));
            p.addMove(Position(1,2));
        }

        REQUIRE(false == p.isBackAndForthTooMuch(Position(1,1)));
    }

    SECTION("3 back and forth case") {
        Pawn p {Role::SCOUT, Team::BLUE};
        for(int i {}; i < 3; i++)
        {
            p.addMove(Position(1,1));
            p.addMove(Position(1,2));
        }

        REQUIRE(false == p.isBackAndForthTooMuch(Position(1,1)));
    }

    SECTION("4 back and forth case") {
        Pawn p {Role::SCOUT, Team::BLUE};
        for(int i {}; i < 4; i++)
        {
            p.addMove(Position(1,1));
            p.addMove(Position(1,2));
        }

        REQUIRE(true == p.isBackAndForthTooMuch(Position(1,1)));
    }
}

TEST_CASE("Test of the toString for all pawn", "[pawn]")
{
    SECTION("Empty pawn") {
        Pawn p;
        REQUIRE(p.toString() == "*");
    }

    SECTION("Wall pawn") {
        Pawn p {Role::WALL, Team::NONE};
        REQUIRE(p.toString() == "W");
    }

    SECTION("Flag pawn") {
        Pawn p {Role::FLAG, Team::NONE};
        REQUIRE(p.toString() == "F");
    }

    SECTION("Bomb pawn") {
        Pawn p {Role::BOMB, Team::NONE};
        REQUIRE(p.toString() == "B");
    }

    SECTION("Spy pawn") {
        Pawn p {Role::SPY, Team::NONE};
        REQUIRE(p.toString() == "1");
    }

    SECTION("Scout pawn") {
        Pawn p {Role::SCOUT, Team::NONE};
        REQUIRE(p.toString() == "2");
    }

    SECTION("Deminer pawn") {
        Pawn p {Role::DEMINER, Team::NONE};
        REQUIRE(p.toString() == "3");
    }

    SECTION("Sergeant pawn") {
        Pawn p {Role::SERGEANT, Team::NONE};
        REQUIRE(p.toString() == "4");
    }

    SECTION("Lieutenant pawn") {
        Pawn p {Role::LIEUTENANT, Team::NONE};
        REQUIRE(p.toString() == "5");
    }

    SECTION("Commander pawn") {
        Pawn p {Role::COMMANDER, Team::NONE};
        REQUIRE(p.toString() == "6");
    }

    SECTION("Wall pawn") {
        Pawn p {Role::MAJOR, Team::NONE};
        REQUIRE(p.toString() == "7");
    }

    SECTION("Wall pawn") {
        Pawn p {Role::COLONEL, Team::NONE};
        REQUIRE(p.toString() == "8");
    }

    SECTION("Wall pawn") {
        Pawn p {Role::GENERAL, Team::NONE};
        REQUIRE(p.toString() == "9");
    }

    SECTION("Wall pawn") {
        Pawn p {Role::MARECHAL, Team::NONE};
        REQUIRE(p.toString() == "10");
    }
}

TEST_CASE("Hide and reveal function", "[pawn]")
{
    SECTION("Reveal pawn") {
        Pawn p;
        p.reveal();
        REQUIRE(p.isVisible() == true);
    }

    SECTION("Hide pawn") {
        Pawn p;
        p.reveal();
        p.hide();
        REQUIRE(p.isVisible() == false);
    }
}

TEST_CASE("Test the creation of the pawn", "[deck][pawn]")
{
    SECTION("Correct number of pawn created") {
        Deck d;
        d.generateDeck(Team::BLUE);

        REQUIRE(d.numberOfPawn() == 40);
    }
}

TEST_CASE("Test when a pawn is remove from the deck.", "[deck][pawn]")
{
    SECTION("When we remove one pawn") {
        Deck d;
        d.generateDeck(Team::BLUE);
        REQUIRE(40 == d.numberOfPawn());
        d.removePawnInDeck();
        REQUIRE(39 == d.numberOfPawn());
    }

    SECTION("Remove all the pawn in the deck") {
        Deck d;
        d.generateDeck(Team::BLUE);
        REQUIRE(40 == d.numberOfPawn());
        for(int i {}; i < 40; i++)
        {
            d.removePawnInDeck();
        }
        REQUIRE(0 == d.numberOfPawn());
    }
}

TEST_CASE("Check the function is all soldier dead", "[graveyard][pawn]")
{
    SECTION("When the graveyard is only soldier") {
        Graveyard g;
        for(int i{}; i < 33; i++)
        {
            Pawn p {Role::SCOUT, Team::BLUE};
            g.addDeadPawn(p);
        }

        REQUIRE(true == g.isAllSoldierDead());
    }

    SECTION("When the graveyard had soldier and unmoveable pawn") {
        Graveyard g;
        for(int i{}; i < 33; i++)
        {
            Pawn p {Role::SCOUT, Team::BLUE};
            g.addDeadPawn(p);
            if(i%10 == 0)
                g.addDeadPawn(Pawn {Role::BOMB, Team::BLUE});
        }

        REQUIRE(true == g.isAllSoldierDead());
    }

    SECTION("When not all soldiers are dead") {
        Graveyard g;
        for(int i{}; i < 30; i++)
        {
            Pawn p {Role::SCOUT, Team::BLUE};
            g.addDeadPawn(p);
            if(i%10 == 0)
                g.addDeadPawn(Pawn {Role::BOMB, Team::BLUE});
        }
        REQUIRE(false == g.isAllSoldierDead());
    }
}

TEST_CASE("Flag and graveyard", "[graveyard][pawn]")
{
    SECTION("When the flag is added to the graveyard") {
        Pawn p {Role::FLAG, Team::BLUE};
        Graveyard g;
        g.addDeadPawn(p);

        REQUIRE(g.isFlagCaptured() == true);
    }

    SECTION("When the flag is added to the graveyard") {
        Pawn p {Role::SCOUT, Team::BLUE};
        Graveyard g;
        g.addDeadPawn(p);

        REQUIRE(g.isFlagCaptured() == false);
    }
}

TEST_CASE("Test if the board is create correctly", "[board][pawn]")
{
    Board b;
    for(int i{}; i < b.getSize() + 2; i++)
    {
        for(int j{}; j < b.getSize() + 2; j++)
        {
            std::cout << b.getPawn(Position(i, j)).toString() << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

TEST_CASE("Test loadFile function in Board", "[board][pawn]")
{
    SECTION("Correct file") {
        Board b;
        std::string s {"../../TestFile/formation1.txt"};
        b.loadFile(s, Team::BLUE);
        for(int i{}; i < b.getSize() + 2; i++)
        {
            for(int j{}; j < b.getSize() + 2; j++)
            {
                std::cout << b.getPawn(Position(i, j)).toString() << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

    SECTION("Correct file but everything is on one line") {
        Board b;
        std::string s {"../../TestFile/formation2.txt"};
        b.loadFile(s, Team::BLUE);
        for(int i{}; i < b.getSize() + 2; i++)
        {
            for(int j{}; j < b.getSize() + 2; j++)
            {
                std::cout << b.getPawn(Position(i, j)).toString() << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

    SECTION("Correct file but everything is on one column") {
        Board b;
        std::string s {"../../TestFile/formation3.txt"};
        b.loadFile(s, Team::BLUE);
        for(int i{}; i < b.getSize() + 2; i++)
        {
            for(int j{}; j < b.getSize() + 2; j++)
            {
                std::cout << b.getPawn(Position(i, j)).toString() << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

    SECTION("File that doesn't exist") {
        Board b;
        std::string s {"../../TestFile/formation0.txt"};
        REQUIRE_THROWS_MATCHES(b.loadFile(s, Team::BLUE), std::invalid_argument,
                               Catch::Message("The file doesn't exist or the path is wrong"));
    }

    SECTION("File that contains a symble that doesn't exist") {
        Board b;
        std::string s {"../../TestFile/formation4.txt"};
        REQUIRE_THROWS_MATCHES(b.loadFile(s, Team::BLUE), std::invalid_argument,
                               Catch::Message("There is a symbole that doesn't exist or this symbole can't be used : D"));
    }

    SECTION("File that contains a symble that can't be used") {
        Board b;
        std::string s {"../../TestFile/formation5.txt"};
        REQUIRE_THROWS_MATCHES(b.loadFile(s, Team::BLUE), std::invalid_argument,
                               Catch::Message("There is a symbole that doesn't exist or this symbole can't be used : W"));
    }

    SECTION("File that contains an excess pawn type") {
        Board b;
        std::string s {"../../TestFile/formation6.txt"};
        REQUIRE_THROWS_MATCHES(b.loadFile(s, Team::BLUE), std::invalid_argument,
                               Catch::Message("The file contains an excess pawn type : B"));
    }

    SECTION("File doesn't contains enough pawn") {
        Board b;
        std::string s {"../../TestFile/formation7.txt"};
        REQUIRE_THROWS_MATCHES(b.loadFile(s, Team::BLUE), std::invalid_argument,
                               Catch::Message("There are 10 missing pawns."));
    }
}

TEST_CASE("When the player want to put a pawn at a given position", "[board][pawn]")
{
    SECTION("A position that is outside of the board") {
        Board b;
        Pawn p {Role::SCOUT, Team::BLUE};
        REQUIRE_THROWS_MATCHES(b.putPawn(p, Position(-5, 8)), std::invalid_argument,
                               Catch::Message("The position is not inside the board."));
        REQUIRE_THROWS_MATCHES(b.putPawn(p, Position(8, -1)), std::invalid_argument,
                               Catch::Message("The position is not inside the board."));
        REQUIRE_THROWS_MATCHES(b.putPawn(p, Position(0, 5)), std::invalid_argument,
                               Catch::Message("The position is not inside the board."));
        REQUIRE_THROWS_MATCHES(b.putPawn(p, Position(8, 0)), std::invalid_argument,
                               Catch::Message("The position is not inside the board."));
        REQUIRE_THROWS_MATCHES(b.putPawn(p, Position(11, 5)), std::invalid_argument,
                               Catch::Message("The position is not inside the board."));
        REQUIRE_THROWS_MATCHES(b.putPawn(p, Position(8, 11)), std::invalid_argument,
                               Catch::Message("The position is not inside the board."));
    }

    SECTION("Position not in the good side of the board") {
        Board b;
        Pawn p1 {Role::SCOUT, Team::BLUE};
        Pawn p2 {Role::SCOUT, Team::RED};
        REQUIRE_THROWS_MATCHES(b.putPawn(p1, Position(6, 1)), std::invalid_argument,
                               Catch::Message("The pawn can only be placed on your side of the board."));
        REQUIRE_THROWS_MATCHES(b.putPawn(p1, Position(6, 5)), std::invalid_argument,
                                Catch::Message("The pawn can only be placed on your side of the board."));
        REQUIRE_THROWS_MATCHES(b.putPawn(p1, Position(6, 10)), std::invalid_argument,
                                Catch::Message("The pawn can only be placed on your side of the board."));
        REQUIRE_THROWS_MATCHES(b.putPawn(p1, Position(3, 1)), std::invalid_argument,
                                Catch::Message("The pawn can only be placed on your side of the board."));
        REQUIRE_THROWS_MATCHES(b.putPawn(p1, Position(2, 5)), std::invalid_argument,
                                Catch::Message("The pawn can only be placed on your side of the board."));
        REQUIRE_THROWS_MATCHES(b.putPawn(p1, Position(2, 9)), std::invalid_argument,
                                Catch::Message("The pawn can only be placed on your side of the board."));
        REQUIRE_THROWS_MATCHES(b.putPawn(p2, Position(7, 1)), std::invalid_argument,
                                Catch::Message("The pawn can only be placed on your side of the board."));
        REQUIRE_THROWS_MATCHES(b.putPawn(p2, Position(7, 5)), std::invalid_argument,
                                Catch::Message("The pawn can only be placed on your side of the board."));
        REQUIRE_THROWS_MATCHES(b.putPawn(p2, Position(7, 10)), std::invalid_argument,
                                Catch::Message("The pawn can only be placed on your side of the board."));
        REQUIRE_THROWS_MATCHES(b.putPawn(p2, Position(8, 6)), std::invalid_argument,
                                Catch::Message("The pawn can only be placed on your side of the board."));
    }

    SECTION("Good position for the pawn") {
        Board b;
        Pawn p1 {Role::SCOUT, Team::BLUE};
        Pawn p2 {Role::SCOUT, Team::RED};
        for(int i {1}; i <= 4; i++)
        {
            for(int j {1}; j <= b.getSize(); j++)
            {
                b.putPawn(p2, Position(i, j));
            }
        }

        for(int i {7}; i <= 10; i++)
        {
            for(int j {1}; j <= b.getSize(); j++)
            {
                b.putPawn(p1, Position(i, j));
            }
        }

        for(int i{1}; i <= b.getSize(); i++)
        {
            for(int j{1}; j <= b.getSize(); j++)
            {
                std::cout << b.getPawn(Position(i, j)).toString() << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
}

TEST_CASE("Pawn replaced when remove from the board", "[board][pawn]")
{
    Board b;
    Pawn p {Role::SCOUT, Team::BLUE};
    b.putPawn(p, Position(8, 5));
    Pawn rp {b.removePawn(Position(8, 5))};
    REQUIRE(b.getPawn(Position(8, 5)).toString() == "*");
    REQUIRE(rp.toString() == "2");
}

TEST_CASE("Pawn that can't be moved", "[board][pawn]")
{
    SECTION("Given position is not inside the board") {
        Board b;
        Pawn p {Role::SCOUT, Team::BLUE};
        Position pos {-1, 10};
        REQUIRE_THROWS_MATCHES(b.canBePicked(Position(11, 0), Team::BLUE), std::invalid_argument,
                               Catch::Message("The given position is not inside the board."));
        REQUIRE_THROWS_MATCHES(b.canBePicked(Position(0, 11), Team::BLUE), std::invalid_argument,
                               Catch::Message("The given position is not inside the board."));
        REQUIRE_THROWS_MATCHES(b.canBePicked(Position(11, 11), Team::BLUE), std::invalid_argument,
                               Catch::Message("The given position is not inside the board."));
    }

    SECTION("The player gives a position where there is no pawn.") {
        Board b;
        Pawn p {Role::SCOUT, Team::BLUE};
        REQUIRE_THROWS_MATCHES(b.canBePicked(Position(8, 5), Team::BLUE), std::invalid_argument,
                               Catch::Message("There is no pawn at the given position."));
        REQUIRE_THROWS_MATCHES(b.canBePicked(Position(9, 9), Team::BLUE), std::invalid_argument,
                               Catch::Message("There is no pawn at the given position."));
        REQUIRE_THROWS_MATCHES(b.canBePicked(Position(2, 4), Team::BLUE), std::invalid_argument,
                               Catch::Message("There is no pawn at the given position."));
    }

    SECTION("The choosen pawn is not a moveable pawn") {
        Board b;
        Pawn bomb {Role::BOMB, Team::BLUE};
        Pawn flag {Role::FLAG, Team::BLUE};
        b.putPawn(bomb, Position(8, 5));
        b.putPawn(flag, Position(9, 9));
        REQUIRE_THROWS_MATCHES(b.canBePicked(Position(8, 5), bomb.getTeam()), std::invalid_argument,
                               Catch::Message("The chosen pawn is not a moveable pawn."));
        REQUIRE_THROWS_MATCHES(b.canBePicked(Position(9, 9), flag.getTeam()), std::invalid_argument,
                               Catch::Message("The chosen pawn is not a moveable pawn."));
    }

    SECTION("The choosen pawn is not from the current player team.") {
        Board b;
        Pawn p {Role::SCOUT, Team::BLUE};
        b.putPawn(p, Position(8, 5));
        REQUIRE_THROWS_MATCHES(b.canBePicked(Position(8, 5), Team::RED), std::invalid_argument,
                               Catch::Message("You can't select an enemy pawn."));
    }

    SECTION("The choosen pawn is surrounded by allied pawns and wall") {
        Board b;
        Pawn p {Role::SCOUT, Team::BLUE};
        b.putPawn(p, Position(7, 2));
        b.putPawn(p, Position(8, 3));
        b.putPawn(p, Position(7, 4));
        b.putPawn(p, Position(7, 3));
        REQUIRE_THROWS_MATCHES(b.canBePicked(Position(7, 3), Team::BLUE), std::invalid_argument,
                               Catch::Message("The can't move because it's surrounded by allied pawn or wall."));
    }

    SECTION("The choosen pawn is surrounded by allied pawns") {
        Board b;
        Pawn p {Role::SCOUT, Team::BLUE};
        b.putPawn(p, Position(7, 3));
        b.putPawn(p, Position(8, 4));
        b.putPawn(p, Position(8, 2));
        b.putPawn(p, Position(9, 3));
        b.putPawn(p, Position(8, 3));
        REQUIRE_THROWS_MATCHES(b.canBePicked(Position(8, 3), Team::BLUE), std::invalid_argument,
                               Catch::Message("The can't move because it's surrounded by allied pawn or wall."));
    }
}

TEST_CASE("The pawn can move", "[board][pawn]")
{
    SECTION("Pawn not surrounded by allied pawn or wall") {
        Board b;
        Pawn p {Role::COLONEL, Team::BLUE};
        b.putPawn(p, Position(8, 5));
        REQUIRE(true == b.canBePicked(Position(8, 5), Team::BLUE));
    }

    SECTION("Pawn surrounded by 1 allied pawns") {
        Board b;
        Pawn p {Role::COLONEL, Team::BLUE};
        b.putPawn(p, Position(8, 5));
        b.putPawn(p, Position(8, 6));
        REQUIRE(true == b.canBePicked(Position(8, 5), Team::BLUE));
    }

    SECTION("Pawn surrounded by 2 allied pawns") {
        Board b;
        Pawn p {Role::COLONEL, Team::BLUE};
        b.putPawn(p, Position(8, 5));
        b.putPawn(p, Position(8, 6));
        b.putPawn(p, Position(7, 5));
        REQUIRE(true == b.canBePicked(Position(8, 5), Team::BLUE));
    }

    SECTION("Pawn surrounded by 3 allied pawns") {
        Board b;
        Pawn p {Role::COLONEL, Team::BLUE};
        b.putPawn(p, Position(8, 5));
        b.putPawn(p, Position(8, 6));
        b.putPawn(p, Position(7, 5));
        b.putPawn(p, Position(8, 4));
        REQUIRE(true == b.canBePicked(Position(8, 5), Team::BLUE));
    }

    SECTION("Pawn surrounded by 1 wall") {
        Board b;
        Pawn p {Role::COLONEL, Team::BLUE};
        b.putPawn(p, Position(7, 4));
        REQUIRE(true == b.canBePicked(Position(7, 4), Team::BLUE));
    }

    SECTION("Pawn surrounded by 1 wall and 1 allied pawn") {
        Board b;
        Pawn p {Role::COLONEL, Team::BLUE};
        b.putPawn(p, Position(7, 4));
        b.putPawn(p, Position(7, 5));
        REQUIRE(true == b.canBePicked(Position(7, 4), Team::BLUE));
    }

    SECTION("Pawn surrounded by 1 wall and 2 allied pawns") {
        Board b;
        Pawn p {Role::COLONEL, Team::BLUE};
        b.putPawn(p, Position(7, 4));
        b.putPawn(p, Position(7, 5));
        b.putPawn(p, Position(8, 4));
        REQUIRE(true == b.canBePicked(Position(7, 4), Team::BLUE));
    }

    SECTION("Pawn surrounded by 2 walls") {
        Board b;
        Pawn p {Role::COLONEL, Team::BLUE};
        b.putPawn(p, Position(10, 1));
        REQUIRE(true == b.canBePicked(Position(10, 1), Team::BLUE));
    }

    SECTION("Pawn surrounded by 2 walls and 1 allied pawn") {
        Board b;
        Pawn p {Role::COLONEL, Team::BLUE};
        b.putPawn(p, Position(10, 1));
        b.putPawn(p, Position(10, 2));
        REQUIRE(true == b.canBePicked(Position(10, 1), Team::BLUE));
    }
}

TEST_CASE("When we want to move the to a position", "[board][pawn]") {

    SECTION("Move a pawn to a position that is not inside the board") {
        Board b;
        Pawn p {Role::SCOUT, Team::BLUE};
        b.putPawn(p, Position(8, 5));
        REQUIRE_THROWS_MATCHES(b.isCorrectMove(Position(8, 5), Position(-1, 0)), std::invalid_argument,
                               Catch::Message("the destination is not inside the board."));
        REQUIRE_THROWS_MATCHES(b.isCorrectMove(Position(8, 5), Position(0, -1)), std::invalid_argument,
                               Catch::Message("the destination is not inside the board."));
        REQUIRE_THROWS_MATCHES(b.isCorrectMove(Position(8, 5), Position(11, 0)), std::invalid_argument,
                               Catch::Message("the destination is not inside the board."));
        REQUIRE_THROWS_MATCHES(b.isCorrectMove(Position(8, 5), Position(0, 11)), std::invalid_argument,
                               Catch::Message("the destination is not inside the board."));
        REQUIRE_THROWS_MATCHES(b.isCorrectMove(Position(8, 5), Position(14, 25)), std::invalid_argument,
                               Catch::Message("the destination is not inside the board."));
        REQUIRE_THROWS_MATCHES(b.isCorrectMove(Position(8, 5), Position(11, 11)), std::invalid_argument,
                               Catch::Message("the destination is not inside the board."));
        REQUIRE_THROWS_MATCHES(b.isCorrectMove(Position(8, 5), Position(0, 0)), std::invalid_argument,
                               Catch::Message("the destination is not inside the board."));
        REQUIRE_THROWS_MATCHES(b.isCorrectMove(Position(8, 5), Position(-6, -21)), std::invalid_argument,
                               Catch::Message("the destination is not inside the board."));
    }

    SECTION("Move a pawn to a position which is already occupied by an allied pawn") {
        Board b;
        Pawn p {Role::SCOUT, Team::BLUE};
        b.putPawn(p, Position(7, 4));
        b.putPawn(p, Position(7, 5));
        REQUIRE_THROWS_MATCHES(b.isCorrectMove(Position(7, 4), Position(7, 5)), std::invalid_argument,
                               Catch::Message("The destination is not free because there is an allied pawn or a wall."));
    }

    SECTION("Move a pawn to a position where there is a wall") {
        Board b;
        Pawn p {Role::SCOUT, Team::BLUE};
        b.putPawn(p, Position(7, 4));
        b.putPawn(p, Position(7, 5));
        REQUIRE_THROWS_MATCHES(b.isCorrectMove(Position(7, 4), Position(6, 4)), std::invalid_argument,
                               Catch::Message("The destination is not free because there is an allied pawn or a wall."));
    }

    SECTION("Too much back and forth for the choosen pawn") {
        Board b;
        Pawn p {Role::SCOUT, Team::BLUE};
        p.addMove(Position(7, 4));
        for(int i {}; i < 3; i++)
        {
            p.addMove(Position(7, 5));
            p.addMove(Position(7, 4));
        }
        b.putPawn(p, Position(7, 5));

        REQUIRE_THROWS_MATCHES(b.isCorrectMove(Position(7, 5), Position(7, 4)), std::invalid_argument,
                               Catch::Message("You can't do more than 3 back and forth."));
    }

    SECTION("Move a scout to a position that is not in the scout's x or y axis") {
        Board b;
        Pawn p {Role::SCOUT, Team::BLUE};
        b.putPawn(p, Position(8, 5));
        REQUIRE_THROWS_MATCHES(b.isCorrectMove(Position(8, 5), Position(7, 4)), std::invalid_argument,
                               Catch::Message("The destination of the pawn is not in the horizontal or "
                                              "vertical axis of the pawn."));
        REQUIRE_THROWS_MATCHES(b.isCorrectMove(Position(8, 5), Position(7, 8)), std::invalid_argument,
                               Catch::Message("The destination of the pawn is not in the horizontal or "
                                              "vertical axis of the pawn."));
        REQUIRE_THROWS_MATCHES(b.isCorrectMove(Position(8, 5), Position(10, 4)), std::invalid_argument,
                               Catch::Message("The destination of the pawn is not in the horizontal or "
                                              "vertical axis of the pawn."));
        REQUIRE_THROWS_MATCHES(b.isCorrectMove(Position(8, 5), Position(9, 3)), std::invalid_argument,
                               Catch::Message("The destination of the pawn is not in the horizontal or "
                                              "vertical axis of the pawn."));
        REQUIRE_THROWS_MATCHES(b.isCorrectMove(Position(8, 5), Position(4, 4)), std::invalid_argument,
                               Catch::Message("The destination of the pawn is not in the horizontal or "
                                              "vertical axis of the pawn."));
        REQUIRE_THROWS_MATCHES(b.isCorrectMove(Position(8, 5), Position(2, 3)), std::invalid_argument,
                               Catch::Message("The destination of the pawn is not in the horizontal or "
                                              "vertical axis of the pawn."));
        REQUIRE_THROWS_MATCHES(b.isCorrectMove(Position(8, 5), Position(2, 7)), std::invalid_argument,
                               Catch::Message("The destination of the pawn is not in the horizontal or "
                                              "vertical axis of the pawn."));
        REQUIRE_THROWS_MATCHES(b.isCorrectMove(Position(8, 5), Position(5, 9)), std::invalid_argument,
                               Catch::Message("The destination of the pawn is not in the horizontal or "
                                              "vertical axis of the pawn."));
        REQUIRE_THROWS_MATCHES(b.isCorrectMove(Position(8, 5), Position(1, 10)), std::invalid_argument,
                               Catch::Message("The destination of the pawn is not in the horizontal or "
                                              "vertical axis of the pawn."));
        REQUIRE_THROWS_MATCHES(b.isCorrectMove(Position(8, 5), Position(1, 2)), std::invalid_argument,
                               Catch::Message("The destination of the pawn is not in the horizontal or "
                                              "vertical axis of the pawn."));
    }

    SECTION("Move a scout to a position but there is an obstacle on the way") {
        Board b;
        Pawn p {Role::SCOUT, Team::BLUE};
        Pawn p2 {Role::SCOUT, Team::RED};
        b.putPawn(p, Position(8, 4));
        b.putPawn(p, Position(8, 2));
        b.putPawn(p, Position(8, 9));
        b.putPawn(p, Position(9, 4));
        b.putPawn(p2, Position(2, 9));
        REQUIRE_THROWS_MATCHES(b.isCorrectMove(Position(8, 4), Position(8, 1)), std::invalid_argument,
                               Catch::Message("There is an obstacle in the way."));
        REQUIRE_THROWS_MATCHES(b.isCorrectMove(Position(8, 4), Position(8, 10)), std::invalid_argument,
                               Catch::Message("There is an obstacle in the way."));
        REQUIRE_THROWS_MATCHES(b.isCorrectMove(Position(8, 4), Position(10, 4)), std::invalid_argument,
                               Catch::Message("There is an obstacle in the way."));
        REQUIRE_THROWS_MATCHES(b.isCorrectMove(Position(8, 4), Position(1, 4)), std::invalid_argument,
                               Catch::Message("There is an obstacle in the way."));
        REQUIRE_THROWS_MATCHES(b.isCorrectMove(Position(8, 9), Position(1, 9)), std::invalid_argument,
                               Catch::Message("There is an obstacle in the way."));
        REQUIRE_THROWS_MATCHES(b.isCorrectMove(Position(2, 9), Position(10, 9)), std::invalid_argument,
                               Catch::Message("There is an obstacle in the way."));
    }

    SECTION("Move a pawn to a position that is farther than 1 square") {
        Board b;
        Pawn p {Role::COLONEL, Team::BLUE};
        b.putPawn(p, Position(8, 4));
        REQUIRE_THROWS_MATCHES(b.isCorrectMove(Position(8, 4), Position(6, 5)), std::invalid_argument,
                               Catch::Message("the destination is not a square around the chosen pawn."));
        REQUIRE_THROWS_MATCHES(b.isCorrectMove(Position(8, 4), Position(7, 6)), std::invalid_argument,
                               Catch::Message("the destination is not a square around the chosen pawn."));
        REQUIRE_THROWS_MATCHES(b.isCorrectMove(Position(8, 4), Position(8, 7)), std::invalid_argument,
                               Catch::Message("the destination is not a square around the chosen pawn."));
        REQUIRE_THROWS_MATCHES(b.isCorrectMove(Position(8, 4), Position(9, 6)), std::invalid_argument,
                               Catch::Message("the destination is not a square around the chosen pawn."));
        REQUIRE_THROWS_MATCHES(b.isCorrectMove(Position(8, 4), Position(10, 5)), std::invalid_argument,
                               Catch::Message("the destination is not a square around the chosen pawn."));
        REQUIRE_THROWS_MATCHES(b.isCorrectMove(Position(8, 4), Position(4, 8)), std::invalid_argument,
                               Catch::Message("the destination is not a square around the chosen pawn."));
        REQUIRE_THROWS_MATCHES(b.isCorrectMove(Position(8, 4), Position(1, 4)), std::invalid_argument,
                               Catch::Message("the destination is not a square around the chosen pawn."));
    }

    SECTION("Correct move for a scout") {
        Board b;
        Pawn p {Role::SCOUT, Team::BLUE};
        b.putPawn(p, Position(8, 5));
        REQUIRE(true == b.isCorrectMove(Position(8, 5), Position(1, 5)));
        REQUIRE(true == b.isCorrectMove(Position(8, 5), Position(8, 1)));
        REQUIRE(true == b.isCorrectMove(Position(8, 5), Position(8, 10)));
        REQUIRE(true == b.isCorrectMove(Position(8, 5), Position(10, 5)));
        REQUIRE(true == b.isCorrectMove(Position(8, 5), Position(5, 5)));
        REQUIRE(true == b.isCorrectMove(Position(8, 5), Position(8, 4)));
        REQUIRE(true == b.isCorrectMove(Position(8, 5), Position(8, 7)));
    }

    SECTION("Correct move for a pawn") {
        Board b;
        Pawn p {Role::SCOUT, Team::BLUE};
        b.putPawn(p, Position(8, 5));
        REQUIRE(true == b.isCorrectMove(Position(8, 5), Position(7, 5)));
        REQUIRE(true == b.isCorrectMove(Position(8, 5), Position(9, 5)));
        REQUIRE(true == b.isCorrectMove(Position(8, 5), Position(8, 4)));
        REQUIRE(true == b.isCorrectMove(Position(8, 5), Position(8, 6)));
    }
}

TEST_CASE("Check if there is an enemy pawn at the destination", "[board][pawn]")
{
    SECTION("When there is no enemy at the position") {
        Board b;
        REQUIRE(false == b.isThereEnemy(Position(3, 6), Team::BLUE));
    }

    SECTION("When there is an enemy pawn at the position") {
        Board b;
        Pawn p {Role::COLONEL, Team::RED};
        b.putPawn(p, Position(3, 6));
        REQUIRE(true == b.isThereEnemy(Position(3, 6), Team::BLUE));
    }
}

TEST_CASE("Move a pawn", "[board][pawn]") {
    Board b;
    Pawn p {Role::COLONEL, Team::BLUE};
    b.putPawn(p, Position(7, 5));
    for(int i{1}; i <= b.getSize(); i++)
    {
        for(int j{1}; j <= b.getSize(); j++)
        {
            std::cout << b.getPawn(Position(i, j)).toString() << " ";
        }
        std::cout << std::endl;
    }

    std::cout << std::endl;
    b.move(Position(7, 5), Position(6, 5));

    for(int i{1}; i <= b.getSize(); i++)
    {
        for(int j{1}; j <= b.getSize(); j++)
        {
            std::cout << b.getPawn(Position(i, j)).toString() << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

TEST_CASE("Duel between 2 pawns", "[board][pawn]")
{
    SECTION("Spy attacking a marechal") {
        Board b;
        Pawn spy {Role::SPY, Team::BLUE};
        Pawn marechal {Role::MARECHAL, Team::RED};
        b.putPawn(spy, Position(7, 5));
        b.putPawn(marechal, Position(4, 5));
        REQUIRE(1 == b.pawnDuel(Position(7, 5), Position(4, 5)));
    }

    SECTION("Deminer attacking a bomb") {
        Board b;
        Pawn deminer {Role::DEMINER, Team::BLUE};
        Pawn bomb {Role::BOMB, Team::RED};
        b.putPawn(deminer, Position(7, 5));
        b.putPawn(bomb, Position(4, 5));
        REQUIRE(1 == b.pawnDuel(Position(7, 5), Position(4, 5)));
    }

    SECTION("A pawn attacking a flag") {
        Board b;
        Pawn deminer {Role::DEMINER, Team::BLUE};
        Pawn flag {Role::FLAG, Team::RED};
        b.putPawn(deminer, Position(7, 5));
        b.putPawn(flag, Position(4, 5));
        REQUIRE(1 == b.pawnDuel(Position(7, 5), Position(4, 5)));
    }

    SECTION("A strong pawn attacking a weak pawn") {
        Board b;
        Pawn colonel {Role::COLONEL, Team::BLUE};
        Pawn deminer {Role::DEMINER, Team::RED};
        b.putPawn(colonel, Position(7, 5));
        b.putPawn(deminer, Position(4, 5));
        REQUIRE(1 == b.pawnDuel(Position(7, 5), Position(4, 5)));
    }

    SECTION("2 pawns of the same value") {
        Board b;
        Pawn colonel1 {Role::COLONEL, Team::BLUE};
        Pawn colonel2 {Role::COLONEL, Team::RED};
        b.putPawn(colonel1, Position(7, 5));
        b.putPawn(colonel2, Position(4, 5));
        REQUIRE(0 == b.pawnDuel(Position(7, 5), Position(4, 5)));
    }

    SECTION("A weak pawn attacking a strong pawn") {
        Board b;
        Pawn deminer {Role::DEMINER, Team::BLUE};
        Pawn colonel {Role::COLONEL, Team::RED};
        b.putPawn(deminer, Position(7, 5));
        b.putPawn(colonel, Position(4, 5));
        REQUIRE(-1 == b.pawnDuel(Position(7, 5), Position(4, 5)));
    }
}

TEST_CASE("Test to check if the player is blocked.", "[board][pawn]")
{
    SECTION("Situation 1 : blocked") {
        Board b;
        Pawn p1 {Role::SCOUT, Team::BLUE};
        Pawn p2 {Role::BOMB, Team::BLUE};
        b.putPawn(p2, Position(8, 1));
        b.putPawn(p2, Position(8, 2));
        b.putPawn(p2, Position(8, 3));
        b.putPawn(p2, Position(8, 4));
        b.putPawn(p2, Position(9, 4));
        b.putPawn(p2, Position(10, 4));
        b.putPawn(p1, Position(9, 1));
        b.putPawn(p1, Position(9, 2));
        b.putPawn(p1, Position(9, 3));
        b.putPawn(p1, Position(10, 1));
        b.putPawn(p1, Position(10, 2));
        b.putPawn(p1, Position(10, 3));
        REQUIRE(true == b.isCurrentPlayerBlocked(Team::BLUE));
    }

    SECTION("Situation 2 : blocked") {
        Board b;
        Pawn p1 {Role::SCOUT, Team::BLUE};
        Pawn p2 {Role::BOMB, Team::BLUE};
        Pawn p3 {Role::FLAG, Team::BLUE};
        b.putPawn(p2, Position(8, 7));
        b.putPawn(p2, Position(8, 8));
        b.putPawn(p3, Position(8, 9));
        b.putPawn(p2, Position(8, 10));
        b.putPawn(p2, Position(9, 7));
        b.putPawn(p2, Position(10, 7));
        b.putPawn(p1, Position(9, 8));
        b.putPawn(p1, Position(9, 9));
        b.putPawn(p1, Position(9, 10));
        b.putPawn(p1, Position(10, 8));
        b.putPawn(p1, Position(10, 9));
        b.putPawn(p1, Position(10, 10));
        REQUIRE(true == b.isCurrentPlayerBlocked(Team::BLUE));
    }

    SECTION("Situation 3 : not blocked") {
        Board b;
        Pawn p1 {Role::SCOUT, Team::BLUE};
        Pawn p2 {Role::BOMB, Team::BLUE};
        b.putPawn(p2, Position(8, 1));
        b.putPawn(p2, Position(8, 2));
        b.putPawn(p2, Position(8, 4));
        b.putPawn(p2, Position(9, 4));
        b.putPawn(p2, Position(10, 4));
        b.putPawn(p1, Position(9, 1));
        b.putPawn(p1, Position(9, 2));
        b.putPawn(p1, Position(9, 3));
        b.putPawn(p1, Position(10, 1));
        b.putPawn(p1, Position(10, 2));
        b.putPawn(p1, Position(10, 3));
        REQUIRE(false == b.isCurrentPlayerBlocked(Team::BLUE));
    }

    SECTION("Situation 4 : not blocked") {
        Board b;
        Pawn p1 {Role::SCOUT, Team::BLUE};
        Pawn p2 {Role::BOMB, Team::BLUE};
        Pawn p3 {Role::FLAG, Team::BLUE};
        b.putPawn(p2, Position(8, 7));
        b.putPawn(p2, Position(8, 8));
        b.putPawn(p3, Position(8, 9));
        b.putPawn(p2, Position(8, 10));
        b.putPawn(p2, Position(9, 7));
        b.putPawn(p1, Position(9, 8));
        b.putPawn(p1, Position(9, 9));
        b.putPawn(p1, Position(9, 10));
        b.putPawn(p1, Position(10, 8));
        b.putPawn(p1, Position(10, 9));
        b.putPawn(p1, Position(10, 10));
        REQUIRE(false == b.isCurrentPlayerBlocked(Team::BLUE));
    }
}

TEST_CASE("Creation of the game and start of the game", "[board][pawn]")
{
    SECTION("The creation of an object Game") {
        Game g;
        REQUIRE(g.getGameResult() == GameResult::CONTINUE);
        REQUIRE(g.getState() == State::NOT_STARTED);
        REQUIRE(g.getDuelResult() == 2);
        REQUIRE(g.getPickedPosition().getX() == 0);
        REQUIRE(g.getPickedPosition().getY() == 0);
        REQUIRE(g.getDestinationPosition().getX() == 0);
        REQUIRE(g.getDestinationPosition().getY() == 0);
    }

    SECTION("The start of the game") {
        Game g;
        g.start(true);
        REQUIRE(g.getState() == State::SET_UP);
        REQUIRE(g.getNumberOfPlayer() == 2);
        REQUIRE(g.getPlayerTeam(0) == Team::BLUE);
        REQUIRE(g.getPlayerTeam(1) == Team::RED);
    }
}
