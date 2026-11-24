
#include <iostream>
#include <string>
#include <limits>
using namespace std;

// book  class
class Book {
public:
    int book_id;
    string title;
    string author;
    int year;
    int total_copies;
    int available_copies;

    Book() {
        book_id = 0;
        title = "";
        author = "";
        year = 0;
        total_copies = 0;
        available_copies = 0;
    }

    Book(int id, string t, string a, int y, int total, int available) {
        book_id = id;
        title = t;
        author = a;
        year = y;
        total_copies = total;
        available_copies = available;
    }

    void display_book() const {
        cout << "\nBook ID: " << book_id;
        cout << "\nTitle: " << title;
        cout << "\nAuthor: " << author;
        cout << "\nYear: " << year;
        cout << "\nTotal Copies: " << total_copies;
        cout << "\nAvailable Copies: " << available_copies;
        cout << "\n--------------------------------\n";
    }
};

// book node

class book_node {
public:
    Book data;
    book_node* left;
    book_node* right;

    book_node(Book b) {
        data = b;
        left = NULL;
        right = NULL;
    }
};


//book bst

class BookTree {
public:

    book_node* root;

    BookTree() {
        root = NULL;
    }

    book_node* insert(book_node* root, Book data) {

        if (root == NULL) {
            return new book_node(data);
        }

        if (data.book_id < root->data.book_id) {
            root->left = insert(root->left, data);
        }

        else if (data.book_id > root->data.book_id) {
            root->right = insert(root->right, data);
        }

        else {
            cout << "Book ID already exists!\n";
        }

        return root;
    }

    book_node* search(book_node* root, int id) {

        if (root == NULL || root->data.book_id == id) {
            return root;
        }

        if (id < root->data.book_id) {
            return search(root->left, id);
        }

        return search(root->right, id);
    }

    int count_books(book_node* root) {

        if (root == NULL) {
            return 0;
        }

        return 1 + count_books(root->left)
                 + count_books(root->right);
    }

    int find_min(book_node* root) {

        if (root == NULL) return -1;

        while (root->left != NULL) {
            root = root->left;
        }

        return root->data.book_id;
    }

    int find_max(book_node* root) {

        if (root == NULL) return -1;

        while (root->right != NULL) {
            root = root->right;
        }

        return root->data.book_id;
    }

    book_node* delete_book(book_node* root, int id) {

        if (root == NULL) {
            return NULL;
        }

        if (id < root->data.book_id) {
            root->left = delete_book(root->left, id);
        }

        else if (id > root->data.book_id) {
            root->right = delete_book(root->right, id);
        }

        else {

            //case1 no left child
            if (root->left == NULL) {
                book_node* temp = root->right;
                delete root;
                return temp;
            }

           //case 2 no right child
            else if (root->right == NULL) {
                book_node* temp = root->left;
                delete root;
                return temp;
            }

           //case 3 two right children
            book_node* temp = root->right;

            while (temp->left != NULL) {
                temp = temp->left;
            }

            root->data = temp->data;

            root->right = delete_book(
                root->right,
                temp->data.book_id
            );
        }

        return root;
    }

    void display_inorder(book_node* root) {

        if (root == NULL) return;

        display_inorder(root->left);

        root->data.display_book();

        display_inorder(root->right);
    }

    void search_by_title(book_node* root, string title) {

        if (root == NULL) return;

        search_by_title(root->left, title);

        if (root->data.title == title) {
            root->data.display_book();
        }

        search_by_title(root->right, title);
    }

    void search_by_author(book_node* root, string author) {

        if (root == NULL) return;

        search_by_author(root->left, author);

        if (root->data.author == author) {
            root->data.display_book();
        }

        search_by_author(root->right, author);
    }

