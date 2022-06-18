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