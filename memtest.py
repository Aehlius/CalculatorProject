def memtest(i=0):
    print(i)
    memtest(i+1)

if __name__ == '__main__':
    memtest(0)