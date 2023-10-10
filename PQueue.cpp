/**
 * implementation file for the  stl vector-based heap max-priority queue class
 * @author William Duncan, Anindo Hazra
 * <pre>
 * file PQueue.cpp
 * Date: 25 September 2023
 * Instructor: Dr. Duncan
 * Course: csc 3102
 * </pre>
*/

#include "PQueue.h"

using namespace std;

template <typename E>
PQueue<E>::PQueue()
{
    
}

template <typename E>
PQueue<E>::PQueue(std::function<int(const E&, const E&)> fn) : cmp(fn) 
{
    // Constructor with a custom comparator function
}


template <typename E>
bool PQueue<E>::isEmpty() const
{
   return tree.empty();
}

template<typename E>
void PQueue<E>::insert(const E& item)
{
    tree.push_back(item);
    int child = tree.size() - 1;
    
    while (child > 0) 
    {
        int parent = (child - 1) / 2;
            if (cmp(tree[child], tree[parent]) < 0) 
            {
                swap(child, parent);
                child = parent;
            }
            else
            {
                break;
            }
    }
}



template<typename E>
E PQueue<E>::remove() 
{
   E root = tree[0];
   tree[0] = tree[tree.size() - 1];
   tree.pop_back();
    rebuild(0);
   return root;
}

template<typename E>
const E& PQueue<E>::peek() const
{
   return tree[0];
}

template<typename E>
int PQueue<E>::size()const
{
   return static_cast<int>(tree.size());

}


template<typename E>
void PQueue<E>::swap(int place, int parent)
{
   E temp = tree[place];
   tree[place] = tree[parent];
   tree[parent] = temp;
}

template<typename E>
void PQueue<E>::rebuild(int root)
{
   int leftChild = 2 * root + 1;
        int rightChild = 2 * root + 2;
        int smallest = root;

        if (leftChild < size() && cmp(tree[leftChild], tree[smallest]) < 0) 
        {
            smallest = leftChild;
        }
        if (rightChild < size() && cmp(tree[rightChild], tree[smallest]) < 0) 
        {
            smallest = rightChild;
        }

        if (smallest != root) 
        {
            swap(root, smallest);
            rebuild(smallest);
        }
}

