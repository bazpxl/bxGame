
#include "BxGame/BxGame.h"

extern "C"
int main( int argc, char * argv [] )
try
{
    std::ios_base::sync_with_stdio( false );
    BxGame game;
    return game.Run();
}
catch( ... )
{
    print( "Non-SDL Exception has occurred!\n" );

    // put a breakpoint in this line, to prevent the shell from closing
    return 66;
}