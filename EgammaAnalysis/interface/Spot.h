#ifndef SPOT_H
#define SPOT_H
#include "DataFormats/DetId/interface/DetId.h"


class Spot{
    public:
        Spot(DetId detid, double energy, const Double_t * row, double fraction, double mip):
            detId_(detid),energy_(energy),row_(row),fraction_(fraction),mip_(mip),multiplcity_(int(energy/mip));
        ~Spot();
        inline DetId detId() const {return detId_;}
        inline double energy() const {return energy_;}
        inline Double_t row() const {return row_;}
        inline double fraction() const {return fraction_;}
        inline double mip() const {return mip_;}

    private:
        DetId detId_;
        double energy_;
        Double_t * row_;
        double fraction_;
        double mip_;
        int multiplicity_;
};

#endif
