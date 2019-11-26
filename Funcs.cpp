#include "Diff_Head.h"


char* cur_ptr = NULL;


char* Delete_Str_Trash (char* str)
{
    char* new_str = (char*) calloc (1, strlen (str));

    char* start = new_str;

    int in_quotes = 0;

    while (*str)
    {
        if (*str == '\"')
            if (in_quotes == 0)
                in_quotes = 1;
            else in_quotes = 0;

        if (((*str == ' ') || (*str =='\t') || (*str == '\n'))&& in_quotes == 0)
            ;
        else
        {
            *new_str = *str;
            new_str++;
        }
        str++;
    }

    return start;
}


int Tree::File_Read (char* file_name)
{
    assert (file_name);

    FILE* f = fopen (file_name, "r");

    char* string = (char*)calloc(1, FILE_SIZE);
    fread (string, 1, FILE_SIZE, f);

    cur_ptr = Delete_Str_Trash(string);
    free (string);

    int letter_num = 0;

    //File_Read_Cycle (this->first_elem);
printf ("stroka %s\n", cur_ptr);
    this->Insert_Node (Get_General (cur_ptr));

    fclose (f);

    return 0;

}


int Find_Operator (char* oper)
{
#define EQU(str) strcmp (oper, str) == 0

    if (EQU ("+"))
        return ADD;
    if (EQU ("-"))
        return MIN;
    if (EQU ("*"))
        return MUL;
    if (EQU ("/"))
        return DIV;
    if (EQU ("^") || EQU ("pow"))
        return POW;
    if (EQU ("log"))
        return LOG;

    if (EQU ("sin"))
        return SIN;
    if (EQU ("cos"))
        return COS;
    if (EQU ("tan") || EQU ("tg"))
        return TAN;
    if (EQU ("cot") || EQU ("ctg"))
        return COTAN;
    if (EQU ("sh") || EQU ("sinh"))
        return SH;
    if (EQU ("ch") || EQU ("cosh"))
        return CH;
    if (EQU ("th") || EQU ("tanh"))
        return TH;
    if (EQU ("cth")||EQU ("cotanh")||EQU("coth"))
        return CTH;
    if (EQU ("ln"))
        return LN;
    if (EQU ("lg"))
        return LG;

    return -1;
#undef EQU
}

int Insert_Var (Node* node1, char* var_name, elem_t value)
{
    if (node1->left)
        Insert_Var (node1->left, var_name, value);
    if (node1->right)
        Insert_Var (node1->right, var_name, value);

    if (node1->node_type == VAR && (!strcmp(node1->sym, var_name)))
    {
        node1->node_type = NUMBER;
        node1->data = value;
    }
    return 0;
}
