#include "high_scores.h"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>


int write_score( const std::string level_filename, const std::string user_name, int newScore)
{
	// данные в каждом файле по уровням должны быть отсортированы, и без поторений имен, если файл был заполнен не этой программой
	// , либо отсутствовать	

	if(std::filesystem::exists(level_filename))
	{		
		std::ifstream in_file{level_filename};
		if (!in_file.is_open()) 
		{
			std::cout << "Failed to open file for read: " << level_filename << "!" << std::endl;
			return -1;
		}
		
		const int max_lines = 10;
		std::string* lines = new std::string[max_lines];

		int ii=0;		
		while((ii<max_lines) && std::getline(in_file, lines[ii])  )
		{
			if(lines[ii].length() >0)
				ii++;			
		}
		int count_lines = ii;		
		in_file.close();

		std::ofstream out_file{level_filename, std::ios_base::trunc}; // открываем файл на перезапись
		if (!out_file.is_open()) {
			std::cout << "Failed to open file for write: " << level_filename << "!" << std::endl;
			delete[](lines);
			return -1;
		}

		int saves = 0;
		bool weak_attempt = false;
		int insertion_index = 0;
		
		for(int i= 0; i< count_lines; i++)
		{
			std::string line = lines[i];
			int pos = line.find(" ");

			std::string saved_name = line.substr(0,pos);
			int score = std::stoi(line.substr(pos+1));

			// записываем оригинальные записи, пока они не хуже новой
			if(score <= newScore)
			{				
				out_file << saved_name << ' ' << score << std::endl;
				if (++saves >= max_lines)
					break;
	
				if(saved_name == user_name) // нашли более лучшую попытку этого же пользователя					
					weak_attempt = true;
				
				insertion_index = i + 1;

				// если обраотали последнюю линию (и она все еще лучше вводимой попытки), и не вышли из цикла раньше по превышению max_lines
				// - то вставляем вводимую попытку (если не была зафиксирована неудачная попытка)
				if( i== count_lines-1 && !weak_attempt) 
				{					
					out_file << user_name << ' ' << newScore << std::endl;
				}				
			}	
			else
			{
				if (weak_attempt) // если была зафиксирована неудачная попытка, то записываем очередную оригинальную запись (имя проверять не нужно - уже встречалось)
				{
					out_file << saved_name << ' ' << score << std::endl;
					if (++saves >= max_lines)
						break;
				}
				else
				{
					if (i == insertion_index) // индекс == индекс вставки - первый индекс после превышения результата (и имя еще не встречалось)
					{
						// пишем новую запись
						out_file << user_name << ' ' << newScore << std::endl;
						if (++saves >= max_lines)
							break;
					}

					// проверка имени в очередной линии. записываем только если не совпадает с именем из вводимой линии(т.к. с таким уже вставляли)
					if (saved_name != user_name)
					{
						out_file << saved_name << ' ' << score << std::endl;
						if (++saves >= max_lines)
							break;
					}
				}
			}
		}
		delete[](lines);
		out_file.close();
	}
	else // если еще нет файла - создаем с единственной записью
	{
		std::ofstream out_file{level_filename, std::ios_base::app};
		if (!out_file.is_open()) {
			std::cout << "Failed to open file for write: " << level_filename << "!" << std::endl;
			return -1;
		}
		out_file << user_name << ' ' << newScore << std::endl;		
		out_file.close();
	}	

	return 0;
}


int read_table(const std::string level_filename, int level)
{	
		
	if(std::filesystem::exists(level_filename))
	{
		std::ifstream in_file{level_filename};
		if (!in_file.is_open()) 
		{
			std::cout << "Failed to open file for read: " << level_filename << "!" << std::endl;
			return -1;
		}

		std::cout << "===== level  " << level << " =====" <<   std::endl;
		std::string line;
		while( std::getline(in_file, line))
		{
			std::cout << line << std::endl;
		}    
		in_file.close();
	}		
	
	return 0;
}