#include "headers/heuristica.h"

void construirSolucaoInicial(vector<vector<vector<int>>> &solucao, vector<Turma> &vetTurmas, 
	                         vector<Sala> &vetSalas, int qtdSalas, int qtdHorarios)
{
	vector<vector<int>> solucaoSegunda;
	solucaoParcial(solucaoSegunda, vetTurmas, vetSalas, qtdSalas, qtdHorarios, 2);

	int solucaoTerca[qtdSalas][qtdHorarios];
	int solucaoQuarta[qtdSalas][qtdHorarios];
	int solucaoQuinta[qtdSalas][qtdHorarios];
	int solucaoSexta[qtdSalas][qtdHorarios];
	int solucaoSabado[qtdSalas][qtdHorarios];
}

void solucaoParcial(vector<vector<int>> &solucao, vector<Turma> &vetTurmas, 
	                vector<Sala> &vetSalas, int qtdSalas, int qtdHorarios, int diaSemana)
{
	vector<int> turmaCodificada;
	getVetorTurmaCodificada(turmaCodificada, vetTurmas);
	
	/**
	 * Garantir a alocação das maiores turmas primeiro
	 */ 
	ordenarPorQuantidadeAlunos(turmaCodificada);

	/**
	 * Construtivo
	 */ 


}

int calculaFO(vector<vector<vector<int>>> &solucao, int qtdDiasSemana, 
			  vector<Sala> &vetSalas, int qtdSalas, int qtdHorarios)
{
	int fo = 0;

	for (int i = 0; i < qtdDiasSemana; ++i)
	{
		fo += calculaFOPorDiaSemana(solucao[i], vetSalas, qtdSalas, qtdHorarios);
	}

	return fo;
}

int calculaFOPorDiaSemana(vector<vector<int>> &solucao, vector<Sala> &vetSalas, 
						  int qtdSalas, int qtdHorarios)
{
	int fo = 0;

	/**
	 * Determina o uso eficiente dos espacos das salas
	 * 		Caso uma sala esteja alocada para uma turma 
	 * 		que ocupe menos que 70% de sua capacidade, 
	 * 		o uso é considerado ineficiente.
	 */ 
	float razaoAlocacaoSalas = 0.7;

	int pesoSolucaoInviavel = 20;
	int pesoSolucaoBaixaQualidade = 5;

	for (int i = 0; i < qtdSalas; ++i)
	{
		Sala sala = vetSalas[i];

		/**
		 * Criterio de inviabilidade
		 */ 
		int qtdTransbordamentos = 0;

		/**
		 * Criterios de qualidade
		 */ 
		int hasHorarioVagoLimpeza = 0;
		int qtdAlocacoesIneficientes = 0;

		for (int j = 0; j < qtdHorarios; ++j)
		{
			int codTurma = solucao[i][j];
			int numAlunos = codTurma % 100;

			hasHorarioVagoLimpeza += codTurma == 0;
			qtdTransbordamentos += numAlunos > sala.capacidade;
			qtdAlocacoesIneficientes += (numAlunos / sala.capacidade) < razaoAlocacaoSalas;
		}

		fo += qtdTransbordamentos * pesoSolucaoInviavel;
		fo += (hasHorarioVagoLimpeza > 0) ? (0) : (pesoSolucaoBaixaQualidade);
		fo += qtdAlocacoesIneficientes * pesoSolucaoBaixaQualidade;
	}

	return fo;
}