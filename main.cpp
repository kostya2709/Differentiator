//!@file

#include "Diff_Head.h"

int main()
{
    //Read_Aloud ("Здорово, люди!");

    char* file_name = "problem.txt";
    File_Clean();
    Write_From_File ("Intro.txt");

    const char* der_var = "x";

    Tree calc1;
    calc1.File_Read (file_name);
    //Insert_Var(calc1.first_elem, "x", 3);
    //calc1.Tree_Simplifier (calc1.first_elem);

    Write_Expr_To_PDF (calc1.first_elem);

    //calc1.Dump();
    //calc1.Tree_Simplifier (calc1.first_elem);
    //calc1.Make_Simple_Tree (calc1.first_elem);
    //calc1.Make_Simple_Tree (calc1.first_elem);
    calc1.Calculate_Consts (calc1.first_elem);

    calc1.Find_Derive (calc1.first_elem, "x");
    calc1.Make_Simple_Tree (calc1.first_elem);
    calc1.Calculate_Consts (calc1.first_elem);
    //calc1.Tree_Simplifier (calc1.first_elem);
    calc1.Dump();
    Write_Expr_To_PDF (calc1.first_elem);


    Write_From_File ("Ending.txt");

    Compile_LaTex ();

    return 0;
}
