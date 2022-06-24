#include "headers/heuristica.h"

void construirSolucaoInicial(vector<vector<vector<Turma>>> &solucao, vector<Turma> &vetTurmas, 
	                         vector<Sala> &vetSalas, int qtdSalas, int qtdHorarios)
{
	printf("\nConstruindo Solucao Inicial...\n");

	printf("\n\tSolucao Segunda-Feira...\n");
	vector<vector<Turma>> solucaoSegunda;
	solucaoParcial(solucaoSegunda, vetTurmas, vetSalas, qtdSalas, qtdHorarios, 2);
	solucao.push_back(solucaoSegunda);

	printf("\n\tSolucao Terca-Feira...\n");
	vector<vector<Turma>> solucaoTerca;
	solucaoParcial(solucaoTerca, vetTurmas, vetSalas, qtdSalas, qtdHorarios, 3);
	solucao.push_back(solucaoTerca);

	printf("\n\tSolucao Quarta-Feira...\n");
	vector<vector<Turma>> solucaoQuarta;
	solucaoParcial(solucaoQuarta, vetTurmas, vetSalas, qtdSalas, qtdHorarios, 4);
	solucao.push_back(solucaoQuarta);

	printf("\n\tSolucao Quinta-Feira...\n");
	vector<vector<Turma>> solucaoQuinta;
	solucaoParcial(solucaoQuinta, vetTurmas, vetSalas, qtdSalas, qtdHorarios, 5);
	solucao.push_back(solucaoQuinta);

	printf("\n\tSolucao Sexta-Feira...\n");
	vector<vector<Turma>> solucaoSexta;
	solucaoParcial(solucaoSexta, vetTurmas, vetSalas, qtdSalas, qtdHorarios, 6);
	solucao.push_back(solucaoSexta);

	printf("\n\tSolucao Sabado...\n");
	vector<vector<Turma>> solucaoSabado;
	solucaoParcial(solucaoSabado, vetTurmas, vetSalas, qtdSalas, qtdHorarios, 3);
	solucao.push_back(solucaoSabado);

	printf("\nSolucao inicial construida com sucesso!\n");

	imprimirSolucao(solucao, qtdSalas, qtdHorarios, 6);

	int fo = calculaFO(solucao, 6, vetSalas, qtdSalas, qtdHorarios);

	printf("\nFO = %d\n", fo);

}

void solucaoParcial(vector<vector<Turma>> &solucao, vector<Turma> &vetTurmas, 
	                vector<Sala> &vetSalas, int qtdSalas, int qtdHorarios, int diaSemana)
{
	solucaoParcialVazia(solucao, qtdSalas, qtdHorarios);


	vector<Turma> turmasFiltro;
	filtraTurmasPorDiaAula(turmasFiltro, vetTurmas, diaSemana);
	
	/**
	 * Garantir a alocação das maiores turmas primeiro
	 */ 
	ordenarPorQuantidadeAlunos(turmasFiltro);

	/**
	 * Construtivo
	 */ 
	for (int i = 0; i < turmasFiltro.size(); ++i)
	{
		Turma turma = turmasFiltro[i];

		for (int j = 0; j < turma.aulas.size(); ++j)
		{
			Aula aula = turma.aulas[j];

			for (int k = 0; k < vetSalas.size(); ++k)
			{
				Sala sala = vetSalas[k];

				int qtdAlunos = turma.qtdAlunos;
				if(sala.capacidade >= qtdAlunos && isHorarioDisponivel(solucao, sala.id, aula))
				{	
					/**
					 * Verifica Aulas Geminadas
					 */ 

					//Melhorar
					if(turma.aulas[j+1].codigoHorarioInicio == aula.codigoHorarioFim 
				    && isHorarioDisponivel(solucao, sala.id, turma.aulas[j+1]))
					{
						alocarAula(solucao, sala.id, aula, turma);
						alocarAula(solucao, sala.id, turma.aulas[j+1], turma);
						j++;
					}
					break;
				}
			}
		}
	}
}

void solucaoParcialVazia(vector<vector<Turma>> &solucao, int qtdSalas, int qtdHorarios)
{
	for (int i = 0; i < qtdSalas; ++i)
	{
		vector<Turma> horariosVazios;
		for (int j = 0; j < qtdHorarios; ++j)
		{
			Turma turma;
			turma.id = 0;
			horariosVazios.push_back(turma);
		}
		solucao.push_back(horariosVazios);
	}
}

void alocarAula(vector<vector<Turma>> &solucao, int salaId, Aula aula, Turma turma)
{
	for (int i = aula.codigoHorarioInicio; i < aula.codigoHorarioFim; ++i)
	{
		solucao[salaId][i] = turma;
	}
}

void desalocarAula(vector<vector<Turma>> &solucao, int salaId, Aula aula)
{
	for (int i = aula.codigoHorarioInicio; i < aula.codigoHorarioFim; ++i)
	{
		solucao[salaId][i].id = 0;
	}
}

void buscaLocal(vector<vector<vector<Turma>>> &solucao, int qtdDiasSemana)
{
	for (int i = 0; i < qtdDiasSemana; ++i)
	{
		buscaLocalPorDiaSemana(solucao[i]);
	}
}

void buscaLocalPorDiaSemana(vector<vector<Turma>> &solucao)
{

	//Implementar Busca local
	
}

void vizinhoAleatorio(vector<vector<Turma>> &solucao)
{
	/**
	 * Aleatoriza uma turma alocada e em seguida aleatoriza uma
	 * sala para tentar realocar
	 */ 
	int qtdSalas = solucao.size();
	int qtdHorarios = solucao[0].size();

	int aulaRealocarHorario;
	int aulaRealocarSalaAtual;

	do 
	{
		aulaRealocarHorario = rand() % qtdHorarios;
	 	aulaRealocarSalaAtual = rand() % qtdSalas;
	}
	while (solucao[aulaRealocarSalaAtual][aulaRealocarHorario].id == 0);

	int novaSala = rand() % qtdSalas;

	/**
	 * Verifica se o horario esta vazio
	 */ 
	if(solucao[novaSala][aulaRealocarHorario].id == 0)
	{
		solucao[novaSala][aulaRealocarHorario] = solucao[aulaRealocarSalaAtual][aulaRealocarHorario];
		solucao[aulaRealocarSalaAtual][aulaRealocarHorario].id = 0;
	}

}

int calculaFO(vector<vector<vector<Turma>>> &solucao, int qtdDiasSemana, 
			  vector<Sala> &vetSalas, int qtdSalas, int qtdHorarios)
{
	int fo = 0;

	for (int i = 0; i < qtdDiasSemana; ++i)
	{

		fo += calculaFOPorDiaSemana(solucao[i], vetSalas, qtdSalas, qtdHorarios);
	}

	return fo;
}

int calculaFOPorDiaSemana(vector<vector<Turma>> &solucao, vector<Sala> &vetSalas, 
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
			Turma turma = solucao[i][j];
			int numAlunos = turma.qtdAlunos;

			hasHorarioVagoLimpeza += turma.id == 0;
			qtdTransbordamentos += numAlunos > sala.capacidade;
			qtdAlocacoesIneficientes += (numAlunos / (sala.capacidade + 1)) < razaoAlocacaoSalas;
		}

		fo += qtdTransbordamentos * pesoSolucaoInviavel;
		fo += (hasHorarioVagoLimpeza > 0) ? (0) : (pesoSolucaoBaixaQualidade);
		fo += qtdAlocacoesIneficientes * pesoSolucaoBaixaQualidade;
	}

	return fo;
}