#include "models/graph.hpp"
#include "models/sudoku.hpp"
#include <vector>
#include <tuple>

using namespace std;

int main()
{
	sudoku s, s2, s3, s4;
	cout << "Carregando pre coloração do enunciado." << endl;
	s.loadFromFile("sudoku.txt");
	s2.loadFromFile("sudoku.txt");
	s3.loadFromFile("sudoku.txt");
	s4.loadFromFile("sudoku.txt");
	s.printSudoku();
	cout << endl << "Pre coloração indices: " << endl;
	s.printPreColorIndex();
	cout << endl << "Quantidade de pre cores: " << s.getPreColorSize() << endl;

	cout << endl;
	cout << "1ª Aplicação de Welsh & Powell em busca de uma solução válida..." << endl;
	if ( s.Welsh_Powell() )
		cout << "Solução válida encontrada!" << endl;
	else
		cout << "Não foi possivel encontrar uma solução válida." << endl;
	s.printSudoku();

	cout << endl;
	cout << "2ª Aplicação de Welsh & Powell em busca de uma solução válida..." << endl;
	if ( s2.Welsh_Powell() )
		cout << "Solução válida encontrada!" << endl;
	else
		cout << "Não foi possivel encontrar uma solução válida." << endl;
	s2.printSudoku();

	cout << endl;
	cout << "3ª Aplicação de Welsh & Powell em busca de uma solução válida..." << endl;
	if ( s3.Welsh_Powell() )
		cout << "Solução válida encontrada!" << endl;
	else
		cout << "Não foi possivel encontrar uma solução válida." << endl;
	s3.printSudoku();

	cout << endl;
	cout << "4ª Aplicação de Welsh & Powell em busca de uma solução válida..." << endl;
	if ( s4.Welsh_Powell() )
		cout << "Solução válida encontrada!" << endl;
	else
		cout << "Não foi possivel encontrar uma solução válida." << endl;
	s4.printSudoku();	

	cout << endl << "Verificando igualdade de solução 2 a 2:" << endl;
	
	if ( s.compara(s2) )
		cout << "1ª é igual a 2ª!" << endl;
	else 
		cout << "1ª é diferente de 2ª!" << endl;

	if ( s.compara(s3) )
		cout << "1ª é igual a 3ª!" << endl;
	else 
		cout << "1ª é diferente de 3ª!" << endl;

	if ( s.compara(s4) )
		cout << "1ª é igual a 4ª!" << endl;
	else 
		cout << "1ª é diferente de 4ª!" << endl;

	if ( s2.compara(s3) )
		cout << "2ª é igual a 3ª!" << endl;
	else 
		cout << "2ª é diferente de 3ª!" << endl;

	if ( s2.compara(s4) )
		cout << "2ª é igual a 4ª!" << endl;
	else 
		cout << "2ª é diferente de 4ª!" << endl;

	if ( s3.compara(s4) )
		cout << "3ª é igual a 4ª!" << endl;
	else 
		cout << "3ª é diferente de 4ª!" << endl;

	cout << endl << "Carregando Sudoku gerado a partir da remoção de 2 números por linha do Sudoku do enunciado." 
	<< endl;
	sudoku reduzido;
	reduzido.loadFromFile("sudoku_menor.txt");
	reduzido.printSudoku();

	cout << endl << "Aplicando Welsh & Powell..." << endl;
	if ( reduzido.Welsh_Powell() )
		cout << "Solução válida encontrada!" << endl;
	else
		cout << "Não foi possivel encontrar uma solução válida." << endl;
	reduzido.printSudoku();	

	return 0;
}