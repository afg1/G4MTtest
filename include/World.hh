#ifndef WORLD_H
#define WORLD_H 1

#include "G4VUserDetectorConstruction.hh"
#include "G4Region.hh"
#include "G4RegionStore.hh"
#include "G4UniformMagField.hh"
#include "G4FieldManager.hh"
#include "G4TransportationManager.hh"
#include <string>

class G4LogicalVolume;
class G4PhysicalVolume;

class world : public G4VUserDetectorConstruction
{
    public:
        world(std::string out);
        ~world();

        G4VPhysicalVolume* Construct();
        void ConstructSDandField();

    private:
        G4LogicalVolume* worldLog;
        G4LogicalVolume* waterLog;
    
    
        G4VPhysicalVolume* worldPhys;
        G4VPhysicalVolume* waterPhys;
    
    
        std::string outloc;
};
#endif
