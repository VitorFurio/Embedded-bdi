// Monitoramento e Alerta em uma Rede de Sensores
!start.

// Estados possíveis:
//alert.

// Informações de comunicação:
//sensor2.
//sensor3.

// Condições iniciais
+!start : true <-
    .my_name("sensor1");
    .print("Agente sensor1 iniciado!").

// Reação ao ambiente e sociabilidade
+alert : not sensor1 <- .broadcast(tell,"sensor1"); !!check_alarm_condition.
-alert : sensor1 <- .broadcast(untell,"sensor1").

// Reação a mensagens
+sensor2 <- !check_alarm_condition.
+sensor3 <- !check_alarm_condition.

// Se pelo menos 2 sensores dispararem, o alarme é acionado.
+!check_alarm_condition: sensor1 & sensor2 <- trigger_alarm.
+!check_alarm_condition: sensor2 & sensor3 <- trigger_alarm.
+!check_alarm_condition: sensor3 & sensor1 <- trigger_alarm.
+!check_alarm_condition.
