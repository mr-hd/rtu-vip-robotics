#include "painlessMesh.h"

#define   MESH_PREFIX     "railnet"
#define   MESH_PASSWORD   "12345678"
#define   MESH_PORT       5555

Scheduler userScheduler;
painlessMesh  mesh;

void sendMessage();

//Task taskSendMessage(TASK_SECOND * 1 , TASK_FOREVER, &sendMessage);

void setup() {
  pinMode(2, OUTPUT);
  digitalWrite(2, HIGH);
  Serial.begin(115200);
  mesh.setDebugMsgTypes(ERROR | STARTUP);
  mesh.init(MESH_PREFIX, MESH_PASSWORD, &userScheduler, MESH_PORT );
  mesh.onReceive(&receivedCallback);
  mesh.onNewConnection(&newConnectionCallback);
  mesh.onChangedConnections(&changedConnectionCallback);
  mesh.onNodeTimeAdjusted(&nodeTimeAdjustedCallback);

  Serial2.begin(9600, SERIAL_8N1, 16, 17);

  //userScheduler.addTask(taskSendMessage);
  //taskSendMessage.enable();
}

void loop() {
  while (Serial.available()) {
    String a = Serial.readString();
    sendMessage(a);
    Serial.println(a);
    if(a.substring(0, 4) == "P1=0"){
      Serial.println(a.substring(0, 4));
      Serial2.println(a.substring(0, 4));
    }
    if(a.substring(0, 4) == "P1=1"){
      Serial.println(a.substring(0, 4));
      Serial2.println(a.substring(0, 4));
    }
    if(a.substring(0, 4) == "P2=0"){
      Serial.println(a.substring(0, 4));
      Serial2.println(a.substring(0, 4));
    }
    if(a.substring(0, 4) == "P2=1"){
      Serial.println(a.substring(0, 4));
      Serial2.println(a.substring(0, 4));
    }
  }
  mesh.update();
}

void sendMessage(String msg) {
  digitalWrite(2, HIGH);
  //String msg = "L1=";
  //msg += random(-100, 100);
  mesh.sendBroadcast(msg);
  //taskSendMessage.setInterval(random(TASK_SECOND * 1, TASK_SECOND * 5 ));
  digitalWrite(2, LOW);
}

void receivedCallback( uint32_t from, String &msg ) {
  //Serial.printf("startHere: Received from %u msg=%s\n", from, msg.c_str());
  Serial.println(msg);
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
