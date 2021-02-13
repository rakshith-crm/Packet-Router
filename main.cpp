#include <stdio.h>
#include "linked_list.h"
#include <fstream>
#include <thread>
#include <mutex>
#include <chrono>
#include <time.h>
int tree_array_size = 20;
int heap_size = 0;
const int INF = 100000;
linked_list A;
int packets_handled=1;
auto g_lock()
{
    static mutex m;
    return unique_lock<decltype(m)>(m);
}

void string_to_char(string value,char *t)
{
    int n=value.length(),i;
 //   cout<<"n="<<n<<endl;
    for(i=0;i<n;i++)
    {
        t[i]=value[i];
        if(value[i]==',')
        {
            if(value[i+1]=='"' && value[i-1]=='"')
            {
                t[i]=value[i];
            }
            else
            {
                t[i]='-';
            }
        }
     //   cout<<value[i];
    }
    t[i]='\0';
}
void swap( int *a, int *b ) {
    int t;
    t = *a;
    *a = *b;
    *b = t;
}

int get_right_child(linked_list &l, int index)
{
    if((((2*index)+1) <= l.get_count()) && (index >= 1))
    {
        return (2*index)+1;
    }
    return -1;
}


int get_left_child(linked_list &l, int index)
{
    if(((2*index) <= l.get_count()) && (index >= 1))
    {
        return 2*index;
    }
    return -1;
}


int get_parent(linked_list &l, int index)
{
    if ((index > 1) && (index <= l.get_count()))
    {
        return index/2;
    }
    return -1;
}

void max_heapify(linked_list &A, int index)
{
    int left_child_index = get_left_child(A,index);
    int right_child_index = get_right_child(A,index);
    node *left_=A.get_node(left_child_index);
    node *right_=A.get_node(right_child_index);
    int largest = index;
    node *largest_=A.get_node(largest);
    if ((left_child_index <= heap_size) && (left_child_index>0))
    {
        if (A[left_child_index] > A[largest])
        {
            largest = left_child_index;
        }
        else if(A[left_child_index]==A[largest])
        {
            if(strcmp(left_->time,largest_->time)<0)
            {
                largest=left_child_index;
            }
        }
    }
    if ((right_child_index <= heap_size && (right_child_index>0)))
    {
        if (A[right_child_index] > A[largest])
        {
            largest = right_child_index;
        }
        else if(A[right_child_index]==A[largest])
        {
            if(strcmp(right_->time,largest_->time)<0)
            {
                largest=right_child_index;
            }
        }
    }

    if (A[largest] != A[index])
    {
        exchange(A.get_node(index), A.get_node(largest));
        max_heapify(A, largest);
    }
}

void build_max_heap(linked_list &A)
{
    int i;
    for(i=heap_size/2; i>=1; i--)
    {
        max_heapify(A, i);
    }
}

int maximum(linked_list &A)
{
    return A[1];
}

node* extract_max(linked_list &A) {
//    cout<<"\nNumber of Element  : "<<A.get_count()<<endl;
    if(A.get_count()==1)
    {
        node *save=new node;
        save_copy(save,A.get_node(1));
        A.delete_last();
      //  cout<<"\ndeleted...\n";
        return save;
    }
    else if(A.get_count()>1)
    {
        node *save=new node;
        save_copy(save,A.get_node(1));
        //  A[1] = A[heap_size];
        exchange(A.get_node(1),A.get_node(heap_size));

        heap_size--;
        A.delete_last();
        max_heapify(A, 1);
        return save;
    }
}

void increase_key(linked_list &A, int index, int key)
{
 //   cout<<index<<endl;
//    A.set_key(key,index);
    while((index>1) && (A[get_parent(A, index)] < A[index]))
    {
        exchange(A.get_node(index), A.get_node(get_parent(A, index)));
        index = get_parent(A, index);
    //    A.display();
       // cin.get();
       // cin.get();
    }
  //  cout<<"hellooo";
}


void insert(linked_list &A,char *sent) {
    heap_size++;
    A.insert_end(sent);
//    A.display();
    //cout<<"hii";
    increase_key(A, heap_size, A.get_key());
}

void print_heap(linked_list &A)
{
    int i;
    for(i=1; i<=heap_size; i++)
    {
        printf("%d\n",A[i]);
    }
    printf("\n");
}
void receive_packets()
{
    cout<<"\n---------------------";
    cout<<"\n###Starting Router###\n";
    cout<<"---------------------\n";
    std::this_thread::sleep_for(200ms);
    string sent;
    sent.resize(1000);
    char sentence[1000];
    ifstream file("1.csv");
    int count=0;
    getline(file,sent);
    while(getline(file,sent))
    {
        cout<<"Receiving Packet : ";
        using namespace std::literals;
        std::this_thread::sleep_for(5ms);
        string_to_char(sent,sentence);
        insert(A,sentence);
        cout<<"\n\n??????Packets Handled : "<<packets_handled++<<endl;

    }

}
void send_packets()
{
    std::this_thread::sleep_for(400ms);

    while(A.get_count()!=0)
    {
        cout<<"\n#########################################CURRENT QUEUE ###"<<"##############################     "<<A.get_count()<<endl;
        cout<<"Re-Transmitting Packet : \n";
        display(extract_max(A));
        using namespace std::literals;
        std::this_thread::sleep_for(10ms);

    }

}
int main()
{
    time_t start,end;
    start=clock();
    thread t1(receive_packets);
    thread t2(send_packets);
    t1.join();
    t2.join();
    end=clock();
    cout<<packets_handled<<endl;
    time_t elapsed=(end-start)/1000.0;
    cout<<"\n\nPACKETS HANDLED : "<<packets_handled<<endl;
    cout<<"\nTime Elapsed : "<<(end-start)/1000.0<<"seconds;  AVERAGE PACKETS HANDLED PER SECOND : "<<(float)packets_handled/elapsed<<endl;
  //  A.display();

  return 0;
}
