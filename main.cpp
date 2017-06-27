#include <iostream>
#include <iomanip>
#include <math.h>

#define f1(x)(1.0 * pow(x,4) - 5.0 * pow(x,3) + 0.5 * pow(x,2) - 11.0 * x + 10.0)

using namespace std;

int Menu( ){
    int iOpcion;

    cout << "Seleccione el numero del metodo que desee: " << endl;
    cout << "   1.- Trapezoidal simple" << endl;
    cout << "   2.- Trapezoidal multiple" << endl;
    cout << "   3.- Simpson 1/3" << endl;
    cout << "   4- Simpson 3/8" << endl;
    cout << "   5.- Secante" << endl;
    cout << "   6.- Newton-Raphson" << endl;
    cout << "   7.- Biseccion" << endl;
    cout << "   8.- Montante" << endl;
    cout << "   9.- Gauss" << endl;
    cout << "   10.- Interpolacion" << endl;
    cout << "   11.- Salir" << endl;
    cin >> iOpcion;

    //if ( iOpcion < 10 || iOpcion > 1 )
    return iOpcion;
}

//BISECCION
double Biseccion()

int main()
{
    int iOpcion;
    do {
        iOpcion = Menu( );
        if ( iOpcion == 1 ){
           /* double h;
            double LimiteInferior, LimiteSuperior;
            cout << "Provee limite inferior";
            cin >> LimiteInferior;
            cout << "Provee limite superior";
            cin >> LimiteSuperior;
            h = ( LimiteSuperior - LimiteInferior ) / 2;
            double i = ( h / 2 ) * ( LimiteInferior + ( 2 * () ) ) //POSIBLE ERROR
*/
        }
        else if ( iOpcion == 2 ){

        }
        else if (iOpcion == 7 ){
            cout << "Provee limite inferior";
            cin >> LimiteInferior;
            cout << "Provee limite superior";
            cin >> LimiteSuperior;
        }
    }
    while ( iOpcion < 10 || iOpcion > 0 );


    return 0;
}
