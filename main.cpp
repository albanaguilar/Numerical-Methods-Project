/*
Proyecto final de la materia Metodos numericos en la ingenieria

Integrantes:
Alban Aguilar Campos
Noe Flores Sifuentes
Salvador Garcia Martinez
Francisco Navarrete Meza
Carlos Manzano

*/

#include <cstdlib>
#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <iomanip>
#include <stdio.h>
#include <math.h>

#define f1(x)(1.0 * pow(x,4) - 5.0 * pow(x,3) + 0.5 * pow(x,2) - 11.0 * x + 10.0)
#define f2(x)(1.0*pow(x,5)-4.0*pow(x,4)+5.0*pow(x,3)-6.0*x+4.0)
#define fp(x)(5.0*pow(x,4)-16.0*pow(x,3)+15.0*pow(x,2)-6.0)
#define f3(x)(1.0*pow(x,4)-5.0*pow(x,3)+10.0*pow(x,2)-10.0*x+4.0)

using namespace std;

void leemat(int , float [30][30]);
void escmat(int, float [30]);
float gaussjor( int , float [30][30], float [30] );
void PideDatos(int *Dat, int *Ord, float Val[][102]);
float Potencia(int n, float Num);
void PreparaSistema(int Ord, int Dat, float Sist[][102], float Val[][102]);
void ResuelveGauss(int Dim, float Sist[][102]);
void EscribeDatos(int Dim, float Sist[][102]);
void leevec(int, float [100] , char[100]);
void DifDivNewton(int, float [100], float [100], float [100]);
void escribirMatriz(int , int , float [50][50], char[10]);
void gaussjordan(int , float [50][50], float [50][50], float [50]);
void escvec(int, float [50], char[10]);
void escpol(int, float [50], char [10]);
void intlag(int, float[50], float[50][50]);

