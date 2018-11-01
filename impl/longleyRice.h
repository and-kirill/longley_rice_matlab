#include<complex>

struct tcomplex
 { double tcreal;
   double tcimag;
 };

struct prop_type
{ double aref;
  double dist;
  double hg[2];
  double wn;
  double dh;
  double ens;
  double gme;
  double zgndreal;
  double zgndimag;
  double he[2];
  double dl[2];
  double the[2];
  int kwx;
  int mdp;
};

struct propv_type
{ double sgc;
  int lvar;
  int mdvar;
  int klim;
};

struct propa_type
{ double dlsa;
  double dx;
  double ael;
  double ak1;
  double ak2;
  double aed;
  double emd;
  double aes;
  double ems;
  double dls[2];
  double dla;
  double tha;
};

/** 
 * \{
 * \name Stuff functions
 */
int mymin(const int &i, const int &j);

int mymax(const int &i, const int &j);

double mymin(const double &a, const double &b);

double mymax(const double &a, const double &b);

double FORTRAN_DIM(const double &x, const double &y);
/**
 * Quick Error Function calculus
 */
double qerfi( double q );

double deg2rad(double d);

/**
 * Frensel integral computation, see section 4.1.1 of ITML manual
 */
double aknfe(const double &v2);

/**
 * \}
 */
/**
 * Longley-Rice internals
 */


double fht(const double& x, const double& pk);

double h0f(double r, double et);

double ahd(double td);

double  ascat( double d, prop_type &prop, propa_type &propa);

double abq_alos (std::complex<double> r);

double  alos( double d, prop_type &prop, propa_type &propa);

void  qlra(int kst[], int klimx, int mdvarx,
           prop_type &prop, propv_type &propv);

void lrprop (double d, prop_type &prop, propa_type &propa);  // PaulM_lrprop

double curve (double const &c1, double const &c2, double const &x1,
              double const &x2, double const &x3, double const &de);

double avar(double zzt, double zzl, double zzc,
            prop_type &prop, propv_type &propv);

void z1sq1 (double z[], const double &x1, const double &x2,
            double& z0, double& zn);

double qerf(const double &z);

void qlrpfl(double pfl[], int klimx, int mdvarx,
            prop_type &prop, propa_type &propa, propv_type &propv );

/**
 * pol: 0-Horizontal, 1-Vertical
 * radio_climate: 1-Equatorial, 2-Continental Subtropical, 3-Maritime Tropical,
 *                4-Desert, 5-Continental Temperate, 6-Maritime Temperate, Over Land,
 *                7-Maritime Temperate, Over Sea
 * conf, rel: .01 to .99
 * elev[]: [num points - 1], [delta dist(meters)], [height(meters) point 1], ..., [height(meters) point n]
 * errnum: 0- No Error.
 *         1- Warning: Some parameters are nearly out of range.
 *                     Results should be used with caution.
 *         2- Note: Default parameters have been substituted for impossible ones.
 *         3- Warning: A combination of parameters is out of range.
 *                     Results are probably invalid.
 *            Other-  Warning: Some parameters are out of range.
 *                             Results are probably invalid.
 *
 */
void point_to_point(double elev[], double tht_m, double rht_m,
          double eps_dielect, double sgm_conductivity, double eno_ns_surfref,
          double frq_mhz, int radio_climate, int pol, double conf, double rel,
          double &dbloss, char *strmode, int &errnum);

/**
 * pol: 0-Horizontal, 1-Vertical
 * radio_climate: 1-Equatorial, 2-Continental Subtropical, 3-Maritime Tropical,
 *                4-Desert, 5-Continental Temperate, 6-Maritime Temperate, Over Land,
 *                7-Maritime Temperate, Over Sea
 * timepct, locpct, confpct: .01 to .99
 * elev[]: [num points - 1], [delta dist(meters)], [height(meters) point 1], ..., [height(meters) point n]
 * propmode:  Value   Mode
 *               -1     mode is undefined
 *                0     Line of Sight
 *                5     Single Horizon, Diffraction
 *                6     Single Horizon, Troposcatter
 *                9     Double Horizon, Diffraction
 *               10     Double Horizon, Troposcatter
 * errnum: 0- No Error.
 *         1- Warning: Some parameters are nearly out of range.
 *                     Results should be used with caution.
 *         2- Note: Default parameters have been substituted for impossible ones.
 *         3- Warning: A combination of parameters is out of range.
 *                     Results are probably invalid.
 *         Other-  Warning: Some parameters are out of range.
 *                         Results are probably invalid.
 */
