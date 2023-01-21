# Implement Tower of Hanoi with n disks and 3 towers  (recursive and non-recursive)

# This program is done by CS20B1044 Avinash R Changrani

# solution to  tower of hanoi problem using recursion
def tower_of_hanoi_rec(n, src, dest, aux):
    # base case
    if n == 0:
        return
    # move n-1 disks from A to B using C
    tower_of_hanoi_rec(n-1, src, aux, dest)
    # move nth disk from A to C
    print(f"Move disk {n} from rod {src} to rod {dest}")
    # move n-1 disks from B to C using A
    tower_of_hanoi_rec(n-1, aux, dest, src)

# helper function to move disks between source peg and destination peg


def helper(src, dest, s, d):
    # if src is empty
    if not len(src):
        disk = dest[-1]
        src.append(dest[-1])
        dest.pop()
        print(f"Move disk {disk} from rod {d} to rod {s}")
    # else if dest is empty
    elif not len(dest):
        disk = src[-1]
        dest.append(src[-1])
        src.pop()
        print(f"Move disk {disk} from rod {s} to rod {d}")
    # else if top disk of src is greater than top disk of dest
    elif (src[-1] > dest[-1]):
        disk = dest[-1]
        src.append(dest[-1])
        dest.pop()
        print(f"Move disk {disk} from rod {d} to rod {s}")
    # else if top disk of dest is greater than top disk of src
    elif (dest[-1] > src[-1]):
        disk = src[-1]
        dest.append(src[-1])
        src.pop()
        print(f"Move disk {disk} from rod {s} to rod {d}")


# solution to  tower of hanoi problem without using recursion
def tower_of_hanoi_nonrec(n, src, dest, aux):
    s, a, d = 1, 2, 3
    total_moves = 2**n - 1
    # if n is even exchange B and C peg value
    if n % 2 == 0:
        a, d = d, a
    # push all disks to the A peg
    for i in range(n, 0, -1):
        src.append(i)
    for i in range(total_moves):
        # move disk between s and d
        if i % 3 == 0:
            helper(src, dest, s, d)
        # move disk between s and a
        elif i % 3 == 1:
            helper(src, aux, s, a)
        # move disk between a and d
        else:
            helper(aux, dest, a, d)

# main function

def main():
    n = int(input("Enter number of disks: "))
    print("Solution to tower of hanoi problem using recursion: ")
    # A is the source peg, B is the auxiliary peg and C is the destination peg
    tower_of_hanoi_rec(n, 1, 3, 2)
    print("Solution to tower of hanoi problem without using recursion: ")
    # stacks for the 3 pegs
    src = []
    dest = []
    aux = []
    tower_of_hanoi_nonrec(n, src, dest, aux)


# running the main function
if __name__ == "__main__":
    main()
