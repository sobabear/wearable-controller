#include <Keyboard.h>



const int joystick_x = A1;
const int joystick_y = A0;
void setup() {
  // put your setup code here, to run once:
  Keyboard.begin();

}

void loop() {
  // put your main code here, to run repeatedly:
  int x_Read = analogRead(joystick_x);
  if( x_Read <= 340 ) {
      Keyboard.press( KEY_LEFT_ARROW );
      } 
      else if ( x_Read >= 660 ) {
      Keyboard.press( KEY_RIGHT_ARROW );
      }
      else{
        Keyboard.release( KEY_LEFT_ARROW );
        Keyboard.release( KEY_RIGHT_ARROW );
      }

      int y_Read = analogRead(joystick_y) ;
      if ( y_Read <= 340 ) {
      Keyboard.press( KEY_UP_ARROW );
      }
      else if ( y_Read >= 660 ) {
      Keyboard.press( KEY_DOWN_ARROW );
      }
      else{
        Keyboard.release( KEY_DOWN_ARROW );
        Keyboard.release( KEY_UP_ARROW );
      }
      Serial.print("X : "); Serial.println(x_Read); 
      Serial.print("Y : "); Serial.println(y_Read);


}
