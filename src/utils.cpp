#include "headers/utils.h"

void lerSalas(vector<Sala> &vetSalas)
{
	FILE *arq;
	arq = fopen("data-teste/capacidade.txt", "r");
	printf("\t\tAbrindo arquivo \"data-teste/capacidade.txt\"\n");

	while (!feof(arq))
	{
		Sala sala;
	    fscanf(arq, "%d|%d|\n", &sala.id, &sala.capacidade);

	    vetSalas.push_back(sala);
	}

	fclose(arq);
	printf("\t\tFechando arquivo \"data-teste/capacidade.txt\"\n");
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
	arq = fopen("data-teste/legenda_departamento.txt", "r");
	printf("\t\tAbrindo arquivo \"data-teste/legenda_departamento.txt\"\n");
	
	while (!feof(arq))
	{
		Departamento departamento;
		
	    fscanf(arq, "%d|%3s|\n", &departamento.id, departamento.sigla);

	    vetDepartamentos.push_back(departamento);
	}

	fclose(arq);
	printf("\t\tFechando arquivo \"data-teste/legenda_departamento.txt\"\n");
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
	arq = fopen("data-teste/nome.txt", "r");
	printf("\t\tAbrindo arquivo \"data-teste/nome.txt\"\n");

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
	printf("\t\tFechando arquivo \"data-teste/nome.txt\"\n");
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
	arq = fopen("data-teste/demanda.txt", "r");
	printf("\t\tAbrindo arquivo \"data-teste/demanda.txt\"\n");

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
	    		turma.codigo = codificarTurma(turma);
	    		break;
	    	}	
	    }

	    vetTurmas.push_back(turma);
	}

	fclose(arq);
	printf("\t\tFechando arquivo \"data-teste/demanda.txt\"\n");
}

int codificarTurma(Turma turma)
{
	/**
	 * A codificação resume em um int as informacoes mais relevantes de
	 * uma turma. 
	 * 
	 * 		0: id departamento
	 * 		1-3: id disciplina
	 * 		4-5: id turma
	 * 		6-7: quantidade de alunos matriculados na turma
	 * 
	 * 		Ex: Código: 11201140
	 * 			* Disciplina: MTM120 ANALISE I (1120)
	 * 			* Turma : 11
	 * 			* numero de matriculados: 40
	 */ 


	int codigo = turma.disciplina.departamento.id * 10000000 +
				 turma.disciplina.id * 10000 +
				 turma.id * 100 +
				 turma.qtdAlunos;

	return codigo;
}

void imprimirTurmas(vector<Turma> &vetTurmas)
{
	printf("\n* Turmas\n");
	for (int i = 0; i < vetTurmas.size(); ++i)
    {
    	Turma turma = vetTurmas[i];

    	printf("Codigo: %d\n", turma.codigo);
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
	arq = fopen("data-teste/horario.txt", "r");
	printf("\t\tAbrindo arquivo \"data-teste/horario.txt\"\n");

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
	printf("\t\tFechando arquivo \"data-teste/horario.txt\"\n");
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

void getAulasTurmaCodificadaPorDiaSemana(vector<Aula> &aulas, vector<Turma> &vetTurmas, 
							int turmaCodificada, int diaSemana)
{
	for (int i = 0; i < vetTurmas.size(); ++i)
	{
		Turma turma = vetTurmas[i];
		if(turma.codigo == turmaCodificada)
		{
			for (int j = 0; j < turma.aulas.size(); ++j)
			{
				Aula aula = turma.aulas[j];
				if(aula.diaSemana == diaSemana)
					aulas.push_back(aula);	
			}

			break;
		}	
	}
}

void getVetorTurmaCodificada(vector<int> &turmaCodificada, vector<Turma> &vetTurmas)
{
	for (int i = 0; i < vetTurmas.size(); ++i)
	{
		Turma turma = vetTurmas[i];
		turmaCodificada.push_back(turma.codigo);
	}
}


void ordenarPorQuantidadeAlunos(vector<int> &turmaCodificada)
{
	/**
	 * Ordenação decrescente por "quantidade de alunos"
	 * usando o algoritmo "ShellSort"
	 */

	int h;
	int n = turmaCodificada.size();

	for(h = 1; h < n; h = 3 * h + 1);

	do
	{
		h = (h - 1) / 3;

		for(int i = h; i < n; i++)
		{
			int aux = turmaCodificada[i];
			int j = i;

			while((turmaCodificada[j-h] % 100) < (aux % 100))
			{
				turmaCodificada[j] = turmaCodificada[j-h];

				j = j - h;

				if(j < h)
					break;
			}
			
			turmaCodificada[j] = aux;
		}

	} while (h != 1);
}

void imprimirSolucaoCodificada(vector<vector<vector<int>>> &solucao)
{

}

void imprimirSolucaoDecodificada(vector<vector<vector<int>>> &solucao, vector<Turma> &vetTurmas, 
								 int qtdSalas, int qtdHorarios, int qtdDiasSemana)
{
	for (int i = 0; i < qtdDiasSemana; ++i)
	{
		printf("\n%da - Feira\n", i + 2);
		
		/**
		 * Cabeçalho
		 */ 
		printf("\t");
		for (int j = 0; j < qtdSalas; ++j)
				printf("\tSala %-3d ", j);
		
		printf("\n");
		for (int k = 0; k < qtdHorarios; ++k)
		{
			printf("Horario %d: ", i);
			for (int j = 0; j < qtdSalas; ++j)
			{
				int turmaCodificada = solucao[i][j][k];

				if (turmaCodificada == 0)
				{
					printf("\t---------");
						continue;
				}

				for (int l = 0; l < vetTurmas.size(); ++l)
				{
					Turma turma = vetTurmas[l];
					if(turma.codigo == turmaCodificada){
						printf("\t%s %d-%d", turma.disciplina.departamento.sigla, 
											turma.disciplina.id, turma.id);
						break;
					}
				}
			}
			printf("\n");
		}
	}
}

int isHorarioDisponivel(vector<vector<int>> &solucao, int salaId, Aula aula)
{	
	for (int i = aula.codigoHorarioInicio; i < aula.codigoHorarioFim; ++i)
	{
		if(solucao[salaId][i] != 0)
			return 0;
	}

	return 1;
}