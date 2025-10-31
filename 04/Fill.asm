// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/4/Fill.asm

// Runs an infinite loop that listens to the keyboard input.
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel. When no key is pressed,
// the screen should be cleared.

//// Replace this comment with your code.

(LOOP)
    @KBD
    D=M              // checking keyboard
    @WHITE
    D;JEQ            // if no key, white
    @BLACK
    0;JMP            // else black

(WHITE)
    @color
    M=0              // white = 0
    @DRAW
    0;JMP

(BLACK)
    @color
    M=-1             // black = -1

(DRAW)
    @SCREEN
    D=A
    @addr
    M=D
    @8192
    D=A
    @count
    M=D

(FILL)
    @color
    D=M
    @addr
    A=M
    M=D              // draw color
    @addr
    M=M+1            // move to next
    @count
    M=M-1
    D=M
    @LOOP
    D;JEQ            // recheck keyboard
    @FILL
    0;JMP
