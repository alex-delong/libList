#include <initializer_list>
#include <stdexcept>

template<class T> class List {
	struct Node {
		Node* next;
		T value;
		Node() : next(nullptr), value(T()) {}
		Node(T arg_value) : next(nullptr), value(arg_value) {}
		Node(const Node& arg_node) : value(arg_node.value) {
			if (arg_node.next == nullptr) {
				this->next = nullptr;
			} else {
				this->next = new Node(*arg_node.next);
			}
		}
		void link(Node* arg_next) {
			Node* new_next = new Node(*arg_next);
			delete this->next;
			this->next = new_next;
		}
		Node& operator=(const Node& arg_node) {
			if (this == &arg_node) {
				return *this;
			}
			delete this->next;
			if (arg_node.next == nullptr) {
				this->next = nullptr;
			} else {
				this->next = new Node(*arg_node.next);
			}
			this->value = arg_node.value;
            return *this;
		}
		~Node() {
			delete next;
		}
	};
	Node* head;
public:
	List() : head(nullptr) {}
	List(std::initializer_list<T>&& arg_values) : head(new Node) {
		*this->head = *arg_values.begin();
		Node* curr_node_ptr = this->head;
		for (int i = 1; i < arg_values.size(); i++) {
			curr_node_ptr->next = new Node(*(arg_values.begin() + i));
			curr_node_ptr = curr_node_ptr->next;
		}
	}
	unsigned size() const {
		Node* curr_node_ptr = this->head;
		unsigned sz = 0;
		while (curr_node_ptr != nullptr) {
			curr_node_ptr = curr_node_ptr->next;
			sz += 1;
		}
		return sz;
	}
	T& operator[](unsigned arg_i) {
		if (arg_i >= this->size()) {
			throw std::out_of_range("Attempted to access an index greater than the list size.");
		}
		Node* curr_node_ptr = this->head;
		for (unsigned i = 0; i < arg_i; i++) {
			curr_node_ptr = curr_node_ptr->next;
		}
		return curr_node_ptr->value;
    }
    List& operator=(std::initializer_list<T>&& arg_values) {
        delete this->head;
        this->head = new Node(*arg_values.begin());
		Node* curr_node_ptr = this->head;
		for (int i = 1; i < arg_values.size(); i++) {
			curr_node_ptr->next = new Node(*(arg_values.begin() + i));
			curr_node_ptr = curr_node_ptr->next;
		}
        return *this;
    }
	~List() {
		delete head;
	}
};
