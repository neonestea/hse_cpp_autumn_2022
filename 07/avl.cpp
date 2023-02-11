#include <iostream>
#include "exception.hpp"

using namespace std;




template<
   class Key,
    class T,
    class Compare = std::less<Key>,
    class Allocator = std::allocator<std::pair<const Key, T>>
> 
class avl
{ 
    struct node // структура для представления узлов дерева
    {
        public:
            Key key_;
            T value_;
            node* left;
            node* right;
            node* parent;
            int n;

        node() { 
            left = right = parent = NULL;
        }

        node(Key k, T v) { 
            key_ = k; value_ = v; left = right = parent = NULL;
        }

		T getValue()
		{
			return value_;
		}
    };

    class iterator {
	friend class avl;
    using reference = T&;
    public:

	iterator() {
	    ptr = nullptr;
	}

	iterator(node* p) {
	    ptr = p;
	}

	iterator(const iterator& it) {
	    ptr = it.ptr;
	}

	iterator& operator=(const iterator& it) {
	    ptr = it.ptr;
	    return *this;
	}

	bool operator==(const iterator& it) const {
	    return ptr == it.ptr;
	}

	bool operator!=(const iterator& it) const {
	    return ptr != it.ptr;
	}

	bool operator<(const iterator& it) const {
	    return **this < *it;
	}

	bool operator>(const iterator& it) const {
	    return **this > *it;
	}

	bool operator<=(const iterator& it) const {
	    return **this <= *it;
	}

	bool operator>=(const iterator& it) const {
	    return **this >= *it;
	}

	// pre-increment
	iterator& operator++() {
	    if (ptr->right) {
		ptr = ptr->right;
		while (ptr->left) {
		    ptr = ptr->left;
		}
	    } else {
		node* before;
		do {
		    before = ptr;
		    ptr = ptr->parent;
		} while (ptr && before == ptr->right);
	    }
	    return *this;
	}

	// post-increment
	iterator operator++(int) {
	    iterator old(*this);
	    ++(*this);
	    return old;
	}

	// pre-decrement
	iterator& operator--() {
	    if (ptr->left) {
		ptr = ptr->left;
		while (ptr->right) {
		    ptr = ptr->right;
		}
	    } else {
		node* before;
		do {
		    before = ptr;
		    ptr = ptr->parent;
		} while (ptr && before == ptr->left);
	    }
	    return *this;
	}

	// post-decrement
	iterator operator--(int) {
	    iterator old(*this);
	    --(*this);
	    return old;
	}

	reference operator*() const {
	    return ptr->value_;
	}

	/*pointer operator->() const {
	    return &(ptr->value_);
	}*/
    private:
	node *ptr;
    };

    
    public:
        node* root;
        int size_;
        using reference = T&;
    
    avl()
    {
        //root = alloc.allocate(1);
	    //alloc.construct(root);
        root = NULL;
        size_ = 0;
    }

    /*~tree() noexcept {
        clear_node(root);
        alloc.destroy(root);
        alloc.deallocate(root, 1);
    }*/

    bool empty()                                              //EMPTY
    {
        return root == NULL;
    }

    int size()                                                //SIZE
    {
        return size_;
    }

    void clear()                                              //CLEAR
    {
        root = NULL;
    }

	iterator begin() 
	{
		return iterator(minValueNode(root));
    }

	iterator end() {
		return iterator(maxValueNode(root));
        //return iterator(root);
    }

	iterator rend() 
	{
		return iterator(minValueNode(root));
    }

	iterator rbegin() {
		return iterator(maxValueNode(root));
    }


    reference operator[](int i) {           //operator[]
	    return *at(i);
    }

    iterator at(int i) {
	// bounds checking
        if (i >= size()) {
            throw ElementNotExistst("Element not exist");
        }

        auto begin_it = begin();
        auto end_it = end();
        int count = 0;
        std::cout << "MAx = " << *end_it << std::endl;
        while (begin_it != end_it)
        {
            std::cout << "i = " << count << "check = " << *begin_it << std::endl;
            if (count == i)
            {
                return begin_it;
            }
            ++begin_it;
            count++;
        }
        return NULL;
        
    }

    int height(node* p)
    {
        if (p == NULL)
        {
            return -1;
        } else
        {
            int lheight = height(p -> left);
            int rheight = height(p -> right);

            /* use the larger one */
            if (lheight > rheight)
            {
                return (lheight + 1);
            } else 
            {
                return (rheight + 1);
            }
        }
    }

