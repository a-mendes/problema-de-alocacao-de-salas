#include "headers/utils.h"
#include "headers/heuristica.h"



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

	/**
	 * Representação tridimensional
	 * 		i - Dias da semana: {Segunda, Terca, Quarta, Quinta, Sexta, Sábado}
	 * 		j - Salas: Depende da instancia
	 * 		k - horários: {07:30 a 21:50} totalizando 16 horários
	 */ 
	vector<vector<vector<Turma>>> solucao;
	
	int qtdSalas = vetSalas.size();
	construirSolucaoInicial(solucao, vetTurmas, vetSalas, qtdSalas, QTD_HORARIOS);

	return 0;
}

void menu()
{
	printf("\n=================================================");
	printf("\n* BCC466 - Tecnicas para Otimizao Metaheuristica");
	printf("\n* Ana Laura Siqueira Mendes");
	printf("\n* Problema de Alocacao de Salas - \"PAS\"");
	printf("\n=================================================\n");
}

void lerInstancia(vector<Sala> &vetSalas, vector<Departamento> &vetDepartamentos, 
				  vector<Disciplina> &vetDisciplinas, vector<Turma> &vetTurmas)
{
	printf("\nLendo instancia...\n");
	
	printf("\n\tLendo SALAS...\n");
	lerSalas(vetSalas);
	
	printf("\n\tLendo DEPARTAMENTOS...\n");
	lerDepartamentos(vetDepartamentos);

	printf("\n\tLendo DISCIPLINAS...\n");
	lerDisciplinas(vetDisciplinas, vetDepartamentos);

	printf("\n\tLendo TURMAS...\n");
	lerTurmas(vetTurmas, vetDisciplinas);

	printf("\n\tLendo AULAS POR TURMA...\n");
	lerAulasPorTurma(vetTurmas);

	printf("\nInstancia lida com sucesso!\n");
}