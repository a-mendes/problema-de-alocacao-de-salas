#ifndef turma_h
#define turma_h

#include "headers/utils.h"
#include "headers/disciplina.h"
#include "headers/aula.h"

typedef struct turma
{
	int id;
	Disciplina disciplina;
	int qtdAlunos;
	vector<Aula> aulas;
} Turma;

#endif