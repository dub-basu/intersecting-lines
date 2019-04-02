from random import randint

RANGE_X_NEG = -20
RANGE_X_POS = 20
RANGE_Y_NEG = -20
RANGE_Y_POS = 20
FILENAME = "case5.txt"

fout = open(FILENAME, 'w+')

def write_line_to_file(line):
    point1, point2 = line
    fout.write(''.join(str(point1).split()))
    fout.write(' ')
    fout.write(''.join(str(point2).split()))
    fout.write('\n')

def get_random_point():
    p1 = (randint(RANGE_X_NEG, RANGE_X_POS + 1), randint(RANGE_Y_NEG, RANGE_Y_POS))
    return(p1)

def get_random_line():
    line = get_random_point(), get_random_point()
    return(line)

for i in range(10000):
    line = get_random_line()
    write_line_to_file(line)

fout.close()