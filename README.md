# Locker Inteligente com Feedback Multissensorial

Projeto desenvolvido para a disciplina CCM520 – Internet das Coisas do Centro Universitário FEI.

## Descrição do Projeto

O projeto consiste em um sistema de controle de acesso para um locker/cofre inteligente utilizando Arduino Uno. O sistema realiza autenticação por senha temporal usando apenas um botão, além de fornecer feedback visual através do LCD, LEDs e movimentação física utilizando um servomotor.

O objetivo é simular o funcionamento de um cofre eletrônico inteligente com controle de acesso, bloqueio de segurança e interação intuitiva com o usuário.

---

# Funcionalidades

- Sistema de senha utilizando tempo de clique
- LCD 16x2 para mensagens e instruções
- Servomotor simulando a abertura da porta do cofre
- LED verde indicando acesso liberado
- LED vermelho indicando acesso negado/cofre fechado
- Sistema de bloqueio após 3 tentativas erradas
- Contagem regressiva de segurança no LCD
- Botão de reset utilizando interrupção externa
- Interface dinâmica e intuitiva para o usuário

---

# Funcionamento da Senha

A senha é baseada na duração do clique do botão:

- Clique curto (< 1 segundo) = 0
- Clique longo (> 1 segundo) = 1

Senha padrão configurada:

0101

Exemplo:
- clique curto
- clique longo
- clique curto
- clique longo

---

# Componentes Utilizados

- Arduino Uno
- LCD 16x2
- Potenciômetro 10kΩ
- Servo Motor SG90
- 2 LEDs
- 2 resistores 220Ω
- 2 botões
- Protoboard
- Jumpers

---

# Ligações do LCD

| LCD | Arduino |
|------|----------|
| GND | GND |
| VCC | 5V |
| VO | Pino central do potenciômetro |
| RS | D7 |
| RW | GND |
| E | D6 |
| DB4 | D5 |
| DB5 | D4 |
| DB6 | D9 |
| DB7 | D8 |
| A | 5V |
| K | GND |

---

# Ligações do Potenciômetro

| Potenciômetro | Ligação |
|---|---|
| ponta esquerda | GND |
| pino central | VO do LCD |
| ponta direita | 5V |

---

# Ligações do Servo Motor

| Servo | Arduino |
|---|---|
| Sinal | D10 |
| VCC | 5V |
| GND | GND |

---

# Ligações dos LEDs

## LED Verde

| LED | Arduino |
|---|---|
| positivo | D12 |
| negativo | resistor 220Ω → GND |

## LED Vermelho

| LED | Arduino |
|---|---|
| positivo | D13 |
| negativo | resistor 220Ω → GND |

---

# Ligações dos Botões

## Botão Senha

| Botão | Arduino |
|---|---|
| um lado | A0 |
| outro lado | GND |

## Botão Reset

| Botão | Arduino |
|---|---|
| um lado | D2 |
| outro lado | GND |

---

# Estados do Sistema

## Cofre Fechado
- LED vermelho ligado
- LCD solicita a senha

## Acesso Liberado
- Servo abre a porta
- LED verde acende
- LCD informa acesso autorizado

## Senha Incorreta
- LED vermelho pisca
- LCD informa tentativa inválida

## Sistema Bloqueado
- Ativado após 3 erros consecutivos
- LCD exibe contagem regressiva
- Usuário deve aguardar para tentar novamente

## Reset do Sistema
- Reinicia completamente o sistema
- Limpa tentativas e senha digitada

---

# Objetivos da Disciplina Atendidos

- Integração de múltiplos periféricos
- Uso de sinais digitais
- Uso de interrupções externas
- Desenvolvimento de interface homem-máquina
- Implementação de lógica de estados
- Sistema embarcado com autenticação
- Feedback visual e físico ao usuário

Circuito no Tinkercad 

<img width="1157" height="681" alt="iot" src="https://github.com/user-attachments/assets/4bd84129-5039-43f4-90e9-e8b148e827cb" />