    int getBalanceFactor(node* p)  //проверяем баланс поддеревьев узла
    {
        if (p == NULL)
        {
            return -1;
        }
      
        return height(p -> left) - height(p -> right);
    }


    node* rightRotate(node* p) // правый поворот вокруг p
    {
        node* q = p->left;
        node* z = q->right;

        q->right = p;
        p->left = z;

        return q;
    }

    node* leftRotate(node * q) { //левый поворот вокруг q
        node* p = q -> right;
        node* z = p -> left;

        p -> left = q;
        q -> right = z;


        return p;
    }

    node* insert(Key k, T v)                       //INSERT
    {
        node* new_node = new node(k, v);
        root = insertNode(root, new_node);
        size_++;
        updateParents(root);
        return root;
    }

    node* insertNode(node* r, node* new_node) 
    {
        if (r == NULL) 
        {
            r = new_node;
            cout << "Value " << new_node->key_ << " inserted successfully" << endl;
            return r;
        }

        if (std::less<Key>{}(new_node -> key_, r -> key_)) 
        {
            r->left = insertNode(r -> left, new_node);
        } else if (std::less<Key>{}(r -> key_, new_node -> key_)) 
        {
            r -> right = insertNode(r -> right, new_node);
        } else {
            cout << "No duplicate values allowed!" << endl;
            return r;
        }

        int bf = getBalanceFactor(r);
        //If BF(node) = +2 and BF(node -> left-child) = +1, perform LL rotation.
        //If BF(node) = -2 and BF(node -> right-child) = 1, perform RR rotation.
        //If BF(node) = -2 and BF(node -> right-child) = +1, perform RL rotation.
        //If BF(node) = +2 and BF(node -> left-child) = -1, perform LR rotation.
       
        // Left Left Case  
        if (bf > 1 && std::less<Key>{}(new_node -> key_, r -> left -> key_))
            return rightRotate(r);

        // Right Right Case  
        if (bf < -1 && std::less<Key>{}(r -> right -> key_, new_node -> key_))
            return leftRotate(r);

        // Left Right Case  
        if (bf > 1 && std::less<Key>{}(r -> left -> key_, new_node -> key_)) {
            r -> left = leftRotate(r -> left);
            return rightRotate(r);
        }

        // Right Left Case  
        if (bf < -1 && std::less<Key>{}(r -> right -> key_, new_node -> key_)) {
            r -> right = rightRotate(r -> right);
            return leftRotate(r);
        }

        return r;

    }

    

    node* minValueNode(node* p) 
    {
        node* current = new node();
        current = p;
        while (current -> left != NULL) {
            current = current -> left;
        }
        cout << "Min node = " << current->key_ << endl;
        return current;
    }

    node* maxValueNode(node* p) 
    {
        node* current = new node();
        current = p;
        while (current -> right != NULL) {
            current = current -> right;
        }
        cout << "Max node = " << current->key_ << endl;
        return current;
    }

    node* erase(Key key_)                                  //ERASE
    {
        node* node_to_erase = find(root, key_);
        if(node_to_erase != NULL)
        {
            root = deleteNode(root, key_);\
            cout << "Deleted " << key_ << endl;
        }
        else
        {
            cout << "Not found!";
        }
        size_--;
        updateParents(root);
        return root;
        
        //objects_.clear();
        //getMap(root);
        //return objects_;
    }

    node* deleteNode(node* r, Key v) {
        // base case 
        if (r == NULL) {
            return NULL;
        }
        // If the key to be deleted is smaller than the root's key, 
        // then it lies in left subtree 
        else if (std::less<Key>{}(v, r -> key_)) {
            r -> left = deleteNode(r -> left, v);
        }
        // If the key to be deleted is greater than the root's key, 
        // then it lies in right subtree 
        else if (std::less<Key>{}(r -> key_, v)) {
            r -> right = deleteNode(r -> right, v);
        }
        // if key is same as root's key, then This is the node to be deleted 
        else {
        // node with only one child or no child 
            if (r -> left == NULL) {
                node * temp = r -> right;
                delete r;
                return temp;
            } else if (r -> right == NULL) {
                node * temp = r -> left;
                delete r;
                return temp;
            } else {
                // node with two children: Get the inorder successor (smallest 
                // in the right subtree) 
                node * temp = minValueNode(r -> right);
                // Copy the inorder successor's content to this node 
                r -> key_ = temp -> key_;
                // Delete the inorder successor 
                r -> right = deleteNode(r -> right, temp -> key_);
                //deleteNode(r->right, temp->value); 
            }
        }

        int bf = getBalanceFactor(r);
        
        if (bf == 2 && getBalanceFactor(r -> left) >= 0)
            return rightRotate(r);
        
        else if (bf == 2 && getBalanceFactor(r -> left) == -1) {
            r -> left = leftRotate(r -> left);
            return rightRotate(r);
        }
        
        else if (bf == -2 && getBalanceFactor(r -> right) <= -0)
            return leftRotate(r);
        
        else if (bf == -2 && getBalanceFactor(r -> right) == 1) {
            r -> right = rightRotate(r -> right);
            return leftRotate(r);
        }
        
        return r;
    }

