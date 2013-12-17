#include "World.hh"
#include "SensitiveDetector.hh"
#include "Hit.hh"

#include "G4LogicalVolume.hh"
#include "G4Tubs.hh"
#include "G4Box.hh"
#include "G4ThreeVector.hh"
#include "G4PVPlacement.hh"
#include "G4AssemblyVolume.hh"
#include "globals.hh"
#include "G4NistManager.hh"
#include "G4Material.hh"
#include "G4Region.hh"
#include "G4RegionStore.hh"
#include "G4PVReplica.hh"
#include "G4PVDivision.hh"
#include "G4ProductionCuts.hh"
#include "G4MaterialCutsCouple.hh"
#include "G4SDManager.hh"
#include "G4SystemOfUnits.hh"
#include <string>

world::world(std::string out):worldLog(NULL), worldPhys(NULL), outloc(out)
{}

world::~world()
{
}


G4VPhysicalVolume* world::Construct()
{
    //Selection of materials
    G4NistManager* matMan = G4NistManager::Instance();
    G4Material* H2O = matMan->FindOrBuildMaterial("G4_WATER");
    G4Material* vac = matMan->FindOrBuildMaterial("G4_Galactic");

    // Construction of the water
    G4double x_dim = 25.*cm;
    G4double y_dim = 25.*cm;
    G4double z_dim = 25.*cm;
    G4double world_dim = 300.*cm;



    G4Box* theWorld = new G4Box("World", world_dim, world_dim, world_dim);
    worldLog = new G4LogicalVolume(theWorld,vac,"worldLog");

    G4Box* water = new G4Box("water", x_dim, y_dim, z_dim);
    waterLog = new G4LogicalVolume(water, H2O, "waterLog");

    G4RegionStore* rS = G4RegionStore::GetInstance();

    worldPhys = new G4PVPlacement(0, G4ThreeVector(),worldLog,"world1",0,false,0);
    waterPhys = new G4PVPlacement(0,G4ThreeVector(), waterLog, "Water", worldLog, false, 0);

    G4Region* reg = new G4Region("Interesting_region");

    G4ProductionCuts* prc = new G4ProductionCuts();
    prc->SetProductionCut(1*um, "gamma");
    prc->SetProductionCut(10*um, "e+");
    prc->SetProductionCut(10*um, "e-");
    prc->SetProductionCut(100*nm, "proton");

    G4MaterialCutsCouple* mcc = new G4MaterialCutsCouple(H2O, prc);
    

    waterLog->SetRegion(reg);
    reg->AddRootLogicalVolume(waterLog);
    reg->SetProductionCuts(prc);
    reg->RegisterMaterialCouplePair(H2O, mcc);
    rS->Register(reg);
    rS->UpdateMaterialList(worldPhys);

    return worldPhys;
}

void world::ConstructSDandField()
{
    std::string outloc1 = outloc + "_water";

    G4SDManager* sdman = G4SDManager::GetSDMpointer();
    G4String name = "_Water";
    
    SensitiveDetector* SD = new SensitiveDetector(name, outloc1, "SD" + name, 2);
    sdman->AddNewDetector(SD);
    SetSensitiveDetector("waterLog", SD);// Now we set the sensitive detector by referring to the logical volume name - therefore must be unique
}
    