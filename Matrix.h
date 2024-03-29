#pragma once
#define NOMINMAX
#include <iomanip>
#include <iostream>
#include <Windows.h>
#include <string>

template <typename type, typename = std::enable_if_t<std::is_arithmetic_v<type>>>
class Matrix
{
private:
	unsigned int row;
	unsigned int col;
	type** data;
public:
	~Matrix()
	{
		for (size_t i = 0; i < row; i++)
		{
			delete[] data[i];
			data[i] = nullptr;
		}
		data = nullptr;
	}
	Matrix(unsigned int row, unsigned int col)
	{
		data = new type * [row];
		for (size_t i = 0; i < row; i++)
		{
			data[i] = new type[col];
		}
		this->row = row;
		this->col = col;

	}
	Matrix(const Matrix<type>& elem) : Matrix(elem.row, elem.col)
	{
		for (size_t i = 0; i < row; i++)
		{
			for (size_t j = 0; j < col; j++)
			{
				data[i][j] = elem.data[i][j];
			}
		}


	}


	// ����������� ������� � ������ ���������� ��� ���������
	static void createArr2D		(type**& init, int row, int col)
	{
		init = new type * [row];
		for (size_t i = 0; i < row; i++)
		{
			init[i] = new type[col];
		}
	}
	static void DeleteArr2D	    (type**& init, int row)
	{
		for (size_t i = 0; i < row; i++)
		{
			delete[] init[i];
			init[i] = nullptr;
		}
		init = nullptr;
	}
	static int	MaxLenElemArr2D (type** init, int row, int col)
	{
		int res = 0;

		for (size_t i = 0; i < row; i++)
		{
			for (size_t j = 0; j < col; j++)
			{
				if (std::to_string(init[i][j]).size() > res) res = std::to_string(init[i][j]).size();
			}
		}
		return res;
	}


	// ���������� �������� �����/������
	friend std::ostream& operator<<(std::ostream& out, Matrix<type> p)
	{
		int maxLen = MaxLenElemArr2D(p.data, p.row, p.col);
		for (size_t i = 0; i < p.row; i++)
		{
			for (size_t j = 0; j < p.col; j++)
			{
				out << std::setw(maxLen+2) << p.data[i][j];
			}
			out << std::endl;
		}
		return out;
	}
	friend std::istream& operator>>(std::istream& in, Matrix<type>& p)
	{
		for (size_t i = 0; i < p.row; i++)
		{
			COORD coord;
			coord.Y = i + 1;
			for (size_t j = 0; j < p.col; j++)
			{
				if (j == 0) coord.X = j + 1;
				bool flag;
				do
				{
					int tmp;
					SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

					in >> tmp;
					p.data[i][j] = tmp;

					int size_tmpElem = std::to_string(tmp).size();
					if (in.fail())
					{
						in.clear();
						in.ignore(32767, '\n');
						SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
						for (size_t i = 0; i < 100; i++) std::cout << " ";
						flag = true;
					}
					else
					{
						flag = false;
						coord.X += size_tmpElem + 2;
					}
				} while (flag);
			}
		}
		return in;

	}

	// ���������� �������������� ��������
	friend Matrix operator+(Matrix<type>& first, Matrix<type>& second)
	{
		if (first.col == second.row)
		{
			Matrix<type> tmp(first.row, second.col);

			for (size_t i = 0; i < tmp.row; i++)
			{
				for (size_t j = 0; j < tmp.col; j++)
				{
					tmp.data[i][j] = 0;
					for (size_t k = 0; k < first.col; k++)
					{

						if (first.data[i][k] != 0 || second.data[k][j] != 0)
						{
							tmp.data[i][j] += (first.data[i][k] + second.data[k][j]);
						}

					}
				}
			}
			return tmp;
		}
	}
	friend Matrix operator-(Matrix<type>& first, Matrix<type>& second)
	{
		if (first.col == second.row)
		{
			Matrix<type> tmp(first.row, second.col);

			for (size_t i = 0; i < tmp.row; i++)
			{
				for (size_t j = 0; j < tmp.col; j++)
				{
					tmp.data[i][j] = 0;
					for (size_t k = 0; k < first.col; k++)
					{

						if (first.data[i][k] != 0 || second.data[k][j] != 0)
						{
							tmp.data[i][j] += (first.data[i][k] - second.data[k][j]);
						}

					}
				}
			}
			return tmp;
		}
	}
	friend Matrix operator*(Matrix<type>& first, Matrix<type>& second)
	{
		/*	if (first.row != second.col || first.row != second.row) return;*/

		if (first.col == second.row)
		{
			Matrix<type> tmp(first.row, second.col);

			for (size_t i = 0; i < tmp.row; i++)
			{
				for (size_t j = 0; j < tmp.col; j++)
				{
					tmp.data[i][j] = 0;
					for (size_t k = 0; k < first.col; k++)
					{
						
						if (first.data[i][k] != 0 || second.data[k][j] != 0)
						{
							tmp.data[i][j] += (first.data[i][k] * second.data[k][j]);
						}
						
					}
				}
			}
			return tmp;
		}
	}
	friend Matrix operator/(Matrix<type>& first, Matrix<type>& second)
	{
		if (first.col == second.row)
		{
			Matrix<type> tmp(first.row, second.col);

			for (size_t i = 0; i < tmp.row; i++)
			{
				for (size_t j = 0; j < tmp.col; j++)
				{
					tmp.data[i][j] = 0;
					for (size_t k = 0; k < first.col; k++)
					{

						if (first.data[i][k] != 0 || second.data[k][j] != 0)
						{
							tmp.data[i][j] += (first.data[i][k] / second.data[k][j]);
						}

					}
				}
			}
			return tmp;
		}
	}

