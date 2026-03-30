
#pragma once
#include <JuceHeader.h>

class Filtro
{
public:
    // Constructor
    Filtro():
        xn1(0),xn2(0) // Inicialización por constructor
    {
        yn1 = 0; yn2 = 0;
        Fc = 1e3; Fs = 44.1e3;
        a1 = 0; a2 = 0; b0 = 0; b1 = 0; b2 = 0;
        filterType = 1;
        // Inicialización por constructor machetera
    }
    void getFs(float newFs) { Fs = newFs; }
    void changeFilter(int newFilter)
    {
        filterType = newFilter;
        recalculateFilter();
    }
    void changeFc(float newFc) { Fc = newFc; }
    void recalculateFilter()
    {
        float K = tan(juce::double_Pi * Fc / Fs);
        float KK = K * K;
        float Q = 0.707;
        if (filterType == 1) // Pasabajas
        {
            b0 = (KK * Q) / (KK * Q + K + Q);
            b1 = (2 * KK * Q) / (KK * Q + K + Q);
            b2 = (KK * Q) / (KK * Q + K + Q);
            a1 = (2 * Q * (KK - 1)) / (KK * Q + K + Q);
            a2 = (KK * Q - K + Q) / (KK * Q + K + Q);
        }
        else if (filterType == 3) // Pasabanda
        {
            b0 = K / (KK * Q + K + Q);
            b1 = 0;
            b2 = -(K / (KK * Q + K + Q));
            a1 = (2 * Q * (KK - 1)) / (KK * Q + K + Q);
            a2 = (KK * Q - K + Q) / (KK * Q + K + Q);
        }
    }

    float filterSignal(float xn)
    {
        float yn = b0 * xn + b1 * xn1 + b2 * xn2 - a1 * yn1 - a2 * yn2;
        yn2 = yn1;
        yn1 = yn;

        xn2 = xn1;
        xn1 = xn;
        return yn;
    }

private:
    float xn1, xn2; // Retrasos de entrada
    float yn1, yn2; // Retrasos de las salidas
    float b0, b1, b2; // Coeficientes de la entrada
    float a1, a2; // Coeficientes de la salida
    float Fs; // Frecuencia de muestreo
    float Fc; //Frecuencia de corte
    int filterType; // seleccionar tipo de filtro
};
