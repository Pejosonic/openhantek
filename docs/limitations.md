---
layout: default
---
## Software triggered devices like the 6022BE

   - Support 48, 24, 16, 8, 4, 2, 1 M and 500, 200, 100 k Hz samplerates. For the 6022 with modded firmware by [jhoenicke](https://github.com/rpcope1/Hantek6022API) 
   - Can detect rising or falling edge of the signal.
   - Note that the first few samples are dropped due to unstable/unusual reading.

## SainSmart DDS140

   - USB VID/PID: `0x8312` / `0x8312`. No firmware upload needed.
   - 2 channels, 8-bit ADC, 131,072-byte capture buffer per acquisition (~65,500 samples/channel).
   - Fixed sample rates: 39 kHz, 625 kHz, 10 MHz, 80 MHz, 100 MHz.
   - Voltage ranges: 50 mV/div, 100 mV/div, 200 mV/div, 500 mV/div, 1 V/div per channel (independent per channel).
   - Software trigger only (rising/falling edge detection in software).
   - AC/DC coupling is not software-switchable on this device; DC coupling only.
   - Voltage scaling is uncalibrated — readings are approximate and may vary between units. Adjust `voltageLimit` in `modelDDS140.cpp` after calibrating against a known reference.
   - No channel offset support.
   - Data is captured via USB interrupt transfer on endpoint `0x82`; a FIFO-ready poll (up to 2 seconds) precedes each acquisition.

