# ros2arduino-test

## env

- Ubuntu Server 18.04 LTS
- Micro-XRCE-DDS-Agent v1.1.0
- ros2arduino v1.4.0

## setup

### RaspberryPi 4

1. ROS2 dashingをインストール
2. aptにて、ros-dashing-rosbridge-suiteをインストール
3. [こちら](https://micro-xrce-dds.docs.eprosima.com/en/latest/installation.html)を参考に、MicroXRCEDDS-Agentをインストール (`git checkout v1.1.0`をわすれないこと)

## usage

1. ラズパイ起動
2. Arduinoをラズパイに接続
3. ラズパイにログイン(192.168.100.110固定)
4. Websocketサーバ起動 `ros2 launch rosbridge_server rosbridge_websocket.py`
5. `LD_PRELOAD="/usr/local/lib/libfastrtps.so.1" MicroXRCEAgent serial --dev /dev/ttyUSB0 -b 115200`
6. ArduinoのRSTボタンを押す
