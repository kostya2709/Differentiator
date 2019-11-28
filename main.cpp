//!@file

#include "Diff_Head.h"

int main()
{
    Read_Aloud ("Здорово");

    char* file_name = "problem.txt";
    File_Clean();

    Write_From_File ("hat.txt");
    Write_From_File ("Intro.txt");

    const char* der_var = "x";

    Tree calc1;

    Tree calc;
    calc.File_Read (file_name);
    calc.Dump();


    calc1.first_elem = Tree_Copy(calc.first_elem);
    //Insert_Var(calc1.first_elem, "x", 3);
    //calc1.Tree_Simplifier (calc1.first_elem);

    STARTL;
    Write_Expr_To_PDF (calc1.first_elem, 0);
    ENDL;

    //calc1.Dump();
    //calc1.Tree_Simplifier (calc1.first_elem);
    //calc1.Make_Simple_Tree (calc1.first_elem);
    //calc1.Make_Simple_Tree (calc1.first_elem);
    calc1.Calculate_Consts (calc1.first_elem);

    //calc1.Find_Derive (calc1.first_elem, "x");
    calc1.Make_Simple_Tree (calc1.first_elem);
    calc1.Calculate_Consts (calc1.first_elem);
    //calc1.Tree_Simplifier (calc1.first_elem);
    calc1.Dump();
//!x*(2*x+3)
    Write_From_File ("answer.txt");

    STARTL;
    Write_Expr_To_PDF (calc.first_elem, 1);
    Write_Str_To_PDF ("=");
    Write_Expr_To_PDF (calc1.first_elem, 0);
    ENDL;

    Write_From_File ("Ending.txt");

    //Compile_LaTex ();

    return 0;
}


/*!
To do

- Make_Simple
- arcsin, ...
-Talor
-Add modified
Make_Simple to "So..."

*/
