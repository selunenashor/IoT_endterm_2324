# Hướng dẫn sử dụng 
## Yêu cầu
#### Phần cứng
- Module Wifi NodeMCU ESP8266
- DHT11 Temperature and Humidity Sensor
- USB to MicroUSB cable
#### Phần mềm
- Arduino IDE. Link tải: https://www.arduino.cc/en/software
- Python và các package liên quan: Flask, requests
```
pip install Flask requests
```
## Hướng dẫn sử dụng
#### Nối mạch
- GND ESP8266 -> GND DHT11
- 3.3V ESP8266 -> VCC DHT11
- D1 ESP8266 -> DATA DHT11
- Nối ESP8266 và PC bằng cable USB to MicroUSB
#### Code
**1. Import ESP8266 Board Manager**
- **File** > **Preferences**
- Tại phần **Additional boards manager URLs**, thêm link sau rồi bấm **OK**
```
http://arduino.esp8266.com/stable/package_esp8266com_index.json
```
- **Tools** > **Board** > **Boards Manager...**
- Tìm kiếm package **esp8266** của _ESP8266 Community_ và install.
- **Tools** > **Board** > **esp8266** > **NodeMCU 1.0 (ESP-12E Module)**
- **Tools** > **Ports** > chọn port kết nối (**COMX** với Windows hoặc **/dev/ttyUSBX** với Linux/macOS)

**2. Code**
Sử dụng code đã có trong file `esp8266_dht11_http.ino` (nhớ thay giá trị cho các biến)

**3. Run**
- Import code vào ESP8266