    void print2D(node* r, int space) 
    {
        if (r == NULL) 
            return;
        space += 10;
        print2D(r -> right, space); 
        cout << endl;
        for (int i = 10; i < space; i++) 
            cout << " "; 
        cout << r -> key_ << "\n";
        print2D(r -> left, space); 
    }

    void print(node * r) //print asc
    {
        if (r == NULL)
            return;
        print(r -> left);
        cout << r -> value_ << " ";
        print(r -> right);
    }

   

    void updateParents(node * r) //print asc
    {
        if (r == NULL)
            return;
        if (r == root)
        {
            //cout << "Update parent for root" << r->key_ << endl;
            r -> parent = NULL;
        } 
            
        node* left_node = r -> left;
        node* right_node = r -> right;
            
            
        if (left_node != NULL)
        {
            //cout << "Update parent for left " << left_node->key_ << " set " << r->key_ << endl;
            
            left_node->parent = r;
        }
        if (right_node != NULL)
        {
            //cout << "Update parent for right " << right_node->key_ << " set " << r->key_ << endl;
            
            right_node->parent = r;
        }
            
            
        
        updateParents(r -> left);
        updateParents(r -> right);
    }

    


    node * find(node * r, Key val) 
    {
        if (r == NULL || r -> key_ == val)
            return r;

        else if (val < r -> key_)
            return find(r -> left, val);

        else
            return find(r -> right, val);
    }

    bool contains(Key key_)                                                           //CONTAINS
    {
        node* node_to_check = find(root, key_);
        return node_to_check == NULL? false : true;
    }

    void getParent(Key k) 
    {
        node* child_node = find(root, k);
        cout << "Child node " <<  child_node->key_ << endl;
        if (child_node == root)
        {
            cout << "Root" << endl;
        } else {
            node* parent_node = child_node->parent;
            cout << "Parent node " <<  parent_node->key_ << endl;
        }
    }

};




/*int main()
{
    avl<int, std::string> tree;
    bool checkEmpty = tree.empty();
    cout << "Tree empty: " << checkEmpty << endl;
    tree.insert(19 , "nineteen");
    tree.insert(36, "thirty six");
    tree.insert(25, "25");
    tree.insert(14, "fourteen");
    tree.insert(12, "12");
    tree.insert(23, "23");
    bool checkNotEmpty = tree.empty();
    cout << "Tree empty: " << checkNotEmpty << endl;
    tree.print2D(tree.root, 5);
    tree.print(tree.root);
    bool checkExists = tree.contains(36);
    bool checkNotExists = tree.contains(37);
    cout << "36 exists: " << checkExists << endl;
    cout << "37 exists: " << checkNotExists << endl;
    
    tree.getParent(19);
    tree.getParent(36);
    tree.getParent(25);
    tree.getParent(14);
    tree.getParent(12);
    tree.getParent(23);

    tree[1] = "NEW";
    
    tree.minValueNode(tree.root);
    tree.maxValueNode(tree.root);
    cout << "Size: " << tree.size() << endl;

    
	
	
    int num = 36;
    tree.erase(num);
    auto begin_it = tree.begin();
    auto end_it = tree.end();
    std::string beg = *begin_it;
    std::string end = *end_it;
    cout << "beg: " << beg << endl;
    cout << "end: " << end << endl;

    auto rbegin_it = tree.rbegin();
    auto rend_it = tree.rend();
    std::string rbeg = *rbegin_it;
    std::string rend = *rend_it;
    cout << "rbeg: " << rbeg << endl;
    cout << "rend: " << rend << endl;
    tree.maxValueNode(tree.root);
    //at36 = tree.at(36);
    //cout << "at 36: " << at36 << endl;
    cout << "Size: " << tree.size() << endl;
    tree.print2D(tree.root, 5);
    tree.print(tree.root);
    tree.clear();
    cout << "Tree empty: " << checkEmpty << endl;

    return 0;
}*/