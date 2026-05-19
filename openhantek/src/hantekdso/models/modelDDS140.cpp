// SPDX-License-Identifier: GPL-2.0+

#include "modelDDS140.h"
#include "hantekdso/hantekdsocontrol.h"
#include "hantekprotocol/controlStructs.h"

using namespace Hantek;

static ModelDDS140 modelInstance;

static void initSpecifications(Dso::ControlSpecification &specification) {
    specification.isDDS140Device = true;
    specification.useControlNoBulk = true;
    specification.isSoftwareTriggerDevice = true;
    specification.isFixedSamplerateDevice = true;
    specification.supportsCaptureState = false;
    specification.supportsOffset = false;
    specification.supportsCouplingRelays = false;
    specification.sampleSize = 8;

    // Fixed sample rates: {id (unused), samplerate Hz}
    // Order must match dds140RateCmds
    specification.fixedSampleRates = {
        {0, 39e3},
        {1, 625e3},
        {2, 10e6},
        {3, 80e6},
        {4, 100e6}
    };

    // USB command byte that selects each sample rate (indexed same as fixedSampleRates)
    specification.dds140RateCmds = {0x1b, 0x18, 0x1c, 0x11, 0x10};

    // Gain steps: V/div
    specification.gain = {
        {0, 0.05},
        {1, 0.10},
        {2, 0.20},
        {3, 0.50},
        {4, 1.00}
    };

    // Gain register values per step, per channel
    // CH1 cmd 0x22: 50mV=0x08, 100mV=0x04, 200mV=0x00, 500mV=0x06, 1V=0x02
    specification.dds140GainCH1 = {0x08, 0x04, 0x00, 0x06, 0x02};
    // CH2 cmd 0x23: 50mV=0x20, 100mV=0x10, 200mV=0x00, 500mV=0x12, 1V=0x02
    specification.dds140GainCH2 = {0x20, 0x10, 0x00, 0x12, 0x02};

    // Uncalibrated: 32 ADC counts per screen division (8-bit, centred at 0x80)
    specification.voltageLimit[0] = {32, 32, 32, 32, 32};
    specification.voltageLimit[1] = {32, 32, 32, 32, 32};

    specification.couplings = {Dso::Coupling::DC};
    specification.triggerModes = {Dso::TriggerMode::HARDWARE_SOFTWARE, Dso::TriggerMode::SINGLE};

    // Samplerate limits (informational — fixed rates are used instead)
    specification.samplerate.single.base = 100e6;
    specification.samplerate.single.max  = 100e6;
    specification.samplerate.single.maxDownsampler = 1;
    specification.samplerate.single.recordLengths  = {UINT_MAX, 65532};
    specification.samplerate.multi = specification.samplerate.single;

    specification.bufferDividers = {1, 1};
}

ModelDDS140::ModelDDS140()
    : DSOModel(ID,
               0x8312, 0x8312,  // VID/PID with firmware loaded
               0,      0,       // no separate bootloader VID/PID
               "",              // no firmware upload needed
               "DDS140",
               Dso::ControlSpecification(2)) {
    initSpecifications(specification);
}

void ModelDDS140::applyRequirements(HantekDsoControl *dsoControl) const {
    dsoControl->addCommand(new ControlDDS140GainCH1(), false);
    dsoControl->addCommand(new ControlDDS140GainCH2(), false);
    dsoControl->addCommand(new ControlDDS140SampleRate(), false);
}
