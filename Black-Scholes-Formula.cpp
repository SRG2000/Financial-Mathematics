#include<iostream>
#include<cmath>
using namespace std;
// The Standard Normal distribution probability distribution function
double norm_pdf(const double& x){
    return (1.0/(pow(2*M_PI, 0.5)))*exp(-0.5*x*x);
}
//The Standard Normal distribution cumulative distribution function
double norm_cdf(const double& x){
    double k = 1.0/(1.0 + 0.2316419*x);
    double k_sum = k*(0.319381530 + k*(-0.356563782 + k*(1.781477937 + k*(-1.821255978 + 1.330274429*k))));

    if (x >= 0.0) {
        return (1.0 - (1.0/(pow(2*M_PI,0.5)))*exp(-0.5*x*x) * k_sum);
    } 
    else {
        return 1.0 - norm_cdf(-x);
    }
}    
//Up and down movements; d_1 and d_2 respectively
double d_j(const int& j, const double& Spot, const double& Strike, const double& Riskfreerate, const double& Volatility, const double& Maturity) {
    return (log(Spot/Strike) + (Riskfreerate + (pow(-1,j-1))*0.5*Volatility*Volatility)*Maturity)/(Volatility*(pow(Maturity,0.5)));
}
//Call option price
double blackScholesCallPrice(const double&  Strike, const double& Maturity, const double& Spot, const double& Volatility, const double& Riskfreerate ){
    return Spot * norm_cdf(d_j(1, Spot, Strike, Riskfreerate, Volatility, Maturity))-Strike*exp(-Riskfreerate*Maturity) * norm_cdf(d_j(2, Spot, Strike, Riskfreerate, Volatility, Maturity));
}
// Call option delta
double CallDelta(const double&  Strike, const double& Maturity, const double& Spot, const double& Volatility, const double& Riskfreerate ){
    return norm_cdf(d_j(1, Spot, Strike, Riskfreerate, Volatility, Maturity));
}
//Put option price
double blackScholesPutPrice(const double&  Strike, const double& Maturity, const double& Spot, const double& Volatility, const double& Riskfreerate){
    return Strike*exp(-Riskfreerate*Maturity) * norm_cdf(-d_j(2, Spot, Strike, Riskfreerate, Volatility, Maturity))-Spot * norm_cdf(-d_j(1, Spot, Strike, Riskfreerate, Volatility, Maturity));
}
// Put option delta
double PutDelta(const double&  Strike, const double& Maturity, const double& Spot, const double& Volatility, const double& Riskfreerate){
    return norm_cdf(d_j(1, Spot, Strike, Riskfreerate, Volatility, Maturity))-1;
}
int main(){
    double Strike;
    double Maturity;
    double Spot;
    double Volatility;
    double Riskfreerate;
    cout << "Enter the Strike price of the underlying stock: ";
    cin>> Strike;
    cout << "Enter the time to Maturity of the call option:  ";
    cin >> Maturity;
    cout << "Enter the Spot price of the underlying stock: ";
    cin >> Spot;
    cout << " Enter the Volatility of the stock: ";
    cin >> Volatility;
    cout << "Enter the Risk-free rate:  ";
    cin >> Riskfreerate;
    double call = blackScholesCallPrice( Strike, Maturity, Spot, Volatility,  Riskfreerate );
    cout << "The call price of the option is "<<call<<" pounds. ";
    double put = blackScholesPutPrice(Strike, Maturity, Spot, Volatility,  Riskfreerate);
    cout << "The put option price is "<<put<<" pounds. ";
    double calldelta = CallDelta(Strike, Maturity, Spot,  Volatility, Riskfreerate);
    cout << "The call option delta is "<<calldelta<<". ";
    double putdelta = PutDelta(Strike, Maturity, Spot, Volatility,  Riskfreerate );
    cout << "The put option delta is "<<putdelta<<".";
    return 0;
}