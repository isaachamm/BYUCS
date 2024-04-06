#include "IntervalTree.h"
#include <vector>

using namespace std;

template <typename T>
class AugmentedIntervalTree : public IntervalTree<T>
{


public:




    /*AugmentedIntervalTree()
    {

    }*/
    ~AugmentedIntervalTree()
    {
        clear();
    }
    void clear()
    {
        clear_function(this->root);
        this->root = nullptr;
        delete this->root;
    }

    bool is_empty() const
    {
        Node<T>* node = this->root;
        if (node == nullptr)
        {

            return true;
        }
        else
        {

            return false;
        }


    }
    bool add(T const& lower, T const& upper)
    {
        //Node<T>* n = this->root;
        Interval<int> myInterval(lower, upper);
        bool wasAdded = add_recursive(this->root, myInterval);

        return wasAdded;
    }
    vector<Interval<T>> query(T const& point) const
    {
        vector<Interval<T>> myVector;
        T myPoint = point;
        query_recursive(myVector, this->root, myPoint);

        return myVector;
    }
    bool remove(T const& lower, T const& upper)
    {
        //return true;
        Interval<int> myInterval(lower, upper);
        Node<T>* n = this->root;
        //cout << n->interval.upper << endl;
        bool wasRemoved = remove_recursive(this->root, myInterval);
        return wasRemoved;
    }

    void clear_function(Node<T>* const& node)
    {
        if (node == NULL)
        {
            return;
        }
        if (node->left != NULL)
        {
            clear_function(node->left);
        }
        if (node->right != NULL)
        {
            clear_function(node->right);
        }

        delete node;
        return;


    }


    bool add_recursive(Node<T>*& n, Interval<T> const&newInterval)
    {
        bool wasAdded = false;
        //cout << "hunting for the phantom return true" << endl;
        //return false;
        if (n == nullptr)
        {
            n = new Node<T>(newInterval);
            //node->interval = myInterval;
            //node->min_max = myInterval;
            n->left = nullptr;
            n->right = nullptr;
            //n = node;
            //cout << "success" << endl;
            //cout << "returning true" << endl;
            wasAdded = true;
            return wasAdded;
        }
        else if (newInterval.lower > newInterval.upper)
        {
            wasAdded = false;
            return wasAdded;
        }
        else if (newInterval.lower == n->interval.lower && newInterval.upper == n->interval.upper)
        {
            wasAdded = false;
            return wasAdded;
        }
        else if (newInterval.upper < n->min_max.lower || newInterval.lower > n->min_max.upper)
        {
            wasAdded = false;
            return wasAdded;
        }
        else if (newInterval.lower < n->interval.lower || ((newInterval.lower == n->interval.lower) && (newInterval.upper < n->interval.upper)))
        {


            wasAdded = add_recursive(n->left, newInterval);

            if (wasAdded)
            {
                update_min_max(n, n->left, n->right);
                wasAdded = true;
            }

            return wasAdded;
        }
        else if(newInterval.lower >= n->interval.lower || newInterval.upper > n->interval.upper)
        {
            wasAdded = add_recursive(n->right, newInterval);
            //cout << "was added is: " << wasAdded << endl;
            if (wasAdded)
            {
                update_min_max(n, n->left, n->right);
                wasAdded = true;
            }
            //cout << "added right" << endl;
            return wasAdded;
        }
        //cout << "returning false" << endl;
        return wasAdded;
    }

    void update_min_max(Node<T>*& n, Node<T>*& left, Node<T>*& right)// a function that updates the min and max of a node based off of its children
    {
        if (right == nullptr && left == nullptr)
        {
            n->min_max.lower = n->interval.lower;
            n->min_max.upper = n->interval.upper;
        }
        else if (left != nullptr && right != nullptr)//two chirrens!!!!
        {

            if (n->min_max.lower <= left->min_max.lower && n->min_max.upper >= right->min_max.upper)
            {

                return;
            }
            if (n->min_max.lower > left->min_max.lower)
            {

                n->min_max.lower = left->min_max.lower;
            }
            if (n->min_max.upper < right->min_max.upper)
            {

                n->min_max.upper = right->min_max.upper;
            }
        }
        else if (right == nullptr)//one child law
        {
            if (n->min_max.lower > left->min_max.lower)
            {
                cout << "why is this not working?" << endl;
                n->min_max.lower = left->min_max.lower;
            }

        }
        else if (left == nullptr)//still a lonely child
        {
            if (n->min_max.upper < right->min_max.upper)
            {
                n->min_max.upper = right->min_max.upper;
            }
        }


        return;
    }