int Menu( ){
    int iOpcion;

    cout << endl;
    cout << "Seleccione el numero del metodo que desee: " << endl;
    cout << "   1.- Trapezoidal" << endl;
    cout << "   2.- Minimos cuadrados" << endl;
    cout << "   3.- Simpson 1/3" << endl;
    cout << "   4- Simpson 3/8" << endl;
    cout << "   5.- Secante" << endl;
    cout << "   6.- Newton-Raphson" << endl;
    cout << "   7.- Biseccion" << endl;
    cout << "   8.- Lagrange" << endl;
    cout << "   9.- Gauss - Jordan" << endl;
    cout << "   10.- Newton (interpolacion) " << endl;
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

//GAUSS-JORDAN
float gaussjor( int n, float a[30][30], float x[30] ){
    int iA, j, k;
    float aux;
    for( iA = 1; iA <= n; iA++ ){
        aux = a[iA][iA];
        for ( j = iA; j <= n + 1; j++ ){
            a[iA][j] = a[iA][j] / aux;
        }
        for ( j = 1; j <= n; j++ ){
            if( j != iA ){
                aux = a[j][iA];
                for (k = iA; k <= n + 1; k++){
                    a[j][k] = ( a[j][k] ) - ( ( a[iA][k] ) * aux );
                }
            }
        }
    }

    for ( iA = 1; iA <= n; iA++ )
        x[iA] = a[iA][n + 1];
}

void leemat(int n, float a[30][30] ){
    int i, j;
    for (i = 1; i <= n; i++ ){
        for( j = 1; j <= n + 1; j++ ){
            cout << "a[" << i << "][" << j << "] = ";
            cin >> a[i][j];
        }
    }
}

void escmat( int n, float x[30] ){
    int i;
    for ( i = 1; i <= n; i++ )
        cout << "x[" << i << "] = " << x[i] << endl;
}

double Trapezoidal(int iValor1, int iValor2, int iValorA, int iValorB){

            double dValorH;
            dValorH = (iValorA + iValorB) / 2.0;
            //C�lculo de m�todo trapezoidal.-
            double dResultado = ( ( 1 / dValorH ) * ( iValor1 + iValor2 ) );
            return dResultado;
}

void PideDatos(int *Dat, int *Ord,float Val[][102])
{
    int A,B;

    printf("\n\n\n METODO DE MINIMOS CUADRADOS.\n\n");
    printf("\n Introduce el numero de datos (Puntos): ");scanf("%d",&*Dat);
    printf("\n\n\n Introce los valores de cada punto\n");

    for(A=1;A<=*Dat;A++)
    {
        printf(" -Valores del Punto %d:\n",A);
        printf("   X%d: ",A); scanf("%f",&Val[0][A]);
        printf("   Y%d: ",A); scanf("%f",&Val[1][A]);
    }
    printf("\n\n\n Introduce el orden del polinomio: "); scanf("%d",&B);
    *Ord=B+1;
}


float Potencia(int n, float Num)
{
    int A;
    float res;

    res=1;
    for(A=1;A<=n;A++) res=res*Num;
    return res;
}



void PreparaSistema(int Ord, int Dat, float Sist[][102], float Val[][102])
{
    int A,B,C,Exp;
    float suma,termino;

    for(A=1;A<=Ord;A++)    for(B=1;B<=Ord;B++)
    {
        suma=0;
        Exp=A+B-2;

        for(C=1;C<=Dat;C++)
        {
            termino=Val[0][C];
            suma=suma+Potencia(Exp,termino);
        }
        Sist[A][B]=suma;
    }
    for(A=1;A<=Ord;A++)
    {
        suma=0;
        Exp=A-1;

        for(C=1;C<=Dat;C++)
        {
            termino=Val[0][C];
            suma=suma+Val[1][C]*Potencia(Exp,termino);
        }
        Sist[A][Ord+1]=suma;
    }
}


void ResuelveGauss(int Dim, float Sist[][102])
{
    int NoCero,Col,C1,C2,A;
    float Pivote,V1;

    for(Col=1;Col<=Dim;Col++){
        NoCero=0;A=Col;
        while(NoCero==0){
            if(Sist[A][Col]!=0){
                NoCero=1;}
            else A++;}
        Pivote=Sist[A][Col];
        for(C1=1;C1<=(Dim+1);C1++){
            V1=Sist[A][C1];
            Sist[A][C1]=Sist[Col][C1];
            Sist[Col][C1]=V1/Pivote;}
        for(C2=Col+1;C2<=Dim;C2++){
            V1=Sist[C2][Col];
            for(C1=Col;C1<=(Dim+1);C1++){
                Sist[C2][C1]=Sist[C2][C1]-V1*Sist[Col][C1];}
        }}

    for(Col=Dim;Col>=1;Col--) for(C1=(Col-1);C1>=1;C1--){
        Sist[C1][Dim+1]=Sist[C1][Dim+1]-Sist[C1][Col]*Sist[Col][Dim+1];
        Sist[C1][Col]=0;
    }
}

void EscribeDatos(int Dim, float Sist[][102])
{
    int A,B;
    printf("\n\n");
    for(A=1;A<=Dim;A++){
        for(B=1;B<=(Dim+1);B++){
            printf("%7.2f",Sist[A][B]);
            if(B==Dim) printf("   |");}
        printf("\n");
    }
    printf("\n\n");
}

void leevec(int iN, float iX[100], char cNom[10])
{
    for(int iC = 1; iC <= iN ; iC++)
    {
        cout << cNom << "[" << iC << "] : ";
        cin >> iX[iC];
    }
}

void escribirMatriz(int iN , int iM, float dA[50][50], char cNom[10])
{
    cout << "Matriz" << cNom << endl;
    for (int iC = 1; iC <= iN; iC++)
    {
        cout << endl;
        for(int iR = 1; iR <= iM; iR++)
        {
            cout << setw(10) << dA[iC][iR];


        }
    }
    cout << endl;
}

void escvec(int iN, float dX[50], char cNom[10])
{
    for(int iC = 1; iC <= iN ; iC++)
    {
        cout << endl;
        cout << cNom << "[" << iC << "] : " << dX[iC];
    }
    cout << endl;
}

void DifDivNewton(int iN, float dX[100], float dY[100], float dA[100])
{
    float DD[50][50], dP[50][50], dVX[50][50], dB[50], P[50][50];

    for(int iC = 1; iC <= iN ;iC++)
    {
        DD[iC][1] = iC - 1;
        DD[iC][2] = dX[iC];
        DD[iC][3] = dY[iC];
    }
    for(int iR = 1; iR <= iN; iR++ )
    {
        for(int iC = 1; iC <= iN - iR; iC++)
        {
            DD[iC][iR+3] = ((DD[iC+1][2+iR])- (DD[iC][2 + iR]))/((DD[iC + iR][2]) -(DD[iC][2]));
        }
    }
    escribirMatriz(iN, iN+2,DD, "DD");
    for (int iC = 1; iC <= iN; iC++)
    {
        dB[iC] = DD[1][iC+2];
    }

    cout << "Valores de B" << endl;
    escvec(iN, dB, "dB");
    for(int iC = 1; iC <= iN ; iC++)
    {
        for(int iR = 1; iR <= iN; iR++)
        {
            P[iC][iR] = 0;
        }

    }
    for(int iC = 1; iC <= iN ; iC++)
    {
        P[iC][1] = 1;
    }
    for(int iC = 2; iC <= iN; iC++)
    {
        for(int iR = 2; iR <= iC; iR++)
        {
            P[iC][iR] = ((P[iC -1][iR - 1])* (-1 * dX[iC -1 ]))+ P[iC - 1][iR];
        }
    }

    escribirMatriz(iN, iN, P, "Polinomios");


    for(int iC = 1; iC <= iN; iC++)
    {
        for(int iR = 1; iR <= iN; iR++)
        {
            P[iC][iR] = P[iC][iR] * dB[iC];
        }
    }
    escribirMatriz(iN, iN , P , "Polinomios");

    for(int iR = 1; iR <= iN; iR++)
    {
        dA[iR -1] = 0;
        for(int iC = iR; iC <= iN ; iC++)
        {
            dA[iR -1] = dA[iR - 1] + P[iC][iC+1 - iR];
        }
    }
    escpol(iN - 1, dA, "P(x)" );
}

void escpol(int iN, float dA[50], char cNom[10]){
    cout << "Polinomio" << cNom << " = ";
    for(int iC = 0; iC <= iN; iC++)
    {
        cout << dA[iC] << "X^" << iC;
            if (iC < iN)
            {
                cout << "+ ";
            }
    }
    cout << endl;
}

void intlag(int n, float a[50], float fx[50][50] ){
    int i, j, k, cont, h, l, t;
    float P[50][50], constP[50][50], x[50], aux[50], PL[50];

    cont = 1;
    for ( i = 0; i <= 50; i++ ){
        aux[i] = 1;
    }

    for ( j = 0; j < n; j++ ){
        for (k = 0; k < n; k++ ){
            if ( j != k )
                aux[j] = aux[j] * ( a[j]- a[k] );
            fx[j][2] = fx[j][1] / aux[j];
        }
    }

    for ( i = 0; i < n; i++ )
        a[i] = a[i] * -1;

    for ( l = 0; l <= n - 1; l++ ){
        t = 0;
        for ( j = 0; j < n; j++ ){
            if (j != l){
                x[t] = a[j];
                t++;
            }
        }

        P[0][0] = 1;
        for (i = 0;  i < n; i++ ){

            for ( j = 1; j < n; j++ ){
                if (i == j)
                    P[i][j] = P[i - 1][j - 1] * x[i - 1];
            }

            for ( j = 1; j <= n; j++ ){
                if (i == 0)
                    P[j][i] = P[0][0];
            }

            for ( j = 1; j < n - 1; j++ ){
                if (i == 1)
                    P[j + 1][i] = P[j][i] + x[j];
            }

            for ( j = 2; j < n; j++ ){
                for( h = j + 1; h < n; h++ ){
                    if (i == j)
                        P[h][j] = P[h - 1][j] + (P[h - 1][j - 1] * x[h - 1]);
                }
            }
        }

        for (j = 0; j < n; j++ )
            constP[0][j] = fx[l][2] * P[n - 1][j];

        for (i = 0; i < n; i++ ){
            for (j = 0; j < n; j++){
                PL[i] = PL[i] + constP[j][i];
            }
        }
        cont++;
    }

    cout << endl << endl;;
    cout << "El polinomio de Lagrange: " << endl << endl;
    cout << "(" <<PL[0]-1 << "x^" << n-1-i << ") + ";
    for (i = 1; i < n; i++ )
        cout << "(" <<PL[i] << "x^" << n-1-i << ") + ";
}

int main()
{
    int iOpcion, numeroIteracciones;
    double errorMenor, LimiteInferior, LimiteSuperior, Raiz, dX0, dX1;
    int n;
    float a[30][30], x[30];

    do {
        iOpcion = Menu( );
        if ( iOpcion == 1 ){
            int iValorA, iValorB, iValor1, iValor2;

             //Valores para calcular el valor de H.-
            cout << "Ingresa el valor de a para calcular H: ";
            cin >> iValorA;
			cout << "Ingresa el valor de b para calcular H: ";
            cin >> iValorB;

            //Valores para el c�lculo de l�mites dentro de la integral.-
			cout << "Ingresa el primer par�metro: ";
            cin >> iValor1;
            cout << "Ingresa el segundo par�metro: ";
            cin >> iValor2;

            //LLamada al m�todo que calcula el m�todo trapezoidal.-
            double dResultado = Trapezoidal(iValor1, iValor2, iValorA, iValorB);
            cout << "El resultado es: " << dResultado << endl;

        }
        else if ( iOpcion == 2 ){
            int Datos,Orden,C;

            float Valores[2][102],Sistema[102][102];
            PideDatos(&Datos,&Orden,Valores);
            PreparaSistema(Orden,Datos,Sistema,Valores);
            printf("\n\n El sistema a resolver es el siguiente:");
            EscribeDatos(Orden,Sistema);
            ResuelveGauss(Orden,Sistema);
            printf("\n\n El sistema resuelto:");
            EscribeDatos(Orden,Sistema);
            printf("\n\n La Ecuacion del Polinomio ajustado por minimos Cuadrados\n\n:");
            for(C=1;C<=Orden;C++)
                printf(" + (%f)X^%d",Sistema[C][Orden+1],C-1);
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
            int n, i;
            float x[50], fx[50][50];

            cout << endl;
            cout << "Metodo de interpolacion de lagrange" << endl;
            cout << "Numero de datos de la lista" ;
            cin >> n;
            cout << "Introduce los datos de x[i]: " << endl;
            for ( i = 0; i <= n - 1; i++){
                cout << endl;
                cout << "x[" << i <<"]= ";
                cin >> x[i];
            }
            cout << endl;
            cout << "Introduce los valores de f(x)" << endl;
            for( i = 0; i <= n - 1; i++ ){
                cout << endl;
                cout << "fx(" <<i <<")= ";
                cin >> fx[i][1];
            }
            intlag(n, x ,fx);
        }
        else if ( iOpcion == 9 ){
            cout << "Numero de ecuaciones: ";
            cin >> n;
            cout << "Introduce los valores de la matriz: ";
            leemat(n, a);
            gaussjor(n, a, x);
            cout << "Soluccion " << endl;
            escmat(n, x);
        }
        else if ( iOpcion == 10 ){
            int iM, iN;
            float dX[100], dY[100], dA[100];

            cout << " >>>>>>>>>>> Dif de Newton >>>>>>>>>>>>>>>>>>" << endl;
            cout << "Cuantos puntos desea : " << endl;
            cin >> iN;
            cout << "Vector de x" << endl;
            leevec(iN, dX, "X");
            cout << "Vector de y" << endl;
            leevec(iN, dY, "Y");

            DifDivNewton(iN, dX, dY, dA);
        }
        else if ( iOpcion == 11 ){
            return 0;
        }
    }
    while ( iOpcion < 10 || iOpcion > 0 );


    return 0;
}
