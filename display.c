

#include <stdio.h>

#include "display.h"

///
/// Name:    clear
///
void clear() {
    printf( "\033[2J" );
    fflush( stdout );
}

///
/// Name:    put
///
void put( char character ) {
    putchar( character );
    fflush( stdout );
}

///
/// Name:    set_cur_postition
///
void set_cur_pos( int rCursor, int cCursor) {
    printf( "\033[%d;%dH", rCursor, cCursor );
}

