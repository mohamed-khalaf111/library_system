#include <iostream>
#include<algorithm>
#include<assert.h>

using namespace std;

const int max_books=10;
const int max_users=10;


struct books{
    int id,quantity,total_borrowed;
    string name;

    books(){
        id=-1;
        name="";
        quantity=0;
        total_borrowed=0;
    }

    void read(){
        cout<<"Enter books info : id , name and quantity \n";
        cin>>id>>name>>quantity;
        total_borrowed=0;
    }

   bool has_perfix(string perfix){
       if(name.size()<perfix.size())
       {
           return false;
       }
       for(int i=0;i<(int)perfix.size();i++)
       {
           if(perfix[i]!=name[i])
           {
               return false;
           }
       }
       return true;
   }
   bool borrow(int user_id){
       if(quantity-total_borrowed==0)
       {
           return false;
       }
       ++total_borrowed;
       return true;
   }
   void return_copy(){
       assert(total_borrowed>0);
       --total_borrowed;
   }
   void print(){
       cout << "id = " << id << " name = " << name << " total_quantity "
				<< quantity << " total_borrowed " << total_borrowed
				<< "\n";
   }
};


bool order_book_by_id(books &a,books &b)
{
    return a.id < b.id;
}

bool order_book_by_name(books &a,books &b)
{
    return a.name < b.name;
}

struct users{
    int id;
    string name;
    int books_borrowed_ids[max_books];
    int len;

    users(){
        id=-1;
        name="";
        len=0;
    }

    void read(){
        cout<<"Enter user info : id and name : \n";
        cin>>id>>name;
    }

    void borrow(int book_id){
        books_borrowed_ids[len]=book_id;
        ++len;
    }

    void return_copy(int book_id){
        bool removed=false;
        for(int i=0;i<len;i++)
        {
            if(books_borrowed_ids[i]==book_id)
            {
                // remove book id from list of ids borrowed
                for(int j=i+1;j<len;j++)
                {
                    books_borrowed_ids[j-1]=books_borrowed_ids[j];
                }
                --len;
                removed=true;
                break;
            }
        }
        if(removed==0)
            cout << "User " << name << " never borrowed book id " << book_id
					<< "\n";
    }
    void print(){
        sort(books_borrowed_ids,books_borrowed_ids+len);

        cout << "user " << name << " id " << id << " borrowed books ids: ";
		for (int i = 0; i < len; ++i)
			cout << books_borrowed_ids[i] << " ";
		cout << "\n";
    }
    bool is_borrowed(int book_id){
        for(int i=0;i<len;i++)
        {
            if(books_borrowed_ids[i]==book_id)
                return true;
        }
        return false;
    }
};

struct library_system{
    int added_books;
    int added_users;
    books book[max_books];
    users user[max_users];

    library_system(){
        added_books=added_users=0;
    }

    void run() {
		while (true) {
			int choice = menu();

			if (choice == 1)
				add_book();
			else if (choice == 2)
				search_books_by_prefix();
			else if (choice == 3)
				print_who_borrowed_book_by_name();
			else if (choice == 4)
				print_library_by_id();
			else if (choice == 5)
				print_library_by_name();
			else if (choice == 6)
				add_user();
			else if (choice == 7)
				user_borrow_book();
			else if (choice == 8)
				user_return_book();
			else if (choice == 9)
				print_users();
			else
				break;
		}
	}

	int menu() {
		int choice = -1;
		while (choice == -1) {
				cout << "\nLibrary Menu;\n";
				cout << "1) add_book\n";
				cout << "2) search_books_by_prefix\n";
				cout << "3) print_who_borrowed_book_by_name\n";
				cout << "4) print_library_by_id\n";
				cout << "5) print_library_by_name\n";
				cout << "6) add_user\n";
				cout << "7) user_borrow_book\n";
				cout << "8) user_return_book\n";
				cout << "9) print_users\n";
				cout << "10) Exit\n";
                cout << "\nEnter your menu choice [1 - 10]: ";
                cin >> choice;
			if (!(1 <= choice && choice <= 10)) {
				cout << "Invalid choice. Try again\n";
				choice = -1;	// to make loop keep working
			}
			}

			return choice;

		}



	void add_book(){
	    book[added_books++].read();
	}

	void search_books_by_prefix(){
	    string perfix;
	    cout<<"Enter perfix of book name : \n";
	    cin>>perfix;
	    int cnt=0;
	    for(int i=0 ; i<added_books ; i++)
	    {
	        if(book[i].has_perfix(perfix))
            {
                cout<<book[i].name<<endl;
                ++cnt;
            }
	    }
	    if(!cnt)
            cout<<"no book with such perfix \n";
	}
	void add_user(){
	    user[added_users++].read();
	}

	int find_user_pos_by_name(string name_of_user){
	    for(int i=0;i<added_users;i++)
	    {
	        if(user[i].name==name_of_user)
                return i;
	    }
	    return -1;
	}
	int find_book_pos_by_name(string book_name){
	    for(int i=0;i<added_books;i++)
        {
            if(book_name==book[i].name)
                return (i);
        }
        return -1;
	}

	bool read_names_for_user_and_book(int &pos_of_user,int &pos_of_book){
	    string name_of_user;
	    string name_of_book;
	    cout<<"Enter name of user and name of book :\n";
	    cin>>name_of_user>>name_of_book;

        pos_of_user = find_user_pos_by_name(name_of_user);
        if(pos_of_user==-1)
        {
            cout << "Invalid user name. Try again\n";
            return false;
        }
        pos_of_book = find_book_pos_by_name(name_of_book);
        if(pos_of_book==-1)
        {
            cout << "Invalid book name. Try again\n";
            return false;
        }
        return true;
	}

	void  user_borrow_book(){
	    int pos_of_user;
	    int pos_of_book;
	    if(!(read_names_for_user_and_book(pos_of_user,pos_of_book)))
            return;

        int user_id=user[pos_of_user].id;
        int book_id=book[pos_of_book].id;

        if(!(book[pos_of_book].borrow(user_id)))
            cout << "No more copies available right now\n";
        else
            user[pos_of_user].borrow(book_id);
	}

	void user_return_book(){
	    int pos_of_user;
	    int pos_of_book;
	    if((read_names_for_user_and_book(pos_of_user,pos_of_book))==0)
            return;

        int book_id=book[pos_of_book].id;
        book[pos_of_book].return_copy();
        user[pos_of_user].return_copy(book_id);
	}

	void print_library_by_id(){
	    sort(book,book+added_books,order_book_by_id);
	    cout << "\n";
		for (int i = 0; i < added_books; ++i)
			book[i].print();
	}

	void print_library_by_name(){
	    sort(book,book+added_books,order_book_by_name);
	    cout << "\n";
		for (int i = 0; i < added_books; ++i)
			book[i].print();
	}

	void print_users(){
	    cout << "\n";
		for (int i = 0; i < added_users; ++i)
			user[i].print();
	}

	void print_who_borrowed_book_by_name(){
	    string name_book;
	    cout<<"Enter name of book \n";
	    cin>>name_book;
	    int book_pos=find_book_pos_by_name(name_book);
	    if(book_pos==-1)
        {
            cout << "Invalid book name.\n";
			return;
        }
        int book_id=book[book_pos].id;
        if(book[book_pos].total_borrowed==0)
        {
            cout << "No borrowed copies\n";
			return;
        }
        for (int i = 0; i < added_users; ++i) {
			if (user[i].is_borrowed(book_id))
				cout << user[i].name << "\n";
		}
	}
};

int main()
{
    library_system library;
    library.run();

    return 0;
}
