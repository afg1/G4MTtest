#include "G4MTRunManager.hh"
#include "G4UImanager.hh"


#ifdef G4VIS_USE
#include "G4VisExecutive.hh"
#endif


#ifdef G4UI_USE
#include "G4UIExecutive.hh"
#endif

#include <cstdlib>
#include <ctime>
#include <sstream>
#include <string>
#include "G4VUserPhysicsList.hh"
#include "G4SystemOfUnits.hh"


#include "World.hh"
#include "Physics.hh"
#include "Initialization.hh"
#include "G4RegionStore.hh"

int main(int argc, char** argv)
{
    bool db(true);
    int rand1, rand2;
    int nthreads(4);
    std::srand(std::time(NULL));// Seed the random number generator
    rand1 = std::rand();
    rand2 = std::rand();
    std::string macname("testmac");
    std::stringstream setrand;
    std::string set_rand;
    std::string outloc;
    setrand << "/random/setSeed " << rand1 <<  " " << rand2;
    set_rand = setrand.str();
    if(argc > 1)
    {
        if((std::string)argv[1] == "h" || (std::string)argv[1] == "help")
        {
            G4cout << "Help for " << (std::string)argv[0] << G4endl;
            G4cout << "Argument 1:\tName of a macro file to run" << G4endl;
            G4cout << "Argument 2:\tPath to put output" << G4endl;
            G4cout << "Argument 3:\tNumber of threads to use (default 4)" << G4endl;
            return 0;
        }
        macname = (std::string)argv[1];
        outloc = (std::string)argv[2];
        if(argc == 4)
        {
            nthreads = atoi(argv[3]);
        }
    }
//    else
//    {
//        G4cerr << "Need to supply arguments or it all goes wrong!" << G4endl;
//        return -1;
//    }
    
    if(db){G4cout << "Debug enabled" << G4endl;}
// First thing to do is construct the run manager:
    G4MTRunManager* runManager = new G4MTRunManager;
    runManager->SetVerboseLevel(0);
    runManager->SetNumberOfThreads(nthreads);

// Now create the world and tell the run manager about it
    world* theWorld = new world(outloc);
    runManager->SetUserInitialization(theWorld);

// Now create physics and tell the run manager about it
    if(db){G4cout << "World done..." << G4endl;}
    G4VUserPhysicsList* phys = new Physics(db);
    runManager->SetUserInitialization(phys);
    
    
    if(db){G4cout << "Physics done..." << G4endl;}
    // Now create the generator and tell the run manager
    Initialization* init = new Initialization;
    runManager->SetUserInitialization(init);
    if(db) {G4cout << "Generator done..." << G4endl;}




// Initialize the run manager
    runManager->Initialize();
    if(db){G4cout << "Run manager initialized..." << G4endl;}
 
//    runManager->DumpRegion(); // Needed to use this to find out the region names
    // Now we hand over control to the UI manager, and set some verbosities

    G4UImanager* UI = G4UImanager::GetUIpointer();
    UI->ApplyCommand(set_rand);// Use the macro command to set the random number
    if(db)
    {
        UI->ApplyCommand("/run/verbose 2");
        UI->ApplyCommand("/event/verbose 2");
        UI->ApplyCommand("/tracking/verbose 2");
        
    }
    else
    {
        UI->ApplyCommand("/run/verbose 0");
        UI->ApplyCommand("/event/verbose 0");
        UI->ApplyCommand("/tracking/verbose 0");
        UI->ApplyCommand("/vis/verbose 0");
    }


    if(db){G4cout << "UI commands applied..." << G4endl;}


// Decide whether to use visualisation
    #ifdef G4VIS_USE
    G4VisManager* visMan = new G4VisExecutive;
    visMan->Initialise();
    #endif
    if(db){G4cout << "After first #ifdef block..." << G4endl;}
    


// Decide whether to use a UI
    #ifdef G4UI_USE
    G4UIExecutive* ui = new G4UIExecutive(argc,argv);
    #endif
    if(db){G4cout << "After second #ifdef block..." << G4endl;}

    
    

    UI->ApplyCommand("/control/execute runmacro.mac");
    runManager->DumpRegion(); // Needed to use this to find out the region names
    if(db){G4cout << "runmacro.mac called..." << G4endl;}
     
    
    if(argc > 1)
    {
        if(db){G4cout << "Applying custom macro..." << G4endl;}
        try
        {
            UI->ApplyCommand("/control/execute " + macname);
            if(db){G4cout << "Macro " << macname << " Applied..." << G4endl;}   //throw -3;
        }
        catch (...)
        {
            G4cout << "Macro not found...giving up" << G4endl;
        }

    }


   #ifdef G4UI_USE
    if(argc == 1)// This means we want to run in interactive mode
    {
        ui->SessionStart();
    }
    #endif
    
    
    
    //cleanup time...
    #ifdef G4VIS_USE
    G4cout << "Visualisation Manager deleting!!" << G4endl;
    delete visMan;
    #endif

    #ifdef G4UI_USE
    G4cout << "UI manager deleting!!" << G4endl;
    delete ui;
    #endif
    G4RegionStore* rs = G4RegionStore::GetInstance();
    G4cout << "Size of Region Store:\t" << rs->size() << G4endl;
    rs->clear();// should work, given the functionality of std::vector (edit: This clears up the last of the segfaults, but I have no idea why it has to be done like this!)
    rs->Clean();
    delete runManager;
    return 0;
}
