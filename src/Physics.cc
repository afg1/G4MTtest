#include "Physics.hh"

#include<iostream>
#include "G4EmDNAPhysics.hh"
#include "G4EmStandardPhysics.hh"
#include "G4EmStandardPhysics_option3.hh"
#include "G4EmProcessOptions.hh"
#include "G4EmPenelopePhysics.hh"
#include "G4RegionStore.hh"
//#include "G4HadronInelasticQLHEP.hh"
//#include "HadronPhysicsQGSP_BIC.hh"
#include "G4ProcessManager.hh"
#include "G4SystemOfUnits.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
//
Physics::Physics(bool dbi): G4VUserPhysicsList()
{
    db = dbi;
    defaultCutValue = 0.01*mm;//1*nanometer;// Changed this in the hope of speeding up the simulation a bit
    cutForGamma = defaultCutValue;
    cutForElectron = defaultCutValue;
    cutForPositron = defaultCutValue;
    cutForProton = defaultCutValue;//1e-6*mm;// Chosen to roughly correspond to the NIST data shortest range

// these cuts are ignored since all Geant4-DNA processes are discrete
    G4int ver(0);
    if(db){ver = 1;}

    G4cout << db << G4endl;
    emPhysicsList = new G4EmStandardPhysics(ver);//EmPhys_Woodcock(ver);
    //hadrPhysicsList = new HadronPhysicsQGSP_BIC("hadronphys");//, ver, false, false, true, false);
}
//
////....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
//
Physics::~Physics()
{
    delete emPhysicsList;
    //delete hadrPhysicsList;

    emPhysicsList = NULL;
    hadrPhysicsList = NULL;
}
//
////....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
//
void Physics::ConstructParticle()
{
    emPhysicsList->ConstructParticle();
    //hadrPhysicsList->ConstructParticle();

}
//
////....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
//
void Physics::ConstructProcess()
{
    AddTransportation();
    emPhysicsList->ConstructProcess();
    //hadrPhysicsList->ConstructProcess();

}
//
////....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
//
void Physics::SetCuts()
{
    SetCutsWithDefault();
    G4Region* region;
    G4ProductionCuts* cuts;
    G4String regName;
    regName = "Interesting_region";
    SetCutsForRegion(defaultCutValue, "Interesting_region");
}

void Physics::SetCutsForRegion(G4double aCut, const G4String& rname)
{
    SetCutValue(aCut, "gamma", rname);
    SetCutValue(aCut, "e-", rname);
    SetCutValue(aCut, "e+", rname);
    SetCutValue(aCut, "proton", rname);
}
//

