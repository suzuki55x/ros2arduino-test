#include <M5Stack.h>
#include <ros2arduino.h>

#define XRCEDDS_PORT Serial

bool is_enable = false;

void subscribeLed(std_msgs::Empty *msg, void *arg)
{
  (void)(arg);

  is_enable = !is_enable;
  //is_enable = true;
  //M5.Lcd.print("hoge");
  //digitalWrite(LED_BUILTIN, msg->data);
}

class LedSub : public ros2::Node
{
public:
  LedSub()
      : Node("ros2arduino_sub_node")
  {
    this->createSubscriber<std_msgs::Empty>("chatter", (ros2::CallbackFunc)subscribeLed, nullptr);
  }
};

void setup()
{
  M5.begin();
  M5.Lcd.println("begin");
  XRCEDDS_PORT.begin(115200);
  while (!XRCEDDS_PORT) ;

  M5.Lcd.println("port");
  ros2::init(&XRCEDDS_PORT);
  M5.Lcd.println("start");
}

void loop()
{
  static LedSub LedNode;

  M5.Lcd.setCursor(10, 100);
  if (is_enable) {
    M5.Lcd.print("hoge");
  } else {
    M5.Lcd.print("fuga");
  }

  ros2::spin(&LedNode);
  //delay(500);
}