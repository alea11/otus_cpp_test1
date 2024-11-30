#include "ex.h"
#include <iostream>

void message_1(); // если вызываемая функция определена ниже вызова, то необходимо ее объявить раньше

int main()
{
   std::cout << "Hello from main func" << std::endl;
   message_1();
   message_2();

   return 0;
}

void message_1()
{
   std::cout << "Hello from message_1 func" << std::endl;
}
