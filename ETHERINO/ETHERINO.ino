#include <SPI.h>
#include <Ethernet.h>
#include <LiquidCrystal.h>

// ------ BEGIN SHIELD ETHERNET ------
// replace the MAC address below by the MAC address printed on a sticker on the Arduino Shield 2
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

IPAddress ip(192, 168, 0, 177);     // endereco ip estatico para o shield
IPAddress gateway(192, 168, 0, 1);  // cabeca da rede
IPAddress subnet(255, 255, 255, 0); // mascara da rede
IPAddress myDns(8, 8, 8, 8);        // dns padrao google
EthernetServer server(80);          // cria um servidor WEB
// ------ END SHIELD ETHERNET ------

// ------ BEGIN LCD KEYPAD SHIELD ------
#define pinBotoesLCD A0
#define pinBackLight 43
#define pinEn 41
#define pinRs 39
#define pinD7 37
#define pinD6 35
#define pinD5 33
#define pinD4 31

LiquidCrystal lcd(pinRs, pinEn, pinD4, pinD5, pinD6, pinD7);

#define btnNENHUM 0
#define btnSELECT 1
#define btnLEFT   2
#define btnUP     3
#define btnDOWN   4
#define btnRIGHT  5

#define tempoDebounce 50

unsigned long delayBotao;
int estadoBotaoAnt = btnNENHUM;

void estadoBotao(int botao);
void botaoApertado(int botao);
void botaoSolto(int botao);
// ------ END LCD KEYPAD SHIELD ------

//Para o exemplo de uso
String descBotao[6] = {"", "SELECT", "LEFT", "DOWN", "UP", "RIGHT"};
int contador = 0;

void setup() {
    Serial.begin(9600);
  
// ------ BEGIN SHIELD ETHERNET ------
    Ethernet.begin(mac, ip, myDns, gateway, subnet); // inicializa shield
    server.begin(); // inicializa servidor
  
    if (Ethernet.hardwareStatus() == EthernetNoHardware) { // checa se shield esta conectado
        Serial.println("Ethernet shield was not found");
    }
    if (Ethernet.linkStatus() == LinkOFF) { // checa se cabo de rede esta conectado
        Serial.println("Ethernet cable is not connected.");
    }
    Serial.print("> Arduino IP address: ");
    Serial.println(Ethernet.localIP());
// ------ END SHIELD ETHERNET ------

// ------ BEGIN LCD KEYPAD SHIELD ------
  pinMode(pinBackLight, OUTPUT);
  digitalWrite(pinBackLight, HIGH);

  lcd.begin(16, 2);
// ------ END LCD KEYPAD SHIELD ------
  
} // fim do setup

void loop() {

// ------ BEGIN SHIELD ETHERNET ------
    EthernetClient client = server.available(); // tenta conectar com cliente
    notaDisponivel(client);
// ------ END SHIELD ETHERNET ------

// ------ BEGIN LCD KEYPAD SHIELD ------
    int valBotoes = analogRead(pinBotoesLCD);
    botaoClick(valBotoes);
// ------ END LCD KEYPAD SHIELD ------

} // fim do loop

void notaDisponivel(EthernetClient client) {
    if (client) { // cliente existe
        boolean currentLineIsBlank = true;
        while (client.connected()) {
            if (client.available()) { // os dados do cliente estão disponiveis para serem lidos
                char c = client.read(); // lê 1 byte (character) do cliente
                // a ultima linha da requisição do cliente é branca e termina com o caractere \n
                // responde para o cliente apenas após a última linha recebida
                if (c == '\n' && currentLineIsBlank) {
                    
                    // cabecalho de uma resposta http
                    client.println("HTTP/1.1 200 OK");
                    client.println("Content-Type: text/html");
                    client.println("Connection: close");
                    client.println();
                    
                    // pagina web
                    client.println("<!DOCTYPE html>");
                    client.println("<html>");
                    client.println("<head>");
                    client.println("<title>NOTAS POR TOM</title>");
                    client.println("</head>");
                    client.println("<body>");
                    client.println("<h1>HELLO WORLD!</h1>");
                    client.println("</body>");
                    client.println("</html>");
                    break;
                }
                // toda linha de texto recebida do cliente termina com os caracteres \r\n
                if (c == '\n') { // ultimo caractere da linha do texto recebido, iniciando nova linha com o novo caractere lido
                    currentLineIsBlank = true;
                } else if (c != '\r') { // um caractere de texto foi recebido do cliente
                    currentLineIsBlank = false;
                }
            } // fim do if (client.available())
        } // fim do while (client.connected())
        
        delay(1);      // da um tempo para o WEB Browser receber o texto
        client.stop(); // termina a conexão
        
    } // fim do if (client)
}

void botaoClick(int valBotoes) {
if ((valBotoes < 800) && (valBotoes >= 600)) {
        estadoBotao(btnSELECT);
    } else if ((valBotoes < 600) && (valBotoes >= 400)) {
        estadoBotao(btnLEFT);
    } else if ((valBotoes < 400) && (valBotoes >= 200)) {
        estadoBotao(btnUP);
    } else if ((valBotoes < 200) && (valBotoes >= 60)) {
        estadoBotao(btnDOWN);
    } else if  (valBotoes < 60) {
        estadoBotao(btnRIGHT);
    } else {
        estadoBotao(btnNENHUM);
    }
}

void estadoBotao(int botao) {
    // Quando um botao estiver apertado
//   if (botao != btnNENHUM) {
//      Serial.println(botao);
//   }
    //Quando o botao for apertado ou solto
    if ((millis() - delayBotao) > tempoDebounce) {
        if ((botao != btnNENHUM) && (estadoBotaoAnt == btnNENHUM) ) {
            botaoApertado(botao); 
            delayBotao = millis();
        }
        if ((botao == btnNENHUM) && (estadoBotaoAnt != btnNENHUM) ) {
            botaoSolto(estadoBotaoAnt); 
            delayBotao = millis();
        }
    }
    estadoBotaoAnt = botao;
}

void botaoApertado(int botao) {
    // Quando um botão for apertado

    // Para o exemplo de uso
    contador++;
    lcd.clear();
    lcd.print(descBotao[botao]);
    lcd.setCursor(14,0);
    lcd.print(contador);
    lcd.setCursor(0,1);
    lcd.print("apertado");
}

void botaoSolto(int botao) {
    //Quando um botão for solto


    // Para o exemplo de uso
    lcd.clear();
    lcd.print(descBotao[botao]);
    lcd.setCursor(14,0);
    lcd.print(contador);
    lcd.setCursor(0,1);
    lcd.print("solto");
}
