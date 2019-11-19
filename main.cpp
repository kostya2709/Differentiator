//!@file

#include "Diff_Head.h"

int main()
{

    char* file_name = "problem.txt";

    Tree calc;

    calc.File_Read (file_name);

    calc.Calculate_Consts (calc.first_elem);

    calc.Make_Simple_Tree (calc.first_elem);

    calc.Dump();

    return 0;
}
