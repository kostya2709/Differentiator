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

    Node* node0 = new Node();
    this->Insert_Node (node0);

    File_Read_Cycle (this->first_elem);
    fclose (f);

    return 0;

}



void Tree::File_Read_Cycle (Node* node1)
{
    assert (node1);

    if (*cur_ptr == '\0')
        return;

    int letter_num = 0;

    cur_ptr += 1;                   ///Skips a brace.


    if (*cur_ptr == '$')
        ;
    else if (*cur_ptr == '(')
    {
        Node* node_left = new Node();
        this->Insert_Node (node1, node_left, 0);
        File_Read_Cycle(node_left);
        cur_ptr++;
    }

        if (isalpha (*cur_ptr) && (!isalpha (*(cur_ptr + 1))))
        {
            sscanf (cur_ptr, "%c %n", node1->sym, &letter_num);
            printf ("var = %c\n", *node1->sym);
            node1->node_type = VAR;
        }
        if (isdigit (*cur_ptr) == 0)
        {
            sscanf (cur_ptr, "%[^(, ), 0-9] %n", node1->sym, &letter_num);
            printf ("c = %s\n", node1->sym);
            node1->node_type = OPERATOR;
            printf ("t = %d\n", node1->node_type, node1);
        }
        else
        {
            sscanf (cur_ptr, "%lf %n", &node1->data, &letter_num);
            printf ("num is %lf\n", node1->data);
        }
        cur_ptr += letter_num;      ///Skips the string.

        if (*cur_ptr == ')')
        {
            return;
        }

        if (*cur_ptr == '$')
            ;
        else if (*cur_ptr == ')')
            return;
        else
        {
            Node* node_right = new Node();
            this->Insert_Node (node1, node_right, 1);
            File_Read_Cycle(node_right);
        }
        if (*cur_ptr == ')')
            cur_ptr++;

}

int Calculate_Consts (Node* node1)
{

#define RIGHT_T node1->right->node_type
#define LEFT_T node1->left->node_type
#define NODE_T node1->node_type

    assert (node1);

    if (node1->left)
        if (LEFT_T == OPERATOR)
            Calculate_Consts (node1->left);

    if (node1->right)
        if (RIGHT_T == OPERATOR)
            Calculate_Consts (node1->right);


    elem_t temp = 0;
    elem_t result = 0;
    int done = 0;

    if (node1->left && node1->right)
        if ((NODE_T == OPERATOR) && (LEFT_T == NUMBER) && (RIGHT_T == NUMBER))
        {
            result = Find_Sol (node1->left->data, node1->right->data, node1->sym);
            done = 1;
        }

    if (NODE_T == OPERATOR)
            if (!node1->left && node1->right)
                if (RIGHT_T == NUMBER)
                {
                    result = Find_Sol (node1->right->data, node1->sym);
                    done = 1;
                }

    if (done == 1)
    {
        strcat (node1->sym, "");
        node1->left = NULL;
        node1->right = NULL;
        node1->node_type = NUMBER;
        node1->data = result;

        printf ("result = %lf\n", result);
    }
    done = 0;

#undef LEFT_T
#undef RIGHT_T
#undef NODE_T

}

elem_t Find_Sol (elem_t a, elem_t b, char* operator_t)
{
#define EQU(str) strcmp (operator_t, str) == 0

    if (EQU ("+"))
        return a + b;
    if (EQU ("-"))
        return a - b;
    if (EQU ("*"))
        return a * b;
    if (EQU ("/"))
        return a / b;
    if (EQU ("^"))
        return pow (a, b);
    if (EQU ("log"))
        return (log (b) / log (a));
    else printf ("UNDEFINED OPERATOR \"%s\"! a = %lf, b = %lf\n", operator_t, a, b);

#undef EQU
}

elem_t Find_Sol (elem_t a, char* operator_t)
{
#define EQU(str) strcmp (operator_t, str) == 0

    if (EQU ("sin"))
        return sin (a);
    if (EQU ("cos"))
        return cos (a);
    if (EQU ("tan") || EQU ("tg"))
        return tan (a);
    if (EQU ("cot") || EQU ("ctg"))
        return cos (a) / sin (a);
    if (EQU ("sh") || EQU ("sinh"))
        return sinh (a);
    if (EQU ("ch") || EQU ("cosh"))
        return cosh (a);
    if (EQU ("th") || EQU ("tanh"))
        return tanh (a);
    if (EQU ("cth")||EQU ("cotanh"))
        return cosh (a) / sinh (a);
    if (EQU ("ln"))
        return log (a);
    if (EQU ("log"))
        return log (a) / log (10);

    else printf ("UNDEFINED OPERATOR \"%s\"!\n", operator_t);

#undef EQU
}
