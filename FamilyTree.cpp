//
// Created by Tzach on 03/04/2020.
//
#include "FamilyTree.hpp"
using namespace std;
namespace family {
    Node::Node(string name)
    {
        this->name = name;
        father=mother=NULL;
    }
    Tree::Tree(string name)
    {
        Node x(name);
        this->root = &x;
    }
    family::Tree family::Tree::addFather(string rootName, string name2)
    {
        return Tree("");
    };
    family::Tree family::Tree::addMother(string rootName, string name2)
    {
        return Tree("");
    };
    void family::Tree::display()
    {
        if (root == NULL)
            return;
        cout<<root->name.length()<<endl;
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