#include "headers/utils.h"

void menu();
void lerInstancia(vector<Sala> &vetSalas, vector<Departamento> &vetDepartamentos, 
				  vector<Disciplina> &vetDisciplinas, vector<Turma> &vetTurmas);

int main()
{
	menu();

	vector<Sala> vetSalas;
	vector<Departamento> vetDepartamentos;
	vector<Disciplina> vetDisciplinas;
	vector<Turma> vetTurmas;

	lerInstancia(vetSalas, vetDepartamentos, vetDisciplinas, vetTurmas);

	return 0;
}

void menu()
{
	printf("\n=================================================");
	printf("\n* BCC466 - Tecnicas para Otimizao Metaheuristica");
	printf("\n* Ana Laura Siqueira Mendes");
	printf("\n=================================================");
	//printf("\n");
	//printf("\n * PROBLEMA DE ALOCACAO DE SALAS");
}

void lerInstancia(vector<Sala> &vetSalas, vector<Departamento> &vetDepartamentos, 
				  vector<Disciplina> &vetDisciplinas, vector<Turma> &vetTurmas)
{
	lerSalas(vetSalas);
	lerDepartamentos(vetDepartamentos);
	lerDisciplinas(vetDisciplinas, vetDepartamentos);
	lerTurmas(vetTurmas, vetDisciplinas);
	lerAulasPorTurma(vetTurmas);
}