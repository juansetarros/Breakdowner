/*
  ==============================================================================

    Delay.h
    Created: 10 Nov 2022 5:17:08pm
    Author:  Wateo

  ==============================================================================
*/

#pragma once
#include <vector>
#include "Filtro.h"

class Delay
{
public:
    Delay():
        fs(44.1e3), delaySamples(0), writeIdx(0), readIdx(0), delayMax(0), t(0)
    {
        
    }
    void setSampleRate(float sampleRate, float maxDelayInSeconds)
    {
        delayMax = round(maxDelayInSeconds * fs);
        // Resize va borrar y volver a crear el vector
        bufferCircular.resize(delayMax + 1, 0);
    }
    // Función es para cuando se va a dar el tiemo en segundos
    void setDelayTime(float newDelayTime)
    {
        delaySamples = round(newDelayTime * fs);
        readIdx = writeIdx - delaySamples;
        if (readIdx < 0)
        {
            readIdx += (delayMax + 1);
        }
    }
    // Función es para cuando se va a dar el tiempo en muestras
    void setDelayTime(int newDelaySamples)
    {
        delaySamples = newDelaySamples;
        readIdx = writeIdx - delaySamples;
        if (readIdx < 0)
        {
            readIdx += (delayMax + 1);
        }
    }
    float processSample(float xn, float fb)
    {
        float oldestSample = interpolateSample(readIdx);

        bufferCircular[(int)writeIdx] = xn + (oldestSample * fb);
        
        //writeIdx = (++writeIdx) % bufferCircular.size();
        writeIdx++;
        if (writeIdx >= bufferCircular.size()) { writeIdx = 0; }
        readIdx = writeIdx - delaySamples;
        if (readIdx < 0)
        {
            readIdx += (delayMax + 1);
        }

        return oldestSample;
    }

    float interpolateSample(float idx)
    {
        int before = floor(idx);
        int after = ceil(idx);
        after = after % bufferCircular.size();
        // Con respecto a la posicion
        float y1 = bufferCircular[before];
        float y2 = bufferCircular[after];
        // Valores en la posicion
        float fracc = idx - before;
        float yn = fracc * y2 + (1 - fracc) * y1;
        return yn;
    }

private:
    // Frecuencia de Muestreo
    float fs;
    // El delay máximo (el tamaño del vector)
    int delayMax;
    // El delay que se usará de ese vector
    int delaySamples;
    float writeIdx; // Indice de escritura
    float readIdx; // Indice de lectura
    std::vector<float> bufferCircular;
    float t;
};