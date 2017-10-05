#ifndef LONGDEPS_H
#define LONGDEPS_H
#include <vector>

class LongDeps{
    public:
        LongDeps(float radius, const std::vector<float>& energyPerLayer, float energyEE,float energyFH,float energyBH):
                energyPerLayer_(energyPerLayer),radius_(radius),energyEE_(energyEE),energyFH_(energyFH),
                energyBH_(energyBH){;}
        ~LongDeps(){;}
        // to check the radius used
        inline float radius() const {return radius_;};
        inline float energyEE() const {return energyEE_;}
        inline float energyFH() const {return energyFH_;}
        inline float energyBH() const {return energyBH_;}
        inline const std::vector<float>& energyPerLayer() const {return energyPerLayer_;}

    private:
        std::vector<float> energyPerLayer_;
        float radius_;
        float energyEE_;
        float energyFH_;
        float energyBH_;
    };
#endif