    void query_recursive(vector<Interval<T>> &myVector, Node<T>* const&n, T const&point) const //a recursive fucntion that does an IOT to find any intervals that overlap the point
    {
        if (n == nullptr)
        {
            return;
        }
        else if (point >= n->min_max.lower && point < n->min_max.upper)
        {
            query_recursive(myVector, n->left, point);
            if(point >= n->interval.lower && point < n->interval.upper)
            {
                //cout << "adding interval to tree" << endl;
                myVector.push_back(n->interval);
                //cout << myVector.at(0) << endl;
            }
            query_recursive(myVector, n->right, point);
            return;
        }
        else
        {
            return;
        }


    }

    bool remove_recursive(Node<T>*& n, Interval<T> const&newInterval)
    {
        bool wasRemoved;
        if (n == nullptr)
        {
            wasRemoved = false;
            return wasRemoved;
        }

        if(newInterval.lower < n->interval.lower || ((newInterval.lower == n->interval.lower) && (newInterval.upper < n->interval.upper)))
        {
            wasRemoved = remove_recursive(n->left, newInterval);

        }
        else if(newInterval.lower > n->interval.lower)
        {

            wasRemoved = remove_recursive(n->right, newInterval);

        }
        else if (n->interval.lower == newInterval.lower && n->interval.upper == newInterval.upper)
        {

            if (n == nullptr)
            {
                wasRemoved = false;
                return wasRemoved;
            }

            if(n->left == nullptr && n->right == nullptr)
            {
                wasRemoved = true;
                delete n;
                n = nullptr;
                return wasRemoved;
            }
            if (n->left == nullptr)
            {
                cout << "is there any issue left checking?" << endl;
                auto tmp = n;
                n = n->right;
                delete tmp;
                tmp == nullptr;
                wasRemoved = true;
//                return wasRemoved;
            }
            else if (n->right == NULL)
            {
                cout << "is there any issue right checking?" << endl;
                auto tmp = n;
                n = n->left;
                delete tmp;
                tmp == nullptr;
                wasRemoved = true;
//                return wasRemoved;
            } else
            {
                cout << "is there an issue iop checking?";
                // have two children -> swap IOP value
                // IOP is rightmost child in left branch
                // Replace node value with IOP value
                // Delete IOP value from left tree
                auto tmp = n->left;
                while (tmp->right != nullptr)
                {
                    tmp = tmp->right;
                }
                Interval<T> iopInterval = tmp->interval;
                n->interval = iopInterval;
                remove_recursive(n->left, iopInterval);
                wasRemoved = true;
//                return wasRemoved;
            }
            return wasRemoved;
        }
        update_min_max(n, n->left, n->right);
        return wasRemoved;
    }






    /*

     bool _remove(Node<T> *&node, T item) {
        if (node == nullptr) {
            return false;
        }
        bool removed = false;
        if (node->value == item) {
            // have no children
            // have one child
            if (node->left == nullptr) {
                auto tmp = node;
                node = node->right;
                delete tmp;
                removed = true;
            } else if (node->right == nullptr) {
                auto tmp = node;
                node = node->left;
                delete tmp;
                removed = true;
            } else {
                // have two children -> swap IOP value
                // IOP is rightmost child in left branch
                // Replace node value with IOP value
                // Delete IOP value from left tree
                T const &iop_value = _get_iop_value(node);
                node->value = iop_value;
                _remove(node->left, iop_value);
                removed = true;
            }
        } else if (item < node->value) {
            removed = _remove(node->left, item);
        } else {
            removed = _remove(node->right, item);
        }
        if (removed) {
            _update_height(node);
        }
        return removed;
    }
    T const &_get_iop_value(Node<T> *const &node) {
        // Will only ever call this if node->left is not null
        //  so no need to check
        auto tmp = node->left;
        while (tmp->right != nullptr) {
            tmp = tmp->right;
        }
        return tmp->value;
    }
  }
    */

};