/*
  ==============================================================================

    HardClipping.h
    Created: 2 Abril 2025 4:26 am
    Author:  Tarros

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include <cmath>

class HardClipping
{
public:
    // Constructor con umbral por defecto
    HardClipping(): 
        threshold(0.5f), blend(1.0f) {}

    // Setter para cambiar el umbral
    void setThreshold(float t) 
    {
        threshold = std::fmax(0.0f, std::fmin(t, 1.0f)); // Asegura que esté entre 0 y 1
    }

    void setBlend(float b)
    {
        blend = b;
    }
    // Procesa una muestra individual
    float processSample(float sample) 
    {
        // Hard Clipping
        if (sample > threshold)
        {
            hard = threshold;
        }
        else if (sample < -threshold)
        {
            hard = -threshold;
        }
        else
        {
            hard = sample;
        }

        // Soft Clipping
        soft = tanh(sample);

        return salida = (1.0f - blend) * soft + blend * hard;
    }


private:
    float threshold; // Umbral de clipping
    float hard; // Valores de Hard Clipping
    float soft; // Valores de Soft Clipping
    float salida; // Mezcla entre el hard y el soft
    float blend; // Cantidad de hard y soft
};
