#include <iostream>
#include <array>
#include <string>
#include <algorithm>
#include <limits>

enum Piece {none, cross, nought};

enum GameState {START, IN_PROGRESS, WINNER, DRAW};

class board {
    int turn = 1;
    GameState game_state = START;

    std::array<std::array<Piece, 3>, 3> board = {{
                                                         {none, none, none},
                                                         {none, none, none},
                                                         {none, none, none}
                                                 }};
    public:
        void print();
        GameState play_turn(int posX, int posY);
        int get_turn();
        Piece at_position(int posX, int posY);
        std::string get_piece();
        GameState getGameState() const;

private:
    GameState winning_condition(Piece side);


};

void board::print() {
    for (int i = 0; i < board.size(); ++i) {
        for (int j = 0; j < board.at(0).size(); ++j) {
            std::cout << board.at(i).at(j) << " ";
        }
        std::cout << std::endl;
    }
}

GameState board::play_turn(int posX, int posY) {
    game_state = IN_PROGRESS;
    auto side = (turn % 2 == 0) ? nought: cross;
    board.at(posY).at(posX) = side;
    print();
    GameState gameState = winning_condition(side);
    if (gameState == IN_PROGRESS)
        turn++;
    return gameState;

}

int board::get_turn() {
    return turn;
}

Piece board::at_position(int posX, int posY) {
    return board.at(posY).at(posX);
}

GameState board::winning_condition(Piece side) {
    //horizontal
    for (int i = 0; i < board.size(); ++i) {
        if (board.at(i).at(0) == side && board.at(i).at(1) == side && board.at(i).at(2) == side){
            return WINNER;
        }
    }

    //vertical
    for (int i = 0; i < board.size(); ++i) {
        if (board.at(0).at(i) == side && board.at(1).at(i) == side && board.at(2).at(i) == side){
            return WINNER;
        }
    }

    //diagonal left
    if (board.at(0).at(0) == side && board.at(1).at(1) == side && board.at(2).at(2) == side){
        return WINNER;
    }

    //diagonial right
    if (board.at(0).at(2) == side && board.at(1).at(1) == side && board.at(2).at(0) == side){
        return WINNER;
    }

    for (int i = 0; i < board.size(); ++i) {
        for (int j = 0; j < board.size(); ++j) {
            if (board.at(i).at(j) == none)
                return IN_PROGRESS;
        }
    }
    return DRAW;

}

std::string board::get_piece() {
    return (turn % 2 == 0) ? "noughts" : "crosses";

}

GameState board::getGameState() const {
    return game_state;
}

int main() {
    std::cout << "Naughts and crosses, enter in coordinate to place your piece" << std::endl;
    board b{};

    while(true){
        int posX, posY;
        std::cout << "Turn: " << b.get_turn() << " Side: " << b.get_piece() << std::endl;

        do {
            // Prevent infinite looping
            if (std::cin.fail()) {
                std::cin.clear();
            }

            std::cout << ">> ";
            std::cin >> posX >> posY;
        } while (posX >= 3 || posX < 0 || posY >= 3 || posY < 0 || b.at_position(posX, posY) != Piece::none);

        GameState gameState = b.play_turn(posX, posY);

        if (gameState == WINNER){
            std::cout << "WINNER! " << b.get_piece() << " on turn " << b.get_turn();
            return 0;
        } else if (gameState == DRAW){
            std::cout << "DRAW! on turn " << b.get_turn();
            return 0;
        }
    }
}
