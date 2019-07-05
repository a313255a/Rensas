-------- PROJECT GENERATOR --------
PROJECT NAME :	testineachday
PROJECT DIRECTORY :	C:\WorkSpace\testineachday\testineachday
CPU SERIES :	RX200
CPU TYPE :	RX210
TOOLCHAIN NAME :	Renesas RX Standard Toolchain
TOOLCHAIN VERSION :	1.2.1.0
GENERATION FILES :
    C:\WorkSpace\testineachday\testineachday\dbsct.c
        Setting of B,R Section
    C:\WorkSpace\testineachday\testineachday\typedefine.h
        Aliases of Integer Type
    C:\WorkSpace\testineachday\testineachday\sbrk.c
        Program of sbrk
    C:\WorkSpace\testineachday\testineachday\iodefine.h
        Definition of I/O Register
    C:\WorkSpace\testineachday\testineachday\intprg.c
        Interrupt Program
    C:\WorkSpace\testineachday\testineachday\vecttbl.c
        Initialize of Vector Table
    C:\WorkSpace\testineachday\testineachday\vect.h
        Definition of Vector
    C:\WorkSpace\testineachday\testineachday\resetprg.c
        Reset Program
    C:\WorkSpace\testineachday\testineachday\testineachday.c
        Main Program
    C:\WorkSpace\testineachday\testineachday\sbrk.h
        Header file of sbrk file
    C:\WorkSpace\testineachday\testineachday\stacksct.h
        Setting of Stack area
START ADDRESS OF SECTION :
 H'1000	B_1,R_1,B_2,R_2,B,R,SU,SI
 H'FFFF8000	PResetPRG
 H'FFFF8100	C_1,C_2,C,C$*,D_1,D_2,D,P,PIntPRG,W*,L
 H'FFFFFFD0	FIXEDVECT

* When the user program is executed,
* the interrupt mask has been masked.
* 
* Program start 0xFFFF8000.
* RAM start 0x1000.

SELECT TARGET :
    RX E1/E20 SYSTEM
DATE & TIME : 2015/1/29 ¤U¤È 03:06:34
