#include "Diff_Head.h"

int DONE = 0;

int Tree::Calculate_Consts (Node* node1)
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
    int ddone = 0;

    if (node1->left && node1->right)
        if ((NODE_T == OPERATOR) && (LEFT_T == NUMBER) && (RIGHT_T == NUMBER))
        {
            result = Find_Sol (node1->left->data, node1->right->data, node1->data);
            ddone = 1;
            DONE = 1;
        }

    if (NODE_T == OPERATOR)
            if (!node1->left && node1->right)
                if (RIGHT_T == NUMBER)
                {
                    result = Find_Sol (node1->right->data, node1->data);
                    ddone = 1;
                    DONE = 1;
                }

    if (ddone == 1)
    {
        strcat (node1->sym, "");
        node1->left = NULL;
        node1->right = NULL;
        node1->node_type = NUMBER;
        node1->data = result;

    }

#undef LEFT_T
#undef RIGHT_T
#undef NODE_T

    return ddone;

}

elem_t Find_Sol (elem_t a, elem_t b, int operator_t)
{

    switch (operator_t)
    {
        case ADD: return a + b;
        case MIN:
        {
            if (a == 0) return b * (-1);
            return a - b;
        }
        case MUL: return a * b;
        case DIV: return a / b;
        case POW: return pow (a, b);
        case LOG: return log (b) / log (a);

        default: printf ("UNDEFINED OPERATOR \"%d\"! a = %lf, b = %lf\n", operator_t, a, b);

    }
    return -1;
}

elem_t Find_Sol (elem_t a, int operator_t)
{

    switch (operator_t)
    {
        case SIN: return sin (a);
        case COS: return cos (a);
        case TAN: return tan (a);
        case COTAN: return cos (a) / sin (a);
        case SH: return sinh (a);
        case CH: return cosh (a);
        case TH: return tanh (a);
        case CTH: return cosh (a) / sinh (a);
        case LN: return log (a);
        case LG: return log (a) / log (10);

        default: printf ("UNDEFINED OPERATOR \"%d\"!\n", operator_t);
    }

    return -1;
}

int Tree::Make_Simple_Tree (Node* node1)
{
#define RIGHT_T node1->right->node_type
#define LEFT_T node1->left->node_type
#define NODE_T node1->node_type

    assert (node1);

    if (node1->left)
        if (LEFT_T == OPERATOR)
            Make_Simple_Tree (node1->left);

    if (node1->right)
        if (RIGHT_T == OPERATOR)
            Make_Simple_Tree (node1->right);


    if (node1->left && node1->right)
        if ((NODE_T == OPERATOR) && ((LEFT_T == NUMBER) || (RIGHT_T == NUMBER)))
        {
            if (node1->left->data == 0 || node1->right->data == 0)
                Kill_Zero (node1);
            else if (node1->right->data == 1 || node1->right->data == 1)
                Kill_One (node1);
        }


#undef LEFT_T
#undef RIGHT_T
#undef NODE_T
}

int Tree::Kill_Zero (Node* node1)
{

    Node* kill = NULL;
    Node* live = NULL;
    int dir = 0;

    if (node1->right->data == 0)
    {
        kill = node1->right;
        live = node1->left;
        dir = 1;
    }
    else
    {
        kill = node1->left;
        live = node1->right;
    }

    switch ((int)node1->data)
    {

    case MUL:
        {
            live->data = 0;
            live->node_type = NUMBER;
            break;
        }
    case DIV:
        {
            if (dir == 1)
                printf ("ERROR! ATTEMPT OF DIVISION ON ZERO!\n");
            else
            {
                live->data = 0;
                live->node_type = NUMBER;
            }

            break;
        }
    case POW:
        {
            if (dir == 1)
            {
                live->data = 1;
                live->node_type = NUMBER;
            }
            else
            {
                live->data = 0;
                live->node_type = NUMBER;
            }
            break;
        }


    }

    if (node1->data == MIN && dir == 0)
    {
        node1->data = MUL;
        sprintf (node1->sym, "*");
        node1->left = Create_Node(NULL, NULL, node1, -1, " ", NUMBER);
        return 0;
    }

        if (node1->parent == NULL)
            Insert_Node(live);
        else
            if (node1 == node1->parent->left)
                Insert_Node(node1->parent, live, 0);
            else
                Insert_Node(node1->parent, live, 1);
        DONE = 1;


    return 0;
}

int Tree::Kill_One (Node* node1)
{
    Node* kill = NULL;
    Node* live = NULL;
    int dir = 0;

    if (node1->right->data == 1)
    {
        kill = node1->right;
        live = node1->left;
        dir = 1;
    }
    else
    {
        kill = node1->left;
        live = node1->right;
    }

    if (node1->data == POW && dir == 0)
    {
        live->data = 1;
        live->node_type = NUMBER;
    }

    if (node1->data == LOG && dir == 1)
    {
        live->data = 0;
        live->node_type = NUMBER;
    }

    if ((node1->data == LOG) || (node1->data == POW) || (node1->data == MUL) || ((node1->data == DIV)&&(dir == 1)))
    {
        if (node1->parent == NULL)
            Insert_Node(live);
        else
            if (node1 == node1->parent->left)
                Insert_Node(node1->parent, live, 0);
            else
                Insert_Node(node1->parent, live, 1);
        DONE = 1;
    }


    return 0;
}

int Tree::Tree_Simplifier (Node* node1)
{
    DONE = 1;
    int temp = 0;

    while (DONE)
    {
    printf ("So\n");
        DONE = 0;
        this->Make_Simple_Tree (node1);
        temp = DONE;
        this->Calculate_Consts (node1);
        temp += DONE;
        DONE = temp;
        DONE = 0;
    }

    return 0;
}

