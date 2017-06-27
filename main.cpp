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
    cout << "   9.- Gauss - Jordan" << endl;
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

    cout << "Iteraccion " << setw(10) << "Li" << setw(10) << "Ls" << setw(10) << "xR" << setw(20) <<"ErrorAbsoluto" << setw(20) << "yI" << setw(18) << "yU" << setw(18) << "yR" << endl;

    do{
        xR1 = ( LimiteInferior + LimiteSuperior) / 2;
        yI = f1( LimiteInferior );
        yU = f1( LimiteSuperior );
        yR = f1( xR1 );

        cout << setw(5) << iContador << setw(15) << LimiteInferior << setw(10) << LimiteSuperior << setw(10) << xR1 << setw(20)
         << ErrorAbsoluto << setw(20) << yI << setw(20) << yU << setw(20) << yR << endl;

        if ( ( yI * yR ) < 0 )
            LimiteSuperior = xR1;
        else if ( ( yI * yR ) > 0 )
            LimiteInferior = xR1;
        else if ( yR == 0 ){
            return xR1;
            ErrorAbsoluto = 0.0;
        }

        xR2 = ( LimiteInferior + LimiteSuperior ) / 2;
        ErrorAbsoluto = fabs( double( xR2 - xR1) / ( xR2 ) );
        iContador++;
    }
    while( ( ErrorAbsoluto > errorMenor ) && ( iContador <= numeroIteracciones) );

    cout << setw(5) << iContador << setw(15) << LimiteInferior << setw(10) << LimiteSuperior << setw(10) <<
    xR2 << setw(20) << ErrorAbsoluto << setw(20) << yI << setw(20) << yU << setw(20) << yR << endl;

    if ( iContador > numeroIteracciones )
        cout << "El metodo no converge para las iteracions dadas" << endl;
    else if ( iContador <= numeroIteracciones ){
        cout << "El metodo converge" << endl;
        cout << endl;
        return xR2;
    }
}

int main()
{
    int iOpcion, numeroIteracciones;
    double errorMenor, LimiteInferior, LimiteSuperior, Raiz;

    do {
        iOpcion = Menu( );
        if ( iOpcion == 1 ){

        }
        else if ( iOpcion == 2 ){

        }
        else if ( iOpcion == 3 ){

        }
        else if ( iOpcion == 4 ){

        }
        else if ( iOpcion == 5 ){

        }
        else if ( iOpcion == 6 ){

        }
        else if (iOpcion == 7 ){
            cout << endl;
            cout << "Provee limite inferior";
            cin >> LimiteInferior;
            cout << "Provee limite superior";
            cin >> LimiteSuperior;
            cout << "Porcentae de error menor a: %";
            cin >> errorMenor;
            cout << "Numero de iteracciones: ";
            cin >> numeroIteracciones;
            Raiz = Biseccion( LimiteInferior, LimiteSuperior, errorMenor, numeroIteracciones );
            cout << "La raiz es: " << setprecision(10) << Raiz << endl;
        }
        else if ( iOpcion == 8 ){

        }
        else if ( iOpcion == 9 ){

        }
        else if ( iOpcion == 10 ){

        }
        else if ( iOpcion == 11 ){
            return 0;
        }
    }
    while ( iOpcion < 10 || iOpcion > 0 );


    return 0;
}
