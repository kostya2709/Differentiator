#include "Diff_Head.h"

Node::Node(): left (NULL), right (NULL), data (-1), node_type (0)
{
    sym = 'k';
}

Node::~Node()
{

}

Tree::Tree(): elem_num (0)
{
    Node zero_node;
    this->first_elem = &zero_node;
}

Tree::~Tree()
{

}

int Tree::Insert_Node (Node* node1, Node* node_new, int pos)
{
    assert (node_new);
    assert (node1);

    if (pos == 0)
        node1->left = node_new;
    else if (pos == 1)
        node1->right = node_new;
    else
    {
        printf ("Error! Wrong position in Insert_Node\n\
                 Expected 0 for left or 1 for right. Received %d.", pos);
        return -1;
    }
    this->elem_num += 1;

    node_new->parent = node1;

    return 0;
}

int Tree::Insert_Node (Node* node_new)
{
    assert (node_new);

    if (this->elem_num == 0)
    {
        this->first_elem = node_new;
        this->elem_num = 1;
        return 0;
    }

    printf ("Error! Your tree is not empty!\n");
    return -1;
}

int Tree::Dump (void)
{
    char* file_name = (char*)calloc (1, FILE_NAME_SIZE);
    char* file_png = (char*)calloc (1, FILE_NAME_SIZE);

    file_name = "equation_print.gv";
    file_png = "equation_print_pic.png";

    FILE* f = fopen (file_name, "w");

    fprintf (f, "digraph First{\n");
    fprintf (f, "node [shape=\"Mrecord\", style=\"filled\", fillcolor=\"lightblue\"];\n");

    Tree_Print (this->first_elem, f);

    fprintf (f, "}");

    fclose (f);

    system ("dot -Tpng equation_print.gv -o equation_print_pic.png");


    file_name = "equation_dump.gv";
    file_png = "equation_dump_pic.png";

    f = fopen (file_name, "w");

    fprintf (f, "digraph First{\n");
    fprintf (f, "node [shape=\"Mrecord\", style=\"filled\", fillcolor=\"lightblue\"];\n");

    Tree_Info_Dump(this->first_elem, f);

    fprintf (f, "}");

    fclose (f);

    system ("dot -Tpng equation_dump.gv -o equation_dump_pic.png");

    return 0;
}

void Tree::Tree_Print (const Node* node1, FILE* f)
{
    assert (node1);

    if (node1 == this->first_elem)
    {
        if (node1->node_type == NUMBER)
            fprintf (f, "\"box%0x\" [label=\"" ACCUR "\"];\n", node1, node1->data);
        else
            fprintf (f, "\"box%0x\" [label=\"" "%c" "\"];\n", node1, node1->sym);
    }

    if (node1->left)
        {
            if (node1->left->node_type == NUMBER)
                fprintf (f, "\"box%0x\" [label=\"" ACCUR "\"];\n", node1->left, (node1->left)->data);
            else
                fprintf (f, "\"box%0x\" [label=\"" "%c" "\"];\n", node1->left, node1->left->sym);
            fprintf (f, "\"box%0x\" -> \"box%0x\"[color=\"red\"];\n", node1, node1->left);

            Tree_Print (node1->left, f);
        }


    if (node1->right)
    {
        if (node1->left->node_type == NUMBER)
            fprintf (f, "\"box%0x\" [label=\"" ACCUR "\"];\n", node1->right, (node1->right)->data);
        else
            fprintf (f, "\"box%0x\" [label=\"" "%c" "\"];\n", node1->right, node1->right->sym);
        fprintf (f, "\"box%0x\" -> \"box%0x\"[color=\"green\"];\n", node1, node1->right);

        Tree_Print (node1->right, f);
    }

}

void Tree::Tree_Info_Dump (const Node* node1, FILE* f)
{
    if (node1 == this->first_elem)
        if (node1->node_type == NUMBER)
            fprintf (f, "\"box%0x\" [label=\"{" ACCUR "|adress=%0x|left=%0x|right=%0x}\"];\n", node1, node1->data, node1, node1->left, node1->right);
        else
            fprintf (f, "\"box%0x\" [label=\"{%c|adress=%0x|left=%0x|right=%0x}\"];\n", node1, node1->sym, node1, node1->left, node1->right);

    if (node1->left)
        {
            if (node1->left->node_type == NUMBER)
                fprintf (f, "\"box%0x\" [label=\"{" ACCUR "|adress %0x|left=%0x|right=%0x|parent=%0x}\"];\n",
                            node1->left, (node1->left)->data, node1->left,
                (node1->left)->left, (node1->left)->right, node1->left->parent);
            else fprintf (f, "\"box%0x\" [label=\"{%c|adress %0x|left=%0x|right=%0x|parent=%0x}\"];\n",
                            node1->left, (node1->left)->sym, node1->left,
                (node1->left)->left, (node1->left)->right, node1->left->parent);
            fprintf (f, "\"box%0x\" -> \"box%0x\"[color=\"red\"];\n", node1, node1->left);

            Tree_Info_Dump (node1->left, f);
        }


    if (node1->right)
    {
        if (node1->right->node_type == NUMBER)
            fprintf (f, "\"box%0x\" [label=\"{" ACCUR "|adress=%0x|left=%0x|right=%0x|parent=%0x}\"];\n", node1->right, (node1->right)->data, node1->right, (node1->right)->left, (node1->right)->right, node1->right->parent);
        else
            fprintf (f, "\"box%0x\" [label=\"{%c|adress=%0x|left=%0x|right=%0x|parent=%0x}\"];\n", node1->right, (node1->right)->sym, node1->right, (node1->right)->left, (node1->right)->right, node1->right->parent);
        fprintf (f, "\"box%0x\" -> \"box%0x\"[color=\"green\"];\n", node1, node1->right);

        Tree_Info_Dump (node1->right, f);
    }

}
