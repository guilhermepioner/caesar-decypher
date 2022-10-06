**[EN-US]**
# Caeser Decipher

This repository contains a console application that I developed in 2020, with a classmate during my high school years, in the subject of **Elements of Programming**. The idea of this project was to create an automatic decipher for the famous Caesar's Cipher.

## What would an automatic decipher be?

When I refer to an automatic decryptor in this repository, it means that the program should receive the encrypted message and, without any other information, be able to present the two most probable translations of it to the user.

## What approach was used?

o find the most probable answers, we used a system of weights for the most common letters in the Portuguese language, where the most common have a higher weight, and the less common have a lower weight.

When these letters appear, their weights are added to an overall sum for the current shift.

To find the best answers, just look for the shifted messages with the highest sum value; these will be the most likely to be correct.

## Options and How to Use

After the landing page, you are presented with two options:

1. [Cipher a message in Caesar to a text file](#cipher)
2. [Decipher a message in Caesar using a text file](#decipher)

### **Cipher**

For the first option, initially, it is necessary to choose which .txt file the user wants the encoded message to be saved to.

After that, simply enter the message to be encrypted and which shift should be applied.

### **Decipher**

For the second option, the user needs to select a .txt file that already contains an encrypted message, in uppercase letters and without spaces.

Having selected the file, there are two possible ways: decrypt it using brute force (lists all possible rotations) or try to decrypt it automatically using the method explained previously.

Regardless of the option chosen, the decryption results are saved in a **.txt file whose name is the same as the original file plus the suffix "_dec"**.

---

**[PT-BR]**
# Decodificador para a Cifra de César

Este repositório contém uma aplicação console que desenvolvi em 2020, com um colega durante meu ensino médio, na disciplina de **Elementos de Programação**. A ideia do projeto era criar um decifrador automático para a famosa Cifra de César.

## O que seria um decifrador automático?

Quando me refiro à um decifrador automático no presente repositório, significa que o programa deve receber a mensagem criptografada e, sem mais nenhuma informação, conseguir apresentar as duas traduções mais prováveis da mesma para o usuário.

## Qual foi a estratégia utilizada?

Para encontrarmos quais as respostas mais prováveis, usamos um
sistema de pesos paras as letras mais incidentes na língua portuguesa, onde as mais
comuns têm um peso maior, e as menos comuns têm um peso menor.

Quando essas letras aparecem, seus pesos são somados à uma soma geral para o deslocamento atual.

Para descobrir as melhores respostas, basta procurar as mensagens deslocadas com o
maior valor da soma geral, estas serão as mais prováveis de estarem corretas.

## Opções e como Utilizar

Após a landing page da aplicação, são apresentadas duas opções:

1. [Cifrar uma mensagem em César para um arquivo de texto](#cifrador)
2. [Decifrar uma mensagem em César utilizando um arquivo de texto](#decifrador)

### **Cifrador**

Para a primeira opção, inicialmente, é necessário escolher qual arquivo .txt o usuário deseja que a mensagem codificada seja salva.

Após isso, basta digitar a mensagem à ser criptografada e qual deslocamento deve ser aplicado.

### **Decifrador**

Para a segunda opção, o usuário precisa selecionar um arquivo .txt que já contenha uma mensagem criptografada, em letras maiúsculas e sem espaços.

Tendo selecionado o arquivo, existem dois caminhos: decodificar através de brute force (lista todas as rotações possíveis) ou tentar decifrar automaticamente através do método explicado anteriormente.

Independente da opção escolhida, os resultados da decodificação são salvos em um **arquivo .txt cujo nome é o mesmo do arquivo original acrescido do sufixo "_dec"**
