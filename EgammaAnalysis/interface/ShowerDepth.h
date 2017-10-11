#ifndef SHOWERDEPTH_H
#define SHOWERDEPTH_H

// Code copied from C. Charlot's

class ShowerDepth {
public:
    ShowerDepth();
    ~ShowerDepth() {;}
    float getClusterLengthCompatibility(float length, float emEnergy) const;

private:
    // longitudinal parametrisation
    double criticalEnergy_;
    double radiationLength_;
    double meant0_;
    double meant1_;
    double meanalpha0_;
    double meanalpha1_;
    double sigmalnt0_;
    double sigmalnt1_;
    double sigmalnalpha0_;
    double sigmalnalpha1_;
    double corrlnalphalnt0_;
    double corrlnalphalnt1_;
};

#endif
