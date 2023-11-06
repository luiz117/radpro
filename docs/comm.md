# Communications protocol

To establish a connection with a Rad Pro device, you can use either a serial port or an SWD connection. When using the serial port, make sure to configure it as follows:

* Baudrate: 115200
* Data bits: 8
* Parity: None
* Stop bits: 1
* Flow Control: None

The employed communications protocol is ASCII-based and follows a request-response model.

`\n` represents the newline character.

## Requests

### Get system identification

* Request: `GET deviceId\n`
* Response: `OK [hardware-id];[software-id];[device-id]\n`

Identifies the device's hardware and software. The response consists of these components:

* `[hardware-id]`: The device's hardware, which may be one of the following: `FS2011 (STM32F051C8)`, `FS2011 (GD32F150C8)`, `FS2011 (GD32F103C8)`, `Bosean FS-600`, `Bosean FS-1000`, `FNIRSI GC-01` or `SDLSim`.
* `[software-id]`: The device's software, typically `Rad Pro` followed by the software version.
* `[device-id]`: A unique device ID number.

Example:

    GET deviceId
    OK FS2011 (STM32F051);Rad Pro 2.0;9847195723

### Get device temperature

* Request: `GET deviceTemperature\n`
* Response: `OK [value]\n`

Returns the device's temperature in degrees Celsius, provided in decimal format with one decimal place.

Example:

    GET deviceTemperature
    OK 24.2

### Get device date and time

* Request: `GET deviceTime\n`
* Response: `OK [value]\n`

Returns the UNIX timestamp (number of seconds since 1/1/1970) of the device's current date and time, provided in decimal format.

Example:

    GET deviceTime
    OK 1690000000

### Set device date and time

* Request: `SET deviceTime [value]\n`
* Response: `OK\n`

Sets the device's current date and time as a UNIX timestamp (number of seconds since 1/1/1970), provided in decimal format.

Example:

    SET deviceTime 1690000000
    OK

### Get tube time

* Request: `GET tubeTime\n`
* Response: `OK [value]\n`

Returns the tube's life time in seconds, provided in decimal format.

Example:

    GET tubeTime
    OK 16000

### Set tube time

* Request: `SET tubeTime [value]\n`
* Response: `OK\n`

Sets the tube's life time in seconds, provided in decimal format.

Example:

    SET tubeTime 16000
    OK

### Get tube pulse count

* Request: `GET tubePulseCount\n`
* Response: `OK [value]\n`

Returns the tube's life pulse count, provided in decimal format.

Example:

    GET tubePulseCount
    OK 1500

### Set tube pulse count

* Request: `SET tubePulseCount [value]\n`
* Response: `OK\n`

Sets the tube's life pulse count, provided in decimal format.

Example:

    SET tubePulseCount 1500
    OK

### Get tube rate value

* Request: `GET tubeRate\n`
* Response: `OK [value]\n`

Returns the tube's instantaneous rate measured in counts per minute (cpm), provided in decimal format with three decimal places.

Example:

    GET tubeRate
    OK 0.315

For improved accuracy, perform two `GET tubePulseCount` measurements over a time period and divide the pulse count difference by the time period (in minutes).

### Get tube duty cycle

* Request: `GET tubeDutyCycle\n` 
* Response: `OK [value]\n`

Returns the tube's duty-cycle of the high-voltage generator, provided in decimal format with three decimal places.

Example:

    GET tubeDutyCycle
    OK 0.415

### Get tube conversion factor

* Request: `GET tubeConversionFactor\n`
* Response: `OK [value]\n`

Returns the tube's conversion factor in cpm/µSv/h, provided in decimal format with three decimal places.

Example:

    GET tubeConversionFactor
    OK 153.000

### Get tube dead-time measurement

* Request: `GET tubeDeadTime\n`
* Response: `OK [value]\n`

Returns the measured upper bound of the tube's dead-time in seconds, provided in decimal format with seven decimal places.

Example:

    GET tubeDeadTime
    OK 0.0002425

### Get tube dead-time compensation

* Request: `GET tubeDeadTimeCompensation\n`
* Response: `OK [value]\n`

Returns the tube's dead-time compensation factor in seconds, provided in decimal format with seven decimal places. Returns `0.0000000` if dead-time compensation is turned off.

Example:

    GET tubeDeadTimeCompensation
    OK 0.0002500

### Get data log

* Request: `GET datalog [value]\n`
* Response: `OK [data]\n`

Returns the data log stored in the device's flash memory. `[value]` is an optional UNIX timestamp (number of seconds since 1/1/1970), provided in decimal format, that limits the output to entries newer than this date and time. `[data]` is a list of records, separated by `;`; each record's fields are separated by `,`. The first record lists the field names, and the following records are actual measurements ordered from least recent to most recent. Valid fields include:

* `time`: The record's UNIX timestamp (number of seconds since 1/1/1970), provided in decimal format.
* `tubePulseCount`: The tube's life pulse count, provided in decimal format.

Example:

    GET datalog 1690000000
    OK time,tubePulseCount;1690000060,1542;1690000120,1618;1690000180,1693

### Get entropy data (from the random number generator)

* Request: `GET entropy\n`
* Response: `OK [value]\n`

Returns up to 16 entropy bytes from the random number generator, provided as hexadecimal digits (0-9, a-f).

Example:

    GET entropy
    OK 9155facb75c00e331cf7fd625102f37a

### Start bootloader

* Request: `START bootloader\n`
* Response: `OK\n`

On certain devices, starts the bootloader for performing firmware updates.

Example:

    START bootloader
    OK

### Invalid or erroneous requests

Invalid or erroneous requests yield an `ERROR` response.

Example:

    SET time
    ERROR