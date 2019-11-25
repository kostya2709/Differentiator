#include "Diff_Head.h"
#include <locale.h>

const int F_SIZE = 2048;


const char* Pdf_file = "Derive.tex";
const char* Pdf_file1 = "Derive.pdf";

int Write_From_File (char* file_name)
{
    setlocale (LC_ALL, "RUS");

    wchar_t* file_text = (wchar_t*)calloc (1, F_SIZE);
    FILE* f = fopen (file_name, "r");
    fread (file_text, 1, F_SIZE, f);
    fclose (f);

    f = fopen (Pdf_file, "a");
    fwrite (file_text, strlen ((char*)file_text), 1, f);
    fclose (f);
}

int Write_Expr_Cycle (Node* node1, char** pos);

int Check_Bracket (Node* node1, char** pos, char bracket);

int Check_Priority (Node* node1);

int Write_Expr_To_PDF (Node* node1)
{
    char* expression = (char*)calloc (1, FILE_SIZE);
    char* ptr = expression;
    int let_num = 0;

    sprintf (ptr, "\n$$");
    ptr += 3;

    Write_Expr_Cycle (node1, &ptr);

    sprintf (ptr, "$$\n");

    printf ("stroka = \n%s\n", expression);

    FILE* f = fopen (Pdf_file, "a");
    fwrite (expression, strlen (expression), 1, f);
    fclose (f);

    free (expression);
}

int Write_Expr_Cycle (Node* node1, char** ptr)
{
    char* pos = *ptr;
    int let_num = 0;
    printf ("%lf %d\n", node1->data, node1->node_type);

    if (node1->data == DIV)
        {
            let_num = sprintf (pos, "\\frac{");
            pos += let_num;
        }

    if (node1->left)
        Write_Expr_Cycle (node1->left, &pos);

    Check_Bracket (node1, &pos, '(');

    switch (node1->node_type)
    {
        case NUMBER:
        {
            if (node1->data > 0)
                let_num = sprintf (pos, "%lg", node1->data);
            else
                let_num = sprintf (pos, "(%lg)", node1->data);
            pos += let_num;
            break;
        }

        case VAR:
        {
            let_num = sprintf (pos, "%s", node1->sym);
            pos += let_num;
            break;
        }

        case OPERATOR:
        {
            switch ((int)node1->data)
            {
                case MIN:
                case ADD:
                {
                    let_num = sprintf (pos, "%s", node1->sym);
                    pos += let_num;
                    break;
                }
                case MUL:
                {
                    let_num = sprintf (pos, "\\cdot");
                    pos += let_num;
                    break;
                }
                case SIN: case COS: case TAN:case COTAN:
                case SH:  case CH:  case TH: case CTH:
                case LG:  case LN:
                {
                    let_num = sprintf (pos, "\\%s{", node1->sym);
                    pos += let_num;
                    break;
                }
                case DIV:
                {
                    let_num = sprintf (pos, "}{");
                    pos += let_num;
                    break;
                }

            default:
            {
                printf ("Unidentified operator %d\n", node1->node_type);
                break;
            }
            }
            break;
        }
        default:
        {
            printf ("Unidentified node_type %d\n", node1->node_type);
            break;
        }
    }

    Check_Bracket (node1, &pos, ')');

    if (node1->parent)
        if (node1 == node1->parent->right && Check_Priority (node1->parent)== 2)
        {
            sprintf (pos, "}");
            pos++;
        }

    if (node1->right)
        Write_Expr_Cycle (node1->right, &pos);
    if (node1->parent)
        if (node1 == node1->parent->right && node1->parent->data == DIV)
        {
            sprintf (pos, "}");
            pos++;
        }

    *ptr = pos;

}

int File_Clean ()
{
    FILE* f1 = fopen (Pdf_file, "w");
    fclose (f1);
}

int Compile_LaTex (void)
{
    char* call = (char*)calloc (1, FILE_SIZE);
    sprintf (call, "pdflatex ");
    strcat (call, Pdf_file);
    system (call);

    sprintf (call, "xdg-open ");
    strcat (call, Pdf_file1);
    system (call);
    return 0;
}

int Check_Bracket (Node* node1, char** pos, char bracket)
{

    if (node1->parent)
        if (node1->parent->parent)
            if (Check_Priority (node1->parent) < Check_Priority (node1->parent->parent))
            {
                if (node1 == node1->parent->left && bracket == '(' ||
                    node1 == node1->parent->right && bracket == ')')
                    {
                        sprintf (*pos, "%c", bracket);
                        (*pos)++;
                    }
            }
    return 0;
}

int Check_Priority (Node* node1)
{
    int oper = node1->data;
    if (oper <= 2)
        return 0;
    if (oper == 3 || oper == 4)
        return 1;
    return 2;
}
