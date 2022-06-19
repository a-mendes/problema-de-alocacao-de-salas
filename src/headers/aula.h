#ifndef aula_h
#define aula_h

#include <string.h>

#define QTD_HORARIOS 16

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