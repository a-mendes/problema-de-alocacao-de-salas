#ifndef aula_h
#define aula_h

typedef struct aula
{
	char tipoAula;
	int diaSemana;
	char horaInicio[6];
	char horaFim[6];
	int codigoHorarioInicio;
	int codigoHorarioFim;
} Aula;

#endif