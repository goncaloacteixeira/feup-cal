/*
 * Sudoku.cpp
 *
 */

#include "Sudoku.h"

/** Inicia um Sudoku vazio.
 */
Sudoku::Sudoku() {
    this->initialize();
}

/**
 * Inicia um Sudoku com um conteudo inicial.
 * Lança excepção IllegalArgumentException se os valores
 * estiverem fora da gama de 1 a 9 ou se existirem números repetidos
 * por linha, coluna ou bloc 3x3.
 *
 * @param nums matriz com os valores iniciais (0 significa por preencher)
 */
Sudoku::Sudoku(int nums[9][9]) {
    this->initialize();

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (nums[i][j] != 0) {
                int n = nums[i][j];
                numbers[i][j] = n;
                lineHasNumber[i][n] = true;
                columnHasNumber[j][n] = true;
                block3x3HasNumber[i / 3][j / 3][n] = true;
                countFilled++;
            }
        }
    }
}

void Sudoku::initialize()
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			for (int n = 0; n < 10; n++)
			{
				numbers[i][j] = 0;
				lineHasNumber[i][n] = false;
				columnHasNumber[j][n] = false;
				block3x3HasNumber[i / 3][j / 3][n] = false;
			}
		}
	}

	this->countFilled = 0;
}

/**
 * Obtem o conteúdo actual (só para leitura!).
 */
int** Sudoku::getNumbers()
{
	int** ret = new int*[9];

	for (int i = 0; i < 9; i++)
	{
		ret[i] = new int[9];

		for (int a = 0; a < 9; a++)
			ret[i][a] = numbers[i][a];
	}

	return ret;
}

/**
 * Verifica se o Sudoku já está completamente resolvido
 */
bool Sudoku::isComplete()
{
    int filled = 0;
	for (int i = 0; i < 9; i++) {
	    for (int j = 0; j < 9; j++) {
	        if (this->numbers[i][j] != 0) {
	            filled++;
	        }
	    }
	}
	return filled == 9*9;
}


/**
 * Resolve o Sudoku.
 * Retorna indicação de sucesso ou insucesso (sudoku impossível).
 */
bool Sudoku::solve() {
    if (this->isComplete()) {
        return true;
    }
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (this->numbers[i][j] == 0) {
                for (int k = 1; k <= 9; k++) {

                    if (this->lineHasNumber[i][k] || this->columnHasNumber[j][k])
                        continue;

                    bool found = false;
                    for (int row = 0; row < 3; row++) {
                        for (int col = 0; col < 3; col++) {
                            if (this->numbers[row + i - i % 3][col + j - j % 3] == k)
                                found = true;
                        }
                        if (found)
                            break;
                    }
                    if (found)
                        continue;


                    this->numbers[i][j] = k;
                    this->lineHasNumber[i][k] = true;
                    this->columnHasNumber[j][k] = true;
                    if (solve()) {
                        return true;
                    }
                    this->lineHasNumber[i][k] = false;
                    this->columnHasNumber[j][k] = false;
                    this->numbers[i][j] = 0;
                }
                return false;
            }
        }
    }
    return false;
}



/**
 * Imprime o Sudoku.
 */
void Sudoku::print()
{
	for (int i = 0; i < 9; i++)
	{
		for (int a = 0; a < 9; a++)
			cout << this->numbers[i][a] << " ";

		cout << endl;
	}
}
