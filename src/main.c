#include <stdbool.h>
#include <time.h>
#include <stdio.h>

#include "run.h"
#include "game.h"
#include "render.h"


volatile long speed = 0;
void speeincr(){
    speed++;
}
END_OF_FUNCTION( speeincr );
LOCK_VARIABLE( speed );
LOCK_FUNCTION( speeincr );


int main()
{
    run( &speed, speeincr );
    return 0;
}
END_OF_MAIN();
