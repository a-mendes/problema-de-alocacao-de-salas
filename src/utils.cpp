#include "headers/utils.h"

void lerSalas(vector<Sala> &vetSalas)
{
	FILE *arq;
	arq = fopen("data/capacidade.txt", "r");
	printf("\t\tAbrindo arquivo \"data/capacidade.txt\"\n");

	while (!feof(arq))
	{
		Sala sala;
	    fscanf(arq, "%d|%d|\n", &sala.id, &sala.capacidade);

	    vetSalas.push_back(sala);
	}

	fclose(arq);
	printf("\t\tFechando arquivo \"data/capacidade.txt\"\n");
}

void imprimirSalas(vector<Sala> &vetSalas)
{
	printf("\n* Salas\n");
	for (int i = 0; i < vetSalas.size(); ++i)
    {
    	Sala sala = vetSalas[i];
    	printf("\tSala %d: %d\n", sala.id, sala.capacidade);
    }
}

void lerDepartamentos(vector<Departamento> &vetDepartamentos)
{
	FILE *arq;
	arq = fopen("data/legenda_departamento.txt", "r");
	printf("\t\tAbrindo arquivo \"data/legenda_departamento.txt\"\n");
	
	while (!feof(arq))
	{
		Departamento departamento;
		
	    fscanf(arq, "%d|%3s|\n", &departamento.id, departamento.sigla);

	    vetDepartamentos.push_back(departamento);
	}

	fclose(arq);
	printf("\t\tFechando arquivo \"data/legenda_departamento.txt\"\n");
}

void imprimirDepartamentos(vector<Departamento> &vetDepartamentos)
{
	printf("\n* Departamentos\n");
	for (int i = 0; i < vetDepartamentos.size(); ++i)
    {
    	Departamento departamento = vetDepartamentos[i];
    	printf("\tDepartamento %d: %s\n", departamento.id, departamento.sigla);
    }
}

void lerDisciplinas(vector<Disciplina> &vetDisciplinas, vector<Departamento> &vetDepartamentos)
{
	FILE *arq;
	arq = fopen("data/nome.txt", "r");
	printf("\t\tAbrindo arquivo \"data/nome.txt\"\n");

	while (!feof(arq))
	{
		Disciplina disciplina;
		char sigla[4];

	    fscanf(arq, "%3s|%d|%[^\n]\n", sigla, &disciplina.id, disciplina.nome);

	    for (int i = 0; i < vetDepartamentos.size(); ++i)
	    {
	    	Departamento departamento = vetDepartamentos[i];

	    	if(strcmp(sigla, departamento.sigla) == 0)
	    	{
	    		disciplina.departamento = departamento;
	    		break;
	    	}
	    }

	    vetDisciplinas.push_back(disciplina);
	}

	fclose(arq);
	printf("\t\tFechando arquivo \"data/nome.txt\"\n");
}

void imprimirDisciplinas(vector<Disciplina> &vetDisciplinas)
{
	printf("\n* Disciplinas\n");
	for (int i = 0; i < vetDisciplinas.size(); ++i)
    {
    	Disciplina disciplina = vetDisciplinas[i];
    	
    	printf("\t%s %d %s\n", disciplina.departamento.sigla, disciplina.id, disciplina.nome);
    }
}

void lerTurmas(vector<Turma> &vetTurmas, vector<Disciplina> &vetDisciplinas)
{
	FILE *arq;
	arq = fopen("data/demanda.txt", "r");
	printf("\t\tAbrindo arquivo \"data/demanda.txt\"\n");

	while (!feof(arq))
	{
		Turma turma;
		
		int idDepartamento;
		int idDisciplina;

	    fscanf(arq, "%d|%d|%d|%d|\n", &idDepartamento, &idDisciplina, &turma.id, &turma.qtdAlunos);

	    for (int i = 0; i < vetDisciplinas.size(); ++i)
	    {
	    	Disciplina disciplina = vetDisciplinas[i];

	    	if(idDisciplina == disciplina.id && idDepartamento == disciplina.departamento.id)
	    	{
	    		turma.disciplina = disciplina;
	    		break;
	    	}	
	    }

	    vetTurmas.push_back(turma);
	}

	fclose(arq);
	printf("\t\tFechando arquivo \"data/demanda.txt\"\n");
}

void imprimirTurmas(vector<Turma> &vetTurmas)
{
	printf("\n* Turmas\n");
	for (int i = 0; i < vetTurmas.size(); ++i)
    {
    	Turma turma = vetTurmas[i];

    	printf("\tTurma %d - %s: %d matriculados \n", turma.id,  turma.disciplina.nome, turma.qtdAlunos);
    	for (int j = 0; j < turma.aulas.size(); ++j)
    	{
    		Aula aula = turma.aulas[j];
    		printf("\t\t%da) %s - %s\n", aula.diaSemana, aula.horaInicio, aula.horaFim);
    	}
    }
}

