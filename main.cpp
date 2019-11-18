//!@file

#include "Diff_Head.h"

int main()
{

    char* file_name = "problem.txt";

    Tree calc;

    Node node1;
    node1.node_type = OPERATOR;
    node1.sym = '+';

    Node node2;
    node2.node_type = NUMBER;
    node2.data = 2;

    Node node3;
    node3.node_type = NUMBER;
    node3.data = 2;


    //calc.Insert_Node (&node1);
    //calc.Insert_Node (&node1, &node2, 0);
    //calc.Insert_Node (&node1, &node3, 1);

    calc.File_Read (file_name);
    calc.Dump();

    return 0;
}
