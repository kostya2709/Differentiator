#include "Diff_Head.h"

Node* Tree::Find_Derive (Node* node1, const char* der_var)
{

#include "DEFINES.h"

    if (node1->right || node1->left)
    {
        Write_From_File ("let's_ take_derive.txt");
        STARTL;
        DER(node1);
        PUT_STR ("=");
    }


Node* answer = NULL;

        switch (node1->node_type)
        {
            case OPERATOR:
            {
                switch ((int)N_DATA)
                {
                    case (MIN):
                    {
                        DER(node1->left);
                        PUT_STR("-");
                        DER(node1->right);
                        ENDL;

                        answer = dMIN (dL, dR);

                        break;
                    }
                    case (ADD):
                    {
                        DER(node1->left);
                        PUT_STR("+");
                        DER(node1->right);
                        ENDL;

                        answer = dSUM (dL, dR);
                        break;
                    }

                    case (MUL):
                    {
                        DER(node1->left);
                        PUT_STR(" \\cdot ");
                        PUT(node1->right);
                        PUT_STR ("+");
                        PUT(node1->left);
                        PUT_STR ("\\cdot");
                        DER (node1->right);
                        ENDL;

                        answer = dSUM (dMUL(dL, cR), dMUL (cL, dR));
                        break;
                    }
                    case (DIV):
                    {
                        PUT_STR ("\\cfrac{");
                        DER (node1->left);
                        PUT_STR (" \\cdot ");
                        PUT (node1->right);
                        PUT_STR ("-");
                        PUT (node1->left);
                        PUT_STR (" \\cdot ");
                        DER (node1->right);
                        PUT_STR ("}{ \\left (");
                        PUT (node1->right);
                        PUT_STR (" \\right )^2}");
                        ENDL;

                        answer = dDIV (dMIN (dMUL (dL, cR), dMUL (cL, dR)), dSQR(cR));
                        break;
                    }
                    case (POW):
                    {

                        if (node1->right->node_type == NUMBER)
                        {
                            PUT_R;
                            PUT_STR (" \\cdot \\left(");
                            PUT_L;
                            PUT_STR (" \\right)^{");
                            PUT_R;
                            PUT_STR ("- 1}");
                            ENDL;

                            answer = dMUL ( dMUL (dPOW (cL, CONST(R_DATA - 1)), cR), cL);
                        }
                        else
                        {
                        printf ("OK\n");
                            PUT_STR ("\\left(e^{ln(");
                            PUT_L;
                            PUT_STR (") \\cdot ");
                            PUT_R;
                            PUT_STR ("}\\right)'=e^{ln(");
                            PUT_L;
                            PUT_STR (") \\cdot ");
                            PUT_R;
                            PUT_STR ("}\\cdot \\left(ln(");
                            PUT_L;
                            PUT_STR (") \\cdot ");
                            PUT_R;
                            PUT_STR ("\\right)'=")

                            PUT_STR (" \\left(")
                            PUT_R;
                            PUT_STR (" \\right)^{");
                            PUT_L;
                            PUT_STR ("} \\cdot \\left(ln(");
                            PUT_L;
                            PUT_STR (") \\cdot ");
                            PUT_R;
                            PUT_STR (" \\right)'");
                            ENDL;

                            answer = dMUL (id, dMUL (dLN (cL), cR));
                        }

                        break;
                    }
                    case (LN):
                    {
                        PUT_STR ("\\frac{1}{");
                        PUT_R;
                        PUT_STR ("} \\cdot \\left(");
                        PUT_R;
                        PUT_STR ("\\right)'");
                        ENDL;

                        answer = dMUL (dDIV (CONST(1), cR), cR);
                        break;
                    }
                    case (LOG):
                    {
                        answer = dDIV (dLN (cL), dLN (cR));
                        break;
                    }
                    case (LG):
                    {
                        answer = dDIV (dLN (cR), dLN (CONST (10)));
                        break;
                    }
                    case (SIN):
                    {

                        answer = dMUL (dCOS, cR);

                        PUT (answer->left);
                        PUT_STR ("\\cdot \\left(");
                        PUT_R;
                        PUT_STR (" \\right)'");
                        ENDL;
                        break;
                    }
                    case (COS):
                    {
                        answer = dMUL ( dMUL (CONST (-1), dSIN), cR);
                        break;
                    }
                    case (TAN):
                    {
                        answer = dMUL (dDIV (CONST (1), dSQR (dCOS) ), cR);
                        break;
                    }
                    case (COTAN):
                    {
                        answer = dMUL ( dDIV ( CONST (-1), dSQR (dSIN)), cR);
                        break;
                    }
                    case (SH):
                    {
                        answer = dMUL (dCH, cR);
                        break;
                    }
                    case (CH):
                    {
                        answer = dMUL (dSH, cR);
                        break;
                    }
                    case (TH):
                    {
                        answer = dMUL (dDIV (CONST (1), dSQR (dCH)), cR);
                        break;
                    }
                    case (CTH):
                    {
                        answer = dMUL (dDIV (CONST (-1), dSQR (dSH)), cR);
                        break;
                    }

                    default:
                    {
                        printf ("Unidentified operator " ACCUR "!\n", N_DATA);
                        break;
                    }

                }

                break;
            }

            case NUMBER:
            {
                N_DATA = 0;
                break;
            }

            case VAR:
            {
                if (!strcmp(node1->sym, der_var))
                {
                    N_DATA = 1;
                }
                else
                {
                    N_DATA = 0;
                }
                node1->node_type = NUMBER;
                break;
            }

            default:
            {
                printf ("Unidentified node_type %d!\n", node1->node_type);
                break;
            }
        }

    if (N_DATA == LOG || N_DATA == LG)
        answer = Find_Derive (answer);


    switch ((int)N_DATA)
    {
        case POW: case LN:case SIN:case COS: case TAN: case COTAN:
        case SH: case CH: case TH: case CTH:
        answer->right = Find_Derive (answer->right);
        break;
    }

    if (answer)
        if (node1->left && node1->right)
            if (node1->left->node_type == OPERATOR || node1->right->node_type == OPERATOR)
    {
        PUT_STR ("So, derive is:\n");
        STARTL;
        DER(node1);
        PUT_STR ("=");
        PUT (answer);
        ENDL;
    }

    if (answer)
    {
        if (node1->parent)
            if (node1->parent->left == node1)
                this->Insert_Node (node1->parent, answer, 0);
            else this->Insert_Node (node1->parent, answer, 1);
        else this->Insert_Node (answer);

        return answer;
    }

#include "UNDEFINES.h"

    return node1;

}

