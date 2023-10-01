## Self-destructing Arduino ESP32 Firmware - Stage 2

![Arduino ESP32 Self-destructing Firmware](/self-destructing-arduino-esp32-firmware-platformio.png)

> Is it possible to erase the firmware of an ESP32 from within itself? Let's try to find out.

If you want to erase the ESP32's flash content, the easiest way would be using `esptool.py` with the `erase_flash` parameter. But how we can do this from within the running Arduino Sketch?

## Installation

![PlatformIO](/platformio.png)

Open the `ESP32-SelfDestruct-Payload` project. Click on the _PlatformIO Icon_ on the sidebar. Under `General` click on `Build`.

Copy the `firmware.bin` file under the folder `.pio/build/{BOARD}/firmware.bin` into the `data` folder of the [ESP32-SelfDestruct](https://github.com/technopolistv/ESP32-SelfDestruct/) project.

Do _not_ upload this code to your ESP32! Just build the project and move the `firmware.bin` into the `data` folder of the `ESP32-SelfDestruct` project and read the [instructions](https://github.com/technopolistv/ESP32-SelfDestruct/).

## Demo Screenshot

The green part highlights the main firmware (Stage 1) and the red part the stub firmware (Stage 2).

![Serial Monitor Arduino ESP32 Self-destructing Firmware](/self-destruct-serial-monitor.png)

## Partition layout of Self-Destructing Firmware

<table>
<thead>
  <tr>
    <th>Offset</th>
    <th>Before Update</th>
    <th>After Update</th>
    <th>After Erase</th>
  </tr>
</thead>
<tbody>
  <tr>
    <td>0x9000</td>
    <td>NVS (Data)</td>
    <td>NVS (Data)</td>
    <td>NVS (Empty)</td>
  </tr>
  <tr>
    <td>0xe000</td>
    <td>OTA<br></td>
    <td>OTA</td>
    <td>OTA (Empty)</td>
  </tr>
  <tr>
    <td>0x10000</td>
    <td>APP0 (Firmware)</td>
    <td>APP0 (Firmware disabled)</td>
    <td>APP0 (Empty)</td>
  </tr>
  <tr>
    <td>0x150000</td>
    <td>APP1 (Empty)</td>
    <td>APP1 (Stub Firmware actived)</td>
    <td>APP1 (Stub Firmware)</td>
  </tr>
  <tr>
    <td>0x290000</td>
    <td>SPIFFS (Stub Firmware)</td>
    <td>SPIFFS (Stub Firmware)</td>
    <td>SPIFFS (Empty)</td>
  </tr>
</tbody>
</table>

## More
- Stage 1 - https://github.com/technopolistv/ESP32-SelfDestruct/
- Stage 2 - This Project

✍️ Blog: https://www.technopolis.tv/PlatformIO-Self-destructing-Arduino-ESP32-Firmware/