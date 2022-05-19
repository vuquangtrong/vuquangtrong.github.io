#include <Preferences.h>
Preferences preferences;

#define NS_ACCOUNT "account"
#define KEY_USER "user"
#define KEY_PASSWD "passwd"

/*
 account {
    user: XXX
    passwd: YYY
 }
*/

String user;
String passwd;
String passwd2;

void input(String& prompt, String& str) {
  str = "";
  Serial.print(prompt);
  while(str == ""){
    str = Serial.readString();
  }
  Serial.println(str);
}

void addUser() {
  while(true) {
    String prompt="Enter Username: ";
    input(prompt, user);
    
    prompt="Enter Password: ";
    input(prompt, passwd);
    
    prompt="Retry Password: ";
    input(prompt, passwd2);
    
    if (passwd == passwd2) {
      int r = -1;
      Serial.println("Save new account: " + user + " / " + passwd);
      r = preferences.putString(KEY_USER, user);
      if (r == 0) Serial.println("Can NOT user!");
      
      r = preferences.putString(KEY_PASSWD, passwd);
      if (r == 0) Serial.println("Can NOT passwd!");
      
      preferences.end();
      delay(1000);

      ESP.restart();
    }
  }
}

void askPassword() {
  Serial.println("Welcome " + user + "!");

  passwd = preferences.getString(KEY_PASSWD);

  int trial = 3;
  String prompt="Enter Password: ";
  
  while(trial > 0) {  
    input(prompt, passwd2);
    trial--;
    
    if(passwd == passwd2) {
      break;
    }
  }

  if (trial > 0) {
    Serial.println("Logged in! You can change user!");
    addUser();
  } else {
    Serial.println("LOCKED!");
    while(true){}
  }
}

void setup() {
  Serial.begin(115200);
  while (!Serial) {}
  
  // open namespace NS_ACCOUNT with readOnly = false
  preferences.begin(NS_ACCOUNT, false);
  
  user = preferences.getString(KEY_USER);
  if (user == "") {
    Serial.println("No user found!");
    addUser();
  } 
  else {
    askPassword();
  }
}

void loop() {
  delay(1000);
}
