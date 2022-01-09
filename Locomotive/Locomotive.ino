#include "Arduino.h"
#include "painlessMesh.h"

#define   MESH_PREFIX     "railnet"
#define   MESH_PASSWORD   "12345678"
#define   MESH_PORT       5555

const int MOTOR_PIN_1 = 18;
const int MOTOR_PIN_2 = 19;
const int DIRECTION_INV = 0;
const int PWM_FREQ = 20000;

const String LOCOMOTIVE_DESIGNATOR = "L1";

Scheduler userScheduler;
painlessMesh  mesh;

void sendMessage();

Task taskSendMessage(TASK_SECOND * 1 , TASK_FOREVER, &sendMessage);

void setup() {
  Serial.begin(115200);

  init_motor(MOTOR_PIN_1, MOTOR_PIN_2, PWM_FREQ);

  mesh.setDebugMsgTypes(ERROR | STARTUP);
  mesh.init(MESH_PREFIX, MESH_PASSWORD, &userScheduler, MESH_PORT );
  mesh.onReceive(&receivedCallback);
  mesh.onNewConnection(&newConnectionCallback);
  mesh.onChangedConnections(&changedConnectionCallback);
  mesh.onNodeTimeAdjusted(&nodeTimeAdjustedCallback);

  taskSendMessage.setInterval(TASK_SECOND * 1);
  userScheduler.addTask(taskSendMessage);
  taskSendMessage.enable();
}

void loop() {

  mesh.update();
}

void sendMessage() {
  String msg = LOCOMOTIVE_DESIGNATOR + "=ONLINE";
  mesh.sendBroadcast(msg);
}

void receivedCallback( uint32_t from, String &msg ) {
  Serial.printf("startHere: Received from %u msg=%s\n", from, msg.c_str());
  if (msg.substring(0, 2) == LOCOMOTIVE_DESIGNATOR) {
    int motor_speed = msg.substring(3, 7).toInt();
    Serial.println(motor_speed);
    set_motor_speed(motor_speed, DIRECTION_INV);
  }
}

void newConnectionCallback(uint32_t nodeId) {
  Serial.printf("--> startHere: New Connection, nodeId = %u\n", nodeId);
}

void changedConnectionCallback() {
  Serial.printf("Changed connections\n");
}

void nodeTimeAdjustedCallback(int32_t offset) {
  Serial.printf("Adjusted time %u. Offset = %d\n", mesh.getNodeTime(), offset);
}

void init_motor(int PIN_1, int PIN_2, int PWM_FREQ)
{
  ledcSetup(0, PWM_FREQ, 8);
  ledcAttachPin(PIN_1, 0);
  ledcSetup(1, PWM_FREQ, 8);
  ledcAttachPin(PIN_2, 1);
}

void motor_stop()
{
  ledcWrite(0, 0);
  ledcWrite(1, 0);
}

void set_motor_speed(int SPEED, int DIRECTION_INV)
{
  int actual_duty;
  motor_stop();
  if (SPEED < 0)
  {
    actual_duty = map(SPEED, 0, -100, 180, 255);
    ledcWrite(0 ^ DIRECTION_INV, actual_duty);
  }
  else if (SPEED > 0)
  {
    actual_duty = map(SPEED, 0, 100, 180, 255);
    ledcWrite(1 ^ DIRECTION_INV, actual_duty);
  }
}
