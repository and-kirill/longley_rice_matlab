/**
 * This is a wareppr function to calculate Longley-Rice
 * propagation model (point mode) in matlab.
 */
#include<iostream>
#include "longleyRice.h"
#include "mex.h"
void itmlrPoint (
        double elevation_profile_meters[], unsigned int profile_length, // Elevation profile at equidistant points, altitude in meters
        double profile_step_meters, // Distance between elevation profile neighbor points in meters
        double tht_m, double rht_m, // transmitter and receiver antenna height
        double eps_dielect, // Earth dielectric coefficient: http://cgiss.boisestate.edu/~billc/dielec.html
        double sgm_conductivity,
        double eno_ns_surfref,
        double frq_mhz,
        int radio_climate,
        int pol,
        double timepct,
        double locpct,
        double confpct,
        double &dbloss, // OUT: propagation loss in decibels
        double &propmode,
        double &deltaH,
        double &errnum
        )
{
    // Prepare elevation profile for longley rice internal profile format
    double elev [profile_length + 2];
    elev[0] = profile_length - 1;
    elev[1] = profile_step_meters;
    for (unsigned int i=0; i < profile_length; i++)
    {
        elev[i+2] = elevation_profile_meters[i];
    }
    // Call ITMLR implementation
    int propmode_ = 0;
    int errnum_;
    
    point_to_pointMDH (elev, tht_m, rht_m,
          eps_dielect, sgm_conductivity, eno_ns_surfref,
          frq_mhz, radio_climate, pol, timepct, locpct, confpct,
          dbloss, propmode_, deltaH, errnum_);
    
    // TODO: integer values
    propmode = double(propmode_);
    errnum = double(errnum_);
}

/// Check that input variable is a double value
void checkDouble(const mxArray* phs)
{
    if(!mxIsDouble(phs) || mxIsComplex(phs) || mxGetNumberOfElements(phs) != 1)
    {
        mexErrMsgIdAndTxt("MyToolbox:arrayProduct:notScalar", "Input profile step must be a scalar double.");
    }
}


void checkMatrixRow(const mxArray* phs)
{
    if( !mxIsDouble(phs) || mxIsComplex(phs))
    {
        mexErrMsgIdAndTxt("ITMLR:point:notDouble", "Input matrix must be type double.");
    }
    /* check that number of rows in second input argument is 1 */
    if(mxGetM(phs) != 1)
    {
        mexErrMsgIdAndTxt("ITMLR:point:notRowVector", "Input must be a row vector.");
    }
}

void mexFunction(int nlhs, mxArray *plhs[],
                 int nrhs, const mxArray *prhs[])
{
    // Inputs:
    double * elev_profile_m;
    unsigned int profile_length; // Elevation profile at equidistant points, altitude in meters
    double profile_step_m; // Distance between elevation profile neighbor points in meters
    double tht_m;
    double rht_m; // transmitter and receiver antenna height
    double eps_dielect; // Earth dielectric coefficient: http://cgiss.boisestate.edu/~billc/dielec.html
    double sgm_conductivity;
    double eno_ns_surfref;
    double frq_mhz;
    int radio_climate;
    int pol;
    double timepct;
    double locpct;
    double confpct;

    if (nrhs != 13)
    {
        mexErrMsgIdAndTxt("ITMLR:point:nrhs", "13 inputs are required.");
    }
    if (nlhs !=4 )
    {
        mexErrMsgIdAndTxt("ITMLR:point:nrhs", "4 outputs are required.");
    }
    // Check all intput arguments:
    checkMatrixRow(prhs[0]);
    for (unsigned int i = 1; i < 13; i ++)
    {
        checkDouble(prhs[i]);
    }

    // Bind imputs
    elev_profile_m =   mxGetPr(prhs[0]); // elevation profiles [altitudes in meters]
    profile_length =   mxGetN(prhs[0]);

    profile_step_m =   mxGetScalar(prhs[1]); // profile distance between neoghbor points [m]
    tht_m =            mxGetScalar(prhs[2]); // transmitter antenna height [m]
    rht_m =            mxGetScalar(prhs[3]); // receiver antenna height [m]

    eps_dielect =      mxGetScalar(prhs[4]); // Earth dielectric constant
    sgm_conductivity = mxGetScalar(prhs[5]); // Earth surface conductivity
    eno_ns_surfref =   mxGetScalar(prhs[6]);
    frq_mhz =          mxGetScalar(prhs[7]); // Signal fcarrier frequency [MHz]
    radio_climate =    mxGetScalar(prhs[8]); // Radio climate
    pol =              mxGetScalar(prhs[9]); // Signal polarization
    
    timepct =          mxGetScalar(prhs[10]);
    locpct =           mxGetScalar(prhs[11]);
    confpct =          mxGetScalar(prhs[12]);

    // Bind outputs
    // TODO: read double without creating array
    plhs[0] = mxCreateDoubleMatrix(1,1,mxREAL);
    double & dbloss = *mxGetPr(plhs[0]);
    // TODO: read integer value
    plhs[1] = mxCreateDoubleMatrix(1,1,mxREAL);
    double & propmode = *mxGetPr(plhs[1]);
    
    plhs[2] = mxCreateDoubleMatrix(1,1,mxREAL);
    double & deltaH = *mxGetPr(plhs[2]);

    plhs[3] = mxCreateDoubleMatrix(1,1,mxREAL);
    double & errnum = *mxGetPr(plhs[3]);

    // Perform calculus
    itmlrPoint (
        elev_profile_m, profile_length,
        profile_step_m,
        tht_m, rht_m,
        eps_dielect,
        sgm_conductivity,
        eno_ns_surfref,
        frq_mhz,
        radio_climate,
        pol,
        timepct,
        locpct,
        confpct,
        dbloss, // OUT: propagation loss in decibels
        propmode,
        deltaH,
        errnum
        );
}
