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
        //IN ORDER PRINT
        if(index < size && root[index] != nullptr){
            printTree(index * 2, out);
            
            //DEBUG
            //cout << "\nINDEX: " << index << endl;
            out << *(root[index]->value) << endl;
            printTree(index * 2 + 1, out);
        }
        /*
        //POST-ORDER PRINT
        if(index < size && root[index] != nullptr){
            
            printTree(index * 2, out);
            printTree(index * 2 + 1, out);
            cout << "\nINDEX: " <<index << endl;
            out << *(root[index]->value) << endl;
        }
         */
	}
    //DEBUG HELPER FUNCTION
    void printArray() {
            int pcount = 1;
            for (int i = 1; i < size; ++i) {
                if (root[i] != nullptr) {
                    cout << i << ":" << root[i]->key << ">" << (i > 1 ? root[i / 2]->key : 0) << "  ";
                    ++pcount;
                }
                if (pcount % 6 == 0) {
                    cout << endl;
                    pcount = 1;
                }
            }
        }
    //Helper function to find index where key is stored
    int findIndex(int key){
        //Finds the index value at which key is stored
        int index = 1;
        while (root[index * 2] != nullptr && root[(index * 2) + 1] != nullptr && root[index]->key != key){
            if(root[index]->key > key){
                index = index * 2;
            }
            else if(root[index]->key < key){
                index = (index * 2) + 1;
            }
        }
        return index;
    }
    
    //Helper recursive function to move array
    void shiftTree(int index, int moveVal){
        ///*
        
        //Left Subtree
        if (root[index * 2] != nullptr){
            shiftTree(index * 2, moveVal * 2);
            root[index] = nullptr;
        }
        
        root[index - moveVal] = root[index];
        root[index] = nullptr;
        
        //Right Subtree
        if(root[index * 2 + 1] != nullptr){
            shiftTree(index * 2 + 1, moveVal * 2);
        }
         //*/
        
        /*
        if(index < size && root[index] != nullptr){
            
            shiftTree(index * 2, moveVal * 2);
            root[index - moveVal] = root[index];
            root[index] = nullptr;
            shiftTree(index * 2 + 1, moveVal * 2);
           
            //root[index] = nullptr;
            
            //root[index] = nullptr;
        }
        // */
        
    }
    //Helper function to grow array when not enough space
    void growArray(){
        //FIXME: Dynamic memory need managing??
        int growthRate = 3;
        
        //Create a new larger array
        this->size = size * growthRate;
        Pair **temp = new Pair*[size];
        //fill new array
        for (int i = 0; i < size; ++i){
            temp[i] = nullptr;
        }
        //Copy former array over to new array
        for (int i = 0; i < size / growthRate; ++i){
            temp[i] = root[i];
        }
        //Set double pointer to new array
        root = temp;
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
        int index = 1;
        while(root[index] != nullptr){
            if(root[index * 2] != nullptr){
                index = index * 2;
            }
            else{
                return root[index]->value;
            }
        }
        return root[1]->value;
	}

	/*
	* Finds the node with the largest element in the tree
	*/
	const Value findMax() const
	{
        int index = 1;;
        while(root[index] != nullptr){
            if(root[index * 2 + 1] != nullptr){
                index = index * 2 + 1;
            }
            else{
                return root[index]->value;
            }
        }
        return root[1]->value;
	}

	/*
	* Finds the node with that the key
	* updates the founditem refrerence if found
	* returns true if it was found 
	* returns false if it was not 
	*/
	bool find(const KeyComparable & key , Value & founditem) const
	{
        //DEBUG
        cout << "\n\n INSIDE FIND FUNCTION\n";
        
        
		
		return false;
	}

	/*
	* Returns true if the item is found in the tree
	*/
	bool contains(const KeyComparable & key) const
	{
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
        for(int i = 1; i < size; ++i){
            delete root[i];
            root[i] = nullptr;
        }
        this->count = 0;
	}

	/*
	* Inserts a node into the tree
	* maintains this property of the tree:
	*     All nodes to the left will be less
	*     All nodes to the right will be greater
	*/
	bool insert( Value value,  KeyComparable key){
        int index = 1;
        
        //Insert node into the root if the tree is empty
        if(root[index] == nullptr){
            root[index] = new Pair(key, value);
            this->count++;
            return true;
        }
        //do the following if the tree is not empty
        else{
            //continue looping until a empty node is found
            while (root[index] != nullptr){
                //Move down the left child if key is less than
                if(key < root[index]->key){
                    index = index * 2;
                    //grow the array if necessary
                    if (index >= size){
                        growArray();
                    }
                }
                //move down the right child is key is greater than
                else if(key > root[index]->key){
                    index = (index * 2) + 1;
                    //grow the array of necessary
                    if (index >= size){
                        growArray();
                    }
                }
                //
                else{
                    return false;
                }
            }
        }
        //add in object into array once appropriate space is found
        root[index] = new Pair(key, value);
        this->count++;
        return true;
    }

	void remove(const KeyComparable & key){
        
        
        //Find index value where the key is stored
        int index = findIndex(key);
        
        //Case: No children
        if(root[index * 2] == nullptr && root[index * 2 + 1] == nullptr){
            delete root[index];
            root[index] = nullptr;
            this->count--;
        }
        //Case: Two Children
        else if(root[index * 2] != nullptr && root[index * 2 + 1] != nullptr){
            
            //DEBUG
            cout << "\n^_^_^_^_^_FOUND: CASE TWO CHILDREN_^_^_^_^_^_\n";
            cout << "INDEX: " << index << endl;
            cout << "ROOT AT INDEX PRE-DELETION: \n" << *(root[index]->value) << endl << endl;
            
            //Find min of right subtree
            int temp = (index * 2) + 1;
            while(root[temp * 2] != nullptr){
                temp = temp * 2;
            }
            root[index] = root[temp];
            if(root[temp * 2 + 1] == nullptr){
                root[temp] = nullptr;
                delete root[temp];
            }
            else{
                remove(root[(temp * 2) + 1]->key);
                //root[temp] = nullptr;
                //shiftTree(temp * 2 + 1, ((temp * 2) + 1) - temp);
                
            }
            this->count--;
            cout << "INDEX: " << index << endl;
            cout << "ROOT AT INDEX POST-DELETION: \n" << *(root[index]->value) << endl;
            cout << "^_^_^_^_^_^_^_^_^_^_^_^_^_^_^_^\n";
            
            /*//DEBUG
            cout << "\n^_^_^_^_^_FOUND: CASE TWO CHILDREN_^_^_^_^_^_\n";
            cout << "INDEX: " << index << endl;
            cout << "ROOT AT INDEX PRE-DELETION: \n" << *(root[index]->value) << endl << endl;
        
            
            
            //Find min of right subtree
            int temp = index * 2 + 1;
            while(root[temp * 2] != nullptr){
                temp = temp * 2;
            }
            Pair* saver = root[temp];
            
            //If remove subtree to min exists run remove code
            if( root[temp * 2 + 1] != nullptr){
                remove (root[temp]->key);
            }
            root[index] = saver;
            root[temp] = nullptr;
            this->count--;
            
            cout << "PRINTING TREE" << endl;
            printTree(index, cout);
            
            cout << "INDEX: " << index << endl;
            cout << "ROOT AT INDEX POST-DELETION: \n" << *(root[index]->value) << endl;
            cout << "^_^_^_^_^_^_^_^_^_^_^_^_^_^_^_^\n";
            */
        }
        //Case: One Child
        else{
            //Left Subtree
            if (root[index * 2] != nullptr){
                shiftTree(index * 2, (index * 2) - index);
            }
            //Right Subtree
            else{
                shiftTree(index * 2 + 1, ((index * 2) + 1) - index);
            }
            this->count--;
        }
    
        
        /*
        //DEBUG
        cout << "INSIDE REMOVE FUNCTION" << endl;
        cout << "KEY: " << key << endl << endl;
        
        //Find index where key is stored
        int index = findIndex(key);
        
        //DEBUG
        cout << "\nAFTER CODE FOUND PROPER INDEX" << endl;
        cout << "ROOT AT INDEX PRE-DELETION: \n" << *(root[index]->value) << endl << endl;

      
        //Case: No Children
        if (root[index * 2] == nullptr && root[index * 2 + 1] == nullptr){
            //DEBUG
            //cout << "~~~~~~~~~~FOUND: CASE NO CHILDREN~~~~~~~~~~\n";
            //cout << "ROOT AT INDEX PRE-DELETION: \n" << *(root[index]->value) << endl << endl;
            
            root[index] = nullptr;
            this->count--;
            
            //DEBUG
            //cout << "ROOT AT INDEX POST-DELETION: \n" << *(root[index]->value) << endl << endl;
            
            //DEBUG
            //cout << "\nCASE: NO CHILDREN (DELETED)\n";
            //cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
            //printTree(1, cout);
        }
        
        //Case: Two Children
        else if(root[index * 2] != nullptr && root[index * 2 + 1] != nullptr){
            //FIXME: Dynamic memory delete?? (Don't believe its necessary)
            
            //DEBUG
            //cout << "\n^_^_^_^_^_FOUND: CASE TWO CHILDREN_^_^_^_^_^_\n";
            //cout << "ROOT AT INDEX PRE-DELETION: \n" << *(root[index]->value) << endl << endl;
        
            //Find min value of right subtree
            int temp = (index * 2) + 1;
            while(root[temp * 2] != nullptr){
                    temp = temp * 2;
            }
            
            Value *saver = &root[temp]->value;
            
            if(root[temp * 2 + 1] != nullptr){
                shiftTree(temp, (temp * 2 + 1) - temp);
            }
            
            root[index] = new Pair(index, *saver);
            //root[temp] = nullptr;
            this->count--;
          
            
            
            //root[index] = root[temp];
            //root[temp] = nullptr;
            
            //if (root[temp * 2 + 1] != nullptr){
            //    int newShift = temp * 2 + 1;
            //    shiftTree(newShift, (newShift * 2 + 1) - newShift);
            //}
            //this->count--;
            //
    
            //DEBUG
            //cout << "\nCASE: TWO CHILDREN (DELETED)\n";
            //cout << "ROOT AT INDEX POST-DELETION: \n" << *(root[index]->value) << endl;
            //cout << "^_^_^_^_^_^_^_^_^_^_^_^_^_^_^_^\n";
            //printTree(1, cout);
        }
        
        //Case: One Child
        else{
            //FIXME: Where to manage dynamic memory?
            
            //DEBUG
            
            //cout << "\n#/#/#/#/#/#/ FOUND: CASE ONE CHILD #/#/#/#/#/#/\n";
            //cout << "KEY: " << key << endl;
            //cout << "ROOT AT INDEX PRE-DELETION: \n" << *(root[index]->value) << endl << endl;
            
            //Left Subtree
            if (root[index * 2] != nullptr && root[index * 2 + 1] == nullptr){
                shiftTree(index, (index * 2) - index);
            }
            //Right Subtree
            else if(root[index * 2] == nullptr && root[index * 2 + 1] != nullptr){
                shiftTree(index, (index * 2 + 1) - index);
            }
            this->count--;
            
            //DEBUG
            //printTree(1, cout);
        
        
            */
            
        
        
        
        /*
        //DEBUG
        cout << "\nINSIDE REMOVE FUNCTION\n";
        cout << "KEY: " << key << endl;
        
        int index = 1;
        //Finds the index value at which key is stored
        while (root[index * 2] != nullptr && root[(index * 2) + 1] != nullptr && root[index]->key != key){
            //DEBUG
            //cout << "\n\nINDEX: " << index << endl;
            //cout << "KEY: " << key;
            
            if(root[index]->key > key){
                //DEBUG
                //cout << "\nCURRENT ARRAY KEY: "<< root[index]->key << endl;
                
                index = index * 2;
                
                //DEBUG
                //cout << "INDEX: " << index << endl << endl;
            }
            else if(root[index]->key < key){
                //DEBUG
                //cout << "\nCURRENT ARRAY KEY: "<< root[index]->key << endl;
                
                index = (index * 2) + 1;
            }
        }
        
        //DEBUG
        cout << "\nAFTER CODE FOUND PROPER INDEX" << endl;
        cout << "ROOT AT INDEX PRE-DELETION: \n" << *(root[index]->value) << endl << endl;
        //ADD REMOVAL AND REASSIGNMENT CODE HERE
        
        //DEBUG
        //cout << "\n\nFOUND NODE WITH REMOVE KEY\n";
        //cout << "INDEX: " << index << endl;
        //cout << "REMOVAL KEY: " << key << endl;
        //cout << "NODE KEY: " << root[index]->key << endl;
        
        //Case: No Children
        if (root[index * 2] == nullptr && root[(index * 2) + 1] == nullptr){
            //DEBUG
            cout << "~~~~~~~~~~FOUND: CASE NO CHILDREN~~~~~~~~~~\n";
            cout << "ROOT AT INDEX PRE-DELETION: \n" << *(root[index]->value) << endl << endl;
            
            //FIXME: delete the dynamic memory
            //delete root[index];
            
            //DEBUG
            //cout << "ROOT AT INDEX POST-DELETION: \n" << *(root[index]->value) << endl << endl;
            root[index] = nullptr;
            
            //DEBUG
            //cout << "\nCASE: NO CHILDREN (DELETED)\n";
            //cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
            
        }
        //Case: Two Children
        else if(root[index * 2] != nullptr && root[(index * 2) + 1] != nullptr){
            //FIXME: Dynamic memory delete?? (Don't believe its necessary)
            
            //DEBUG
            cout << "\n^_^_^_^_^_FOUND: CASE TWO CHILDREN_^_^_^_^_^_\n";
            cout << "ROOT AT INDEX PRE-DELETION: \n" << *(root[index]->value) << endl << endl;
            
            //Find min value of right subtree
            int temp = (index * 2) + 1;
            while(root[temp * 2] != nullptr){
                //if (root[temp * 2] != nullptr){
                    temp = temp * 2;
                //}
            }
            root[index] = root[temp];
            root[temp] = nullptr;
            
            //DEBUG
            //cout << "\nCASE: TWO CHILDREN (DELETED)\n";
            //cout << "ROOT AT INDEX POST-DELETION: \n" << *(root[index]->value) << endl;
            //cout << "^_^_^_^_^_^_^_^_^_^_^_^_^_^_^_^\n";
        }
        //Case: One Child
        else{
            //DEBUG
            
            cout << "\n#/#/#/#/#/#/ FOUND: CASE ONE CHILD #/#/#/#/#/#/\n";
            cout << "KEY: " << key << endl;
            cout << "ROOT AT INDEX PRE-DELETION: \n" << *(root[index]->value) << endl << endl;
            
            //Left Subtree
            if (root[index * 2] != nullptr){
                //DEBUG
                cout << "\nLEFT SUBTREE CASE\n";
                
                //root[index] = nullptr;
                shiftTree(index, (index * 2) - index, index);
                ;
            }
            //Right Subtree
            else{
                //DEBUG
                cout << "\nRIGHT SUBTREE CASE\n";
                
                //root[index] = nullptr;
                shiftTree(index, (index * 2 + 1) - index, index);
                ;
            }
             
            */
            
            
            /*
            //Case: Left of root
            if (root[index]->key < root[1]->key){
                //Case: Left Subtree
                if(root[index * 2] != nullptr){
                    shiftTree(index);
                    //FIXME: Add code
                    ;
                }
                //Case: Right Subtree
                else{
                    shiftTree(index);
                    //FIXME: add code
                    ;
                }
                
            }
            //Case: Right of root
            else{
                //Case: Left Subtree
                if(root[index * 2] != nullptr){
                    //FIXME: Add code
                    shiftTree(index);
                    ;
                }
                //Case: Right Subtree
                else{
                    //FIXME: add code
                    shiftTree(index);
                    ;
                }
            }
             */
            //DEBUG
            //cout << "\n#/#/#/#/#/#/#/#/#/#/#/#/#/#/#/#/#/#/\n";
            //cout << "PRINTING TREE POST REMOVAL\n";
            //printTree();
        //}
        
	}

	int getSize() {
		return this->size;
	}

	int getCount() {
		return this->count;
	}
    

};
