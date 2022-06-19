#ifndef util_h
#define util_h

using namespace std;

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <iostream>
#include <vector>

#include "sala.h"
#include "departamento.h"
#include "disciplina.h"
#include "aula.h"
#include "turma.h"

void lerSalas(vector<Sala> &vetSalas);
void imprimirSalas(vector<Sala> &vetSalas);

void lerDepartamentos(vector<Departamento> &vetDepartamentos);
void imprimirDepartamentos(vector<Departamento> &vetDepartamentos);

void lerDisciplinas(vector<Disciplina> &vetDisciplinas, vector<Departamento> &vetDepartamentos);
void imprimirDisciplinas(vector<Disciplina> &vetDisciplinas);

void lerTurmas(vector<Turma> &vetTurmas, vector<Disciplina> &vetDisciplinas);
int codificarTurma(Turma turma);
void imprimirTurmas(vector<Turma> &vetTurmas);

void lerAulasPorTurma(vector<Turma> &vetTurmas);
int codigoHorario(char horario[6]);
void getAulasTurmaCodificada(vector<Aula> &aulas, vector<Turma> &vetTurmas, int turmaCodificada);

void getVetorTurmaCodificada(vector<int> &turmaCodificada, vector<Turma> &vetTurmas);
void ordenarPorQuantidadeAlunos(vector<int> &turmaCodificada);

void imprimirSolucaoCodificada(vector<vector<vector<int>>> &solucao);

void imprimirSolucaoDecodificada(vector<vector<vector<int>>> &solucao, 
								 vector<Turma> &vetTurmas, vector<Sala> &vetSalas);

int isHorarioDisponivel(vector<vector<int>> &solucao, int salaId, Aula aula);

#endif
