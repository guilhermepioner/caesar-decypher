**[EN-US]**
# Caeser Decypher

> TBD - Some English Content

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

1. [Cifrar uma mensagem em César utilizando um arquivo de texto](#cypher-1)
2. [Decifrar uma mensagem em César utilizando um arquivo de texto](#decypher-2)

<h3 id="cypher-1"><strong>Cifrador</strong></h3>

Para a primeira opção, inicialmente, é necessário escolher qual arquivo .txt o usuário deseja que a mensagem codificada seja salva.

Após isso, basta digitar a mensagem à ser criptografada e qual deslocamento deve ser aplicado.

<h3 id="decypher-2"><strong>Decifrador</strong></h3>

Para a segunda opção, o usuário precisa selecionar um arquivo .txt que já contenha uma mensagem criptografada, em letras maiúsculas e sem espaços.

Tendo selecionado o arquivo, existem dois caminhos: decodificar através de brute force (lista todas as rotações possíveis) ou tentar decifrar automaticamente através do método explicado anteriormente.

Independente da opção escolhida, os resultados da decodificação são salvos em um **arquivo .txt cujo nome é o mesmo do arquivo original acrescido do sufixo "_dec"**
