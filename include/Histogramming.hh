#ifndef HISTOGRAMMING_H
#define HISTOGRAMMING_H 1

#include <vector>
#include <string>

class Histogram2D
{
    public:
        Histogram2D(int binsx, int binsy, double minx, double maxx, double miny, double maxy);
        ~Histogram2D();
        void Fill(double xval, double yval, double weight);
        void Write(std::string filename);
    
    private:
        std::vector< std::vector<double> >* HistData;
        double spacingX;
        double spacingY;
        double maxX;
        double minX;
        double maxY;
        double minY;
        double centreX;
        double centreY;
    
        int nbinsX;
        int nbinsY;
        int centreBinX;
        int centreBinY;
    
    
};

#endif
