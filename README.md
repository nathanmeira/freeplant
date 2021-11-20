# FreePlant - Mackenzie Arduino Project

<h3> Integrantes:</h3>

- Nathan Meira  TIA: 41901886
- Gabriel Freire TIA: 41921836

### O que é o FreePlant:
Com a facilidade dos objetos conectados e inteligentes, resolvemos aplicar este benefício em um projeto que seja capaz de ler a umidade do solo e indicar se este precisa de uma manutenção em sua umidade, dependendo de cada tipo de solo ou planta, para que haja uma consistência e coerência na manutenção deste solo. O principal objetivo é manter um jardim caseiro úmido, de maneira que as plantas consigam receber a quantidade de água adequada para seu crescimento e prolongamento de sua existência. Com este sistema conectado à internet, através de um bot a ser consultado via telefone móvel, será possível ser notificado sobre informações do solo e também enviar comandos para que o sistema seja regulado de maneira correta. O registro de leitura umidade x tempo será registrado na plataforma Ubidots.

### Hardware Utilizado:
- <b>NodeMCU (Amica):</b> microcontrolador de baixo custo onde será instalado o software desenvolvido para atender este sistema.
- <b>Sensor de umidade do solo:</b> este sensor funciona com dois diodos que passam uma corrente elétrica e medem a resistência que existe de um diodo para o outro. Quanto maior a resistência, menos corrente é passada, portanto entende-se que menos umidade está presente no ambiente que está inserido. 
- <b>Servo Motor 9g:</b> componente utilizado para executar atividades mecânicas como a abertura do container onde os componentes estão armazenados, quando ativado no modo manutenção.

### Software Utilizado:
- <b>Arduino IDE:</b> É uma aplicação usada para escrever e fazer upload de códigos para placas compatíveis com Arduino.
- <b>Ubidots:</b> É uma plataforma que utiliza a comunicação MQTT para enviar os dados de umidade x tempo do cenário, registrando as informações em um gráfico com o histórico de registro.
- <b>Telegram Bot:</b> São robôs utilizados para enviar comandos através de um canal do telegram, podendo utilizá-los para realizar várias tarefas.


### 📊 Dashboard Ubidots:
https://bit.ly/3DwJteB

### 👨🏻‍💻 Video explicativo (código)
https://youtu.be/4aTDCqfo2ZU

### ⚙️ Video demonstrativo (mecânica)
https://youtu.be/uAAbOQzittM

### Fluxograma:
<img src="https://cdn.discordapp.com/attachments/704873438443077673/911415734394056775/Fluxograma.png">

### Circuito Esquematico
<img src="https://cdn.discordapp.com/attachments/704873438443077673/911439909913522186/WhatsApp_Image_2021-11-19_at_23.14.55.jpeg"> 
