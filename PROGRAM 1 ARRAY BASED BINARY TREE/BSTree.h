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
            out << *(root[index]->value) << endl;
            printTree(index * 2 + 1, out);
        }
   
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
        int index = 1;
        while(root[index] != nullptr){
            if(key < root[index]->key){
                index = index * 2;
            }
            else if(key > root[index]->key){
                index = index * 2 + 1;
            }
            else if(key == root[index]->key){
                return index;
            }
        }
        return 0;
    }
    
    //Helper recursive function to move array
    void shiftTree(int origin, int moveVal){
        /*
        root[origin - moveVal] = root[origin];
        root[origin] = nullptr;
        if (root[origin * 2] != nullptr){
            shiftTree(origin * 2, moveVal * 2);
        }
        if (root[origin * 2 + 1] != nullptr){
            shiftTree(origin * 2 + 1, moveVal);
        }
         */
        
        // ********************************************
        // ********************************************
        /*
        root[origin - moveVal] = root[origin];
        root[origin] = nullptr;
        shiftTree(origin * 2, moveVal * 2);
        shiftTree(origin * 2 + 1, moveVal * 2);
         */
        
        // ********************************************
        // ********************************************
        /*
        //if (root[dest] != root[origin]){
        //    root[dest] = nullptr;
        //}
        //DEBUG
        cout << "ORIGIN: " << origin << endl;
        cout << "MOVEVAL: " << moveVal << endl;
        cout << "DIFFERENCE: " << origin - moveVal << endl;
        
        
        //left Subtree
        if(root[origin * 2] != nullptr){
            shiftTree(origin,origin * 2, moveVal * 2);
        }
        root[origin - moveVal] = root[origin];
        root[origin] = nullptr;
        
        if(root[origin * 2 + 1]){
            shiftTree(origin,origin * 2 + 1, moveVal * 2);
        }
        
         */
         
        // ********************************************
        // ********************************************
        /*

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
         */
        
        // ********************************************
        // ********************************************
        /*
        int next; //
        //Actions if left subtree
        if (subTree == 1){
            next = origin * 2;
        }
        //Action if right subtree
        if(subTree == 2){
            next = origin * 2 + 1;
        }
        moveVal = next - origin;
        root[next - moveVal] = root[next];
        root[next] = nullptr;
        if(root[next * 2] != nullptr){
            shiftTree(next, 1);
        }
        if(root[next * 2 + 1] != nullptr){
            shiftTree(next, 2);
        }
         */
        
        // ********************************************
        // ********************************************
        
        /*
        int next =
        //Left Subtree
        if (root[origin * 2] != nullptr){
            next = origin * 2;
            root[next - moveVal] = root[next];
            
        }
        //Right Subtree
        if(root[origin * 2 + 1] != nullptr){
            next = origin * 2 + 1;
            root[next - moveVal] = root[next];
            //root[next] = nullptr;
            //shiftTree(next, moveVal * 2);
        }
        
        root[ - moveVal] = root[next];
        root[next] = nullptr;
        shiftTree(next, moveVal * 2);
       */
        
        // ********************************************
        // ********************************************
        
        
        if(origin < size && root[origin] != nullptr){
            
            shiftTree(origin * 2, moveVal * 2);
            root[origin - moveVal] = root[origin];
            root[origin] = nullptr;
            shiftTree(origin * 2 + 1, moveVal * 2);
           
            //root[index] = nullptr;
            
            //root[index] = nullptr;
        }
        
        
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
        makeEmpty();
        delete [] root;
		// add needed code
	}

	/*
	* Finds the node with the smallest element in the tree	
	*/
	const Value findMin() const
	{
        int index = 1;
        while(root[index * 2] != nullptr){
            index = index * 2;
        }
        return root[index]->value;
	}

	/*
	* Finds the node with the largest element in the tree
	*/
	const Value findMax() const
	{
        int index = 1;
        while(root[index * 2 + 1] != nullptr){
            index = index * 2 + 1;
        }
        return root[index]->value;
	}

	/*
	* Finds the node with that the key
	* updates the founditem refrerence if found
	* returns true if it was found 
	* returns false if it was not 
	*/
	bool find(const KeyComparable & key , Value & founditem) const
	{
        int index = 1;
        while(root[index] != nullptr){
            if(key < root[index]->key){
                index = index * 2;
            }
            else if(key > root[index]->key){
                index = index * 2 + 1;
            }
            else if(key == root[index]->key){
                founditem = root[index]->value;
                return true;
            }
        }
		return false;
	}

	/*
	* Returns true if the item is found in the tree
	*/
	bool contains(const KeyComparable & key) const
	{
        int index = 1;
        while(root[index] != nullptr){
            if(key < root[index]->key){
                index = index * 2;
            }
            else if(key > root[index]->key){
                index = index * 2 + 1;
            }
            else if(key == root[index]->key){
                return true;
            }
        }
		return false;
	}

	/*
	* Returns true if tree has no nodes
	*/
	bool isEmpty() const{
		return root[1] == nullptr;
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
        
        //Index at which key is stored
        int index = findIndex(key);
        
        //If the key is not in the tree display message and exit
        if(key == 0){
            cout << "KEY: " << key << endl;
            cout << "\nKey was not found. Exiting Remove Function\n";
        }
        
        //DEBUG
        //cout << "\n\nPRINTING ARRAY BEFORE REMOVE\n\n";
        //printArray();
        //cout << "INDEX: " << index << endl;
        
        else{
            //Case: No Children
            if(root[index * 2] == nullptr && root[index * 2 + 1] == nullptr){
                delete root[index];
                root[index] = nullptr;
                //this->count--;
                
                //DEBUG
                
                cout << "\n\nPRINTING ARRAY AFTER REMOVE CASE NO CHILDREN\n\n";
                printArray();
            }
            
            //Case: Two Children
            else if(root[index * 2] != nullptr && root[index * 2 + 1] != nullptr){
                int next; //successor node
                
                //find min of right subtree
                next = index * 2 + 1;
                while(root[next * 2] != nullptr){
                    next = next * 2;
                }
                
                //if no subtree off of next
                if(root[next * 2 + 1] == nullptr || next >= size){
                    delete root[index];
                    root[index] = root[next];
                    root[next] = nullptr;
                }
                
                //if right subtree of of next
                else{
                    //Save pointer to pair object
                    Pair *saver = root[next];
                    
                    //remove next to shift tree
                    remove(root[next]->key);
                    
                    //set original node equal to next
                    root[index] = saver;
                    
                    //delete node at next if nothing took its place
                    if(root[next] == saver){
                        //delete saver;
                        root[next] = nullptr;
                    }
                }
            }
            
            //Case One Child
            else{
                //Left Subtree
                if(root[index * 2] != nullptr){
                    //Save pointer to pair object
                    Pair *saver = root[index];
                    
                    //recursively move tree
                    shiftTree(index * 2, index * 2 - index);
                    
                    //if nothing has taken the place delete node
                    if(root[index] == saver){
                        root[index] = nullptr;
                    }
                }
                //Right subtree
                else{
                    //Save pointer to pair object
                    Pair *saver = root[index];
                    
                    //recursively move tree
                    shiftTree(index * 2 + 1, (index * 2 + 1) - index);
                    
                    //if nothing has taken the place delete node
                    if(root[index] == saver){
                        root[index] = nullptr;
                    }
                }
            }
        }
        
        // ********************************************
        // ********************************************
        
        /*
        
        //Find index of key
        int index = findIndex(key);
        
        //Case: No children
        if (root[index * 2] == nullptr && root[index * 2 + 1] == nullptr){
            //FIXME: Dynamic Memory Management?
            cout << "\n* * * * * * *CASE: ONE CHILD* * * * * * *\n";
            cout << "INDEX: " << index << endl;
            cout << "KEY: " << key << endl;
            cout << "ROOT AT INDEX PRE-DELETION: \n" << *(root[index]->value) << endl << endl;
            
            delete root[index];
            root[index] = nullptr;
            this->count--;
            
            //DEBUG
            //printArray();
        }
        //Case: Two Children
        else if (root[index * 2] != nullptr && root[index * 2 + 1] != nullptr){
            
            //DEBUG
            cout << "\n^_^_^_^_^_FOUND: CASE TWO CHILDREN_^_^_^_^_^_\n";
            cout << "INDEX: " << index << endl;
            cout << "KEY: " << key << endl;
            cout << "ROOT AT INDEX PRE-DELETION: \n" << *(root[index]->value) << endl << endl;
            
            
            //FIXME: Dynamic Memory Management?
            //Determine min value of right subtree
            int successor = index * 2 + 1;
            while(root[successor * 2] != nullptr){
                successor = successor * 2;
            }
            //If no subtrees
            if (root[successor * 2 + 1] == nullptr) {
                root[index] = root[successor];
                root[successor] = nullptr;
            }
            //If right subtree exist
            else if(root[index * 2 + 1] != nullptr){
                //Save pointer to the computer scientist object
                Value *saver = &(root[successor]->value);
                //Remove the successor
                remove(root[successor]->key);
                //Set the node from the original removed node equal to the saved CS object
                root[index]->value = *saver;
                root[index]->key = (root[index]->value)->getID();
                //set the pointer at successor index equal to nullptr if it hasnt changed
                if (root[successor]->value == *saver){
                    root[successor] = nullptr;
                }
            }
            printArray();
            cout << "INDEX: " << index << endl;
            cout << "ROOT AT INDEX POST-DELETION: \n" << *(root[index]->value) << endl;
            cout << "^_^_^_^_^_^_^_^_^_^_^_^_^_^_^_^\n";
        }
        //Case: One Child
        else{
            //DEBUG
            cout << "\n~~~~~~~~~FOUND: CASE ONE CHILDREN~~~~~~~~~\n";
            cout << "INDEX: " << index << endl;
            cout << "ROOT AT INDEX PRE-DELETION: \n" << *(root[index]->value) << endl << endl;
            
            //Left Subtree Child
            if(root[index * 2] != nullptr){
                //Save a pointer to CS object
                Value *saver = &(root[index * 2]->value);
                //Move child up
                //root[index] = root[index * 2];
                //remove the child
                remove(root[index * 2]->key);
                root[index]->value = *saver;
                root[index]->key = (root[index]->value)->getID();
                //set node equal to nullptr if nothing else tooks its place
                if (root[index * 2]->value == *saver){
                    root[index * 2] = nullptr;
                }
                
            }
            //Right Subtree Child
            else{
                //Save a pointer to CS object
                Value *saver = &(root[index * 2 + 1]->value);
                //Move child up
                //root[index] = root[index * 2 + 1];
                //remove the child
                remove(root[index * 2]->key);
                root[index]->value = *saver;
                root[index]->key = (root[index]->value)->getID();
                //set node equal to nullptr if nothing else took its place
                if (root[index * 2 + 1]->value == *saver){
                    root[index * 2 + 1] = nullptr;
                }
            }
            printArray();
            cout << "INDEX: " << index << endl;
            //cout << "ROOT AT INDEX POST-DELETION: \n" << *(root[index]->value) << endl;
            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
            
        }
        
        */
        
        // ********************************************
        // ********************************************
        
        /*
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
        */
	}

	int getSize() {
		return this->size;
	}

	int getCount() {
		return this->count;
	}
};
