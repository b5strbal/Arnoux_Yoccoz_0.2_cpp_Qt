/**
 * @mainpage    Arnoux-Yoccoz
 *
 *              The main goal of the program is to construct Arnoux-Yoccoz-type pseudo-anosovs.
 */



#include <iostream>
#include <time.h>
#include "Foliation.h"
//#include "io.h"
#include "FoliationRP2.h"
#include "AlmostPFMatrix.h"

using namespace std;







int main (int argc, const char * argv[])
{

    try {
      //  Foliation f({0.21, 0.21, 0.11, 0.11, 0.17, 0.17}, Permutation({1, 0, 3, 2, 5, 4}), 0.5);
        for (int i = 3; i < 200; i++) {
            cout << i << " ";   arnouxYoccozStretchFactor(i);
            cout << endl;
        }
    } catch (const std::exception& ex) {
        cout << "Error: " << ex.what();
    }
    
    
    
    /*
     // double alpha = 0.5436890126920764; // The stretch factor of the Arnoux-Yoccoz pseudo-anosov.
     long double alpha = 0.54368901269207636157085597180174799;
     std::vector<long double> list = {(alpha + pow(alpha,2))/2, (pow(alpha,2) + pow(alpha,3))/
     2, (alpha + pow(alpha,3))/2};
     
     WeighedTree wt(list);
     FoliationRP2 fAY(wt);
     //  std::cout << std::setprecision(30);
     
     // std::cout << "aplha = " << 1/alpha << std::endl;
     // std::cout << "aplha^2 = " << 1/(alpha * alpha) << std::endl;
     // std::cout << "aplha^3 = " << 1/(alpha * alpha * alpha) << std::endl;
     
     std::cout << "The Arnoux-Yoccoz pseudo-anosov: " << fAY << std::endl;
     
     
     {
     clock_t t1, t2;
     t1 = clock();
     
     // fAY.GenerateGoodShiftedSeparatrixSegments(10);
     // fAY.GenerateSimpleClosedCurves();
     // fAY.GenerateNewParametrizations(100000);
     t2 = clock();
     float seconds = ((float)t2 - (float)t1)/CLOCKS_PER_SEC;
     std::cout << "Time1:" << seconds << std::endl ;
     }
     
     */
    
    
    
    /*
    
    Greetings();
    FoliationRP2* Foliation;
    bool Exit = false;
    while(!Exit){
        try {
            Foliation = GetFoliation();
            cout << *Foliation;
            WaitForEnter();
            PerformOperation(Foliation);
        } catch (int i) {
            if (i < 0) {
                Exit = true;
            }
        }
    }
    delete Foliation;
    */
    
    
    return 0;
}

