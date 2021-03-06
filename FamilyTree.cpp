//
// Created by Tzach on 03/04/2020.
//
#include "FamilyTree.hpp"
#define COUNT 10
using namespace std;
using namespace family;
Node::Node()
{
    this->name = "";
    this->father = nullptr;
    this->mother = nullptr;
    this->child = nullptr;
    this->height= 0;
    this->parent_type = "me";
    this->relation = "";
}
Node::Node(string name)
{
    this->name = name;
    father=mother=NULL;
    child = NULL;
    height = 0;
    parent_type = "unknown";
    relation = "";
}
Tree::Tree(string name)
{
    root = new Node;
    root->name = name;
    root->father= nullptr;
    root->mother = nullptr;
    root->child = nullptr;
    root->setHeight(0);
    root->parent_type = "me";
    root->setRelation(relation(name));
}
Tree::~Tree() {
    deleteSubTree(root->father);
    deleteSubTree(root->mother);
    //Only then delete the root itself
    delete root;
    root = nullptr;
}

/* take Node and name to search for */
/*  */
Node* Tree::findPos(Node* currentN, string name)
{
    if (currentN->name.compare(name) == 0)
        return currentN;
    if(currentN->father!= nullptr) {
        Node *fromFather = findPos(currentN->father, name);
        if (fromFather != NULL) return fromFather;
    }
    if(currentN->mother!= nullptr) {
        Node *fromMother = findPos(currentN->mother, name);
        if (fromMother != NULL) return fromMother;
    }
    return NULL;
}
Tree& Tree::addFather(string rootName, string newName)
{
    Node *curr = findPos(this->root, rootName);
    if (curr != NULL)
    {
        if (curr->father == NULL)
        {
            curr->father = new Node(newName);
            curr->father->setParentType("father");
            curr->father->setHeight(curr->getHeight()+1);
            curr->father->setRelation(relation(newName));
            if(curr->father!= nullptr)
            curr->father->child = curr;
            if(curr->mother!= nullptr)
            curr->mother->child = curr;
        }
        else
        {
            string test = "'" + rootName + "' already have a father!!";
            throw invalid_argument(test);
        }
    }
    else // we didn't find the root name
    {
        string test = "Could'nt find '" + rootName + "'";
        throw invalid_argument(test);
    }
    return *this;
};
Tree& Tree::addMother(string rootName, string newName)
{
    Node *curr = findPos(this->root, rootName);
    if (curr != NULL)
    {
        if (curr->mother == NULL)
        {
            curr->mother = new Node(newName);
            curr->mother->setParentType("mother");
            curr->mother->setHeight(curr->getHeight()+1);
            curr->mother->setRelation(relation(newName));
            curr->father->child = curr;
            curr->mother->child = curr;
        }
        else
        {
            string test = "'" + rootName + "' already have a mother!!";
            throw invalid_argument(test);
        }
    }
    else // we didn't find the root name
    {
        string test = "Could'nt find '" + rootName + "'";
        throw invalid_argument(test);
    }
    return *this;
};
void Tree::display()
{
    print2DUtil(this->root, 0);
};
string Tree::relation(string who) {
    Node* curr=findPos(this->root,who);
    string ans;
    if(curr==NULL)
        return "unrelated";
    if(curr==this->getRoot()) return "me";
    for (int i = 2; i < curr->getHeight(); ++i)
        ans+="great-";
    if(curr->getHeight()>1) {
        ans += "grand";
    }
    if(curr->getParentType() == "father") {
        ans += "father";
    }
    if(curr->getParentType()=="mother") {
        ans += "mother";
    }
    return ans;
};

// https://www.geeksforgeeks.org/print-binary-tree-2-dimensions/
void Tree::print2DUtil(Node *root, int space)
{
    // Base case
    if (root == NULL)
        return;

    // Increase distance between levels
    space += COUNT;

    // Process right child first
    print2DUtil(root->father, space);

    // Print current node after space
    // count
    cout<<endl;
    for (int i = COUNT; i < space; i++)
        cout<<" ";
    cout<<root->name<<"\n";

    // Process left child
    print2DUtil(root->mother, space);
}
Node* Tree::findPosByType(Node* currentN, string name)
{
    if(currentN == nullptr)
        return nullptr;
    if (currentN->getRelation().compare(name) == 0)
        return currentN;
    if(currentN->father!= nullptr)
    {
        Node *fromFather = findPosByType(currentN->father, name);
        if (fromFather != NULL)
            return fromFather;
    }
    if(currentN->mother!= nullptr)
    {
        Node *fromMother = findPosByType(currentN->mother, name);
        if (fromMother != NULL) return fromMother;
    }
    return NULL;
}
string family::Tree::find(string type)
{
    Node* curr = findPosByType(root,type);
    if(curr==nullptr) throw std::out_of_range("The tree cannot handle the 'uncle' relation");
    return curr->name;
};
void Tree::remove(string person_name)
{
    Node* PersonToRemove = findPos(this->root,person_name);
    if (PersonToRemove == nullptr)
        throw runtime_error("The person doesn't exist in tree");
    if (PersonToRemove == root)
        throw runtime_error("Can't remove myself, the root of the tree");
    if(PersonToRemove == PersonToRemove->child->father)
    {
        PersonToRemove->child->father = nullptr;
    }
    else
        {
            PersonToRemove->child->mother = nullptr;
        }
    deleteSubTree(PersonToRemove);
    //deleteSubTree(&PersonToRemove);
    if (PersonToRemove == nullptr)
        cout << "tree successfully deleted!";
}
void Tree::deleteSubTree(Node *&node) {
    if (node == nullptr) {
        return;
    }

    deleteSubTree(node->father);
    deleteSubTree(node->mother);
    node->father = nullptr;
    node->mother = nullptr;
    node->child = nullptr;
    delete node;
    node = nullptr;//We don't want a dangling pointer
}
