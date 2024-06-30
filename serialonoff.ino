void setup() {
  pinMode(33,OUTPUT);
  pinMode(4,OUTPUT);
  digitalWrite(33, LOW);
  digitalWrite(4,LOW);
  Serial.begin(9600);

}

void loop() {
  char in_char;
if (Serial.available())
{
    in_char = Serial.read();
  if (in_char == 'A')
  {
  digitalWrite(33,HIGH);
  Serial.println( " A recd L1 ON");
   }
  if (in_char == 'a')
  {
  digitalWrite(33,LOW);
  Serial.println( " a recd L1 OFF");
   }
   
   if (in_char == 'B')
  {
  digitalWrite(4,HIGH);
  Serial.println( " B recd L2 ON");
   }
   
    if (in_char == 'b')
  {
  digitalWrite(4,LOW);
  Serial.println( " b recd L2 OFF");
   }
   
    if (in_char == 'Z')
  {
  digitalWrite(33,HIGH);
  digitalWrite(4,HIGH);
  Serial.println( " Z recd L1 and L2 ON");
   }
   
    if (in_char == 'z')
  {
  digitalWrite(4,LOW);
  Serial.println( " z recd L1 and L2 OFF");
   }
  }
}
