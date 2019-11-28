
#define Find_Derive(node) Find_Derive(node, der_var)

#define dL Find_Derive(cL)
#define dR Find_Derive(cR)

#define cL Tree_Copy(node1->left)
#define cR Tree_Copy(node1->right)

#define dSUM(node_l, node_r)                                \
Create_Node(node_l, node_r, NULL, ADD, "+", OPERATOR)

#define dMUL(node_l, node_r)                                \
Create_Node(node_l, node_r, NULL, MUL, "*", OPERATOR)

#define dMIN(node_l, node_r)                                \
Create_Node(node_l, node_r, NULL, MIN, "-", OPERATOR)

#define dDIV(node_l, node_r)                                \
Create_Node(node_l, node_r, NULL, DIV, "/", OPERATOR)



#define dSIN                                                \
Create_Node(NULL, cR, NULL, SIN, "sin", OPERATOR)

#define dCOS                                                \
Create_Node(NULL, cR, NULL, COS, "cos", OPERATOR)

#define dSH                                                 \
Create_Node(NULL, cR, NULL, SIN, "sh", OPERATOR)

#define dCH                                                 \
Create_Node(NULL, cR, NULL, COS, "ch", OPERATOR)



#define dSQR(node2)                                          \
Create_Node(node2, CONST (2), NULL, POW, "^", OPERATOR)

#define id Tree_Copy(node1)

#define CONST(num)                                          \
Create_Node(NULL, NULL, NULL, num, " ", NUMBER)

#define dLN(node2)                                          \
Create_Node(NULL, node2, NULL, LN, "ln", OPERATOR)

#define dPOW(node_l, node_r)                                \
Create_Node(node_l, node_r, NULL, POW, "^", OPERATOR)

#define R_DATA node1->right->data
#define N_DATA node1->data

#define PUT_STR(str) Write_Str_To_PDF (str);
#define DER(node2) Write_Expr_To_PDF(node2, 1);
#define PUT(node2) Write_Expr_To_PDF(node2, 0);
#define PUT_L Write_Expr_To_PDF(node1->left, 0);
#define PUT_R Write_Expr_To_PDF(node1->right, 0);
