# Solve TicTacToe Problem using Alpha Beta Pruning
# This program is done by CS20B1044 Avinash R Changrani

from random import choice
from math import inf as infinity

# initialize the board with 0's
board = [
    [0, 0, 0],
    [0, 0, 0],
    [0, 0, 0]
]

# function to print the board
def print_board(board):
    print("-------------")
    for row in board:
        print("| ", end="")
        for cell in row:
            if cell == 0:
                print(" ", end=" | ")
            elif cell == 1:
                print("X", end=" | ")
            elif cell == -1:
                print("O", end=" | ")
        print()
        print("-------------")

# function to clear the board
def clear_board(board):
    for row in range(3):
        for col in range(3):
            board[row][col] = 0

# function to check if the player has won the game
def is_winning(board, player):
    # Check horizontal locations for win
    for row in range(3):
        win = True
        for col in range(3):
            if board[row][col] != player:
                win = False
                continue
        if win == True:
            return win

    # Check vertical locations for win
    for col in range(3):
        win = True
        for row in range(3):
            if board[row][col] != player:
                win = False
                continue
        if win == True:
            return win

    # Check diagonal locations for win
    if board[0][0] == player and board[1][1] == player and board[2][2] == player:
        win = True
        return win
    if board[0][2] == player and board[1][1] == player and board[2][0] == player:
        win = True
        return win

    return False

# function to check if the game is over (won by either player)
def game_over(board):
    return is_winning(board, 1) or is_winning(board, -1)

# function to print the result
def print_result(board):
    if is_winning(board, 1):
        print("X wins!")
    elif is_winning(board, -1):
        print("O wins!")
    else:
        print("Tie!")

# function to get the empty cells
def empty_cells(board):
    cells = []
    for x, row in enumerate(board):
        for y, cell in enumerate(row):
            if cell == 0:
                cells.append([x, y])
    return cells

# function to check if the board is full
def is_board_full(board):
    if len(empty_cells(board)) == 0:
        return True
    return False

# function to set the move
def set_move(board,x, y, player):
    board[x][y] = player

# function to get the player move
def player_move(board):
    move = -1
    # print the number and respective cell
    print("1 | 2 | 3")
    print("4 | 5 | 6")
    print("7 | 8 | 9")
    while move < 1 or move > 9:
        try:
            move = int(input("Enter a number (1-9): "))
            coord = [int((move - 1) / 3), (move - 1) % 3]
            if move < 1 or move > 9:
                print("Please enter a valid number")
            elif board[coord[0]][coord[1]] != 0:
                print("Cell already taken!")
                move = -1
                continue
            else:
                set_move(board, coord[0], coord[1], 1)    
                print_board(board)
                break
        except (KeyError, ValueError):
            print("Please enter a valid number")

# function to assign score to the board
def assign_score(board):
    # if the game is won by X, return 1
    if is_winning(board, 1):
        return 1
    # if the game is lost by X and won by O, return -1
    elif is_winning(board, -1):
        return -1
    # if the game is a tie, return 0
    else:
        return 0

# function to get the computer move
def alpha_beta_minmax(board, depth, alpha, beta, max_player):
    # when the game is over or we have reached the max depth
    if depth == 0 or game_over(board):
        return [-1,-1,assign_score(board)]
    else:
        # initialize the best move
        best = [-1,-1,-infinity] if max_player else [-1,-1,infinity]
        # loop through all the empty cells
        for cell in empty_cells(board):
            x, y = cell[0], cell[1]
            # set the move
            board[x][y] = 1 if max_player else -1
            # get the score
            score = alpha_beta_minmax(board, depth - 1, alpha, beta, not max_player)
            # undo the move
            board[x][y] = 0
            # update the best move
            score[0], score[1] = x, y
            # if it is the max player (X)
            if max_player:
                if score[2] > alpha:
                    alpha = score[2]
                    best = score
            # if it is the min player        
            else:
                if score[2] < beta:
                    beta = score[2]
                    best = score
            # if alpha is greater than or equal to beta, break (pruning)
            if alpha >= beta:
                break

        return best

# function to do the computer move (O move)
def o_move(board):
    # if the board is empty, choose a random cell
    if(len(empty_cells(board)) == 9):
        x = choice([0, 1, 2])
        y = choice([0, 1, 2])
    # if the board is not empty, get the best move
    else:
        move = alpha_beta_minmax(board, 9, -infinity, infinity, False)
        x, y = move[0], move[1]
    board[x][y] = -1
    print_board(board)

# function to do the computer move (X move)
def x_move(board):
    # if the board is empty, choose a random cell
    if(len(empty_cells(board)) == 9):
        x = choice([0, 1, 2])
        y = choice([0, 1, 2])
    # if the board is not empty, get the best move
    else:
        move = alpha_beta_minmax(board, 9, -infinity, infinity, True)
        x, y = move[0], move[1]
    board[x][y] = 1
    print_board(board)

# function to do the move
def make_move(board, player, isplayerplaying):
    if isplayerplaying:
        if(player == 1):
            player_move(board)
        else:
            o_move(board)
    else:
        if(player == 1):
            o_move(board)
        else:
            x_move(board)  

# main function so that game can be played by the user
def main():
    # get if the player wants to play first
    while True:
        try:
            order = int(input("Who plays first? 1 for yourself, 2 for computer: "))
            if not(order == 1 or order == 2):
                print("Please enter 1 or 2")
            else:
                break
        except (KeyError, ValueError):
            print("The input must be a number")
    # initialize the board
    clear_board(board)
    # if the player plays first
    if(order == 1):
        player = 1
    # if the player plays second
    else:
        player = -1

    # loop until the game is over
    while not (game_over(board) or is_board_full(board)):
        # do the move and change the player
        make_move(board, player, True)
        player = player * -1

    print_result(board)

if __name__ == "__main__":
    print("Welcome to Tic Tac Toe!")
    print("You are playing against the computer.")
    print("The computer uses the minimax algorithm with alpha-beta pruning.")
    print()
    main()

