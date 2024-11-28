//Câmara de ionização em modo de descarga

usigned long pulse = 0;
+
void setup() {
  
  pinMode(8, OUTPUT);
  digitalWrite(8, HIGH); //Configuração alta no corpo da câmara
  Serial.begin(115200); //Comunicação serial

}

void loop() {
  
  pinMode(11, OUTPUT); //Preparação para alta
  digitalWrite(11, LOW); //Atraso de descarga (250)
  pulse(0); //Definir comprimento de pulso para zero
  pinMode(11, INPUT);//Início da carga
  
do {
  pulse++;
  }
  while (digitalRead(11)== LOW); //Estamos
carregando até que o Alto seja alcançado
  Serial.println(pulse); //Resultado enviado via serial
  delay(250);
}
