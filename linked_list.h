#include <iostream>
#include <string.h>
using namespace std;
    int prior1=700;
    int prior2=600;
    int prior3=500;
    int prior4=400;
    int prior5=300;
    int prior6=200;
    int prior7=100;
struct node
{
    char sno[10];
    char time[20];
    char source[30];
    char destination[30];
    char protocol[10];
    char length[20];
    char info[400];
    int key;
    node *right;
    node *left;
};

void display(node *n)
{
    cout<<n->sno<<" "<<n->time<<" "<<n->source<<" "<<n->destination<<" "<<n->protocol<<" "<<n->length<<" "<<n->info<<endl;
    cout<<"PACKET PRIORITY : "<<n->key<<endl;
}
void save_copy(node *n1,node *n2)
{
    strcpy(n1->sno,n2->sno);
    strcpy(n1->time,n2->time);
    strcpy(n1->source,n2->source);
    strcpy(n1->destination,n2->destination);
    strcpy(n1->protocol,n2->protocol);
    strcpy(n1->length,n2->length);
    strcpy(n1->info,n2->info);
    n1->key=n2->key;

}
void exchange(node *n1,node *n2)
{
    char sno[10];
    char time[20];
    char source[30];
    char destination[30];
    char protocol[10];
    char length[20];
    char info[400];
    strcpy(sno,n1->sno);
    strcpy(time,n1->time);
    strcpy(source,n1->source);
    strcpy(destination,n1->destination);
    strcpy(protocol,n1->protocol);
    strcpy(length,n1->length);
    strcpy(info,n1->info);


    strcpy(n1->sno,n2->sno);
    strcpy(n1->time,n2->time);
    strcpy(n1->source,n2->source);
    strcpy(n1->destination,n2->destination);
    strcpy(n1->protocol,n2->protocol);
    strcpy(n1->length,n2->length);
    strcpy(n1->info,n2->info);

    strcpy(n2->sno,sno);
    strcpy(n2->time,time);
    strcpy(n2->source,source);
    strcpy(n2->destination,destination);
    strcpy(n2->protocol,protocol);
    strcpy(n2->length,length);
    strcpy(n2->info,info);
    int k=n1->key;
    n1->key=n2->key;
    n2->key=k;

}
node *create_node(char *sent)
{
    node *n=new node;

    char del[]=",";
    char *no=strtok(sent,del);
    char *ti=strtok(NULL,del);
    char *sour=strtok(NULL,del);
    char *dest=strtok(NULL,del);
    char *prot=strtok(NULL,del);
    char *len=strtok(NULL,del);
    char *inf=strtok(NULL,del);
    strcpy(n->sno,no);
    strcpy(n->time,ti);
    strcpy(n->source,sour);
    strcpy(n->destination,dest);
    strcpy(n->protocol,prot);
    strcpy(n->length,len);
    strcpy(n->info,inf);
    if(strcmp(n->protocol,"\"TCP\"")==0)
    {
   //     cout<<"\n------Packet Priority 1-------\n";
        n->key=prior1--;
        if(prior1==600)
        {
            prior1=700;
        }
    }
    else if(strcmp(n->protocol,"\"TLsv1\"")==0)
    {
    //    cout<<"\n------Packet Priority 2-------\n";
        n->key=prior2--;
        if(prior2==500)
        {
            prior2=600;
        }
    }
    else if(strcmp(n->protocol,"\"SSDP\"")==0)
    {
   //     cout<<"\n------Packet Priority 3-------\n";
        n->key=prior3--;
        if(prior3==400)
        {
            prior3=500;
        }
    }
    else if(strcmp(n->protocol,"\"NBNS\"")==0)
    {
   //     cout<<"\n------Packet Priority 4-------\n";
        n->key=prior4--;
        if(prior4==300)
        {
            prior4=400;
        }
    }
    else if(strcmp(n->protocol,"\"QVIC\"")==0)
    {
    //    cout<<"\n------Packet Priority 5-------\n";
        n->key=prior5--;
        if(prior5==200)
        {
            prior5=300;
        }
    }
    else if(strcmp(n->protocol,"\"MDNS\"")==0)
    {
   //     cout<<"\n------Packet Priority 6-------\n";
        n->key=prior6--;
        if(prior6==100)
        {
            prior6=200;
        }
    }
    else
    {
   //     cout<<"\n------Packet Priority 7-------\n";
        n->key=prior7--;
        if(prior7==0)
        {
            prior7=100;
        }
    }

    n->left=NULL;
    n->right=NULL;
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
    int operator [](int);
    int get_key();
    void display();
    node * get_node(int);
    void set_key(int,int);
};
int linked_list::get_key()
{
    return end->key;
}
void linked_list::set_key(int key,int index)
{
    node *n=get_node(index);
    n->key=key;
}
linked_list::linked_list()
{
    count=0;
    start=NULL;
    end=NULL;
}
int linked_list::get_count()
{
    return count;
}
void linked_list::insert_end(char *sent)
{
    count++;
    node *n=create_node(sent);
    if(start==NULL)
    {
        start=n;
        end=n;
        return;
    }
    end->right=n;
    n->left=end;
    end=n;
}
void linked_list::delete_last()
{
    if(count==1)
    {
        delete(end);
        start=end=NULL;
        count--;
    }
    else if(end!=NULL)
    {
        node *n=end;
        end=end->left;
        end->right=NULL;
        delete(n);
        count--;
    }
}
int linked_list::operator[](int index)
{
    if(index<=1)
    {
        return start->key;
    }
    else if(index>=count)
    {
        return end->key;
    }
    node *n=start;
    index=index-1;
    while(index>0 && n!=NULL)
    {
        n=n->right;
        index--;
    }
    return n->key;
}

void linked_list::display()
{
    node *n=start;
    while(n!=NULL)
    {
        cout<<"[" << n->protocol << "-" << n->sno <<"-"<<n->key<<"]" << "\n";
        n=n->right;
    }
    cout<<"NULL"<<endl;
}
node *linked_list::get_node(int index)
{
    if(index<=1)
    {
        return start;
    }
    else if(index>=count)
    {
        return end;
    }
    node *n=start;
    index--;
    while(index>0 && n!=NULL)
    {
        n=n->right;
        index--;
    }
    return n;
}
