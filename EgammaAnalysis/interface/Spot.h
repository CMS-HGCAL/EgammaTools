#ifndef SPOT_H
#define SPOT_H
#include "DataFormats/DetId/interface/DetId.h"

#include <vector>

class Spot{
    public:
        Spot(DetId detid, double energy, const std::vector<double>& row, unsigned int layer, double fraction, double mip):
            detId_(detid),energy_(energy),row_(row),layer_(layer),fraction_(fraction),mip_(mip),multiplicity_(int(energy/mip)){;};
        ~Spot(){;};
        inline DetId detId() const {return detId_;}
        inline double energy() const {return energy_;}
        inline const double * row() const {return &row_[0];}
        inline double fraction() const {return fraction_;}
        inline double mip() const {return mip_;}
        inline int multiplicity() const {return multiplicity_;}
        inline unsigned int layer() const { return layer_;}

    private:
        DetId detId_;
        double energy_;
        std::vector<double> row_;
        unsigned int layer_;
        double fraction_;
        double mip_;
        int multiplicity_;
};

#endif
