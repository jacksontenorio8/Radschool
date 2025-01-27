//Câmara de ionização em modo de descarga

#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

// Configurações do display Nokia 5110
#define PIN_SCE 5
#define PIN_RST 4
#define PIN_DC 16
#define PIN_SDIN 17
#define PIN_SCLK 18
Adafruit_PCD8544 display = Adafruit_PCD8544(PIN_SCLK, PIN_SDIN, PIN_DC, PIN_SCE, PIN_RST);

// Configurações do circuito
#define PUSH_BUTTON_PIN 13 // Pino do botão push para ligar o sistema
#define ADC_PIN 34         // Pino ADC para leitura da tensão do circuito (usando o GPIO34 para ESP32 na IDE Arduino)

bool systemOn = false; // Estado do sistema (ligado/desligado)
unsigned long previousMillis = 0;
const long interval = 1000; // Intervalo de 1 segundo
int graphData[84];         // Dados do gráfico (84 pontos para o display)

void setup() {
  pinMode(PUSH_BUTTON_PIN, INPUT_PULLUP); // Configura o botão push como entrada com pull-up
  display.begin();                        // Inicializa o display Nokia 5110
  display.setContrast(50);               // Define o contraste do display
  display.clearDisplay();
  display.display();

  // Mensagem inicial
  display.setTextSize(1);
  display.setTextColor(BLACK);
  display.setCursor(0, 0);
  display.println("Sistema Desligado");
  display.display();
}

void loop() {
  // Verifica o estado do botão push
  if (digitalRead(PUSH_BUTTON_PIN) == LOW) {
    systemOn = !systemOn; // Altera o estado do sistema
    delay(300);           // Debounce para evitar leituras múltiplas
  }

  if (systemOn) {
    unsigned long currentMillis = millis();

    // Atualiza o display com "Sistema Ligado"
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("Sistema Ligado");

    // Verifica se 1 segundo se passou
    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;

      // Lê a tensão do circuito (simulando radiação)
      int adcValue = analogRead(ADC_PIN); // Leitura do ADC
      float voltage = (adcValue / 4095.0) * 3.3; // Converte para tensão (3.3V)

      // Desloca os dados do gráfico para a esquerda
      for (int i = 0; i < 83; i++) {
        graphData[i] = graphData[i + 1];
      }

      // Adiciona o novo dado no final do gráfico
      graphData[83] = map(voltage * 100, 0, 330, 0, 47); // Escala para o display (0-47 pixels)
    }

    // Desenha o gráfico no display
    for (int x = 0; x < 84; x++) {
      display.drawLine(x, 47, x, 47 - graphData[x], BLACK); // Desenha linhas do gráfico
    }

    display.display();
  } else {
    // Atualiza o display com "Sistema Desligado"
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("Sistema Desligado");
    display.display();
  }
}
