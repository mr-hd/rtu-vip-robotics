import controlP5.*;
import processing.serial.*;

ControlP5 cp5;
int myColor = color(255);
int c1,c2;
float n,n1;

Serial myPort;

void setup() {
  size(600,800);
  noStroke();
  
  String portName = Serial.list()[0];
  myPort = new Serial(this, portName, 115200); 
  
  cp5 = new ControlP5(this);
  
  cp5.addLabel("Locomotive 1")
    .setPosition(10,15)
    .setFont(createFont("arial", 20, true))
    ;
  cp5.addLabel("Locomotive 2")
    .setPosition(10,45)
    .setFont(createFont("arial", 20, true))
    ;
  cp5.addLabel("Points")
    .setPosition(10,75)
    .setFont(createFont("arial", 20, true))
    ;
  
  cp5.addButton("L1=0")
     .setValue(0)
     .setPosition(150,10)
     .setSize(80,30)
     .setFont(createFont("arial", 20, true))
     ;
   cp5.addButton("L1=25")
     .setValue(0)
     .setPosition(235,10)
     .setSize(80,30)
     .setFont(createFont("arial", 20, true))
     ;
   cp5.addButton("L1=50")
     .setValue(0)
     .setPosition(320,10)
     .setSize(80,30)
     .setFont(createFont("arial", 20, true))
     ;
   cp5.addButton("L1=75")
     .setValue(0)
     .setPosition(405,10)
     .setSize(80,30)
     .setFont(createFont("arial", 20, true))
     ;
   cp5.addButton("L1=100")
     .setValue(0)
     .setPosition(490,10)
     .setSize(80,30)
     .setFont(createFont("arial", 20, true))
     ;
   cp5.addButton("L2=0")
     .setValue(0)
     .setPosition(150,45)
     .setSize(80,30)
     .setFont(createFont("arial", 20, true))
     ;
   cp5.addButton("L2=25")
     .setValue(0)
     .setPosition(235,45)
     .setSize(80,30)
     .setFont(createFont("arial", 20, true))
     ;
   cp5.addButton("L2=50")
     .setValue(0)
     .setPosition(320,45)
     .setSize(80,30)
     .setFont(createFont("arial", 20, true))
     ;
   cp5.addButton("L2=75")
     .setValue(0)
     .setPosition(405,45)
     .setSize(80,30)
     .setFont(createFont("arial", 20, true))
     ;
   cp5.addButton("L2=100")
     .setValue(0)
     .setPosition(490,45)
     .setSize(80,30)
     .setFont(createFont("arial", 20, true))
     ;
   cp5.addButton("P1=0")
     .setValue(0)
     .setPosition(150,80)
     .setSize(80,30)
     .setFont(createFont("arial", 20, true))
     ;
   cp5.addButton("P1=1")
     .setValue(0)
     .setPosition(235,80)
     .setSize(80,30)
     .setFont(createFont("arial", 20, true))
     ;
   cp5.addButton("P2=0")
     .setValue(0)
     .setPosition(405,80)
     .setSize(80,30)
     .setFont(createFont("arial", 20, true))
     ;
   cp5.addButton("P2=1")
     .setValue(0)
     .setPosition(490,80)
     .setSize(80,30)
     .setFont(createFont("arial", 20, true))
     ;

  
}

void draw() {
  background(0);
}

public void controlEvent(ControlEvent theEvent) {
  String name = theEvent.getController().getName();
  println(name);
  name = name + "\n";
  myPort.write(name);
}