    void update_book(int id, Book& oldBook, Book& newBook) {

        book_node* b = search(root, id);

        if (b == NULL) {
            cout << "Book does not exist!\n";
            return;
        }

        oldBook = b->data;

        cout << "\n1. Update Title";
        cout << "\n2. Update Author";
        cout << "\n3. Update Year";
        cout << "\n4. Update Total Copies";
        cout << "\nEnter choice: ";

        int choice;
        cin >> choice;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {

            case 1:
                cout << "Enter new title: ";
                getline(cin, b->data.title);
                break;

            case 2:
                cout << "Enter new author: ";
                getline(cin, b->data.author);
                break;

            case 3:
                cout << "Enter new year: ";
                cin >> b->data.year;
                break;

            case 4: {
                int total;
                cout << "Enter new total copies: ";
                cin >> total;

                if (total < b->data.total_copies -
                            b->data.available_copies) {
                    cout << "Cannot set total below borrowed copies!\n";
                    return;
                }

                b->data.available_copies +=
                    total - b->data.total_copies;

                b->data.total_copies = total;
                break;
            }

            default:
                cout << "Invalid choice!\n";
                return;
        }

        newBook = b->data;
        cout << "Book updated successfully!\n";
    }

    void store_books(book_node* root, Book arr[], int& index) {

        if (root == NULL) return;

        store_books(root->left, arr, index);

        arr[index++] = root->data;

        store_books(root->right, arr, index);
    }

    ~BookTree() {
        clear(root);
    }

    void clear(book_node* root) {
        if (root == NULL) return;

        clear(root->left);
        clear(root->right);

        delete root;
    }
};


//user class

class user {
public:
    int user_id;
    string name;
    string email;
    string phone_number;
    int borrowed_books;

    user() {
        user_id = 0;
        name = "";
        email = "";
        phone_number = "";
        borrowed_books = 0;
    }

    user(int id, string n, string e, string p, int borrowed) {
        user_id = id;
        name = n;
        email = e;
        phone_number = p;
        borrowed_books = borrowed;
    }

    void display_user() const {

        cout << "\nUser ID: " << user_id;
        cout << "\nName: " << name;
        cout << "\nEmail: " << email;
        cout << "\nPhone: " << phone_number;
        cout << "\nBorrowed Books: " << borrowed_books;
        cout << "\n--------------------------------\n";
    }
};

//hash table lp

class hash_table {
public:

    static const int SIZE = 100;

    user table[SIZE];

    //0 empty
    //1 occupied
    // 2 = deleted

    int status[SIZE];

    hash_table() {
        for (int i = 0; i < SIZE; i++) {
            status[i] = 0;
        }
    }

    int hash_function(int id) {
        return (id % SIZE + SIZE) % SIZE;
    }

    bool insert_user(user u) {

        int index = hash_function(u.user_id);

        for (int i = 0; i < SIZE; i++) {

            int current = (index + i) % SIZE;

            if (status[current] == 1) {

                if (table[current].user_id == u.user_id) {
                    cout << "User ID already exists!\n";
                    return false;
                }
            }

            else {
                table[current] = u;
                status[current] = 1;

                cout << "User registered successfully!\n";
                return true;
            }
        }

        cout << "Hash Table is full!\n";
        return false;
    }

    user* search_user(int id) {

        int index = hash_function(id);

        for (int i = 0; i < SIZE; i++) {

            int current = (index + i) % SIZE;

            if (status[current] == 0) {
                return NULL;
            }

            if (status[current] == 1 &&
                table[current].user_id == id) {

                return &table[current];
            }
        }

        return NULL;
    }

    bool delete_user(int id) {

        user* u = search_user(id);

        if (u == NULL) {
            cout << "User does not exist!\n";
            return false;
        }

        if (u->borrowed_books > 0) {
            cout << "Cannot delete user with borrowed books!\n";
            return false;
        }

        int index = hash_function(id);

        for (int i = 0; i < SIZE; i++) {

            int current = (index + i) % SIZE;

            if (status[current] == 0) break;

            if (status[current] == 1 &&
                table[current].user_id == id) {

                status[current] = 2;

                cout << "User deleted successfully!\n";
                return true;
            }
        }

        return false;
    }

    void display_allusers() {

        bool found = false;

        for (int i = 0; i < SIZE; i++) {

            if (status[i] == 1) {
                table[i].display_user();
                found = true;
            }
        }

        if (!found) {
            cout << "No users registered!\n";
        }
    }
};


//borrow record class

class borrow_record {
public:

