#include <iostream>

template <class Type>
struct ListNode{
    Type m_data;
    ListNode<Type>* m_next;
    ListNode(Type const& data) : m_data(data), m_next(nullptr) {}
};

template <class Type>
class List{
private:
    ListNode<Type>* m_root;
    ListNode<Type>* m_last;
    size_t m_size;
public:
    List() : m_root(nullptr), m_size(0) {}
    void push_back(Type const& val){
        ListNode<Type>* new_node = new ListNode<Type>(val);
        if (m_root == nullptr){
            m_root = new_node;
            m_last = m_root;
        }
        else{
            m_last->m_next = new_node;
            m_last = new_node;
        }
        ++m_size;
    }
    ~List(){
        while (m_root != nullptr){
            auto next = m_root->m_next;
            delete m_root;
            m_root = next;
        }
    }

    class Iterator{
    private:
        ListNode<Type>* m_node;
    public:
        Iterator(ListNode<Type>* node) : m_node(node) {}
        Iterator(Iterator const&) = default;
        Iterator& operator=(Iterator const& val){
            m_node = val.m_node;
        }
        Type& operator*(){
            return m_node->m_data;
        }
        Iterator& operator++(){
            m_node = m_node->m_next;
            return *this;
        }
        Iterator operator++(int){
            Iterator iter_copy(m_node);
            m_node = m_node->m_next;
            return iter_copy;
        }
        bool operator==(Iterator const& val){
            return m_node == val.m_node;
        }
        bool operator!=(Iterator const& val){
            return !(*this == val);
        }
    };

    Iterator begin(){
        return Iterator(m_root);
    }

    Iterator end(){
        return Iterator(nullptr);
    }
};

int main(){
    size_t const SZ = 3;
    int arr[SZ] = {1, 2, 3};
    for (size_t idx = 0; idx < SZ; ++idx)
        std::cout << arr[idx] << " "; // std::cout << *(arr+idx) << " ";
    std::cout << "\n";
    
    int* curr_arr = arr;
    int * const arr_end = arr + SZ;
    while (curr_arr != arr_end)
        std::cout << *(curr_arr++) << " ";
    std::cout << "\n";
    
    List<int> int_list;
    for (size_t idx = 1; idx <= 3; ++idx)
        int_list.push_back(idx);

    for (auto start = int_list.begin(); start != int_list.end(); ++start)
        std::cout << *start << " ";
    std::cout << "\n";

    *(int_list.begin()) = 42;

    auto second = int_list.begin();
    ++second;

    for (int val: int_list)
        std::cout << val << " ";
    std::cout << "\n";

    //*
    //++
    //--
    //+n
    //-n
    //==
    //!=
    return 0;
}