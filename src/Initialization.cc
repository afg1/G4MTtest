#include "Initialization.hh"
#include "Generator.hh"

void Initialization::Build() const
{
    SetUserAction(new Generator);
    
}

void Initialization::BuildForMaster() const
{


}