    int record_id;
    int user_id;
    int book_id;

    string borrow_date;
    string due_date;

    bool return_status;

    borrow_record() {
        record_id = 0;
        user_id = 0;
        book_id = 0;
        return_status = false;
    }

    borrow_record(int r, int u, int b,
                  string bd, string dd, bool status) {

        record_id = r;
        user_id = u;
        book_id = b;
        borrow_date = bd;
        due_date = dd;
        return_status = status;
    }

    void display_record() const {

        cout << "\nRecord ID: " << record_id;
        cout << "\nUser ID: " << user_id;
        cout << "\nBook ID: " << book_id;
        cout << "\nBorrow Date: " << borrow_date;
        cout << "\nDue Date: " << due_date;

        cout << "\nReturn Status: "
             << (return_status ? "Returned" : "Not Returned");

        cout << "\n--------------------------------\n";
    }
};


//borrow node
class borrow_node {
public:

    borrow_record data;
    borrow_node* next;

    borrow_node(borrow_record b) {
        data = b;
        next = NULL;
    }
};


//borrow ll
class BorrowList {
public:

    borrow_node* head;
    int next_record_id;

    BorrowList() {
        head = NULL;
        next_record_id = 1;
    }

    bool has_active_user(int id) {

        borrow_node* temp = head;

        while (temp != NULL) {

            if (temp->data.user_id == id &&
                !temp->data.return_status) {
                return true;
            }

            temp = temp->next;
        }

        return false;
    }

    bool has_active_book(int id) {

        borrow_node* temp = head;

        while (temp != NULL) {

            if (temp->data.book_id == id &&
                !temp->data.return_status) {
                return true;
            }

            temp = temp->next;
        }

        return false;
    }

    borrow_node* search_borrow_book(int id) {

        borrow_node* temp = head;

        while (temp != NULL) {

            if (temp->data.record_id == id) {
                return temp;
            }

            temp = temp->next;
        }

        return NULL;
    }

    void add_borrow_record(borrow_record b) {

        borrow_node* new_node = new borrow_node(b);

        if (head == NULL) {
            head = new_node;
            return;
        }

        borrow_node* temp = head;

        while (temp->next != NULL) {
            temp = temp->next;
        }

        temp->next = new_node;
    }

    void borrow_book(BookTree& books, hash_table& users) {

        int uid, bid;

        cout << "Enter User ID: ";
        cin >> uid;

        cout << "Enter Book ID: ";
        cin >> bid;

        user* u = users.search_user(uid);

        if (u == NULL) {
            cout << "User does not exist!\n";
            return;
        }

        book_node* b = books.search(books.root, bid);

        if (b == NULL) {
            cout << "Book does not exist!\n";
            return;
        }

        if (b->data.available_copies <= 0) {
            cout << "No available copies!\n";
            return;
        }

        string borrow_date, due_date;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Enter Borrow Date: ";
        getline(cin, borrow_date);

        cout << "Enter Due Date: ";
        getline(cin, due_date);

        // Update book
        b->data.available_copies--;

        // Update user
        u->borrowed_books++;

        // Create borrowing record
        borrow_record record(
            next_record_id++,
            uid,
            bid,
            borrow_date,
            due_date,
            false
        );

        add_borrow_record(record);

        cout << "\nBook borrowed successfully!\n";
        cout << "Record ID: " << record.record_id << endl;
    }

    void return_book(BookTree& books, hash_table& users) {

        int id;

        cout << "Enter Borrow Record ID: ";
        cin >> id;

        borrow_node* record = search_borrow_book(id);

        if (record == NULL) {
            cout << "Borrow record does not exist!\n";
            return;
        }

        if (record->data.return_status) {
            cout << "Book is already returned!\n";
            return;
        }

        book_node* b = books.search(
            books.root,
            record->data.book_id
        );

        user* u = users.search_user(record->data.user_id);

        if (b == NULL || u == NULL) {
            cout << "Book or user record is missing!\n";
            return;
        }

       
        b->data.available_copies++;

      
        u->borrowed_books--;

        
        record->data.return_status = true;

        cout << "Book returned successfully!\n";
    }

