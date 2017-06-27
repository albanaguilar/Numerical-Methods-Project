/*
Proyecto final de la materia Metodos numericos en la ingenieria

Integrantes:
Alban Aguilar Campos
Noe Flores Sifuentes
Salvador Garcia Martinez
Francisco Navarrete Meza
Carlos Manzano

*/

#include <iostream>
#include <iomanip>
#include <math.h>

#define f1(x)(1.0 * pow(x,4) - 5.0 * pow(x,3) + 0.5 * pow(x,2) - 11.0 * x + 10.0)
#define f2(x)(1.0*pow(x,5)-4.0*pow(x,4)+5.0*pow(x,3)-6.0*x+4.0)
#define fp(x)(5.0*pow(x,4)-16.0*pow(x,3)+15.0*pow(x,2)-6.0)
#define f3(x)(1.0*pow(x,4)-5.0*pow(x,3)+10.0*pow(x,2)-10.0*x+4.0)

using namespace std;

int Menu( ){
    int iOpcion;

    cout << endl;
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

    return iOpcion;
}

//SECANTE
double Secante( double dX0, double dX1, double errorMenor, int numeroIteracciones)
{
    double dX2, ErrorAbsoluto, dY0, dY1, dPend;

    cout << "iteracion" << setw(10) << "xi-1" << setw(10) <<
    "xi" << setw(10) << "xi+1" << setw(10) << "Error" << setw(10)<<
    "f(xi-1)"<< setw(10) << "f(xi)" << setw(10) << "pend" << endl;

    for(int iCont = 1; iCont <= numeroIteracciones; iCont++)
    {
        dY0 = f3(dX0);
        dY1 = f3(dX1);
        dPend = (dY1 - dY0)/(dX1 - dX0);
        dX2 = dX1 - (dY1/dPend);
        ErrorAbsoluto = fabs((dX2 - dX1)/(dX2));

        cout << setw(5) << iCont << setw(15)<< dX0 << setw(10) << dX1 << setw(10)<< dX2 << setw(10)<<
        ErrorAbsoluto<< setw(10) << dY0 << setw(10)<< dY1<< setw(10) << dPend << endl;

        dX0 = dX1;
        dX1 = dX2;

        if( ErrorAbsoluto < errorMenor )
        {
            cout << "El metodo converge a" << iCont << "Iteraciones" << endl;
            return dX2;
            break;
        }
    }

    if( ErrorAbsoluto > errorMenor )
        cout << "El metodo no converge para las iteraciones especificadas" << endl;
        return 0;
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

//NEWTON - RAPHSON
double NewtonRaphson(double LimiteInferior, double errorMenor, int numeroIteracciones )
{
    double x2, ea, y1, yp1;
    cout << "iteracion " << setw(10) << "xi" << setw(10) << "xi+1" << setw(10) << "Ea" << setw(10) << "f(x1)" << setw(10) << "f'(x1)" << endl;
    for(int cont = 1; cont <= numeroIteracciones; cont++)
    {
        y1 = f2(LimiteInferior);
        yp1 = fp(LimiteInferior);
        if(yp1 == 0)
        {
            cout << "f'(xi) = 0" << endl;
            break;
        }
        x2 = LimiteInferior - ( y1 / yp1 );
        ea = fabs( ( x2 - LimiteInferior) / x2);

        cout << setw(5) << cont << setw(15) << LimiteInferior << setw(10) << x2 << setw(10) << ea << setw(10) << y1 << setw(10) << yp1 << endl;

        LimiteInferior = x2;

        if( ea < errorMenor )
        {
            cout << "El metodo coincide a " << cont << " iteraciones." << endl;
            return x2;
            break;
        }
    }
    if(ea>errorMenor)
    {
        cout << "El metodo no coincide para las " << numeroIteracciones << " iteraciones indicadas" << endl;
    }
    return 0;
}


int main()
{
    int iOpcion, numeroIteracciones;
    double errorMenor, LimiteInferior, LimiteSuperior, Raiz, dX0, dX1;

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
            cout << "Punto inicial (xi-1)" << endl;
            cin >> dX0;
            cout << "Punto inicial 2 (xi)" << endl;
            cin >> dX1;
            cout << "Error"<< endl;
            cin >> errorMenor;
            cout << "Numero de iteraciones" << endl;
            cin >> numeroIteracciones;
            cout.precision(4);

            Raiz = Secante(dX0, dX1, errorMenor, numeroIteracciones);
            cout << "La raiz es: " << setprecision(10) << Raiz << endl;
        }
        else if ( iOpcion == 6 ){
            //cout << "f2(x)(1.0*pow(x,5)-4.0*pow(x,4)+5.0*pow(x,3)-6.0*x+4.0)" << endl;
          //  cout << "fp(x)(5.0*pow(x,4)-16.0*pow(x,3)+15.0*pow(x,2)-6.0)" << endl;
            cout << endl;
            cout << "Datos" << endl;
            cout << "___________________________________________________________________" << endl;
            cout << "Punto Inicial (Xi)= ";
            cin >> LimiteInferior;
            cout << endl;
            cout << "Error = ";
            cin >> errorMenor;
            cout << endl;
            cout << "Numero de iteracciones (especifique si el metodo termina antes) = ";
            cin >> numeroIteracciones;
            cout << endl;
            cout.precision(4);
            Raiz = NewtonRaphson( LimiteInferior, errorMenor,  numeroIteracciones );
            cout << "La raiz es: " <<setprecision(10) << Raiz;
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
