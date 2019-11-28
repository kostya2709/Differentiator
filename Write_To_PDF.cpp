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

int Check_Bracket (Node* node1, char** pos, int bracket);

int Check_Priority (Node* node1);

int Write_Str_To_PDF (char* string)
{
    FILE* f = fopen (Pdf_file, "a");
    fwrite (string, strlen (string), 1, f);
    fclose (f);
}

int Write_Expr_To_PDF (Node* node1, int bracket)
{
    char* expression = (char*)calloc (1, F_SIZE);
    char* ptr = expression;
    int let_num = 0;

    if (bracket)
    {
        let_num = sprintf (ptr, " \\left ( ");
        ptr += let_num;
    }

    Write_Expr_Cycle (node1, &ptr);

    if (bracket)
    {
        let_num = sprintf (ptr, " \\right)'");
        ptr += let_num;
    }



    FILE* f = fopen (Pdf_file, "a");
    fwrite (expression, strlen (expression), 1, f);
    fclose (f);

    free (expression);
}

int Write_Str (char* str_main, char* str_in, char** pos);

int Write_Expr_Cycle (Node* node1, char** ptr)
{

#define Write_Str(str_in) Write_Str (pos, str_in, &pos);

    char* pos = *ptr;
    int let_num = 0;

    if (node1->data == DIV && node1->node_type == OPERATOR)
        Write_Str ("\\cfrac{");

    if (node1->data == POW && node1->node_type == OPERATOR)
        Write_Str ("{");

    if (node1->parent)
        if (node1->node_type == OPERATOR && Check_Priority(node1->parent) > Check_Priority(node1))
            Write_Str ("\\left(");

    if (node1->left)
        Write_Expr_Cycle (node1->left, &pos);


    switch (node1->node_type)
    {
        case NUMBER:
        {
            if (node1->data >= 0)
                let_num = sprintf (pos, "%lg", node1->data);
            else
                let_num = sprintf (pos, "(%lg)", node1->data);
            pos += let_num;
            break;
        }

        case VAR:
        {
            Write_Str (node1->sym);
            break;
        }

        case OPERATOR:
        {
            switch ((int)node1->data)
            {
                case MIN:
                case ADD:
                {
                    Write_Str (node1->sym);
                    break;
                }
                case MUL:
                {
                    Write_Str (" \\cdot ");
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
                    Write_Str ("}");
                    break;
                }
                case POW:
                {
                    Write_Str ("}^");
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

    if (node1->right)
    {
        if (node1->node_type == OPERATOR && (node1->data == DIV || node1->data == POW))
            Write_Str ("{");

        Write_Expr_Cycle (node1->right, &pos);
    }

    Check_Bracket (node1, &pos, 1);

    if (node1->node_type == OPERATOR && ((node1->data == DIV)||(node1->data == POW)))
        Write_Str("}");

    if (Check_Priority (node1) == 2)
        Write_Str ("}");


    *ptr = pos;

#undef Write_Str
}

int Write_Str (char* str_main, char* str_in, char** pos)
{
    int let_num = 0;
    let_num = sprintf (str_main, "%s", str_in);
    *pos += let_num;

    return let_num;
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

    system ("clear");

    return 0;
}

int Check_Bracket (Node* node1, char** pos, int bracket)
{
    int let_num = 0;

    if ((node1->parent)&&(node1->node_type == OPERATOR))
            if (Check_Priority (node1) < Check_Priority (node1->parent))
            {
                        if (bracket == 0)
                            let_num = sprintf (*pos, " \\left (");
                        else if (bracket == 1)
                            let_num = sprintf (*pos, " \\right )");
                        (*pos) += let_num;
            }
    return 0;
}

int Check_Priority (Node* node1)
{
    if (node1->node_type != OPERATOR)
        return -1;
    int oper = node1->data;
    if (oper <= 2)
        return 0;
    if (oper == MUL || oper == DIV)
        return 1;
    if (oper == POW)
        return 3;
    return 2;
}
