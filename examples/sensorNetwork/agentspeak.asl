// Monitoramento e Alerta em uma Rede de Sensores
!start.

// Condições iniciais
+!start : true <-
    .my_name("sensor1");
    -sensor1;
    -sensor2;
    -sensor3;
    print_init.

// Reação ao ambiente e sociabilidade
+fire : true <- print_fire; +alert; .broadcast(tell,sensor1).
-fire : true <- print_not_fire; .broadcast(untell,sensor1).

// Reação a mensagens
+sensor2 <- +alert.
+sensor3 <- +alert.
+alert <- print_alert; !!check_alarm_condition.

// Se pelo menos 2 sensores dispararem, o alarme é acionado.
+!check_alarm_condition: fire & sensor2 <- trigger_alarm.
+!check_alarm_condition: fire & sensor3 <- trigger_alarm. 

+!check_alarm_condition: sensor1 <- !!check_alarm_condition.
+!check_alarm_condition: sensor2 <- !!check_alarm_condition.
+!check_alarm_condition: sensor3 <- !!check_alarm_condition.

+!check_alarm_condition <- -alert; print_default.


// # Proatividade -> persiste no seu objetivo de checar a condição de alarme.
// # Autonomia    -> O agente decide por conta própria quando deve acionar o alarme e se deve manter um estado de alerta ou não.

