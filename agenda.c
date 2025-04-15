struct Horario{
    int hora,minuto,segundo;

}

struct data{
    int dia,mes,ano;
}

struct compromisso {
    struct Horario hrio;
    struct data dt;
    char descricao[100];
}