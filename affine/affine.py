#!/bin/python
# affine Cipher 
# usage ./affine [e|d] <alpha> <beta>
# usage ./affine [a] <filename>

import sys
import os

alphabet=   "abcdefghijklmnopqrstuvwxyz"
capalphabet="ABCDEFGHIJKLMNOPQRSTUVWXYZ"

def inverse(a , b):
    for i in range( b ):
        if( (a * i ) % b == 1 ):
            return i
    return( -1)

def encrypt (a, b):
    reverse =""

    for i in alphabet:
        x = (ord(i)-ord('a'))
        m = ((x*a + b) % 26)
        reverse += chr( m + ord('a') )

    for i in capalphabet:
        x = (ord(i)-ord('A'))
        m = ((x*a + b) % 26)
        reverse += chr( m + ord('A') )

    command = "awk \' {   print $0 | \"sed y/"
    command += alphabet + capalphabet + "/"
    command += reverse + "/\"} \' "

    os.system( command )

def decrypt(a , b):
    a = inverse(a,26)

    reverse =""

    for i in alphabet:
        x = (ord(i)-ord('a'))
        m = (((x - b)*a) % 26)
        reverse += chr( m + ord('a') )

    for i in capalphabet:
        x = (ord(i)-ord('A'))
        m = (((x - b)*a) % 26)
        reverse += chr( m + ord('A') )


    command = "awk \' {   print $0 | \"sed y/"
    command += alphabet + capalphabet + "/"
    command += reverse + "/\"} \' "

    os.system( command )

def gcd(a,b):
    while b != 0:
        a, b = b, a%b
    return a

def validate( a, b):
    if( gcd(a,b) == 1):
        return True
    else:
        return False

def analysis( name ):
    f = open( name, "r" )
    freq = {}

    for i in f:
        for j in i.lower():
            if( j.isalpha() ):
                if( j in freq ):
                    freq[j] += 1
                else:
                    freq[j] = 1

    freq = [(t[1], t[0]) for t in freq.items()]
    freq.sort()
    freq =  freq[::-1]
    print( freq )
    e = ord(freq[0][1]) - ord('a') 
    t = ord(freq[1][1]) - ord ('a')

    alpha = ((e-t)*inverse(ord('e') - ord('t'),26)) % 26
    beta = ( e - ((ord('e')-ord('a'))*alpha)) %26

    alpha = str(alpha)
    beta = str(beta)

    print( "Best guess for a:" +alpha +" b:" + beta )


if( __name__=="__main__" ):
    if( sys.argv[1] == 'a' and len(sys.argv) == 3 ):
        analysis( sys.argv[2] )
        pass
    elif( len(sys.argv) != 4):
        print("Improper usage", file=sys.stderr)
        exit()
    else:
        a = int(sys.argv[2])
        b = int(sys.argv[3])

        if( not validate( a, b ) ):
            print("Invalid Choice of key", file=sys.stderr)
            print( "gcd(" + str(a) + "," + str(b) + ") is " + str(gcd(a,b)) + " not 1" ,file=sys.stderr)
            exit()

        if ( sys.argv[1] == 'd'):
            decrypt(a, b)
        elif ( sys.argv[1] == 'e'):
            encrypt(a, b)