void point_to_pointMDH (double elev[], double tht_m, double rht_m,
          double eps_dielect, double sgm_conductivity, double eno_ns_surfref,
          double frq_mhz, int radio_climate, int pol, double timepct, double locpct, double confpct,
          double &dbloss, int &propmode, double &deltaH, int &errnum);




	// pol: 0-Horizontal, 1-Vertical
	// radio_climate: 1-Equatorial, 2-Continental Subtropical, 3-Maritime Tropical,
	//                4-Desert, 5-Continental Temperate, 6-Maritime Temperate, Over Land,
	//                7-Maritime Temperate, Over Sea
	// conf, rel: .01 to .99
	// elev[]: [num points - 1], [delta dist(meters)], [height(meters) point 1], ..., [height(meters) point n]
	// errnum: 0- No Error.
	//         1- Warning: Some parameters are nearly out of range.
	//                     Results should be used with caution.
	//         2- Note: Default parameters have been substituted for impossible ones.
	//         3- Warning: A combination of parameters is out of range.
	//                     Results are probably invalid.
	//         Other-  Warning: Some parameters are out of range.
	//                          Results are probably invalid.

void point_to_pointDH (double elev[], double tht_m, double rht_m,
          double eps_dielect, double sgm_conductivity, double eno_ns_surfref,
          double frq_mhz, int radio_climate, int pol, double conf, double rel,
          double &dbloss, double &deltaH, int &errnum);

//********************************************************
//* Area Mode Calculations                               *
//********************************************************

	// pol: 0-Horizontal, 1-Vertical
	// TSiteCriteria, RSiteCriteria:
	//		   0 - random, 1 - careful, 2 - very careful
	// radio_climate: 1-Equatorial, 2-Continental Subtropical, 3-Maritime Tropical,
	//                4-Desert, 5-Continental Temperate, 6-Maritime Temperate, Over Land,
	//                7-Maritime Temperate, Over Sea
	// ModVar: 0 - Single: pctConf is "Time/Situation/Location", pctTime, pctLoc not used
    //         1 - Individual: pctTime is "Situation/Location", pctConf is "Confidence", pctLoc not used
    //         2 - Mobile: pctTime is "Time/Locations (Reliability)", pctConf is "Confidence", pctLoc not used
    //         3 - Broadcast: pctTime is "Time", pctLoc is "Location", pctConf is "Confidence"
	// pctTime, pctLoc, pctConf: .01 to .99
	// errnum: 0- No Error.
	//         1- Warning: Some parameters are nearly out of range.
	//                     Results should be used with caution.
	//         2- Note: Default parameters have been substituted for impossible ones.
	//         3- Warning: A combination of parameters is out of range.
	//                     Results are probably invalid.
	//         Other-  Warning: Some parameters are out of range.
	//                          Results are probably invalid.
	// NOTE: strmode is not used at this time.


void area(long ModVar, double deltaH, double tht_m, double rht_m,
          double dist_km, int TSiteCriteria, int RSiteCriteria, 
          double eps_dielect, double sgm_conductivity, double eno_ns_surfref,
          double frq_mhz, int radio_climate, int pol, double pctTime, double pctLoc,
          double pctConf, double &dbloss, char *strmode, int &errnum);

double ITMAreadBLoss(long ModVar, double deltaH, double tht_m, double rht_m,
          double dist_km, int TSiteCriteria, int RSiteCriteria, 
          double eps_dielect, double sgm_conductivity, double eno_ns_surfref,
          double frq_mhz, int radio_climate, int pol, double pctTime, double pctLoc,
          double pctConf);
