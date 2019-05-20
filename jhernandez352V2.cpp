#include<iostream>
#include<vector>
using namespace std;
//Node structure is a link between lists.
struct node
{
	int data;
	node *next;
};
//List class implements the node class to make linked lists
class List{
private:
	node *head,*tail;
public:
	//List keeps track of head and tail just incase you want to add from front and back.
	List(){
		head = NULL;
		tail = NULL;
	}
	//Creates a list with its starting node of data a.
	List(int a){
		node *temp = new node;
		temp ->data = a;
		head = temp;
		tail = temp;
	}
	//Checks if list is empty. This is used to check before we insert new elements.
	bool checkHeadNull(){
		if(this->head = NULL){
			return 1;
		}
		else{
			return 0;
		}
	}
	//Insert function.
	void insert(int a){
		node *temp = new node;
		temp -> data = a;
		temp -> next = NULL;
		//If empty list, we add a prand new node as head.
		if(this->head == NULL){
			this->head = temp;
			this->tail = temp;
		}
		//Else link it to the front of the list.
		else{
			temp->next = this->head;
			this->head = temp;
		}
	}
	//Print func. Itterates till we find the end of list and outputs every element.
	void print(){
		if(this->head != NULL){
			node *temp = this->head;
			while(temp != NULL){
				cout << temp ->data << "->";
				temp = temp->next;
			}
		}
	}
	//Deletion func.
	void del(int a){
		//Keeps track of a deletion. We only want to delete the first found instance.
		bool deleted = false;
		node *temp = this->head;
		node *prev = this->head;
		while(temp != NULL && !deleted){
			if(temp->data == a){
				//If its at the head, we gotta do a little extra.
				if(temp == this->head){
					this->head = temp->next;
					delete[] temp;
					deleted = true;
					cout << a << ":DELETED;" << endl;
					break;
				}
				//We just connect the previous and next node together.
				else{
					prev->next = temp->next;
					delete[] temp;
					deleted = true;
					cout << a << ":DELETED;" << endl;
					break;
				}
			}
			prev = temp;
			temp = temp->next;
		}
		if(!deleted){
			cout << a << ":DELETE_FAILED;" << endl;
		}
	}
	//Search func. We return the index i of the instance.
	int search (int a){
		bool found = false;
		node *temp = this->head;
		int count = 0;
		while(temp != NULL){
			if(temp->data == a){
				return count;
			}
			count++;
			temp = temp->next;
		}
		if(!found){
			return -1;
		}
	}
};
class hashTable{
//Class variables, list of lists and size of table.
	int size;
	vector <List> hash;
	//public modifiers and constructors
	public:
	//Constructor function.
	hashTable(int mod){
		size = mod;
		for(int i = 0; i < size; i++){
			List list;
			hash.push_back(list);
		}
	}
	//Mod fuction that follows the convetion h(k) = k mod m.
	int mod(int k){
		return k%size;
	}
	//Insert key fucntion.
	void insertKey(int k){
		int index = mod(k);
		hash[index].insert(k);
	}
	//Delete key function.
	void deleteKey(int k){
		int index = mod(k);
		hash[index].del(k);
	}
	//Searching function.
	void searchKey(int k){
		int index = mod(k);
		int search = hash[index].search(k);
		if(search == -1)
			cout << k << ":NOT_FOUND;" << endl;
		else
			cout << k << ":FOUND_AT" << index << "," << search << ";" << endl;
	}
	//Display table fuction.
	void output(){
		for(int i = 0; i < size; i++){
			cout << i << ":";
			hash[i].print(); 
			cout << ";" << endl;
		}
	}
	//Gotta follow c++ convetion, delete any pointers.
	~hashTable(){
	}
};
int main(){
	int size;
	//Collect size.
	cin >> size;
	//These are variables to store inputs.
	char func;
	int key = 0;
	//Initialized table.
	hashTable table(size);
	//While loop to continue fuction until e is entered in.
	while(func != 'e'){
		//collect the function character.
		cin >> func;
		switch(func){
			//i(key): inserts elements.
			case 'i':
				cin >> key;
				table.insertKey(key);
				//cout << "Insetion of " << key << ":" << endl;
				//table.output();
				break;
			//d(key): deletes elements.
			case 'd':
				cin >> key;
				table.deleteKey(key);
				//cout << "Deletion of " << key << ":" << endl;
				//table.output();
				break;
			//s(key): searches for elements.
			case 's':
				cin >> key;
				table.searchKey(key);
				//cout << "Searching of " << key << ":" << endl;
				//table.output();
				break;
			case 'o':
			//o: display table
				//cout << "Printing of " << key << ":" << endl;
				table.output();
				break;
			//e: finish program with exit code 0.
			case 'e':
				return 0;
		}
	}
}
