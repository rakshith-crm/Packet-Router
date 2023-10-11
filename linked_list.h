#include <iostream>
#include <string.h>

const int prior1 = 700;
const int prior2 = 600;
const int prior3 = 500;
const int prior4 = 400;
const int prior5 = 300;
const int prior6 = 200;
const int prior7 = 100;

struct node
{
    std::string sno;
    std::string time;
    std::string source;
    std::string destination;
    std::string protocol;
    std::string length;
    std::string info;
    int key;
    node *right;
    node *left;
};

void display(node *n)
{
    std ::cout << n->sno << " " << n->time << " " << n->source << " " << n->destination << " " << n->protocol << " " << n->length << " " << n->info << endl;
    std ::cout << "PACKET PRIORITY : " << n->key << endl;
}
void save_copy(node *n1, node *n2)
{
    strcpy(n1->sno, n2->sno);
    strcpy(n1->time, n2->time);
    strcpy(n1->source, n2->source);
    strcpy(n1->destination, n2->destination);
    strcpy(n1->protocol, n2->protocol);
    strcpy(n1->length, n2->length);
    strcpy(n1->info, n2->info);
    n1->key = n2->key;
}
void exchange(node *n1, node *n2)
{
    std::string sno;
    std::string time;
    std::string source;
    std::string destination;
    std::string protocol;
    std::string length;
    std::string info;
    strcpy(sno, n1->sno);
    strcpy(time, n1->time);
    strcpy(source, n1->source);
    strcpy(destination, n1->destination);
    strcpy(protocol, n1->protocol);
    strcpy(length, n1->length);
    strcpy(info, n1->info);

    strcpy(n1->sno, n2->sno);
    strcpy(n1->time, n2->time);
    strcpy(n1->source, n2->source);
    strcpy(n1->destination, n2->destination);
    strcpy(n1->protocol, n2->protocol);
    strcpy(n1->length, n2->length);
    strcpy(n1->info, n2->info);

    strcpy(n2->sno, sno);
    strcpy(n2->time, time);
    strcpy(n2->source, source);
    strcpy(n2->destination, destination);
    strcpy(n2->protocol, protocol);
    strcpy(n2->length, length);
    strcpy(n2->info, info);
    int k = n1->key;
    n1->key = n2->key;
    n2->key = k;
}
node *create_node(char *sent)
{
    node *n = new node;

    std::string del = ",";
    std::string no = strtok(sent, del);
    std::string ti = strtok(NULL, del);
    std::string sour = strtok(NULL, del);
    std::string dest = strtok(NULL, del);
    std::string prot = strtok(NULL, del);
    std::string len = strtok(NULL, del);
    std::string inf = strtok(NULL, del);
    n->sno = no;
    n->time = ti;
    n->source = sour;
    n->destination = dest;
    n->protocol = prot;
    n->length = len;
    n->info = inf;

    if (n->protocol == "\"TCP\"")
    {
        //     std :: cout<<"\n------Packet Priority 1-------\n";
        n->key = prior1--;
        if (prior1 == 600)
        {
            prior1 = 700;
        }
    }
    else if (n->protocol == "\"TLsv1\"")
    {
        //    std :: cout<<"\n------Packet Priority 2-------\n";
        n->key = prior2--;
        if (prior2 == 500)
        {
            prior2 = 600;
        }
    }
    else if (n->protocol == "\"SSDP\"")
    {
        //     std :: cout<<"\n------Packet Priority 3-------\n";
        n->key = prior3--;
        if (prior3 == 400)
        {
            prior3 = 500;
        }
    }
    else if (n->protocol == "\"NBNS\"")
    {
        //     std :: cout<<"\n------Packet Priority 4-------\n";
        n->key = prior4--;
        if (prior4 == 300)
        {
            prior4 = 400;
        }
    }
    else if (n->protocol == "\"QVIC\"")
    {
        //    std :: cout<<"\n------Packet Priority 5-------\n";
        n->key = prior5--;
        if (prior5 == 200)
        {
            prior5 = 300;
        }
    }
    else if (n->protocol == "\"MDNS\"")
    {
        //     std :: cout<<"\n------Packet Priority 6-------\n";
        n->key = prior6--;
        if (prior6 == 100)
        {
            prior6 = 200;
        }
    }
    else
    {
        //     std :: cout<<"\n------Packet Priority 7-------\n";
        n->key = prior7--;
        if (prior7 == 0)
        {
            prior7 = 100;
        }
    }

    n->left = NULL;
    n->right = NULL;
}
class linked_list
{
    int count;
    node *start;
    node *end;

public:
    linked_list();
    int get_count();
    void insert_end(char *);
    void delete_last();
    int operator[](int);
    int get_key();
    void display();
    node *get_node(int);
    void set_key(int, int);
};
int linked_list::get_key()
{
    return end->key;
}
void linked_list::set_key(int key, int index)
{
    node *n = get_node(index);
    n->key = key;
}
linked_list::linked_list()
{
    count = 0;
    start = NULL;
    end = NULL;
}
int linked_list::get_count()
{
    return count;
}
void linked_list::insert_end(char *sent)
{
    count++;
    node *n = create_node(sent);
    if (start == NULL)
    {
        start = n;
        end = n;
        return;
    }
    end->right = n;
    n->left = end;
    end = n;
}
void linked_list::delete_last()
{
    if (count == 1)
    {
        delete (end);
        start = end = NULL;
        count--;
    }
    else if (end != NULL)
    {
        node *n = end;
        end = end->left;
        end->right = NULL;
        delete (n);
        count--;
    }
}
int linked_list::operator[](int index)
{
    if (index <= 1)
    {
        return start->key;
    }
    else if (index >= count)
    {
        return end->key;
    }
    node *n = start;
    index = index - 1;
    while (index > 0 && n != NULL)
    {
        n = n->right;
        index--;
    }
    return n->key;
}

void linked_list::display()
{
    node *n = start;
    while (n != NULL)
    {
        std ::cout << "[" << n->protocol << "-" << n->sno << "-" << n->key << "]"
                   << "\n";
        n = n->right;
    }
    std ::cout << "NULL" << endl;
}
node *linked_list::get_node(int index)
{
    if (index <= 1)
    {
        return start;
    }
    else if (index >= count)
    {
        return end;
    }
    node *n = start;
    index--;
    while (index > 0 && n != NULL)
    {
        n = n->right;
        index--;
    }
    return n;
}
