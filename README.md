[![Rad Pro Demonstration](docs/img/radpro-video.jpg)](https://www.youtube.com/watch?v=7dpVG1jSLn8)

## Introduction

Rad Pro (formerly FS2011 Pro) is a custom firmware that enhances the capabilities of several low-cost Geiger counters, including the [FS2011](https://www.amazon.com/s?k=fs2011), [FS9000](https://www.amazon.com/s?k=fs9000), [NR-950](https://www.amazon.com/s?k=nr950) and [YT-203B](https://www.amazon.com/s?k=yt-203b). Support for the [Bosean FS-600](https://www.bosean.net/products/nuclear_radiation_detector.html) and [Bosean FS-1000](https://www.bosean.net/products/FS-1000_nuclear_radiation_detector.html) is planned.

With Rad Pro, you can:

* Measure instantaneous radiation rate (based on the last 11 pulses or 5-second moving-average).
* Measure average radiation rate (over a time period).
* Measure cumulative dose (stored in non-volatile memory).
* Generate customizable rate and dose alarms.
* Plot historical radiation rate over different time periods (2 minutes, 10 minutes, 1 hour, 6 hours and 24 hours).
* Generate secure passwords (letters & numbers, full ASCII), random hexadecimal and decimal numbers, coin flips, and dice throws (4-sided, 6-sided, 8-sided, 12-sided and 20-sided).
* Log data to the built-in flash memory or live on a computer, optionally sending the data to the https://gmcmap.com or https://radmon.org radiation monitoring websites.

## Updates

* Rad Pro 1.3.0 adds configurable Geiger tube conversion factors and data logging support.
<!-- * Rad Pro 1.3.1 adds a real time clock for accurate data logging and support for the FS2011 with GD32F103 processors. -->

## Project overview

* [Before installing](docs/legal.md)
* [Installing on the FS2011/FS9000/NR-950/YT-203B](docs/install-fs2011.md)
* [Installing on other devices](docs/install-other.md)
* [User's manual](docs/manual.md)
* [Developers](docs/developers.md)

## Thanks

* Thanks to the u8g2 team for their excellent LCD library.
* Thanks to Alfred90, danielhahn76, felixsteghofer and DG0MG for device testing.
* Thanks to pixitha for the FS2011 board photo with a J305 Geiger tube.
