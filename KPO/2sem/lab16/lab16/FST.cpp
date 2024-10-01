#include "FST.h"
#include <iostream>
#include < string.h  > 

namespace FST
{
	RELATION::RELATION(char c, short ns)
	{
		symbol = c;
		nnode = ns;
	};

	NODE::NODE()
	{
		n_relation = 0;
		RELATION* relations = NULL;
	};

	NODE::NODE(short n, RELATION rel, ...)
	{
		n_relation = n;
		RELATION* p = &rel;
		relations = new RELATION[n];
		for (short i = 0; i < n; i++) relations[i] = p[i];
	};

	FST::FST(char* s, short ns, NODE n, ...)
	{
		string = s;
		nstates = ns;
		nodes = new NODE[ns];
		NODE* p = &n;
		for (int k = 0; k < ns; k++) nodes[k] = p[k];
		rstates = new short[nstates];
		memset(rstates, 0xff, sizeof(short) * nstates);
		rstates[0] = 0;
		position = -1;
	};

	bool step(FST& fst, short*& rstates)
	{
		bool rc = false;  // Изначально считаем, что переход не был выполнен

		std::swap(rstates, fst.rstates); // Меняем местами указатели на состояния автомата

		// Проходим по всем состояниям автомата
		for (short i = 0; i < fst.nstates; i++)
		{
			if (rstates[i] == fst.position) // Проверяем, совпадает ли текущее состояние с позицией в строке
			{
				for (short j = 0; j < fst.nodes[i].n_relation; j++) // Если совпадает, проходим по всем отношениям текущего состояния
				{
					if (fst.nodes[i].relations[j].symbol == fst.string[fst.position]) // Проверяем, совпадает ли символ в строке с символом в отношении
					{
						fst.rstates[fst.nodes[i].relations[j].nnode] = fst.position + 1; // Если совпадает, обновляем состояние автомата
						rc = true; // Помечаем, что переход выполнен
					}
				}
			}
		}

		return rc; // Возвращаем true, если хотя бы один переход был выполнен, иначе false
	}


	bool execute(FST& fst)
	{
		short* rstates = new short[fst.nstates]; // Создаем массив состояний
		memset(rstates, 0xff, sizeof(short) * fst.nstates);

		short lstring = strlen(fst.string); // Получаем длину входной строки
		bool rc = true; // Изначально считаем, что автомат примет строку

		for (short i = 0; i < lstring && rc; i++) // Проходим по всей входной строке и выполняем шаги автомата
		{
			fst.position++; // Увеличиваем текущую позицию в строке
			rc = step(fst, rstates); // Выполняем один шаг автомата и обновляем rc
		}

		delete[] rstates; // Освобождаем массив состояний
		return (rc ? (fst.rstates[fst.nstates - 1] == lstring) : rc); // Возвращаем true, если автомат достиг конечного состояния, иначе false
	}

}