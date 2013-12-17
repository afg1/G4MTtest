#include "GeneratorMessenger.hh"
#include "Generator.hh"

#include "G4UIdirectory.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"

GeometryMessenger::GeometryMessenger(Generator* theGen): genPtr(theGen)
{
    GenMessDir = new G4UIdirectory("/generatorMessenger/");
    GenMessDir->SetGuidance("Messenger for my generator. Replaces the /gps/ directory");
    
    setEnergy = new G4UIcmdWithADoubleAndUnit("/generatorMessenger/setEnergy", this);
    setEnergy->SetGuidance("Set the energy of the beam, don't forget units!");
    
}

GeometryMessenger::~GeometryMessenger()
{
    delete setEnergy;
    delete GenMessDir;
}

void GeometryMessenger::SetNewValue(G4UIcommand* cmd, G4String newValue)
{
//    if(cmd == setEnergy)
//    {
//        genPtr->SetEnergy(setEnergy->GetNewDoubleValue(newValue));
//    }
}
