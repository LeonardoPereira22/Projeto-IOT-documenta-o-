#include <LiquidCrystal.h>
#include <Servo.h>

LiquidCrystal lcd(7, 6, 5, 4, 9, 8);

Servo porta;

// PINOS

const int servoPin = 10;

const int ledVerde = 12;
const int ledVermelho = 13;

const int botaoSenha = A0;
const int botaoReset = 2;

// SENHA

String senhaCorreta = "0101";
String senhaDigitada = "";

// CONTROLE

int tentativas = 0;

bool bloqueado = false;

volatile bool resetar = false;

// INTERRUPCAO

void interrupcaoReset() {

  resetar = true;
}

// SETUP

void setup() {

  pinMode(ledVerde, OUTPUT);
  pinMode(ledVermelho, OUTPUT);

  pinMode(botaoSenha, INPUT_PULLUP);
  pinMode(botaoReset, INPUT_PULLUP);

  lcd.begin(16,2);

  delay(500);

  porta.attach(servoPin);

  porta.write(0);

  attachInterrupt(
    digitalPinToInterrupt(botaoReset),
    interrupcaoReset,
    FALLING
  );

  // TELA INICIAL

  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print("LOCKER FEI");

  lcd.setCursor(0,1);
  lcd.print("Inicializando");

  delay(2000);

  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print("Curto = 0");

  lcd.setCursor(0,1);
  lcd.print("Longo = 1");

  delay(3000);

  fecharCofre();
}

// LOOP

void loop() {

  if(resetar) {

    sistemaReset();
  }

  if(bloqueado) {

    modoBloqueio();

    return;
  }

  verificarBotaoSenha();
}

// BOTAO SENHA

void verificarBotaoSenha() {

  if(digitalRead(botaoSenha) == LOW) {

    delay(50);

    if(digitalRead(botaoSenha) == LOW) {

      unsigned long tempoInicio = millis();

      while(digitalRead(botaoSenha) == LOW) {
        delay(10);
      }

      unsigned long duracao = millis() - tempoInicio;

      // CURTO

      if(duracao < 1000) {

        senhaDigitada += "0";

        lcd.clear();

        lcd.setCursor(0,0);
        lcd.print("Curto = 0");
      }

      // LONGO

      else {

        senhaDigitada += "1";

        lcd.clear();

        lcd.setCursor(0,0);
        lcd.print("Longo = 1");
      }

      lcd.setCursor(0,1);
      lcd.print("Senha:");
      lcd.print(senhaDigitada);

      delay(500);

      // VERIFICA

      if(senhaDigitada.length() == 4) {

        lcd.clear();

        lcd.setCursor(0,0);
        lcd.print("Verificando");

        lcd.setCursor(0,1);
        lcd.print("Senha...");

        delay(1000);

        if(senhaDigitada == senhaCorreta) {

          acessoLiberado();
        }

        else {

          acessoNegado();
        }

        senhaDigitada = "";
      }
    }
  }
}

// FECHAR

void fecharCofre() {

  porta.write(0);

  digitalWrite(ledVerde, LOW);
  digitalWrite(ledVermelho, HIGH);

  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print("COFRE FECHADO");

  lcd.setCursor(0,1);
  lcd.print("Digite senha");
}

// ABRIR

void abrirCofre() {

  porta.write(90);
}

// ACESSO LIBERADO

void acessoLiberado() {

  abrirCofre();

  digitalWrite(ledVerde, HIGH);
  digitalWrite(ledVermelho, LOW);

  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print("ACESSO");

  lcd.setCursor(0,1);
  lcd.print("LIBERADO");

  delay(4000);

  tentativas = 0;

  fecharCofre();
}

// ACESSO NEGADO

void acessoNegado() {

  tentativas++;

  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print("SENHA ERRADA");

  lcd.setCursor(0,1);

  lcd.print("Tentativa ");
  lcd.print(tentativas);

  for(int i = 0; i < 3; i++) {

    digitalWrite(ledVermelho, HIGH);

    delay(200);

    digitalWrite(ledVermelho, LOW);

    delay(200);
  }

  if(tentativas >= 3) {

    bloqueado = true;
  }

  else {

    fecharCofre();
  }
}

// BLOQUEIO

void modoBloqueio() {

  for(int tempo = 15; tempo > 0; tempo--) {

    lcd.clear();

    lcd.setCursor(0,0);
    lcd.print("BLOQUEADO");

    lcd.setCursor(0,1);

    lcd.print("Espere ");
    lcd.print(tempo);
    lcd.print("s");

    digitalWrite(ledVermelho, HIGH);

    delay(500);

    digitalWrite(ledVermelho, LOW);

    delay(500);
  }

  bloqueado = false;

  tentativas = 0;

  fecharCofre();
}

// RESET

void sistemaReset() {

  resetar = false;

  bloqueado = false;

  tentativas = 0;

  senhaDigitada = "";

  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print("RESETANDO");

  lcd.setCursor(0,1);
  lcd.print("SISTEMA");

  delay(2000);

  fecharCofre();
}