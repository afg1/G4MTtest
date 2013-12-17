#include "Histogramming.hh"
#include "G4UImanager.hh"

#include <fstream>


Histogram2D::Histogram2D(int binsx, int binsy, double minx, double maxx, double miny, double maxy)
{
    std::vector<double> temp(binsy, 0.0);// Initialize a vector of length binsy, all of which is zero
    HistData = new std::vector< std::vector<double> >(binsx, temp);// Should initialize a vector of vectors made from temp
    spacingX = (maxx - minx)/binsx;
    spacingY = (maxy - miny)/binsy;
    centreX = (maxx - minx)/2.0;
    centreY = (maxy - miny)/2.0;
    nbinsX = binsx;
    nbinsY = binsy;
    centreBinX = nbinsX/2;
    centreBinY = nbinsY/2;
    maxX = maxx;
    maxY = maxy;
    minX = minx;
    minY = miny;
}

Histogram2D::~Histogram2D()
{
    delete HistData;
}

void Histogram2D::Fill(double xval, double yval, double weight)
{
    int bx(0), by(0);
    bx = int((xval)/spacingX) + centreBinX;
    by = int((yval)/spacingY) + centreBinY;
 
//    G4cerr << bx << "\t" << by << G4endl;
//    G4cerr << centreBinX << "\t" << centreBinY << G4endl;
    if(bx < nbinsX && bx > 0 && by < nbinsY && by > 0)
    {
        HistData->at(bx).at(by) += weight;
    }
    else
    {
        return;
    }
    
}


void Histogram2D::Write(std::string filename)
{
    std::ofstream output;
    output.open(filename.c_str());
    if(output.is_open())
    {
        for(size_t i=0; i < nbinsX; ++i)
        {
            for(size_t j=0; j < nbinsY; ++j)
            {
                output << HistData->at(j).at(i) << " ";
            }
            output << std::endl;
        }
    }
    else
    {
        G4cerr << "File not found!" << G4endl;
    }
    
}