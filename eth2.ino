    #include <SPI.h>
    #include <Ethernet.h>
     
    byte mac[] = { 0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX }; //physical mac address(back of the ethernet shield)
    byte ip[] = { 192, 168, 1, 101 }; // ip in lan
    byte gateway[] = { 192, 168, 1, 1 }; // internet access via router
    byte subnet[] = { 255, 255, 255, 0 }; //subnet mask
    EthernetServer server(80); //server port
     
    String readString;
     
    void setup(){
     
      pinMode(2, OUTPUT); //pin selected to control
      //start Ethernet
      Ethernet.begin(mac, ip, gateway, subnet);
      server.begin();
      //enable serial data print
      Serial.begin(9600);
      Serial.println("server LED test 1.0"); // so I can keep track of what is loaded
    }
     
    void loop(){
      // Create a client connection
      EthernetClient client = server.available();
      if (client) {
        while (client.connected()) {
          if (client.available()) {
            char c = client.read();
     
            //read char by char HTTP request
            if (readString.length() < 100) {
     
              //store characters to string
              readString += c;
              //Serial.print(c);
            }
     
            //if HTTP request has ended
            if (c == '\n') {
     
              Serial.println(readString); //print to serial monitor for debuging
     
              client.println("HTTP/1.1 200 OK"); //send new page
              client.println("Content-Type: text/html");
              client.println();
     
              client.println("<HTML>");
              client.println("<HEAD>");
              client.println("<meta name='apple-mobile-web-app-capable' content='yes' />");
              client.println("<meta name='apple-mobile-web-app-status-bar-style' content='black-translucent' />");
              client.println("<link rel='stylesheet' type='text/css' href='http://url_with_css_file/a.css' />"); 
              //css file can be stored on ethernet's shield microSD or on external url 
              //In either case is optional and the sketch works ok!
              client.println("<TITLE>EKSM</TITLE>");
              client.println("</HEAD>");
              client.println("<BODY>");
              client.println("<H1>EKSM - UPatras</H1>");
              client.println("<hr />");
              client.println("<br />");
             
              client.println("<a href=\"/?lighton\"\">Turn On Light</a>");
              client.println("<a href=\"/?lightoff\"\">Turn Off Light</a><br />");        
     
              client.println("</BODY>");
              client.println("</HTML>");
     
              delay(1);
              //stopping client
              client.stop();
     
              // control arduino pin
              if(readString.indexOf("?lighton") >0){//checks for on

                digitalWrite(2, HIGH);    // set pin high
                Serial.println("Led On");
              }
              else{
              if(readString.indexOf("?lightoff") >0){//checks for off
                digitalWrite(2, LOW);    // set pin low
                Serial.println("Led Off");
              }
              }
              //clearing string for next read
              readString="";
     
            }
          }
        }
      }
    }
