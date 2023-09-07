#include<iostream>
#include<fstream>
#include<string>

using namespace std;


struct Node
{
	int data = 0;
	int bf = 0;
	Node* left = NULL;
	Node* right = NULL;
};

class AVL
{
private:
	
	bool stop = false;

	void add(int value, Node* current)  // inside of the class 
	{
		if (!root)  
		{
			root = new Node;
			root->data = value;
		}if (value < current->data)
		{
			if (!current->left)     // move left
			{
				current->left = new Node;
				current = current->left;
				current->left->data = value;

			}
			else {
				add(value, current->left);
			}

		}
		else {
			if (!current->right)     // move right
			{
				current->right = new Node;

				current->right->data = value;

			}
			else {
				add(value, current->right);
			}
		}

	}
	void Save(Node* trav, ofstream& offile)  // saves the data
	{
		if (trav)
		{
			offile << trav->data << ' ';
			if (trav->left != NULL)
			{
				Save(trav->left, offile);
			}if (trav->right != NULL)
			{
				Save(trav->right, offile);
			}
		}
	}
	bool search(Node* current, int val)  
	{

		if (current->data == NULL)
		{
			return false;
		}
		else if (current->data == val)
		{
			return true;
		}
		else if (current->data > val)
		{

			search(current->left, val);
		}
		else                            
		{
			search(current->right, val);
		}


	}

	void Inorder(Node* current)
	{

		if (current == NULL)
		{
			return;
		}
		else
		{
			Inorder(current->left);
			cout << current->data << " ";

			Inorder(current->right);
		}
	}
	void Delete(Node* trav) //private
	{
		if (trav != NULL)
		{
			Delete(trav->left);
			Delete(trav->right);
			delete trav;
		}
	}

	

	void Add_AVL(Node*& current, int val)
	{
		if (!current)
		{
			current = new Node;
			current->data = val;
		}
		else
		{
			if (current->data > val)
			{
				
				Add_AVL(current->left, val);

				if (stop == false)     // comparing the bf, if bf if -1,0,1 that it is valid.
				{
					if (current->bf == 0)
					{
						current->bf = -1;
					}
					else if (current->bf == 1)
					{
						current->bf = 0;
						stop = true;
					}
					else if (current->bf == -1)
					{
						if (current->left->bf == -1)
						{
							SingleRotateRight(current);
						}
						else
						{
							doubleRotateleftRight(current);
						}
					}
				}

			}
			else
			{
				Add_AVL(current->right, val); 
				if (stop == false)
				{
					if (current->bf == 0)
					{
						current->bf = 1;
					}
					else if (current->bf == -1)
					{
						current->bf = 0;
						stop = true;
					}
					else if (current->bf == 1)
					{
						if (current->right->bf == 1)
						{
							SingleRotateleft(current);
						}
						else
						{
							DoubleRotaterightleft(current);
						}
					}
				}


			}
		}
	}
	void SingleRotateRight(Node*& current)
	{
		Node* temp = current->left;
		current->left = temp->right;
		temp->right = current;
		current = temp;
		current->bf = 0;
		current->right->bf = 0;
		stop = true;
	}
	void doubleRotateleftRight(Node*& current)
	{
		Node* temp = current->left;
		current->left = temp->right->right;
		temp->right->right = current;
		current = temp->right;
		temp->right = temp->right->left;
		
		current->left = temp;
		stop = true;
		if (current->bf == 0)
		{
			current->bf = 0;
			current->left = 0;
			current->right = 0;
		}

		if (current->bf == -1)
		{
			current->right->bf = 1;
			current->left->bf = 0;
			current->bf = 0;
		}

		if (current->bf == 1)
		{
			current->left->bf = -1;
			current->bf = 0;
			current->right->bf = 0;
		}


	}
	void SingleRotateleft(Node*& current)
	{
		Node* temp = current->right;
		current->right = temp->left;
		temp->left = current;
		current = temp;
		current->bf = 0;
		current->left->bf = 0;
		stop = true;
	}

	void DoubleRotaterightleft(Node*& current)
	{
		Node* temp = current->right;
		current->right = temp->left->left;
		temp->left->left = current;
		current = temp->left;
		temp->left = temp->left->right;
		
		current->right = temp;
		stop = true;
		if (current->bf == 0)
		{
			current->bf = 0;
			current->left->bf = 0;
			current->right->bf = 0;
		}

		if (current->bf == -1)
		{
			current->right->bf = 1;
			current->left->bf = 0;
			current->bf = 0;
		}

		if (current->bf == 1)
		{
			current->left->bf = -1;
			current->bf = 0;
			current->right->bf = 0;
		}

	}

public:
	Node* root = NULL;
	

	void ADD(int value)
	{
		Add_AVL(root, value);
	}

	void Delete()
	{
		Delete(root);
		root = NULL;
	}

	void Save(string atfile)
	{

		ofstream tofile;
		tofile.open(atfile, ios::out);
		Save(root, tofile);
		tofile.close();

	}

	void Load(string userfile)
	{
		int temp;
		Delete();

		ifstream infile;
		infile.open(userfile, ios::in);
		while (!infile.eof())
		{
			infile >> temp;
			ADD(temp);
		}

	}

	void Inorder()
	{
		Inorder(root);
	}


	bool Search(int val)
	{
		if (search(root, val) == true)
		{
			cout << "Number exits" << endl;
			return true;
		}
		else
		{
			cout << "Number does not exists" << endl;
			return false;
		}

	}


	

};
void menu()
{

	cout << "1.)Add numbers: " << endl;
	cout << "2.)Search numbers: " << endl;
	cout << "3.)Clear: " << endl;
	cout << "4.)In order: " << endl;
	cout << "5.)Save: " << endl;
	cout << "6.)Load: " << endl;
	cout << "Press any other key to exit: " << endl;

}

int main()
{
	AVL avl;
	menu();


	char s;
	int enter;
	string addfile;
	string file;

	cin >> s;



	while (s != '7')
	{

		switch (s)
		{

		case '1':
			cout << "Enter a value: " << endl;
			cin >> enter;
			avl.ADD(enter);

			break;
		case '2':
			cout << "Search value" << endl;
			int search;
			cin >> search;
			avl.Search(search);
			break;
		case '3':
			avl.Delete();
			break;
		case '4':
			avl.Inorder();
			cout << endl;
			break;
		case '5':
			cout << "Name the file, and add .txt after: " << endl;
			
			cin >> addfile;
			avl.Save(addfile);
			break;
		case '6':
			cout << "Enter your file name: " << endl;
			
			cin >> file;
			avl.Load(file);
			break;

		default:
			exit(0);
			break;
		}


		menu();
		cin >> s;

	}
	


	return 0;
}