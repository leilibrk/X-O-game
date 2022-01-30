#include <LiquidCrystal.h>
#include <Keypad.h>
const int rs = 13, en = 12, d4 = 11, d5 = 10, d6 = 9, d7 = 8
;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
byte rowPins[ROWS] = {22, 23, 24, 25}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {26, 27, 28}; //connect to the column pinouts of the keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
char gameBoard[5][5] = {
  {' ','|',' ','|',' '},
  {'-','-','-','-','-'},
  {' ','|',' ','|',' '},
  {'-','-','-','-','-'},
  {' ','|',' ','|',' '},
};
boolean turn = true;
boolean win = false;
boolean lose = false;
boolean tie = false;
void setup() {
  pinMode(45,OUTPUT);
  pinMode(46,OUTPUT);
  pinMode(47,OUTPUT);
  pinMode(48,OUTPUT);
  pinMode(49,OUTPUT);
  pinMode(50,OUTPUT);
  pinMode(51,OUTPUT);
  pinMode(52,OUTPUT);
  pinMode(53,OUTPUT);
  Serial.begin(9600);
  lcd.begin(16, 4);
  lcd.clear();
  printBoard();
}

void loop() { 
  if(Serial.available()){
     char input = Serial.read();
     if(input == 'e'){ //end game
        turn = false;
        checkEnd();
        turnOnLeds();
          
     }
     else{
         turn = true;
         int p = input - '0';
         place(p, 'O');
         printBoard();                        
     }
  }

  if(turn){
     char k = keypad.getKey();  
     if (k){
        int p = k - '0';
        bool b = place(p, 'X'); 
        if(b){
          turn = false; 
          printBoard();
          Serial.write(k); 
          if(checkEnd()){
            Serial.write('e'); //end game
            turnOnLeds();
          } 
        }         
     }
  }
}
void printBoard(){
  lcd.clear();
  int n =0;
  for(int i = 0; i < 5; i+=2){
    for(int j = 0; j < 5; j++){
      lcd.setCursor(j,n);
      lcd.print(gameBoard[i][j]);
    }
    n++;
  }
}
bool place(int p, char c){
  if(p == 0){
    if(gameBoard[0][0] == ' '){
      gameBoard[0][0] = c;
    }
    else{
      return false;
    }
  }
  else if(p == 1){
    if(gameBoard[0][2] == ' '){
      gameBoard[0][2] = c;
    }
    else{
      return false;
    }
  }
  else if(p == 2){
    if(gameBoard[0][4] == ' '){
      gameBoard[0][4] = c;
    }
    else{
      return false;
    }
  }
  else if(p == 3){
    if(gameBoard[2][0] == ' '){
      gameBoard[2][0] = c;
    }
  }
  else if(p == 4){
    if(gameBoard[2][2] == ' '){
      gameBoard[2][2] = c;
    }
    else{
      return false;
    }
  }
  else if(p == 5){
    if(gameBoard[2][4] == ' '){
      gameBoard[2][4] = c;
    }
    else{
      return false;
    }
  }
  else if(p == 6){
    if(gameBoard[4][0] == ' '){
      gameBoard[4][0] = c;
    }
    else{
      return false;
    }
  }
  else if(p == 7){
    if(gameBoard[4][2] == ' '){
      gameBoard[4][2] = c;
    }
  }
  else if(p == 8){
    if(gameBoard[4][4] == ' '){
      gameBoard[4][4] = c;
    }
    else{
      return false;
    }
  }
  else{
    return false;
  }
  return true;
}
bool checkRow(){
  if(gameBoard[0][0] == 'X' && gameBoard[0][2] == 'X' && gameBoard[0][4] == 'X'){
    win = true;
    return true;
  }
  else if(gameBoard[2][0] == 'X' && gameBoard[2][2] == 'X' && gameBoard[2][4] == 'X'){
    win = true;
    return true;
  }
  else if(gameBoard[4][0] == 'X' && gameBoard[4][2] == 'X' && gameBoard[4][4] == 'X'){
    win = true;
    return true;
  }
  if(gameBoard[0][0] == 'O' && gameBoard[0][2] == 'O' && gameBoard[0][4] == 'O'){
    lose = true;
    return true;
  }
  else if(gameBoard[2][0] == 'O' && gameBoard[2][2] == 'O' && gameBoard[2][4] == 'O'){
    lose = true;
    return true;
  }
  else if(gameBoard[4][0] == 'O' && gameBoard[4][2] == 'O' && gameBoard[4][4] == 'O'){
    lose = true;
    return true;
  }
  return false;
}
bool checkColumn(){
  if(gameBoard[0][0] == 'X' && gameBoard[2][0] == 'X' && gameBoard[4][0] == 'X'){
    win = true;
    return true;
  }
  if(gameBoard[0][2] == 'X' && gameBoard[2][2] == 'X' && gameBoard[4][2] == 'X'){
    win = true;
    return true;
  }
  if(gameBoard[0][4] == 'X' && gameBoard[2][4] == 'X' && gameBoard[4][4] == 'X'){
    win = true;
    return true;
  }
  if(gameBoard[0][0] == 'O' && gameBoard[2][0] == 'O' && gameBoard[4][0] == 'O'){
    lose = true;
    return true;
  }
  if(gameBoard[0][2] == 'O' && gameBoard[2][2] == 'O' && gameBoard[4][2] == 'O'){
    lose = true;
    return true;
  }
  if(gameBoard[0][4] == 'O' && gameBoard[2][4] == 'O' && gameBoard[4][4] == 'O'){
    lose = true;
    return true;
  }
  return false;
}
bool checkDiagonal(){
  if(gameBoard[0][0] == 'X' && gameBoard[2][2] == 'X' && gameBoard[4][4] == 'X'){
    win = true;
    return true;
  }
  if(gameBoard[0][0] == 'O' && gameBoard[2][2] == 'O' && gameBoard[4][4] == 'O'){
    lose = true;
    return true;
  }
  if(gameBoard[0][4] == 'X' && gameBoard[2][2] == 'X' && gameBoard[4][0] == 'X'){
    win = true;
    return true;
  }
  if(gameBoard[0][4] == 'O' && gameBoard[2][2] == 'O' && gameBoard[4][0] == 'O'){
    lose = true;
    return true;
  }
  return false;
}
bool checkEnd(){
   if(checkRow() || checkColumn() || checkDiagonal() ) {
      return true;
   }
   if(gameBoard[0][0] != ' ' && gameBoard[0][2] != ' ' && gameBoard[0][4] != ' '  && gameBoard[2][0] != ' ' && gameBoard[2][2] != ' ' && gameBoard[2][4] != ' ' &&
       gameBoard[4][0] != ' ' && gameBoard[4][2] != ' ' && gameBoard[4][4] != ' '){
        tie = true;
        return true;
   }
   return false;
}
void turnOnLeds(){
  if(win){
    lcd.setCursor(0,3);
    lcd.print("You won :)");
    digitalWrite(45, HIGH);
    digitalWrite(47, HIGH);
    digitalWrite(49, HIGH);
    digitalWrite(51, HIGH);
    digitalWrite(53, HIGH);
  }
  if(lose){
    lcd.setCursor(0,3);
    lcd.print("You lost :(");
    digitalWrite(46, HIGH);
    digitalWrite(48, HIGH);
    digitalWrite(50, HIGH);
    digitalWrite(52, HIGH);
  }
  if(tie){
    lcd.setCursor(0,3);
    lcd.print("Tie!!");
    digitalWrite(45, HIGH);
    digitalWrite(46, HIGH);
    digitalWrite(47, HIGH);
    digitalWrite(49, HIGH);
    digitalWrite(52, HIGH);
  }
}
