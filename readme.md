# OpenHantek [![Build Linux](https://github.com/Pejosonic/openhantek/actions/workflows/build-linux.yml/badge.svg)](https://github.com/Pejosonic/openhantek/actions/workflows/build-linux.yml)

OpenHantek is a free, open-source oscilloscope application for Hantek and compatible USB devices. This fork adds native support for the **SainSmart DDS140** (and DDS120), reverse-engineered from USB protocol captures and cross-referenced with the OpenBuudai project.

<table><tr>
    <td> <img alt="Image of main window on linux" width="100%" src="docs/images/screenshot_mainwindow.png"> </td>
    <td> <img alt="Image of main window on Windows" width="100%" src="docs/images/screenshot_mainwindow_win.png"> </td>
</tr></table>

* **Supported OS:** Linux (primary), MacOSX, Windows
* **Supported devices:** DSO2xxx Series, DSO52xx Series, 6022BE/BL, **SainSmart DDS140**

## Download

A Linux x86_64 binary is built automatically on every commit and published as a pre-release:

**[⬇ Download latest Linux build](https://github.com/Pejosonic/openhantek/releases/tag/latest)**

## SainSmart DDS140 support

The DDS140 (USB VID `0x8312` / PID `0x8312`) works out of the box — no firmware upload is needed. On Linux, grant non-root USB access with a udev rule:

```bash
echo 'SUBSYSTEM=="usb", ATTR{idVendor}=="8312", ATTR{idProduct}=="8312", MODE="0666"' \
  | sudo tee /etc/udev/rules.d/61-dds140.rules
sudo udevadm control --reload-rules && sudo udevadm trigger
```

Replug the device, then launch OpenHantek — it will be detected automatically.

| Feature | Details |
|---|---|
| Channels | 2 |
| Sample rates | 39 kHz, 625 kHz, 10 MHz, 80 MHz, 100 MHz |
| Voltage ranges | 50 mV/div · 100 mV/div · 200 mV/div · 500 mV/div · 1 V/div (per channel) |
| Trigger | Software (rising/falling edge) |
| Coupling | DC only |
| Voltage calibration | Uncalibrated — see [limitations](docs/limitations.md#sainsmartdds140) |

## Features

* Digital phosphor effect to notice even short spikes
* Voltage and spectrum view for all supported channels
* Math channel (Ch1+Ch2, Ch1−Ch2)
* Freely configurable colors
* Export to CSV, JPG, PNG or print
* Hardware and software trigger support
* Zoom view with freely selectable range
* Settings saved to and loaded from a configuration file
* Multiple instances with a different device each

## Building from source

Dependencies:

* [CMake 3.5+](https://cmake.org/download/)
* [Qt 5.4+](https://www1.qt.io/download-open-source/)
* [FFTW 3+](http://www.fftw.org/)
* libusb 1.x
* C++11 compiler

Build instructions: [Linux](docs/build.md#linux) · [macOS](docs/build.md#apple) · [Windows](docs/build.md#windows)

## Running OpenHantek

Requires OpenGL 3.2+ or OpenGL ES 2.0+. To force OpenGL ES:

```
OpenHantek --useGLES
```

For Hantek devices on Linux, copy `firmware/60-hantek.rules` to `/lib/udev/rules.d/` and replug the device.

## Specifications and limitations

See the [Specifications, Features, Limitations](docs/limitations.md) page.

## Other DSO open source software

* [SigRok](http://www.sigrok.org)
* [OpenBuudai](https://github.com/OpenHantek/OpenBuudai) — inspiration for DDS140 support
* [Software for the Hantek 6022BE/BL only](http://pididu.com/wordpress/basicscope/)