    void display_all_borrowrecords() {

        if (head == NULL) {
            cout << "No borrowing records found!\n";
            return;
        }

        borrow_node* temp = head;

        while (temp != NULL) {

            temp->data.display_record();

            temp = temp->next;
        }
    }

    void display_user_borrowings(int uid) {

        borrow_node* temp = head;
        bool found = false;

        while (temp != NULL) {

            if (temp->data.user_id == uid) {

                temp->data.display_record();
                found = true;
            }

            temp = temp->next;
        }

        if (!found) {
            cout << "No borrowing records for this user!\n";
        }
    }

    ~BorrowList() {

        borrow_node* temp = head;

        while (temp != NULL) {

            borrow_node* next = temp->next;

            delete temp;

            temp = next;
        }
    }
};


// reservation class
class reservation {
public:

    int reservation_id;
    int user_id;
    int book_id;

    reservation() {
        reservation_id = 0;
        user_id = 0;
        book_id = 0;
    }

    reservation(int r, int u, int b) {
        reservation_id = r;
        user_id = u;
        book_id = b;
    }

    void display() const {

        cout << "\nReservation ID: " << reservation_id;
        cout << "\nUser ID: " << user_id;
        cout << "\nBook ID: " << book_id;
        cout << "\n--------------------------\n";
    }
};

//circular reservation queue
class reservation_queue {
public:

    int front;
    int rear;
    int capacity;
    int count;

    reservation* arr;

    reservation_queue(int cap) {

        capacity = cap;
        front = 0;
        rear = -1;
        count = 0;

        arr = new reservation[capacity];
    }

    bool isEmpty() {
        return count == 0;
    }

    bool isFull() {
        return count == capacity;
    }

    void enqueue(int rid, int uid, int bid) {

        if (isFull()) {
            cout << "Reservation Queue is full!\n";
            return;
        }

        rear = (rear + 1) % capacity;

        arr[rear] = reservation(rid, uid, bid);

        count++;

        cout << "Reservation added successfully!\n";
    }

    void dequeue() {

        if (isEmpty()) {
            cout << "Reservation Queue is empty!\n";
            return;
        }

        cout << "Removed reservation:\n";

        arr[front].display();

        front = (front + 1) % capacity;

        count--;
    }

    void peek() {

        if (isEmpty()) {
            cout << "Queue is empty!\n";
            return;
        }

        arr[front].display();
    }

    void display_all() {

        if (isEmpty()) {
            cout << "Queue is empty!\n";
            return;
        }

        int i = front;

        for (int j = 0; j < count; j++) {

            arr[i].display();

            i = (i + 1) % capacity;
        }
    }

    ~reservation_queue() {
        delete[] arr;
    }
};


//operation class for undo
class operation {
public:

    string action;

    Book old_data;
    Book new_data;

    operation() {
        action = "";
    }

    operation(string a, Book oldBook, Book newBook) {

        action = a;
        old_data = oldBook;
        new_data = newBook;
    }
};


//stack undo

class undo_stack {
public:

    operation* arr;

    int top;
    int capacity;

    undo_stack(int cap) {

        capacity = cap;
        top = -1;

        arr = new operation[capacity];
    }

    bool isEmpty() {
        return top == -1;
    }

    bool isFull() {
        return top == capacity - 1;
    }

    void push(operation op) {

        if (isFull()) {
            cout << "Undo Stack is full!\n";
            return;
        }

        arr[++top] = op;
    }

    bool pop(operation& op) {

        if (isEmpty()) {
            cout << "No operation to undo!\n";
            return false;
        }

        op = arr[top--];

        return true;
    }

    void peek() {

        if (isEmpty()) {
            cout << "Stack is empty!\n";
            return;
        }

        cout << "Latest operation: "
             << arr[top].action << endl;
    }

    void display() {

        if (isEmpty()) {
            cout << "Undo history is empty!\n";
            return;
        }

        for (int i = top; i >= 0; i--) {

            cout << "Operation: "
                 << arr[i].action << endl;
        }
    }

    ~undo_stack() {
        delete[] arr;
    }
};


