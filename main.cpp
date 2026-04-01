
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include "coordinate.h"

using namespace std;

void add_coordinate(Coordinate *list_end,float x,float y)
{
    Coordinate *n = new Coordinate;
    n->x = x; n->y = y;
    n->next = NULL;
    n->previous = list_end;
    n->coord_id = list_end->coord_id + 1;
    list_end->next = n;
}

void forward_display(Coordinate *list_beginning)
{
    Coordinate *c=list_beginning;
    while(c!=NULL){
        cout<<"ID:"<<c->coord_id<<" ("<<c->x<<","<<c->y<<")"<<endl;
        c=c->next;
    }
}

void backward_display(Coordinate *list_end)
{
    Coordinate *c=list_end;
    while(c){
        cout<<"ID:"<<c->coord_id<<" ("<<c->x<<","<<c->y<<")"<<endl;
        c=c->previous;
    }
}

void delete_coordinate(Coordinate *list_beginning,int id)
{
    Coordinate *c = list_beginning;

    while(c!=NULL){
        if(c->coord_id==id){
            if(c->previous) c->previous->next=c->next;
            if(c->next) c->next->previous=c->previous;
            delete c;
            cout<<"Deleted coordinate ID "<<id<<endl;
            return;
        }
        c=c->next;
    }
    cout<<"Coordinate ID not found."<<endl;
}

int list_length(Coordinate *list_beginning)
{
    int cnt=0;
    Coordinate *c=list_beginning;
    while(c){
        cnt++;
        c=c->next;
    }
    return cnt;
}

void closest_to(Coordinate *list_beginning,float x,float y)
{
    Coordinate *c=list_beginning;
    Coordinate *best=NULL;
    float d=0;

    while(c){
        float dx=c->x-x;
        float dy=c->y-y;
        float dist=sqrt(dx*dx+dy*dy);

        if(!best || dist<d){
            d=dist;
            best=c;
        }
        c=c->next;
    }

    if(best){
        cout<<"Closest to ("<<x<<","<<y<<") is ID "
            <<best->coord_id<<" ("<<best->x<<","<<best->y
            <<") distance = "<<d<<endl;
    }
}

int main(int argc,char *argv[])
{
    if(argc!=2){
        cout<<"Usage: ./main <number_of_coordinates>"<<endl;
        return 1;
    }

    int n=atoi(argv[1]);
    srand(time(NULL));

    Coordinate *head=new Coordinate;
    head->x=(rand()%100)/10.0f;
    head->y=(rand()%100)/10.0f;
    head->coord_id=1;
    head->previous=NULL;
    head->next=NULL;

    Coordinate *tail=head;

    for(int i=1;i<n;i++){
        float x=(rand()%100)/10.0f;
        float y=(rand()%100)/10.0f;
        add_coordinate(tail,x,y);
        tail=tail->next;
    }

    cout<<"\nForward display:\n";
    forward_display(head);

    cout<<"\nBackward display:\n";
    backward_display(tail);

    cout<<"\nList length: "<<list_length(head)<<endl;

    cout<<"\nDeleting coordinate ID 2:\n";
    delete_coordinate(head,2);

    cout<<"\nForward display after delete:\n";
    forward_display(head);

    cout<<"\nClosest to (5.0,5.0):\n";
    closest_to(head,5.0f,5.0f);

    Coordinate *c=head;
    while(c){
        Coordinate *nxt=c->next;
        delete c;
        c=nxt;
    }

    return 0;
}

