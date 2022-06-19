#ifndef heuristica_h
#define heuristica_h

#include "utils.h"

void construirSolucaoInicial(vector<vector<vector<int>>> &solucao, vector<Turma> &vetTurmas, 
	                         vector<Sala> &vetSalas, int qtdSalas, int qtdHorarios);

void solucaoParcial(vector<vector<int>> &solucao, vector<Turma> &vetTurmas, vector<Sala> &vetSalas, 
					int qtdSalas, int qtdHorarios, int diaSemana);

int calculaFO(vector<vector<vector<int>>> &solucao, int qtdDiasSemana, 
			  vector<Sala> &vetSalas, int qtdSalas, int qtdHorarios);

int calculaFOPorDiaSemana(vector<vector<int>> &solucao, vector<Sala> &vetSalas, 
						  int qtdSalas, int qtdHorarios);

#endif