	/*Matrix& operator=(Matrix<type>& second)
	{
		if (data != nullptr)
		{
			clear();
		}
		row = second.row;
		col = second.col;

		data = new type * [row];
		for (size_t i = 0; i < col; i++)
		{
			data[i] = new type[col];
		}

		for (size_t i = 0; i < row; i++)
		{
			for (size_t j = 0; j < col; j++)
			{
				data[i][j] = second.data[i][j];
			}
		}
		return *this;
	}*/
	Matrix& operator=(Matrix<type> second)
	{
		if (data != nullptr)
		{
			clear();
		}
		row = second.row;
		col = second.col;

		data = new type * [row];
		for (size_t i = 0; i < col; i++)
		{
			data[i] = new type[col];
		}

		for (size_t i = 0; i < row; i++)
		{
			for (size_t j = 0; j < col; j++)
			{
				data[i][j] = second.data[i][j];
			}
		}
		return *this;
	}
	friend bool operator==(Matrix<type>& first, Matrix<type>& second)
	{
		if (first.row != second.row || first.col != second.col) return false;

		for (size_t i = 0; i < first.row; i++)
		{
			for (size_t j = 0; j < first.col; j++)
			{
				if (first.data[i][j] != second.data[i][j]) return false;
			}
		}
		return true;
	}
	friend bool operator!=(Matrix<type>& first, Matrix<type>& second)
	{
		if (first.row != second.row || first.col != second.col) return true;

		for (size_t i = 0; i < first.row; i++)
		{
			for (size_t j = 0; j < first.col; j++)
			{
				if (first.data[i][j] != second.data[i][j]) return true;
			}
		}
		return false;
	}

	// ������� �������
	void clear()
	{
		for (size_t i = 0; i < row; i++)
		{
			delete[] data[i];
			data[i] = nullptr;
		}
		data = nullptr;
		row = 0;
		col = 0;
	}

	// ���������� ������� ���������� �������
	void randomFill(type min = 0, type max = 10)
	{		
		for (size_t i = 0; i < row; i++)
		{
			for (size_t j = 0; j < col; j++)
			{
				if constexpr (std::is_integral_v<type>) data[i][j] = rand() % (max - min + 1) + min;
				else data[i][j] = (max - min) * rand() / RAND_MAX + min;
			}
		}
	}


	// ����� ������� �� �����
	void print()
	{
		for (size_t i = 0; i < row; i++)
		{
			for (size_t j = 0; j < col; j++)
			{
				std::cout << std::setw(3) << data[i][j];
			}
			std::cout << std::endl;
		}
	}

	// ���������������� �������
	void transposition()
	{
		// ������� ����� ������ � ����������� ����������� ����� � �������
		type** NewData;
		createArr2D(NewData, col, row);
	
		// ������� ������
		for (size_t i = 0; i < row; i++)
		{
			for (size_t j = 0; j < col; j++)
			{
				NewData[j][i] = data[i][j];
			}
		}

		// ������� ������� ������ 
		for (size_t i = 0; i < row; i++)
		{
			delete[] data[i];
			data[i] = nullptr;
		}
		data = nullptr;

		std::swap(row, col);

		// ����������� ��������� �� ������ ����� 
		data = NewData;
	}

	// ������ ���� �������
	void KbInput(int posX = 0, int posY = 0)
	{
		for (size_t i = 0; i < row; i++)
		{
			COORD coord;
			coord.Y = i + 1 + posY;
			for (size_t j = 0; j < col; j++)
			{
				if (j == 0) coord.X = j + 1 + posX;
				bool flag;
				do
				{
					int tmp;
					SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

					std::cin >> tmp;
					data[i][j] = tmp;

					int size_tmpElem = std::to_string(tmp).size();
					if (std::cin.fail())
					{
						std::cin.clear();
						std::cin.ignore(32767, '\n');
						SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
						for (size_t i = 0; i < 100; i++) std::cout << " ";
						flag = true;
					}
					else
					{
						flag = false;
						coord.X += size_tmpElem + 2;
					}
				} while (flag);
			}
		}

	}

	// ������
	unsigned int getRow() const { return row; }
	unsigned int getCol() const { return col; }

