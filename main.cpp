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
double Biseccion( double LimiteInferior, double LimiteSuperior, double errorMenor,int numeroIteracciones){
    int iContador = 1;
    double xR1, xR2, ErrorAbsoluto, yI, yU, yR;
    cout << "Iteraccion " << setw(10) << "xI" << setw(10) << "xU"  << setw(10) << "xR" << setw(10)
    <<"ErrorAbsoluto" << setw(10) << "yI" << setw(10) << "yU" << setw(10) << "yR" << endl;
    do{

    }
    while( );
}

int main()
{
    int iOpcion, numeroIteracciones;
    double errorMenor, LimiteInferior, LimiteSuperior, Raiz;

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
            cout << "Error menor a: ";
            cin >> errorMenor;
            cout << "Numero de iteracciones: ";
            cin >> numeroIteracciones;
            Raiz = Biseccion( LimiteInferior, LimiteSuperior, errorMenor, numeroIteracciones );
            cout << "La raiz es: " << setprecision(10) << Raiz << endl;
        }
    }
    while ( iOpcion < 10 || iOpcion > 0 );


    return 0;
}
