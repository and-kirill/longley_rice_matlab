/**
 * Run C++ ITM Longley-Rice implementation directly.
 */
#include "longley_rice.h"
#include <iostream>
#include <cstdio>

int main()
{
    // Generate some test profile
    double elev []= {5, 3000, 5, 5, 5, 5, 5, 5, 5, 5}; // [N, step, values]
    // Transmisison antenna height
    double tht_m = 6.0;
    // Receiver antenna height
    double rht_m = 1.5;

    // Carrier frequency
    double frq_mhz = 600;

    // Model constants:
    // Earth dielectric constant [epsilon]
    double eps_dielect = 15.0; // http://www.qsl.net/n9zia/conduct.html
    // Earth conductivity [S/m]
    double sgm_conductivity = 0.005; // http://www.qsl.net/n9zia/conduct.html
    // The surface refractivity of the atmosphere [N]
    double eno_ns_surfref = 310;
    // Radio climate: Continental Temperate
    int radio_climate = 5;
    // Signal polarization: vertical
    int pol = 0;

    double conf = 0.9;
    double rel = 0.9;


    // prepare output variables
    double deltaH;
    int errnum;
    char strmode [100];
    double dbloss;
    
    // test point mode
    std::cout << "Test POINT mode:" << std::endl;
    point_to_point(elev, tht_m, rht_m,
          eps_dielect, sgm_conductivity, eno_ns_surfref,
          frq_mhz, radio_climate, pol, conf, rel,
          dbloss, strmode, errnum);
    std::cout << "Loss value:" << dbloss << ", errno = " << errnum << ", propagation mode: " << strmode << std::endl;

    point_to_pointDH (elev, tht_m, rht_m,
          eps_dielect, sgm_conductivity, eno_ns_surfref,
          frq_mhz, radio_climate, pol, conf, rel,
          dbloss, deltaH, errnum);
    std::cout << "Loss value:" << dbloss << ", errno = " << errnum << ", propagation mode: " << strmode << std::endl;
    std::cout << "Estimated height difference: " << deltaH << " m." << std::endl;


    int propmode = 0;
    double timepct = 0.9;
    double locpct  = 0.9;
    double confpct = 0.9;

    point_to_pointMDH (elev, tht_m, rht_m,
          eps_dielect, sgm_conductivity, eno_ns_surfref,
          frq_mhz, radio_climate, pol, timepct, locpct, confpct,
          dbloss, propmode, deltaH, errnum);
    
    std::cout << "Loss value:" << dbloss << ", errno = " << errnum << ", propagation mode: " << propmode << std::endl;
    std::cout << "Estimated height difference: " << deltaH << " m." << std::endl;
    
    // Test area mode
    std::cout << "Test AREA mode:" << std::endl;
    double dist_km = 20;
    int TSiteCriteria = 0; // Random
    int RSiteCriteria = 0; // Random
    
    long ModVar = 0; // All three confidence zones are utilized
    double pctTime = 0.9;
    double pctLoc  = 0.9;
    double pctConf = 0.9;
    deltaH = 10.0; // Typical height difference

    area(ModVar, deltaH, tht_m, rht_m,
          dist_km, TSiteCriteria, RSiteCriteria, 
          eps_dielect, sgm_conductivity, eno_ns_surfref,
          frq_mhz, radio_climate, pol, pctTime, pctLoc,
          pctConf, dbloss, strmode, errnum);
    
    std::cout << "Loss value:" << dbloss << ", errno = " << errnum << ", propagation mode: " << strmode << std::endl;

    dbloss = ITMAreadBLoss(ModVar, deltaH, tht_m, rht_m,
          dist_km, TSiteCriteria, RSiteCriteria, 
          eps_dielect, sgm_conductivity, eno_ns_surfref,
          frq_mhz, radio_climate, pol, pctTime, pctLoc,
          pctConf);
    std::cout << "Loss value:" << dbloss << std::endl;

    return 0;
}
