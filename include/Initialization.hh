#ifndef INITIALIZATION_H
#define INITIALIZATION_H 1

#include "G4VUserActionInitialization.hh"

#include "Generator.hh"

class Initialization : public G4VUserActionInitialization
{
    public:
        void Build() const;
        void BuildForMaster() const;
    
};

#endif
