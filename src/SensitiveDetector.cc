#include "SensitiveDetector.hh"
#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"
#include "Hit.hh"
#include "G4ThreeVector.hh"
#include "G4SystemOfUnits.hh"

#include <fstream>
#include <string>
#include <sstream>
#include "G4SDManager.hh"
#include <iomanip>


SensitiveDetector::SensitiveDetector(G4String name, std::string out, G4String HCname, int slf) : G4VSensitiveDetector(name), outloc(out), selflag(slf)
{
    collectionName.insert(HCname);
    DoseHist = new Histogram2D(1000, 1000, -25*cm, 25*cm, -25*cm, 25*cm);
}

SensitiveDetector::~SensitiveDetector()
{
    WriteFiles();
}

void SensitiveDetector::Initialize(G4HCofThisEvent* HCE)
{
    collection = new G4HitCollection(SensitiveDetectorName, collectionName[0]);
    static G4int HCID = -1;
    if(HCID < 0)
    {
        HCID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
    }
    HCE->AddHitsCollection(HCID, collection);
}

G4bool SensitiveDetector::ProcessHits(G4Step* aStep, G4TouchableHistory*)
{
    G4double edep = aStep->GetTotalEnergyDeposit();
    
    if(selflag == 1)
    {
        if(aStep->GetTrack()->GetParentID() == 0)
        {
            G4ThreeVector pos =  aStep->GetTrack()->GetPosition();
            G4double E = aStep->GetTrack()->GetKineticEnergy();
            WaterHit* newHit = new WaterHit();
            newHit->SetPosition(pos);
            newHit->SetEdep(edep);
            newHit->SetEne(E);
            collection->insert(newHit);
        }
    }
    else if(selflag ==2)// I only care about the protons, so discard all other dose info
    {
        if(aStep->GetTrack()->GetParentID() == 0 && aStep->GetTrack()->GetDefinition()->GetParticleName() == "proton")
        {
            G4ThreeVector pos =  aStep->GetTrack()->GetPosition();
            G4double E = aStep->GetTrack()->GetKineticEnergy();
            WaterHit* newHit = new WaterHit();
            newHit->SetPosition(pos);
            newHit->SetEdep(edep);
            newHit->SetEne(E);
            collection->insert(newHit);
        }
    }
    return true;
}

void SensitiveDetector::EndOfEvent(G4HCofThisEvent* CHC)
{
    int id(-1);
    id = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
    G4HitsCollection* HC = 0;
    HC = (G4HitsCollection*)CHC->GetHC(id);
    int n_hits(0);
    n_hits = HC->GetSize();
    
    
// Now we store the data in some vectors, we will write out at the end of the run, rather than at the end of the proton track


    if(selflag == 1)
    {
        for(int k=0; k<n_hits; k++)
        {
            WaterHit* hit = (WaterHit*)HC->GetHit(k);
            if(hit->GetEne() == 0.)
            {
                PosRes* temp = new PosRes;
                temp->x = hit->GetPosition()[0];
                temp->y = hit->GetPosition()[1];
                temp->z = hit->GetPosition()[2];
                positionResults.push_back(*temp);
                delete temp;
            }
        }
    }
    else if(selflag == 2)
    {
        for(int k=0; k<n_hits; k++)
        {
            WaterHit* hit = (WaterHit*)HC->GetHit(k);
            DoseHist->Fill(hit->GetPosition()[0], hit->GetPosition()[1], hit->GetEdep());
        }
    }
}

void SensitiveDetector::WriteFiles()
{
    std::stringstream threadout;
    std::string threadout_str;
    threadout << outloc << G4Threading::G4GetThreadId();
    threadout_str = threadout.str();
//    std::ofstream output;
    
//    if(fexists(threadout_str.c_str()))
//    {
//        output.open(threadout_str.c_str(), std::ios::app|std::ios::binary);
//    }
//    else
//    {
//        output.open(threadout_str.c_str(), std::ios::binary);
////        output.write((char*)&selflag, sizeof(int));// This line writes a 4 byte header to the file (if it is being created) which signifies the type of data collected
//    }
//    if(output.is_open())
//    {
        if(selflag == 1 && positionResults.size() > 0)
        {
            double outtemp[3];
//            for(size_t i=0; i<positionResults.size(); ++i)
//            {
//                outtemp[0] = positionResults.at(i).x;
//                outtemp[1] = positionResults.at(i).y;
//                outtemp[2] = positionResults.at(i).z;
//                output.write((char*)&outtemp, sizeof(outtemp));
//            }
        }
        else if(selflag == 2)
        {
            DoseHist->Write(threadout_str);
        }
//    }
}
                


bool SensitiveDetector::fexists(const char* fname)// Handy function I wrote to check for the existence of the output file
{
    std::ifstream ifile(fname);
    return ifile;
}
