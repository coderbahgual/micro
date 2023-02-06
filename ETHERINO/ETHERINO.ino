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

// ------ BEGIN MIC ------
int in[128];
byte NoteV[13]={8,23,40,57,76,96,116,138,162,187,213,241,255}; // dpinMicata for note detection based on frequency
float f_peaks[5]; // top 5 frequencies peaks in descending order
int pinMic;
// ------ END MIC ------

int nota;
String notaABC;
String notaLCD;

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

// ------ BEGIN MIC ------
  pinMic = A7; // change as per Microphone   pin
// ------ END MIC ------
  
} // fim do setup

void loop() {

    EthernetClient client = server.available(); // tenta conectar com cliente
    notaDisponivel(client);

    int valBotoes = analogRead(pinBotoesLCD);
    botaoClick(valBotoes);

    lcd.setCursor(1,0);
    lcd.print("NOTAS POR TOM");

    nota = Tone_det();
    if (nota != -1) {
      notaABC = intToNotaAbcjs(nota);
      notaLCD = intToNotaLCD(nota);
      lcd.setCursor(7,1);
      lcd.print(notaLCD);
      Serial.println(notaABC);
    }

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
                    client.println("Server: Notas por Tom");
                    client.println("Connection: close");
                    client.println("Access-Control-Allow-Origin: *");
                    client.println("Content-Type: application/json; charset=utf-8");
                    client.println();
                    
                    // pagina web
                    client.print("{\"nota\": \"");
                    client.print(notaABC);
                    client.println("\"}");
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
            // botaoApertado(botao); 
            delayBotao = millis();
        }
        if ((botao == btnNENHUM) && (estadoBotaoAnt != btnNENHUM) ) {
            // botaoSolto(estadoBotaoAnt); 
            delayBotao = millis();
        }
    }
    estadoBotaoAnt = botao;
}

// void botaoApertado(int botao) {
//     // Quando um botão for apertado

//     // Para o exemplo de uso
//     contador++;
//     lcd.clear();
//     lcd.print(descBotao[botao]);
//     lcd.setCursor(14,0);
//     lcd.print(contador);
//     lcd.setCursor(0,1);
//     lcd.print("apertado");
// }

// void botaoSolto(int botao) {
//     //Quando um botão for solto


//     // Para o exemplo de uso
//     lcd.clear();
//     lcd.print(descBotao[botao]);
//     lcd.setCursor(14,0);
//     lcd.print(contador);
//     lcd.setCursor(0,1);
//     lcd.print("solto");
// }

int Tone_det() {
  long unsigned int a1,b,a2;
  float a;
  float sum1=0,sum2=0;
  float sampling;
  a1=micros();
  for(int i=0;i<128;i++){
    a=analogRead(pinMic)-500; //rough zero shift
    //utilising time between two sample for windowing & amplitude calculation
    sum1=sum1+a; //to average value
    sum2=sum2+a*a; // to RMS value
    a=a*(sin(i*3.14/128)*sin(i*3.14/128)); // Hann window
    in[i]=10*a; // scaling for float   to int conversion
    delayMicroseconds(195); // based on operation frequency range
  }
  b=micros();

  sum1=sum1/128;              // Average amplitude
  sum2=sqrt(sum2/128);        // RMS
  sampling= 128000000/(b-a1); // real time sampling frequency

  //for very low or no amplitude, this code wont start
  //it takes very small aplitude of sound to initiate for value sum2-sum1>3,   
  //change sum2-sum1 threshold based on requirement
  if(sum2-sum1>3){  
    FFT(128,sampling);        
    //EasyFFT based optimised  FFT code,   
    //this code updates f_peaks array with 5 most dominent frequency in descending   order
  
    for(int i=0;i<12;i++){in[i]=0;} // utilising in[] array for further   calculation

    int j=0,k=0; //below loop will convert frequency value to note   
    for(int i=0;i<5;i++){
      if(f_peaks[i]>1040)                           {f_peaks[i]=0;}
      if(f_peaks[i]>=65.4   && f_peaks[i]<=130.8)   {f_peaks[i]=255*((f_peaks[i]/65.4)-1);}
      if(f_peaks[i]>=130.8  && f_peaks[i]<=261.6)   {f_peaks[i]=255*((f_peaks[i]/130.8)-1);}
      if(f_peaks[i]>=261.6  && f_peaks[i]<=523.25)  {f_peaks[i]=255*((f_peaks[i]/261.6)-1);}
      if(f_peaks[i]>=523.25 && f_peaks[i]<=1046)    {f_peaks[i]=255*((f_peaks[i]/523.25)-1);}
      if(f_peaks[i]>=1046   && f_peaks[i]<=2093)    {f_peaks[i]=255*((f_peaks[i]/1046)-1);}
      if(f_peaks[i]>255)                            {f_peaks[i]=254;}
      j=1;k=0;
      while(j==1){
        if(f_peaks[i]<NoteV[k]){f_peaks[i]=k;j=0;}
          k++;  // a note with max peaks (harmonic) with aplitude priority is   selected
          if(k>15){j=0;}
      }
      if(f_peaks[i]==12){f_peaks[i]=0;}
      k=f_peaks[i];
      in[k]=in[k]+(5-i);
    }
    k=0;j=0;
    for(int i=0;i<12;i++){
      if(k<in[i]){k=in[i];j=i;} //Max value detection
    }
    // Note print
    // if you need to use note value for some application, use of note number recomendded
    // where, 0=c;1=c#,2=D;3=D#;.. 11=B;      
    // a2=micros(); // time   check
    k=j;
    // if(k==0) {Serial.println('C');}
    // if(k==1) {Serial.print('C');Serial.println('#');}
    // if(k==2) {Serial.println('D');}
    // if(k==3) {Serial.print('D');Serial.println('#');}
    // if(k==4) {Serial.println('E');}
    // if(k==5) {Serial.println('F');}
    // if(k==6) {Serial.print('F');Serial.println('#');}
    // if(k==7) {Serial.println('G');}
    // if(k==8) {Serial.print('G');Serial.println('#');}
    // if(k==9) {Serial.println('A');}
    // if(k==10){Serial.print('A');Serial.println('#');}
    // if(k==11){Serial.println('B');}
    return k;
  }
  return -1;
}

