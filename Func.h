#ifndef FUNC_H
#define FUNC_H

//declare functions which are used for the fits
double Background(double* x, double* par);
double custGaus(double *x, double *par);
double Dfit(double* x, double* par);
double D0fit(double* x, double* par);
double Granet(double* x, double* par);

//declare reference values of masses
const double Pimass = 0.13957;
const double pdgD0mass = 1.86483;
const double pdgDstmass = 2.01026;
const double pdgDeltam = 0.145426;



double custGaus(double *x, double *par) {
    
    double xcur = x[0];
    double mu = par[0]; // free param signal position
    double sigma = par[1]; // free param: width
    double N = par[2]; // free param: constant
    double t = std::abs((xcur-mu)/sigma);
    double expot = 1 + 1 / (1 + 0.5 * t);

    return ( N * exp(-0.5 * TMath::Power(t, expot)) );
    
}

double Background(double* x, double* par) {

    return par[0]*x[0]*x[0]+par[1]*x[0]+par[2];
}

double Granet(double* x, double* par) {
    
    double xcur = fabs(x[0]-Pimass);
    double A = par[0];
    double B = par[1];
    double C = par[2];
    return (A * TMath::Power(xcur,B) * exp ((C*xcur)) ) ;
}

double relGranet(double* x, double* par) {
    
    double xcur = fabs(x[0]-Pimass);
    double A = par[0];
    double B = par[1];
    double C = par[2];
    double D = par[3];
    return D * (A * TMath::Power(xcur,B) * exp ((C*xcur)) ) ;
}

double D0fit(double* x, double* par){
    return (custGaus(x,par) + Background(x,&par[3]));
}

double Dfit(double* x, double* par) {
    return ( custGaus(x,par)+ Granet(x,&par[3]) );
}

#endif
