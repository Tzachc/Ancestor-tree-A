//
// Created by Tzach on 07/04/2020.
//
#include "FamilyTree.hpp"
using namespace std;
namespace family {
    Tree::Tree(string name)
    {
        root=new Node;
        root->name=name;
        root->father=NULL;
        root->mother=NULL;
    };
    Tree&Tree::addFather(string rootName, string name2)
    {
        return *this;
    };
    Tree&Tree::addMother(string rootName, string name2)
    {
        return *this;
    };
    void family::Tree::display()
    {
        if (root == NULL)
            return;
        cout<<root->name<<endl;
    };
    string family::Tree::relation(string name)
    {
        return "";
    };
    string family::Tree::find(string name)
    {
        return "";
    };

    void family::Tree::remove(string name)
    {

    };
}
