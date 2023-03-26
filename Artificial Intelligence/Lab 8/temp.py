# Performance measure:
#  +1000 for picking up gold, -1000 for death (meeting a live wumpus or falling into a pit)
#  -1 for each action taken, -10 for using arrow
# Actions: Turn Left, Turn Right, Move Forward, Grab, Shoot, release
# Sensors: Breeze,Stench,Glitter,Scream (When the Wumpus is killed),Bump (when the agent hits a wall)
# The agent starts at the bottom left corner of the grid and has to reach the room with gold and teleports out of the grid

# This program is done by CS20B1044 Avinash R Changrani

import numpy as np
from random import randint

# Constants
# stench
S = 0
# Breeze
B = 1
# Pit
P = 2
# Wumpus
W = 3
# Vacant
V = 4
# Glitter
G = 5


class WumpusWorld:
    def __init__(self, default=True):
        if default:
            self.world = np.matrix([    
                ['S',       '',         'B',        'P'], 
                ['W',       'B,S,G',    'P',        'B'], 
                ['S',       '',         'B',        ''], 
                ['',        'B',        'P',        'B']
            ])
        else:
            self.world = self.create_world()
    
    def create_world(self):
        temp_world = np.zeros((4,4), dtype=str)

        components = []
        while len(components) < 3:
            row = randint(0,3)
            col = randint(0,3)
            if row != 0 and col != 0 and temp_world[row][col] == '':
                temp_world[row][col] = 'P'
                components.append(['P', [row, col]])
                
        while len(components) < 4:
            row = randint(0,3)
            col = randint(0,3)
            if row != 0 and col != 0 and temp_world[row][col] == '':
                temp_world[row][col] = 'W'
                components.append(['W', [row, col]])
                
        while len(components) < 5:
            row = randint(0,3)
            col = randint(0,3)
            if row != 0 and col != 0 and temp_world[row][col] == '':
                temp_world[row][col] = 'G'
                components.append(['G', [row, col]])

        for t, pos in components:
            if pos[0] + 1 < 4:
                self.create_stench_and_breeze(temp_world, pos[0]+1, pos[1], t == 'W')
            if pos[0] - 1 > 0:
                self.create_stench_and_breeze(temp_world, pos[0]-1, pos[1], t == 'W')
            if pos[0] + 1 < 4:
                self.create_stench_and_breeze(temp_world, pos[0], pos[1]+1, t == 'W')
            if pos[1] - 1 > 0:
                self.create_stench_and_breeze(temp_world, pos[0], pos[1]-1, t == 'W')
        
        return temp_world


    def create_stench_and_breeze(self, temp_world, row, col, stench):
        if stench:
            if temp_world[row][col] == '':
                temp_world[row][col] = 'S'
            else:
                temp_world[row][col] += ',S'
        else:
            if temp_world[row][col] == '':
                temp_world[row][col] = 'B'
            else:
                temp_world[row][col] += ',B'
            

    def get_pos(self, wld, col, row):
        return wld[4-row, col-1]


    def cell(self, col, row):
        return self.get_pos(self.world, col, row).split(",")


    def view(self):
        return self.world

# Agent
class Agent:
    def __init__(self, w_world, start_col, start_row):
        self.w_world = w_world
        self.c = start_col
        self.r = start_row
        self.direction = 'N'
        self.is_alive = True
        self.has_exited = False
        self.kb = np.zeros(
            (w_world.world.shape[0], w_world.world.shape[1], 6), 
            dtype=object
        )
        self.score = 0

        for i in range(self.kb.shape[0]):
            for j in range(self.kb.shape[1]):
                for k in range(self.kb.shape[2]):
                    self.kb[i][j][k] = ""
       
    def print_kb(self):
        for r in range(4):
            for c in range(4):
                for x in range(6):
                    print('{:>2},'.format(self.kb[r][c][x]), end='')
                print('\t', end='')
            print('\n')
    
    def loc(self):
        return np.array([self.c, self.r])
    
    
    # sensors (this must be an array of size 5...)
    def perceives(self):
        pos = self.loc()
        return self.w_world.cell(pos[0],pos[1])
    
    # this can only return inmediate locations to current position, does not return diagonal cells
    def adjacent(self):
        rows = self.w_world.world.shape[0]
        cols = self.w_world.world.shape[1]
        locations = []
        for row in [self.r - 1, self.r + 1]:
            if row > 0 and row < rows:
                #print(row, self.c)
                locations.append([(row, self.c), self.w_world.cell(row, self.c)])
        for col in [self.c - 1, self.c + 1]:
            if col > 0 and col < cols:
                #print(self.r, col)
                locations.append([(self.r, col), self.w_world.cell(self.r, col)])
        return locations
    
    
    # Agent can only move one step at the time
    def move(self, new_r, new_c):
        if new_r != self.r:
           if new_r < self.w_world.world.shape[0] and new_r > 0:
               self.r = new_r
        if new_c != self.c:
           if new_c < self.w_world.world.shape[1] and new_c > 0:
               self.c = new_c

        return 0
    
    
    def learn_from_pos(self):
        
        actual_components = self.perceives()
        
        self.kb[4-self.r, self.c-1][S] = ("S" if "S" in actual_components else "~S")
        self.kb[4-self.r, self.c-1][B] = ("B" if "B" in actual_components else "~B")
        self.kb[4-self.r, self.c-1][P] = ("P" if "P" in actual_components else "~P")
        self.kb[4-self.r, self.c-1][W] = ("W" if "W" in actual_components else "~W")
        self.kb[4-self.r, self.c-1][V] = ("V")
        self.kb[4-self.r, self.c-1][G] = ("G" if "G" in actual_components else "~G")       
        
        for (nrow, ncol), _ in self.adjacent():

            if "S" in actual_components:
                if "~W" not in self.kb[4-nrow, ncol-1][W]:
                    self.kb[4-nrow, ncol-1][W] = "W?"
            else:
                self.kb[4-nrow, ncol-1][W] = "~W"

            if "B" in actual_components:
                if "~P" not in self.kb[4-nrow, ncol-1][P]:
                    self.kb[4-nrow, ncol-1][P] = "P?"
            else:
                self.kb[4-nrow, ncol-1][P] = "~P"

    
    # this algorithm returns the path taken to Gold or to death.
    def find_gold(self):
        path = []
        gold = False

        while not gold:
            print(f"Agent is on: {self.r}, {self.c}")
            self.learn_from_pos()
            path.append([self.r, self.c])
            next_xy = []
            self.print_kb()
            if 'G' in self.perceives():
                gold = True
                self.score += 1000
                break
            for (x,y), _ in self.adjacent():
                if "~W" == self.kb[4-x, y-1][W]:
                   if "~P" == self.kb[4-x, y-1][P]:
                      if "V" != self.kb[4-x, y-1][V]:
                        next_xy = [x,y]
                        break
            if len(next_xy) > 0:
                self.move(next_xy[0], next_xy[1])
            else:
                # if no adjacent cell is safe, go back to the last safe cell
                prev_xy = path[-2]
                self.move(prev_xy[0], prev_xy[1])
                #self.move(path[-1][0], path[-1][1])

            print()
        print("Path Taken:", path)
        self.score -= len(path)
        return "Path Taken has a score: " + str(self.score)

def main():
    wumpus_world = WumpusWorld()
    agent = Agent(wumpus_world, 1, 1)
    print("Wumpus World: ")
    print(wumpus_world.world)
    print(agent.find_gold())

if __name__ == '__main__':
    main()

