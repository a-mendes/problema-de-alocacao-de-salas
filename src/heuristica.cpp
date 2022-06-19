#include "headers/heuristica.h"

void construirSolucaoInicial(vector<vector<vector<int>>> &solucao, vector<Turma> &vetTurmas, 
	                         vector<Sala> &vetSalas, int qtdSalas, int qtdHorarios)
{
	printf("\nConstruindo Solucao Inicial...\n");

	printf("\n\tSolucao Segunda-Feira...\n");
	vector<vector<int>> solucaoSegunda;
	solucaoParcial(solucaoSegunda, vetTurmas, vetSalas, qtdSalas, qtdHorarios, 2);
	solucao.push_back(solucaoSegunda);

	printf("\n\tSolucao Terca-Feira...\n");
	vector<vector<int>> solucaoTerca;
	solucaoParcial(solucaoTerca, vetTurmas, vetSalas, qtdSalas, qtdHorarios, 3);
	solucao.push_back(solucaoTerca);

	printf("\n\tSolucao Quarta-Feira...\n");
	vector<vector<int>> solucaoQuarta;
	solucaoParcial(solucaoQuarta, vetTurmas, vetSalas, qtdSalas, qtdHorarios, 4);
	solucao.push_back(solucaoQuarta);

	printf("\n\tSolucao Quinta-Feira...\n");
	vector<vector<int>> solucaoQuinta;
	solucaoParcial(solucaoQuinta, vetTurmas, vetSalas, qtdSalas, qtdHorarios, 5);
	solucao.push_back(solucaoQuinta);

	printf("\n\tSolucao Sexta-Feira...\n");
	vector<vector<int>> solucaoSexta;
	solucaoParcial(solucaoSexta, vetTurmas, vetSalas, qtdSalas, qtdHorarios, 6);
	solucao.push_back(solucaoSexta);

	printf("\n\tSolucao Sabado...\n");
	vector<vector<int>> solucaoSabado;
	solucaoParcial(solucaoSabado, vetTurmas, vetSalas, qtdSalas, qtdHorarios, 3);
	solucao.push_back(solucaoSabado);

	printf("\nSolucao inicial construida com sucesso!\n");

	imprimirSolucaoDecodificada(solucao, vetTurmas, qtdSalas, qtdHorarios, 6);

}

void solucaoParcial(vector<vector<int>> &solucao, vector<Turma> &vetTurmas, 
	                vector<Sala> &vetSalas, int qtdSalas, int qtdHorarios, int diaSemana)
{
	solucaoParcialVazia(solucao, qtdSalas, qtdHorarios);

	vector<int> turmasCodificadas;
	getVetorTurmaCodificada(turmasCodificadas, vetTurmas);
	
	/**
	 * Garantir a alocação das maiores turmas primeiro
	 */ 
	ordenarPorQuantidadeAlunos(turmasCodificadas);

	/**
	 * Construtivo
	 */ 

	for (int i = 0; i < turmasCodificadas.size(); ++i)
	{
		int turmaCodificada = turmasCodificadas[i];
		
		vector<Aula> aulas;
		getAulasTurmaCodificadaPorDiaSemana(aulas, vetTurmas, turmaCodificada, diaSemana);

		for (int j = 0; j < aulas.size(); ++j)
		{
			Aula aula = aulas[j];

			for (int k = 0; k < vetSalas.size(); ++k)
			{
				Sala sala = vetSalas[k];

				int qtdAlunos = turmaCodificada % 100;
				if(sala.capacidade >= qtdAlunos && isHorarioDisponivel(solucao, sala.id, aula))
				{
					alocarAula(solucao, sala.id, aula, turmaCodificada);
				}
			}
		}
	}
}

void alocarAula(vector<vector<int>> &solucao, int salaId, Aula aula, int turmaCodificada)
{
	for (int i = aula.codigoHorarioInicio; i < aula.codigoHorarioFim; ++i)
	{
		solucao[salaId][i] = turmaCodificada;
	}
}

void desalocarAula(vector<vector<int>> &solucao, int salaId, Aula aula)
{
	for (int i = aula.codigoHorarioInicio; i < aula.codigoHorarioFim; ++i)
	{
		solucao[salaId][i] = 0;
	}
}

void solucaoParcialVazia(vector<vector<int>> &solucao, int qtdSalas, int qtdHorarios)
{
	for (int i = 0; i < qtdSalas; ++i)
	{
		vector<int> horariosVazios;
		for (int j = 0; j < qtdHorarios; ++j)
		{
			horariosVazios.push_back(0);
		}
		solucao.push_back(horariosVazios);
	}
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