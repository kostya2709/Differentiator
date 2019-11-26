#include "Diff_Head.h"

const char* str_ptr = NULL;

Node* Get_General (const char* str);

Node* Get_Number (void);

Node* Get_Expr (void);

Node* Get_Top (void);

Node* Get_Pbrack (void);

Node* Func (char* oper);

Node* Get_Str (void);

Node* Get_General (const char* str)
{
    str_ptr = str;
    Node* result = Get_Expr();
    if (*str_ptr != '\0')
        printf ("WTF\n");
    else str_ptr++;

    return result;
}

Node* Get_Number (void)
{
    double val = 0;
    int let_num = 0;

    Node* node1 = NULL;
    char* sym = (char*)calloc (1, operator_size);

    sscanf (str_ptr, "%lf %n", &val, &let_num);
    printf ("num = %lf\n", val);

    str_ptr += let_num;
    printf ("next = %c\n", *str_ptr);

    if (let_num == 0)
    {
        printf ("An Error detected! Expected a symbol in N!\n");
        return NULL;
    }

    return Create_Node (NULL, NULL, NULL, val, "", NUMBER);
}

Node* Get_Expr (void)
{
    Node* res = Get_Top ();
    Node* res3 = res;
    while ((*str_ptr == '+') || (*str_ptr == '-'))
    {
        char op = *str_ptr;
        str_ptr++;
        printf ("oper = %c\n", *str_ptr);
        Node* res2 = Get_Top();

        if (op == '+')
            res3 = Create_Node(res3, res2, NULL, ADD, "+", OPERATOR);
        else res3 = Create_Node(res3, res2, NULL, ADD, "-", OPERATOR);
    }

    return res3;
}

Node* Get_Top (void)
{
    Node* val = Get_Pbrack ();
    while ((*str_ptr == '*') || (*str_ptr == '/'))
    {
        char op = *str_ptr;
        str_ptr++;
        printf ("oper = %c\n", op);
        Node* val2 = Get_Pbrack();

        if (op == '*')
            val = Create_Node (val, val2, NULL, MUL, "*", OPERATOR);
        else if (op == '/')
            val = Create_Node (val, val2, NULL, DIV, "/", OPERATOR);
    }
assert (val);
    return val;
}


Node* Get_Pbrack (void)
{
    if (*str_ptr == '(')
    {
        str_ptr++;
        Node* val = Get_Expr();
        if (*str_ptr == ')')
            printf ("OK\n");
        else
        {
            printf ("Expected ')'!\n");
            system ("pause");
        }
        str_ptr++;
        return val;
    }
    else if (*str_ptr >= '0' && *str_ptr <= '9')
        return Get_Number();
    else
        Get_Str();

}

Node* Func (char* oper)
{
    if (*str_ptr != '(')
    {
        printf ("Expected an opening bracket after function %s!\n", oper);
        system ("pause");
    }
    str_ptr++;
    Node* val = Get_Expr();
    if (*str_ptr != ')')
    {
        printf ("Expected a closing bracket after function %s!\n", oper);
        system ("pause");
    }
    str_ptr++;

    return Create_Node (NULL, val, NULL, Find_Operator (oper), oper, OPERATOR);
}

Node* Get_Str (void)
{
    char* oper = (char*)calloc (1, operator_size);
    int let_num = 0;
    sscanf (str_ptr, "%[a-z, A-Z] %n", oper, &let_num);
    str_ptr += let_num;

    if (Find_Operator(oper) != -1)
                return Func(oper);
    else return Create_Node (NULL, NULL, NULL, -2, oper, VAR);

}
