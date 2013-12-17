#ifndef GENERATOR_MESSENGER_H
#define GENERATOR_MESSENGER_H 1

#include "globals.hh"
#include "G4UImessenger.hh"

class Generator;
class G4UIdirectory;
//class G4UIcmdWithoutParameter;
//class G4UIcmdWithAnInteger;
class G4UIcmdWithADoubleAndUnit;
//class G4UIcmdWith3VectorAndUnit;

class GeometryMessenger: public G4UImessenger
{
    public:
        GeometryMessenger(Generator* );
        ~GeometryMessenger();
    
        void SetNewValue(G4UIcommand*, G4String);
    
    private:
        Generator* genPtr;
    
        G4UIdirectory*  GenMessDir;
    
        G4UIcmdWithADoubleAndUnit* setEnergy;
    
};

#endif
