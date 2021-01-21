#include <M5Stack.h>
#include <ros2arduino.h>

#define XRCEDDS_PORT Serial
#define STATE_STOP 0
#define STATE_GOAHEAD 1
#define STATE_BACKOFF 2
#define STATE_TURNRIGHT 3
#define STATE_TURNLEFT 4

int state = STATE_STOP;

void cb_goAhead(std_msgs::Empty *msg, void *arg) {
  (void)(arg);

  state = STATE_GOAHEAD;
}
void cb_backOff(std_msgs::Empty *msg, void *arg) {
  (void)(arg);

  state = STATE_BACKOFF;
}
void cb_turnRight(std_msgs::Empty *msg, void *arg) {
  (void)(arg);

  state = STATE_TURNRIGHT;
}
void cb_turnLeft(std_msgs::Empty *msg, void *arg) {
  (void)(arg);

  state = STATE_TURNLEFT;
}
void cb_allStop(std_msgs::Empty *msg, void *arg) {
  (void)(arg);

  state = STATE_STOP;
}

class LedSub : public ros2::Node
{
public:
  LedSub()
      : Node("ros2arduino_sub_node")
  {
    this->createSubscriber<std_msgs::Empty>("nexus4wd/goAhead", (ros2::CallbackFunc)cb_goAhead, nullptr);
    this->createSubscriber<std_msgs::Empty>("nexus4wd/backOff", (ros2::CallbackFunc)cb_backOff, nullptr);
    this->createSubscriber<std_msgs::Empty>("nexus4wd/turnRight", (ros2::CallbackFunc)cb_turnRight, nullptr);
    this->createSubscriber<std_msgs::Empty>("nexus4wd/turnLeft", (ros2::CallbackFunc)cb_turnLeft, nullptr);
    this->createSubscriber<std_msgs::Empty>("nexus4wd/allStop", (ros2::CallbackFunc)cb_allStop, nullptr);
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
  switch(state) {
    case STATE_GOAHEAD:
      break;
      M5.Lcd.print("state: f");
    case STATE_BACKOFF:
      break;
      M5.Lcd.print("state: b");
    case STATE_TURNRIGHT:
      break;
      M5.Lcd.print("state: r");
    case STATE_TURNLEFT:
      break;
      M5.Lcd.print("state: l");
    case STATE_STOP:
    default:
      M5.Lcd.print("state: s");
  }

  ros2::spin(&LedNode);
  //delay(500);
}