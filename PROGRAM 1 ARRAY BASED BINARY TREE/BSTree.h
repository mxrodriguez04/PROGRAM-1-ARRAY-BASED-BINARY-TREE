#include "BSTInterface.h"
#include <string>

using namespace std;
template <typename KeyComparable, typename Value >
class BinarySearchTree : BSTInterface < KeyComparable, Value >
{
private:
	
	/*
	* Private Node Class  
	*
	*/
	class Pair
	{
		public:
			KeyComparable key;
			Value value;
						
			//Initialize class members from constructor arguments 
			//by using a member initializer list.
			//This method uses direct initialization, which is more
			//efficient than using assignment operators inside the constructor body.
			Pair( KeyComparable & key, Value & value )
				: value{ value },  key{ key }
			{

			}

	};

	// number of values stored in the tree
	int count = 0;
	// capacity of array holding the tree
	int size = 25;
	// the array that holds the pairs
	Pair **root = new Pair*[size];
		
	/*
	* Prints the inorder the tree to the stream out
	*
	*/
	void printTree(int index, std::ostream & out) const
	{
        //DEBUG
        cout << "INSIDE PRINTTREE\n\n";
        
        if(/*index < size &&*/ root[index] != nullptr){
            printTree(index * 2, out);
            out << *(root[index]->value) << endl;
            printTree(index * 2 + 1, out);
        }
	}
	
public:
	BinarySearchTree()
	{
		// add needed code
        for (int index = 0; index < size; ++index){  //FIXME: Unsure
            root[index] = nullptr;
        }
	}
	
	~BinarySearchTree()
	{
		// add needed code
	}

	/*
	* Finds the node with the smallest element in the tree	
	*/
	const Value findMin() const
	{
		// stub code remove
		return nullptr;
	}

	/*
	* Finds the node with the largest element in the tree
	*/
	const Value findMax() const
	{
		// stub code remove
		return nullptr;
	}

	/*
	* Finds the node with that the key
	* updates the founditem refrerence if found
	* returns true if it was found 
	* returns false if it was not 
	*/
	bool find(const KeyComparable & key , Value & founditem) const
	{
		
		return false;
	}

	/*
	* Returns true if the item is found in the tree
	*/
	bool contains(const KeyComparable & key) const
	{
		// stub code remove
		return false;
	}

	/*
	* Returns true if tree has no nodes
	*/
	bool isEmpty() const{
		// stub code remove
		return root == nullptr;
	}

	/*
	* Prints the inorder the tree to the stream out
	*/
	void printTree(std::ostream & out = cout) const
	{
		printTree(1 , out);

	}

	/*
	* Removes all nodes from the tree
	*/
	void makeEmpty()
	{

	}

	/*
	* Inserts a node into the tree
	* maintains this property of the tree:
	*     All nodes to the left will be less
	*     All nodes to the right will be greater
	*/
	bool insert( Value value,  KeyComparable key)
	{
        //DEBUG
        cout << "\nINSIDE BSTREE INSERT" << endl;
        cout << *value << endl;
        
        //Index value starting at root
        int index = 1;
        
        //Insert node into root if tree is empty
        if (root[index] == nullptr){
            root[index] = new Pair (key, value);
            this->count++;
            return true;
        }
        //If the tree is not empty do the following
        else{
            while (root[index] != nullptr){
                if (key < root[index]->key){
                    //DEBUG
                    cout << "NODE WAS FULL MOVING DOWN LEFT CHILD\n\n";
                    
                    insert(value, key);
                }
                else if{
                    ;
                    
                }
            }
            
            return false;
        }
		return false;
	}

	/*
	* Removes the nodes if it contains the given item
	*/
	void remove(const KeyComparable & key)
	{

	}

	int getSize() {
		return this->size;
	}

	int getCount() {
		return this->count;
	}

};
