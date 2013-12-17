/*
This class implements the sensitive detector, which also handles file output
*/
#ifndef SENSITIVE_DETECTOR_H
#define SENSITIVE_DETECTOR_H

#include "G4VSensitiveDetector.hh"
#include "Hit.hh"
#include <string>
#include <vector>
#include "Histogramming.hh"

class G4Step;

struct PosRes
{
    double x;
    double y;
    double z;
};

struct DoseRes
{
    double x;
    double y;
    double z;
    double dE;
    double E;
};


class SensitiveDetector : public G4VSensitiveDetector
{
    public:
        SensitiveDetector(G4String, std::string, G4String HCname, int);
        ~SensitiveDetector();

        void Initialize(G4HCofThisEvent*);
        G4bool ProcessHits(G4Step*, G4TouchableHistory*);
        void EndOfEvent(G4HCofThisEvent*);

    private:
        void WriteFiles();
        G4HitCollection* collection;
        std::string outloc;
        int selflag;
        bool fexists(const char* fname);
        std::vector<PosRes> positionResults;
        std::vector<DoseRes> doseResults;
        Histogram2D* DoseHist;


};

#endif
