//
// Created by Tzach on 07/04/2020.
//
#pragma once
#include <iostream>
using namespace std;
#include <stdio.h>
#include <string>
#include <cmath>
#include <cassert>
namespace family{
    class Node{
    public:
        string name;
        Node* father;
        Node* mother;
    };
    class Tree{
        Node* root;
    public:
        Tree(string name);
        Tree()
        {
            root = NULL;
        }
        Tree addFather(string rootName, string name2);
        Tree addMother(string rootName, string name2);
        void display();
        std::string relation(string name);
        std::string find(string name);
        void remove(string name);
    };
}
