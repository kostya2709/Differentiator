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

        sscanf (cur_ptr, "%lf %n", &node1->data, &letter_num);
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

