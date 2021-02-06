
def compare(a,b,c,d):
    if a > b and a > c and a > d:
        return a
    if b > a and b > c and b > d:
        return b
    if c > b and c > a and c > d:
        return c
    return d

def lowSintaxFile():
    f = open("data/file1.txt", 'r')
    print("File open.")
    fileData = f.read()
    
    f.close()

def test():
    print(compare(1, 2, 3, 4))
    print(compare(5, 2, 3, 4))
    print(compare(1, 6, 3, 4))
    print(compare(1, 2, 7, 4))

#test()
lowSintaxFile()
