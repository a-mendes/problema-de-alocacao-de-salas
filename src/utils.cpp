#include "headers/utils.h"

void lerSalas(vector<Sala> &vetSalas)
{
	FILE *arq;
	fopen("data/capacidade.txt", "r");

	while (!feof(arq))
	{
		Sala sala;
	    fscanf(arq, "%d|%d|\n", &sala.id, &sala.capacidade);
	    vetSalas.push_back(sala);
	}

	fclose(arq);
}

void lerDepartamentos(vector<Departamento> &vetDepartamentos)
{
	FILE *arq;
	fopen("data/legenda_departamento.txt", "r");

	while (!feof(arq))
	{
		Departamento departamento;
		
	    fscanf(arq, "%s|%d|\n", departamento.sigla, &departamento.id);
	    vetDepartamentos.push_back(departamento);
	}

	fclose(arq);
}

void lerDisciplinas(vector<Disciplina> &vetDisciplinas, vector<Departamento> &vetDepartamentos)
{
	FILE *arq;
	fopen("data/nome.txt", "r");

	while (!feof(arq))
	{
		Disciplina disciplina;
		string sigla;

	    fscanf(arq, "%s|%d|%s|\n", sigla, &disciplina.id, disciplina.nome);

	    for (int i = 0; i < vetDepartamentos.size(); ++i)
	    {
	    	Departamento departamento = vetDepartamentos[i];

	    	if(sigla.compare(departamento.sigla) == 0)
	    	{
	    		disciplina.departamento = departamento;
	    		break;
	    	}
	    }

	    vetDisciplinas.push_back(disciplina);
	}

	fclose(arq);
}

void lerTurmas(vector<Turma> &vetTurmas, vector<Disciplina> &vetDisciplinas)
{
	FILE *arq;
	fopen("data/demanda.txt", "r");

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
}

void lerAulasPorTurma(vector<Turma> &vetTurmas)
{
	FILE *arq;
	fopen("data/horario.txt", "r");

	while (!feof(arq))
	{
		Aula aula;
		int idDepartamento;
		int idDisciplina;
		int idTurma;

	    fscanf(arq, "%d|%d|%d|%c|%d|%s|%s|\n", &idDepartamento, &idDisciplina, &idTurma, 
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
}