float FFT(byte N,float Frequency) {
  byte data[8]={1,2,4,8,16,32,64,128};
  int a,c1,f,o,x;
  a=N;  
  for(int i=0;i<8;i++) { //calculating the levels
    if(data[i]<=a){o=i;}
  }
  o=7;
  byte in_ps[data[o]]={};   //input for sequencing
  float out_r[data[o]]={};  //real part of transform
  float out_im[data[o]]={}; //imaginory part of transform

  x=0;  
  for(int b=0;b<o;b++){ // bit reversal
    c1=data[b];
    f=data[o]/(c1+c1);
    for(int   j=0;j<c1;j++){ 
      x=x+1;
      in_ps[x]=in_ps[j]+f;
    }
  }
  for(int i=0;i<data[o];i++){ //   update input array as per bit reverse order
    if(in_ps[i]<a){
      out_r[i]=in[in_ps[i]];
    }
    if(in_ps[i]>a){
      out_r[i]=in[in_ps[i]-a];
    }
  }

  int i10,i11,n1;
  float e,c,s,tr,ti;
  for(int   i=0;i<o;i++){ //fft
    i10=data[i];               // overall values of sine cosine  
    i11=data[o]/data[i+1];     // loop with similar sine cosine
    e=6.283/data[i+1];
    e=0-e;
    n1=0;

    for(int j=0;j<i10;j++){
      c=cos(e*j);   
      s=sin(e*j); 
      n1=j;
      for(int k=0;k<i11;k++){
        tr=c*out_r[i10+n1]-s*out_im[i10+n1];
        ti=s*out_r[i10+n1]+c*out_im[i10+n1];
        out_r[n1+i10]=out_r[n1]-tr;
        out_r[n1]=out_r[n1]+tr;
        out_im[n1+i10]=out_im[n1]-ti;
        out_im[n1]=out_im[n1]+ti;
        n1=n1+i10+i10;
      }       
    }
  }
  //---> here onward   out_r contains amplitude and our_in conntains frequency (Hz)
  for(int i=0;i<data[o-1];i++){ // getting amplitude from compex number
    out_r[i]=sqrt((out_r[i]*out_r[i])+(out_im[i]*out_im[i]));   // to  increase the speed delete sqrt
    out_im[i]=(i*Frequency)/data[o];
    /*
    Serial.print(out_im[i],2); Serial.print("Hz");
    Serial.print("\  ");                             // uncomment to print freuency bin    
    Serial.println(out_r[i]);   
    */
  }

  x=0; // peak detection
  for(int i=1;i<data[o-1]-1;i++){
    if(out_r[i]>out_r[i-1] && out_r[i]>out_r[i+1]){
      in_ps[x]=i;     //in_ps array used for storage of peak number
      x=x+1;
    }    
  }

  s=0;
  c=0;
  for(int i=0;i<x;i++){ // re arraange as per magnitude
    for(int j=c;j<x;j++){
      if(out_r[in_ps[i]]<out_r[in_ps[j]]){
        s=in_ps[i];
        in_ps[i]=in_ps[j];
        in_ps[j]=s;}
    }
    c=c+1;
  }
    
  for(int i=0;i<5;i++){ // updating   f_peak array (global variable)with descending order
    f_peaks[i]=(out_im[in_ps[i]-1]*out_r[in_ps[i]-1]+out_im[in_ps[i]]*out_r[in_ps[i]]+out_im[in_ps[i]+1]*out_r[in_ps[i]+1])
      /(out_r[in_ps[i]-1]+out_r[in_ps[i]]+out_r[in_ps[i]+1]);
  }
}

String intToNotaAbcjs(int n) {
    String notaRetorno = "";
    switch(n) {
        case  0: notaRetorno = "C";  break;
        case  1: notaRetorno = "^C"; break;
        case  2: notaRetorno = "D";  break;
        case  3: notaRetorno = "^D"; break;
        case  4: notaRetorno = "E";  break;
        case  5: notaRetorno = "F";  break;
        case  6: notaRetorno = "^F"; break;
        case  7: notaRetorno = "G";  break;
        case  8: notaRetorno = "^G"; break;
        case  9: notaRetorno = "A";  break;
        case 10: notaRetorno = "^A"; break;
        case 11: notaRetorno = "B";  break;
    }
    return notaRetorno;
}

String intToNotaLCD(int n) {
    String notaRetorno = "";
    switch(n) {
        case  0: notaRetorno = "C "; break;
        case  1: notaRetorno = "C#"; break;
        case  2: notaRetorno = "D "; break;
        case  3: notaRetorno = "D#"; break;
        case  4: notaRetorno = "E "; break;
        case  5: notaRetorno = "F "; break;
        case  6: notaRetorno = "F#"; break;
        case  7: notaRetorno = "G "; break;
        case  8: notaRetorno = "G#"; break;
        case  9: notaRetorno = "A "; break;
        case 10: notaRetorno = "A#"; break;
        case 11: notaRetorno = "B "; break;
    }
    return notaRetorno;
}