void lerAulasPorTurma(vector<Turma> &vetTurmas)
{
	FILE *arq;
	arq = fopen("data/horario.txt", "r");
	printf("\t\tAbrindo arquivo \"data/horario.txt\"\n");

	while (!feof(arq))
	{
		Aula aula;
		int idDepartamento;
		int idDisciplina;
		int idTurma;

	    fscanf(arq, "%d|%d|%d|%c|%d|%5s|%5s|\n", &idDepartamento, &idDisciplina, &idTurma, 
	    									   &aula.tipoAula, &aula.diaSemana, aula.horaInicio, aula.horaFim);

	    aula.codigoHorarioInicio = codigoHorario(aula.horaInicio);
	    aula.codigoHorarioFim = codigoHorario(aula.horaFim);
	    
	    for (int i = 0; i < vetTurmas.size(); ++i)
	    {
	    	Turma turma = vetTurmas[i];

	    	if(idTurma == turma.id 
	    	&& idDisciplina == turma.disciplina.id
	    	&& idDepartamento == turma.disciplina.departamento.id)
	    	{
	    		vetTurmas[i].aulas.push_back(aula);
	    		break;
	    	}
	    }
	}

	fclose(arq);
	printf("\t\tFechando arquivo \"data/horario.txt\"\n");
}

int codigoHorario(char horario[6])
{
	if(strcmp(horario, "07:30") == 0)
		return 0;
	if(strcmp(horario, "08:20") == 0)
		return 1;
	if(strcmp(horario, "09:10") == 0 || strcmp(horario, "09:30") == 0)
		return 2;
	if(strcmp(horario, "10:20") == 0)
		return 3;
	if(strcmp(horario, "11:10") == 0 || strcmp(horario, "11:20") == 0)
		return 4;
	if(strcmp(horario, "12:10") == 0 || strcmp(horario, "13:00") == 0)
		return 5;
	if(strcmp(horario, "13:50") == 0)
		return 6;
	if(strcmp(horario, "14:40") == 0 || strcmp(horario, "15:00") == 0)
		return 7;
	if(strcmp(horario, "15:50") == 0)
		return 8;
	if(strcmp(horario, "16:40") == 0 || strcmp(horario, "16:50") == 0)
		return 9;
	if(strcmp(horario, "17:40") == 0)
		return 10;
	if(strcmp(horario, "18:30") == 0 || strcmp(horario, "19:00") == 0)
		return 11;
	if(strcmp(horario, "19:50") == 0)
		return 12;
	if(strcmp(horario, "20:40") == 0 || strcmp(horario, "21:00") == 0)
		return 13;
	if(strcmp(horario, "21:50") == 0)
		return 14;
	if(strcmp(horario, "22:40") == 0)
		return 15;
}

void filtraTurmasPorDiaAula(vector<Turma> &turmaPorDiaAula, vector<Turma> &vetTurmas, 
							  int diaSemana)
{
	for (int i = 0; i < vetTurmas.size(); ++i)
	{
		Turma turma = vetTurmas[i];

		Turma turmaFiltro;
		turmaFiltro.id = turma.id;
		turmaFiltro.disciplina = turma.disciplina;
		turmaFiltro.qtdAlunos = turma.qtdAlunos;

		for (int j = 0; j < turma.aulas.size(); ++j)
		{
			Aula aula = turma.aulas[j];

			if (aula.diaSemana == diaSemana)
				turmaFiltro.aulas.push_back(aula);
		}

		turmaPorDiaAula.push_back(turmaFiltro);
	}
}

void ordenarPorQuantidadeAlunos(vector<Turma> &turmas)
{
	/**
	 * Ordenação decrescente por "quantidade de alunos"
	 * usando o algoritmo "ShellSort"
	 */

	int h;
	int n = turmas.size();

	for(h = 1; h < n; h = 3 * h + 1);

	do
	{
		h = (h - 1) / 3;

		for(int i = h; i < n; i++)
		{
			Turma aux = turmas[i];
			int j = i;

			while(turmas[j-h].qtdAlunos < aux.qtdAlunos)
			{
				turmas[j] = turmas[j-h];

				j = j - h;

				if(j < h)
					break;
			}
			
			turmas[j] = aux;
		}

	} while (h != 1);
}

void imprimirSolucao(vector<vector<vector<Turma>>> &solucao)
{
	int qtdDiasSemana = solucao.size();
	int qtdSalas = solucao[0].size();
	int qtdHorarios = solucao[0][0].size();
	
	for (int i = 0; i < qtdDiasSemana; ++i)
	{
		printf("\n===============================================================\n");
		imprimirDiaSemana(i+2);
		
		/**
		 * Cabeçalho
		 */ 
		printf("\t");
		for (int j = 0; j < qtdSalas; ++j)
				printf("\tSala %-3d ", j);
		
		printf("\n");
		for (int k = 0; k < qtdHorarios; ++k)
		{
			printf("Horario %d: ", k);
			for (int j = 0; j < qtdSalas; ++j)
			{
				Turma turma = solucao[i][j][k];

				if (turma.id == 0)
				{
					printf("\t---------");
						continue;
				}

				
				printf("\t%s %d-%d", turma.disciplina.departamento.sigla, 
											turma.disciplina.id, turma.id);
			}
			printf("\n");
		}
	}
}

void imprimirDiaSemana(int numeroDia)
{
	switch(numeroDia)
	{
		case 1: printf("\nDomingo\n");
			break;

		case 2: printf("\nSegunda-Feira\n");
			break;

		case 3: printf("\nTerca-Feira\n");
			break;

		case 4: printf("\nQuarta-Feira\n");
			break;

		case 5: printf("\nQuinta-Feira\n");
			break;

		case 6: printf("\nSexta-Feira\n");
			break;

		case 7: printf("\nSabado\n");
			break;
	}
}

int isHorarioDisponivel(vector<vector<Turma>> &solucao, int salaId, Aula aula)
{	
	for (int i = aula.codigoHorarioInicio; i < aula.codigoHorarioFim; ++i)
	{
		if(solucao[salaId][i].id != 0)
			return 0;
	}

	return 1;
}