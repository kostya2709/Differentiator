//!@file

#include "Diff_Head.h"

int main()
{

    char* file_name = "problem.txt";

    Tree calc;

    calc.File_Read (file_name);

    Tree calc1;
    calc1.Insert_Node (Tree_Copy (calc.first_elem));
    calc1.Dump();

    calc1.Tree_Simplifier (calc1.first_elem);
    //calc1.Tree_Simplifier (calc1.first_elem);
    //calc1.Make_Simple_Tree (calc1.first_elem);
    //calc1.Make_Simple_Tree (calc1.first_elem);
    //calc1.Calculate_Consts (calc1.first_elem);

    calc1.Find_Derive (calc1.first_elem);
    //calc1.Calculate_Consts (calc1.first_elem);
    //calc1.Make_Simple_Tree (calc1.first_elem);
    calc1.Tree_Simplifier (calc1.first_elem);

    calc1.Dump();
//(((x) * (2))^(2))
    return 0;
}