void undo_operation(
    undo_stack& st,
    BookTree& books
) {

    operation op;

    if (!st.pop(op)) {
        return;
    }

    if (op.action == "ADD") {

        books.root = books.delete_book(
            books.root,
            op.new_data.book_id
        );

        cout << "Book addition undone!\n";
    }

    else if (op.action == "DELETE") {

        books.root = books.insert(
            books.root,
            op.old_data
        );

        cout << "Book deletion undone!\n";
    }

    else if (op.action == "UPDATE") {

        books.root = books.delete_book(
            books.root,
            op.new_data.book_id
        );

        books.root = books.insert(
            books.root,
            op.old_data
        );

        cout << "Book update undone!\n";
    }
}


//advanced sorting algorithm
void merge(Book arr[], int left, int mid, int right) {

    int n1 = mid - left + 1;
    int n2 = right - mid;

    Book* l = new Book[n1];
    Book* r = new Book[n2];

    for (int i = 0; i < n1; i++) {
        l[i] = arr[left + i];
    }

    for (int j = 0; j < n2; j++) {
        r[j] = arr[mid + 1 + j];
    }

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {

        if (l[i].book_id <= r[j].book_id) {
            arr[k++] = l[i++];
        }

        else {
            arr[k++] = r[j++];
        }
    }

    while (i < n1) {
        arr[k++] = l[i++];
    }

    while (j < n2) {
        arr[k++] = r[j++];
    }

    delete[] l;
    delete[] r;
}

void merge_sort(Book arr[], int left, int right) {

    if (left >= right) return;

    int mid = left + (right - left) / 2;

    merge_sort(arr, left, mid);
    merge_sort(arr, mid + 1, right);

    merge(arr, left, mid, right);
}


// quick sorting
int partition(Book arr[], int low, int high) {

    int pivot = arr[high].year;

    int i = low - 1;

    for (int j = low; j < high; j++) {

        if (arr[j].year <= pivot) {

            i++;

            Book temp = arr[i];

            arr[i] = arr[j];

            arr[j] = temp;
        }
    }

    Book temp = arr[i + 1];

    arr[i + 1] = arr[high];

    arr[high] = temp;

    return i + 1;
}

void quick_sort(Book arr[], int low, int high) {

    if (low < high) {

        int pi = partition(arr, low, high);

        quick_sort(arr, low, pi - 1);

        quick_sort(arr, pi + 1, high);
    }
}


//radix sorting
int get_max(Book arr[], int n) {

    int maximum = arr[0].book_id;

    for (int i = 1; i < n; i++) {

        if (arr[i].book_id > maximum) {
            maximum = arr[i].book_id;
        }
    }

    return maximum;
}

void count_sort(Book arr[], int n, int exp) {

    Book* output = new Book[n];

    int count[10] = {0};

    for (int i = 0; i < n; i++) {

        int digit = (arr[i].book_id / exp) % 10;

        count[digit]++;
    }

    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }

    for (int i = n - 1; i >= 0; i--) {

        int digit = (arr[i].book_id / exp) % 10;

        output[count[digit] - 1] = arr[i];

        count[digit]--;
    }

    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }

    delete[] output;
}

void radix_sort(Book arr[], int n) {

    if (n <= 1) return;

    int maximum = get_max(arr, n);

    for (int exp = 1; maximum / exp > 0; exp *= 10) {

        count_sort(arr, n, exp);

        if (exp > maximum / 10) {
            break;
        }
    }
}


//report functions
void display_array(Book arr[], int n) {

    for (int i = 0; i < n; i++) {
        arr[i].display_book();
    }
}

void all_books_report(BookTree& books) {

    if (books.root == NULL) {
        cout << "No books available!\n";
        return;
    }

    cout << "\n========== ALL BOOKS REPORT ==========\n";

    books.display_inorder(books.root);

    cout << "Total Books: "
         << books.count_books(books.root) << endl;
}

