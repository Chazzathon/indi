/*
    indi_rtlsdr_detector - a software defined radio driver for INDI
    Copyright (C) 2017  Ilia Platone

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#pragma once

#include "indidetector.h"

enum Settings
{
    FREQUENCY_N = 0,
    SAMPLERATE_N,
    BANDWIDTH_N,
    NUM_SETTINGS
};
class RadioSim : public INDI::Detector
{
    public:
        RadioSim();

        bool ISNewNumber (const char *dev, const char *name, double values[], char *names[], int n) override;
        void ISGetProperties(const char *dev) override;

    protected:
        // General device functions
        bool Connect() override;
        bool Disconnect() override;
        const char *getDefaultName() override;
        bool initProperties() override;
        bool updateProperties() override;

        // Detector specific functions
        bool StartCapture(float duration) override;
        bool CaptureParamsUpdated(float sr, float freq, float bps, float bw, float gain) override;
        bool AbortCapture() override;
        void TimerHit() override;

        virtual bool StartStreaming() override;
        virtual bool StopStreaming() override;


    private:
        INumber DetectorPropertiesN[1];
        INumberVectorProperty DetectorPropertiesNP;
        INumberVectorProperty DetectorCoordsNP;
        // Utility functions
        float CalcTimeLeft();
        void setupParams();
        void grabData();

        // Are we exposing?
        //bool InCapture;
        // Struct to keep timing
        struct timeval CapStart;
        double DishSize; //simulated dish size in meters
        //double Ra; //should not stay here
        //double Dec; //should not stay here

        //int n_read;
        int to_read;
        //int b_read;
        float CaptureRequest;
        uint8_t* continuum;
        uint8_t* spectrum;

        int streamPredicate;
        pthread_t primary_thread;
        bool terminateThread;
};
