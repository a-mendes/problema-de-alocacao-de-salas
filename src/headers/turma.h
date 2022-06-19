#ifndef turma_h
#define turma_h

#include <vector>
#include "disciplina.h"

typedef struct turma
{
	int id;
	int codigo;
	Disciplina disciplina;
	int qtdAlunos;
	vector<Aula> aulas;
} Turma;

#endif