void sorted_books_report(BookTree& books, int choice) {

    int n = books.count_books(books.root);

    if (n == 0) {
        cout << "No books available!\n";
        return;
    }

    Book* arr = new Book[n];

    int index = 0;

    books.store_books(books.root, arr, index);

    if (choice == 1) {
        merge_sort(arr, 0, n - 1);
        cout << "\nSorted by Book ID (Merge Sort)\n";
    }

    else if (choice == 2) {
        quick_sort(arr, 0, n - 1);
        cout << "\nSorted by Publication Year (Quick Sort)\n";
    }

    else if (choice == 3) {

        for (int i = 0; i < n; i++) {
            if (arr[i].book_id < 0) {
                cout << "Radix Sort requires non-negative IDs!\n";
                delete[] arr;
                return;
            }
        }

        radix_sort(arr, n);

        cout << "\nSorted by Book ID (Radix Sort)\n";
    }

    display_array(arr, n);

    delete[] arr;
}

// main func
int main() {

    BookTree books;

    hash_table users;

    BorrowList borrowing;

    reservation_queue reservations(100);

    undo_stack undo(100);

    int reservation_id = 1;

    int choice;

    do {

        cout << "\n\n";
        cout << "====================================\n";
        cout << "     LIBRARY MANAGEMENT SYSTEM\n";
        cout << "====================================\n";

        cout << "\n--- BOOK MANAGEMENT ---\n";
        cout << "1. Add Book\n";
        cout << "2. Search Book by ID\n";
        cout << "3. Delete Book\n";
        cout << "4. Update Book\n";
        cout << "5. Search Book by Title\n";
        cout << "6. Search Book by Author\n";
        cout << "7. All Books Report\n";

        cout << "\n--- USER MANAGEMENT ---\n";
        cout << "8. Register User\n";
        cout << "9. Search User\n";
        cout << "10. Delete User\n";
        cout << "11. Display All Users\n";

        cout << "\n--- BORROW MANAGEMENT ---\n";
        cout << "12. Borrow Book\n";
        cout << "13. Return Book\n";
        cout << "14. Display All Borrow Records\n";
        cout << "15. Display User Borrowings\n";

        cout << "\n--- RESERVATION MANAGEMENT ---\n";
        cout << "16. Add Reservation\n";
        cout << "17. Process Reservation\n";
        cout << "18. View Next Reservation\n";
        cout << "19. Display Reservations\n";

        cout << "\n--- SORTING REPORTS ---\n";
        cout << "20. Merge Sort (Book ID)\n";
        cout << "21. Quick Sort (Year)\n";
        cout << "22. Radix Sort (Book ID)\n";

        cout << "\n--- UNDO MANAGEMENT ---\n";
        cout << "23. Undo Last Book Operation\n";
        cout << "24. View Undo History\n";

        cout << "\n0. Exit\n";

        cout << "\nEnter your choice: ";

        cin >> choice;

        switch (choice) {

            //add book
            case 1: {

                Book b;

                cout << "Enter Book ID: ";
                cin >> b.book_id;

                if (b.book_id < 0 ||
                    books.search(books.root, b.book_id) != NULL) {

                    cout << "Invalid or duplicate Book ID!\n";
                    break;
                }

                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                cout << "Enter Title: ";
                getline(cin, b.title);

                cout << "Enter Author: ";
                getline(cin, b.author);

                cout << "Enter Publication Year: ";
                cin >> b.year;

                cout << "Enter Total Copies: ";
                cin >> b.total_copies;

                if (b.total_copies <= 0) {
                    cout << "Copies must be greater than zero!\n";
                    break;
                }

                b.available_copies = b.total_copies;

                books.root = books.insert(books.root, b);

                undo.push(operation("ADD", Book(), b));

                cout << "Book added successfully!\n";

                break;
            }

            //search
            case 2: {

                int id;

                cout << "Enter Book ID: ";
                cin >> id;

                book_node* found = books.search(books.root, id);

                if (found == NULL) {
                    cout << "Book not found!\n";
                }

                else {
                    found->data.display_book();
                }

                break;
            }

           //delete book
            case 3: {

                int id;

                cout << "Enter Book ID: ";
                cin >> id;

                book_node* found = books.search(books.root, id);

                if (found == NULL) {
                    cout << "Book not found!\n";
                    break;
                }

                if (borrowing.has_active_book(id)) {
                    cout << "Cannot delete a book currently borrowed!\n";
                    break;
                }

                Book oldBook = found->data;

                books.root = books.delete_book(books.root, id);

                undo.push(operation("DELETE", oldBook, Book()));

                cout << "Book deleted successfully!\n";

                break;
            }

            //update book
            case 4: {

                int id;

                cout << "Enter Book ID: ";
                cin >> id;

                Book oldBook, newBook;

                books.update_book(id, oldBook, newBook);

                if (oldBook.book_id != 0 &&
                    newBook.book_id != 0 &&
                    (oldBook.title != newBook.title ||
                     oldBook.author != newBook.author ||
                     oldBook.year != newBook.year ||
                     oldBook.total_copies != newBook.total_copies)) {

                    undo.push(operation("UPDATE", oldBook, newBook));
                }

                break;
            }

            //search book by title
            case 5: {

                string title;

                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                cout << "Enter Title: ";
                getline(cin, title);

                books.search_by_title(books.root, title);

                break;
            }

            //searcg book by author
            case 6: {

                string author;

                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                cout << "Enter Author: ";
                getline(cin, author);

                books.search_by_author(books.root, author);

                break;
            }

            // all books reports
            case 7: {

                all_books_report(books);

                break;
            }

           //register user
            case 8: {

                int id;

                string name, email, phone;

                cout << "Enter User ID: ";
                cin >> id;

                if (id < 0) {
                    cout << "Invalid User ID!\n";
                    break;
                }

                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                cout << "Enter Name: ";
                getline(cin, name);

                cout << "Enter Email: ";
                getline(cin, email);

                cout << "Enter Phone Number: ";
                getline(cin, phone);

                user u(id, name, email, phone, 0);

                users.insert_user(u);

                break;
            }

            //search user
            case 9: {

                int id;

                cout << "Enter User ID: ";
                cin >> id;

                user* found = users.search_user(id);

                if (found == NULL) {
                    cout << "User not found!\n";
                }

                else {
                    found->display_user();
                }

                break;
            }

            //delete user
            case 10: {

                int id;

                cout << "Enter User ID: ";
                cin >> id;

                users.delete_user(id);

                break;
            }

            //display user details
            case 11: {

                users.display_allusers();

                break;
            }

            //borrow book
            case 12: {

                borrowing.borrow_book(books, users);

                break;
            }

            //retun book
            case 13: {

                borrowing.return_book(books, users);

                break;
            }

            //borrow record
            case 14: {

                borrowing.display_all_borrowrecords();

                break;
            }

            //user borrowing
            case 15: {

                int id;

                cout << "Enter User ID: ";
                cin >> id;

                borrowing.display_user_borrowings(id);

                break;
            }

           // add reseervation
            case 16: {

                int uid, bid;

                cout << "Enter User ID: ";
                cin >> uid;

                cout << "Enter Book ID: ";
                cin >> bid;

                user* u = users.search_user(uid);

                book_node* b = books.search(books.root, bid);

                if (u == NULL || b == NULL) {
                    cout << "Invalid user or book!\n";
                    break;
                }

                if (b->data.available_copies > 0) {
                    cout << "Book is currently available. You can borrow it directly!\n";
                    break;
                }

                reservations.enqueue(
                    reservation_id++,
                    uid,
                    bid
                );

                break;
            }

            //reservation processing
            case 17: {

                reservations.dequeue();

                break;
            }

           //peek reservation
            case 18: {

                reservations.peek();

                break;
            }

            //display reservation details
            case 19: {

                reservations.display_all();

                break;
            }

            //merge sort
            case 20: {

                sorted_books_report(books, 1);

                break;
            }

           //quick sort
            case 21: {

                sorted_books_report(books, 2);

                break;
            }

            //radix sort
            case 22: {

                sorted_books_report(books, 3);

                break;
            }

            //undo
            case 23: {

                undo_operation(undo, books);

                break;
            }

           //display undo history detail 
            case 24: {

                undo.display();

                break;
            }

            case 0: {

                cout << "Exiting Library Management System...\n";

                break;
            }

            default: {

                cout << "Invalid choice!\n";

                break;
            }
        }

    } while (choice != 0);

    return 0;
}

