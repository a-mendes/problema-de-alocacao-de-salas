#ifndef util_h
#define util_h

using namespace std;

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <vector>
#include <string>

#include "sala.h"
#include "departamento.h"
#include "disciplina.h"
#include "aula.h"
#include "turma.h"

void lerSalas(vector<Sala> &vetSalas);
void lerDepartamentos(vector<Departamento> &vetDepartamentos);
void lerDisciplinas(vector<Disciplina> &vetDisciplinas, vector<Departamento> &vetDepartamentos);
void lerTurmas(vector<Turma> &vetTurmas, vector<Disciplina> &vetDisciplinas);
void lerAulasPorTurma(vector<Turma> &vetTurmas);

#endif
