void loop() {
  if(wb==0){
    Firebase.getString(FirebaseDataObj, "wifiorbluetooth");
    ch= FirebaseDataObj.stringData();
    if(ch=="1"){
        x=1;
        EEPROM.write(0,x);
        ESP.restart();
    }
    Firebase.getString(FirebaseDataObj, "engine");
    ch1= FirebaseDataObj.stringData();  
    if(ch1=="o"){
        digitalWrite(ENGINE, HIGH);
      }
    else if(ch1=="l"){
        digitalWrite(ENGINE, HIGH);
      }
    }
    
  }
  if(wb==1){
      if(SerialBT.available()){
        ch1= SerialBT.read();
        Serial.print("received data: ");
        Serial.println(ch1);
      }
    delay(20);
    if(ch1=="0"){
        x=0;
        EEPROM.write(0,x);
        ESP.restart();
      }
    if(ch1=="o"){
        digitalWrite(ENGINE, HIGH);
      }
    else if(ch1=="1"){
        digitalWrite(ENGINE, HIGH);
      }
    
    }
   
}

void irsense(){
    digitalWrite(ENGINE,LOW);
  }

void dhtsense(void *parameter)
{
  while(1){
    temp= dht1.readTemperature();
    Serial.print("temperature= ");
    Serial.println(temp);
    vTaskDelay(5000);
    if(wb==0){
      Firebase.setFloat(FirebaseDataObj,"TEMPERATURE_CAR",temp);
    }
    if(wb==1 && ch1=="t"){
        SerialBT.println(temp);
      }
  } 
}

void rainsense(void *parameter)
{
  if(wb==1 && ch1=="r"){
  while(1){
    rain= digitalRead(34);
    Serial.print("rain sensor= ");
    Serial.println(rain);
    SerialBT.println(rain);
    vTaskDelay(10000);
  } 
  }
}

void ultrasense(void *parameter)
{ 
  if(wb==1 && ch1=="u"){
  while(1){
    digitalWrite(trig,LOW);
    digitalWrite(trig,HIGH);
    delayMicroseconds(10);
    digitalWrite(trig,LOW);
    t1=pulseIn(echo,HIGH);
    distance=(0.034 * t1)/2;
    delay(500);
    Serial.println(distance);
    SerialBT.println(distance);
  }
  }
}
