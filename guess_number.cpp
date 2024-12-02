
#include "guess_number.h"
#include "high_scores.h"
#include <iostream>
#include <string>


int main(int argc, char** argv)
{
    const std::string high_scores_filename = "high_scores_";
    bool only_table = false;
    int level = 0;
    int max = 0;
    std::string user_name;

    if(get_params(argc, argv, only_table, level, max) == -1)
    {
        std::cout << "invalid arguments" << std::endl;
        return -1;
    }

    if(only_table)
    {
        const int max_level = 5;
        for(int i = 1; i<=max_level; i++)
        {
            std::string level_fname = high_scores_filename + std::to_string(i) + ".txt";
            int res2 = read_table(level_fname, i);
        }
    }
    else
    {
        std::cout << "Hi! Enter your name, please:" << std::endl;
        std::cin >> user_name;
        
        if(max > 0 && level > 0)
        {
            std::cout << "defining values simultaneously 'level' and 'max' is not allowed" << std::endl;
            return -2;
        }

        int val = get_target_value( level, max);
        if(val < 0) // error
        {
            std::cout << "invalid level or max value" << std::endl;
            return -3;
        }
        //std::cout << "val = " << val << std::endl;

        int cnt = check_value(val);
	    
        if(cnt > 0)
        {
            std::string level_fname = high_scores_filename + std::to_string(level) + ".txt";
            int res1 = write_score( level_fname, user_name, cnt);
            int res2 = read_table(level_fname, level);
        }
        else
        {
            std::cout << std::endl << "game canceled by user.  bye-bye" << std::endl;
            std::cout << "----------------------" << std::endl;
            
        }
    }

    
    return 0;
}

int get_params(int argc, char** argv, bool& table, int& level, int& max)
{    
    int i = 1;
    while(i < argc)
    {
        std::string arg{ argv[i++] };
        if(arg == "-table")
        {
            table = true;
            break; // выход из цикла (другие параметры уже не интересны)
        }
        else
        {
            if(i>=argc)
                return -1; // error
            if(arg == "-level")                
                level = std::stoi(argv[i++]);            
            else if(arg == "-max")
                max = std::stoi(argv[i++]);
            else
                return -1; // error Неизвестный параметр
        }
    }

    return 0;
}

int get_target_value(int& level, int max)
{
    const int max_value_def = 100;
    const int max_value_max = 100000;
    const int level_def = 2;
    const int max_level = 5;

    if(max<0 || level<0 || level > max_level || max > max_value_max)
        return -1;

    if(level == 0)
    {
        if(max == 0)
        {
            max = max_value_def;
            level = level_def;
;
        }
        else if(max < 10) 
        {
            max = 10;
            level = 1;
        }
        else
        {
            level = std::log10f(max);
        }
    }
    else
    {
        max = std::pow(10, level);
    }
    
    std::cout << "level = " << level <<  ", max = " << max << std::endl;

    std::srand(std::time(nullptr)); // use current time as seed for random generator
	return std::rand() % max;    
}

int check_value(int target_value)
{
    int cnt = 0; // к-во попыток, ==0 -> отказ пользователя
    int current_value;

    std::cout << "Enter your guess:" << std::endl;

    do
    {
        std::cin >> current_value;
        cnt++;
        if(current_value < 0)
        {
            return -1; // cancel by user
        }
        if (current_value > target_value) 
        {
			std::cout << "less than " << current_value << std::endl;
		}
		else if (current_value < target_value) 
        {
			std::cout << "greater than " << current_value << std::endl;
		}
		else 
        {
			std::cout << std::endl << "you win!" << std::endl<< std::endl;
			break;
		}

    } while (true);   

    return cnt;
}