	// �������� ������
	bool DelRow(int pos = -1)
	{
		if (pos == -1) pos = row - 1;
		if (pos < -1 || pos > row - 1) return false;
		


		type** NewData = new type * [row - 1];

		createArr2D(NewData, row - 1, col);

		if (pos != 0)
		{
			for (size_t i = 0; i < pos; i++)
			{
				for (size_t j = 0; j < col; j++)
				{
					NewData[i][j] = data[i][j];
				}
			}
		}
		
		for (size_t i = pos+1, i_posNew = pos; i < row ; i++, i_posNew++)
		{
			for (size_t j = 0, j_posNew = 0; j < col; j++, j_posNew++)
			{
				NewData[i_posNew][j_posNew] = data[i][j];
			}
		}
	
		DeleteArr2D(data, row);
		data = NewData;
		row--;
		return true;
	}

	// �������� �������
	bool DelCol(int pos)
	{
		if (pos < 0 || pos > col - 1) return false;

		type** NewData; 
		createArr2D(NewData, row, col - 1);

		if (pos != 0)
		{
			for (size_t i = 0; i < row; i++)
			{
				for (size_t j = 0; j < pos; j++)
				{
					NewData[i][j] = data[i][j];
				}
			}
		}
	
		for (size_t i = 0; i < row; i++)
		{
			for (size_t j = pos+1, j_NewData = pos; j < col; j++, j_NewData++)
			{
				NewData[i][j_NewData] = data[i][j];
			}
		}

		DeleteArr2D(data, row);
		data = NewData;
		col--;
		return true;
	}

	// ���������� ������������� ��������
	type findMaxElem()
	{
		type res = data[0][0];
		for (size_t i = 0; i < row; i++)
		{
			for (size_t j = 0; j < col; j++)
			{
				if (data[i][j] > res) res = data[i][j];
			}
		}
		return res;
	}

	// ���������� ������������ ��������
	type findMinElem()
	{
		type res = data[0][0];
		for (size_t i = 0; i < row; i++)
		{
			for (size_t j = 0; j < col; j++)
			{
				if (data[i][j] < res) res = data[i][j];
			}
		}
		return res;
	}


	// ���������� ������
	bool AddRow(type*& elem, int pos = -1)
	{
		if (pos < -1 || pos > row) return false;
		if (pos == -1) pos = row;

		type** NewData;
		createArr2D(NewData, row + 1, col);


		for (size_t i = 0; i < pos; i++)
		{
			for (size_t j = 0; j < col; j++)
			{
				NewData[i][j] = data[i][j];
			}
		}

		
		for (size_t i = 0; i < col; i++)
		{
			NewData[pos][i] = elem[i];
		}

		for (size_t i = pos; i < row; i++)
		{
			for (size_t j = 0; j < col; j++)
			{
				NewData[i + 1][j] = data[i][j];
			}
		}

		DeleteArr2D(data, row);
		data = NewData;
		row++;
		return true;
	}

	// ���������� ������� �� ������� � ���
	bool AddCol(type*& elem, int pos = -1)
	{
		if (pos < -1 || pos > col) return false;
		if (pos == -1) pos = col;

		type** NewData;
		createArr2D(NewData, row , col+ 1);

		for (size_t i = 0; i < row; i++)
		{
			for (size_t j = 0; j < pos; j++)
			{
				NewData[i][j] = data[i][j];
			}
		}

		for (size_t i = 0; i < row ; i++)
		{
			NewData[i][pos] = elem[i];
		}

		for (size_t i = 0; i < row; i++)
		{
			for (size_t j_new = pos+1, j_old = pos; j_old < col; j_new++, j_old++)
			{
				NewData[i][j_new] = data[i][j_old];
			}
		}
		DeleteArr2D(data, row);
		data = NewData;
		col++;
		return true;
	}

	// ���������� ����������
	void lineByline_Sort()
	{
		for (size_t i = 0; i < row; i++)
		{
			for (size_t j = 0; j < col-1; j++)
			{
				int min = j;
				for (size_t b = j+1; b < col; b++)
				{
					if (data[i][b] < data[i][min])
						min = b;
				}
				std::swap(data[i][j], data[i][min]);
			}
		}
	}

	// ������ ���������� �������
	void Full_Sort()
	{
		for (size_t i_swap = 0; i_swap < row; i_swap++)
		{
			for (size_t j_swap = 0; j_swap < col; j_swap++)
			{
				int row_min = i_swap;
				int col_min = j_swap;
				for (size_t i = row_min; i < row; i++)
				{
					if (i == row_min)
					{
						for (size_t j = col_min + 1; j < col; j++)
						{
							if (data[i][j] < data[row_min][col_min])
							{
								row_min = i;
								col_min = j;
							}
						}
					}
					else
					{
						for (size_t j = 0; j < col; j++)
						{
							if (data[i][j] < data[row_min][col_min])
							{
								row_min = i;
								col_min = j;
							}
						}
					}
				}
				std::swap(data[i_swap][j_swap], data[row_min][col_min]);
			}
			
		}
	}

};