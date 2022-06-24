#ifndef heuristica_h
#define heuristica_h

#include "utils.h"

void construirSolucaoInicial(vector<vector<vector<Turma>>> &solucao, vector<Turma> &vetTurmas, 
	                         vector<Sala> &vetSalas, int qtdSalas, int qtdHorarios);

void solucaoParcial(vector<vector<Turma>> &solucao, vector<Turma> &vetTurmas, vector<Sala> &vetSalas, 
					int qtdSalas, int qtdHorarios, int diaSemana);

void solucaoParcialVazia(vector<vector<Turma>> &solucao, int qtdSalas, int qtdHorarios);

void alocarAulaGeminada(vector<vector<Turma>> &solucao, int salaId, vector<Aula> aulas, 
						int i, Turma turma);
void alocarAula(vector<vector<Turma>> &solucao, int salaId, Aula aula, Turma turma);
void desalocarAula(vector<vector<Turma>> &solucao, int salaId, Aula aula);

void buscaLocal(vector<vector<vector<Turma>>> &solucao, int qtdDiasSemana);
void buscaLocalPorDiaSemana(vector<vector<Turma>> &solucao);

int calculaFO(vector<vector<vector<Turma>>> &solucao, int qtdDiasSemana, 
			  vector<Sala> &vetSalas, int qtdSalas, int qtdHorarios);

int calculaFOPorDiaSemana(vector<vector<Turma>> &solucao, vector<Sala> &vetSalas, 
						  int qtdSalas, int qtdHorarios);

#endif