#ifndef disciplina_h
#define disciplina_h

#include "departamento.h"
/**
 * Ex: BCC466 TECNICAS METAHEURISTICAS PARA OTIMIZACAO COMBINATORIA
 * 		id: 466
 * 		departamento: BCC
 * 		nome: TECNICAS METAHEURISTICAS PARA OTIMIZACAO COMBINATORIA
 */ 
typedef struct disciplina
{
	int id;
	Departamento departamento;
	char nome[50];

} Disciplina;

#endif