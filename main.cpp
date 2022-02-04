#include <iostream>
#include<conio.h>
#include<stdlib.h>
#include<fstream>
#include<stdio.h>
#include<string.h>
#include<process.h>
#include<time.h>
using namespace std;

class Stock
{
	int id;
	string name;
	float rate;

	public:
        int stock;
		void enter();
		void display()
		{
			cout<<id<<"\t\t"<<name<<"\t\t"<<rate<<"\t\t"<<stock<<endl;
		}
		int returnid()
		{
			return id;
		}
		string returnname()
		{
			return name;
		}
		float returnrate()
		{
			return rate;
		}

		/*void editstock(int qty,int no)
		{
			if(no==1)
				stock = stock + qty;
			else
				stock = stock - qty;

		}*/
}s;

void Stock::enter()
		{

			cout<<endl;
			cout<<"ID: ";
			cin>>id;
			cout<<"Name: ";
			cin>>name;
			cout<<"Rate: ";
			cin>>rate;
			cout<<"Quantity: ";
			cin>>stock;
		}
class item
{
	int id,qty;
	string name;   //name,rate from stock are copied to the item's name and rate when id matches
	float amount,rate;
	public:

		void enter();
		void display()
		{

			amount=qty*rate;
			cout<<id<<"\t\t"<<name<<"\t\t"<<rate<<"\t\t"<<qty<<"\t\t"<<amount<<endl;
		}
		int returnid()
		{
			return id;
		}
		float returnamount()
		{
			return amount;
		}
		string returnname()
		{
			return name;
		}
		float returnrate()
		{
			return rate;
		}
		int returnqty()
		{
			return qty;
		}
		void enterqty(int);
		void transfer();


}it;

void item::enter()
{
    cout<<endl;
    cout<<"\nID: ";
    cin>>id;
    cout<<"Quantity: ";
    cin>>qty;
}

void item::enterqty(int id)
{
			cin>>qty;
			ifstream f("masterfile.dat",ios::binary);
			ofstream f2("temp.dat",ios::binary);

			while(f.read((char*)&s,sizeof(s)))
			{
				if(id==s.returnid())
				{
					if(qty>s.stock)
					{
						cout<<"\nSorry! Stock is not sufficient. Enter a lesser quantity = ";
						cin>>qty;
					}
					while(qty>s.stock)
					{
						cout<<"\nSorry! Stock is not sufficient. Enter a lesser quantity = ";
						cin>>qty;
					}
					s.stock = s.stock - qty;
				 }
				 f2.write((char*)&s,sizeof(s));
		}
		remove("masterfile.dat");
        rename("temp.dat","masterfile.dat");
}


void item::transfer()
{
	ifstream f2("masterfile.dat",ios::binary);
	ofstream f("temp.dat",ios::binary);

			int found=0;

			while(f2.read((char*)&s,sizeof(s)))
			{
				if(id==s.returnid())
				{
					found=1;
					while(qty>s.stock)
					{
						cout<<"\nSorry! Stock is not sufficient. Enter a lesser quantity = ";
						cin>>qty;
					}
					s.stock = s.stock - qty;
					//reduce the stock by an amount of qty
					cout<<"\nItem successfully added to purchase list!\n";
					name = s.returnname();
					rate=s.returnrate();
					cout<<"\nName: "<<name<<endl;
					cout<<"Rate = "<<rate<<endl;

				}
				f.write((char*)&s,sizeof(s));


			}
			f2.close();
			f.close();
			remove("masterfile.dat");
			rename("temp.dat","masterfile.dat");
			if(found==0)
				cout<<"\nItem does not exist!! Enter again!\n";
			while(found==0)
			{
				cout<<endl;
				cout<<"\nID: ";
				cin>>id;

				cout<<"Quantity: ";
				cin>>qty;

				ifstream f2("masterfile.dat",ios::binary);
				ofstream f("temp.dat",ios::binary);

				while(f2.read((char*)&s,sizeof(s)))
				{
					if(id==s.returnid())
					{
						found=1;
						if(qty>s.stock)
						{
							cout<<"\nSorry! Stock is not sufficient. Enter a lesser quantity = ";
							cin>>qty;
						}
						while(qty>s.stock)
						{
							cout<<"\nSorry! Stock is not sufficient. Enter a lesser quantity = ";
							cin>>qty;
						}
						s.stock = s.stock - qty;
						f.write((char*)&s,sizeof(s));
						//reduce the stock by an amount of qty

						cout<<"\nItem successfully added to purchase list!\n";
						name = s.returnname();
						rate=s.returnrate();
						cout<<"\nName: "<<name<<endl;
						cout<<"Rate = "<<rate<<endl;
						continue;

					}
					f.write((char*)&s,sizeof(s));
				}
				f2.close();
				f.close();
				if(found==0)
					cout<<"\nItem does not exist!! Enter again!\n";
			}
}


void create_stock()
{
	system("cls");

	int n;
	cout<<"Enter the number of products to add to stock = ";
	cin>>n;
	ofstream f;
	f.open("masterfile.dat",ios::out|ios::binary);
	cout<<"\nEnter the details"<<":"<<endl;
	for(int i=1;i<=n;i++)
	{

		s.enter();
		f.write((char*)&s,sizeof(s));
	}
	cout<<"\nProduct(s) successfully added to stock!!\n";
	f.close();
	getch();
}
void append_stock()
{
	system("cls");

	int n;
	cout<<"Enter the number of products to add to stock = ";
	cin>>n;
	ofstream f;
	f.open("masterfile.dat",ios::app|ios::binary);
	cout<<"\nEnter the details"<<":"<<endl;
	for(int i=1;i<=n;i++)
	{

		s.enter();
		f.write((char*)&s,sizeof(s));
	}
	cout<<"\nProduct(s) successfully added to stock!!\n";
	f.close();
	getch();
}
void display_stock()
{
	system("cls");

	ifstream f;
	cout<<"\t\t\t\tStock\n";
	f.open("masterfile.dat",ios::binary);
	cout<<endl;
	cout<<"________________________________________________________________________________\n";
	cout<<"ID\t\tName\t\tRate\t\tQuantity"<<endl;
	cout<<"________________________________________________________________________________\n";
	while(f.read((char*)&s,sizeof(s)))
		s.display();
	f.close();
	getch();
}
void search_stock()
{
	system("cls");
	int id, found=0;
	cout<<"Enter the ID of the product to search = ";
	cin>>id;

	ifstream f("masterfile.dat",ios::binary);
	while(f.read((char*)&s,sizeof(s)))
		if(id==s.returnid())
		{
			found=1;
			cout<<"\nProduct found!!\n\n";
			cout<<"Details:\n";
			cout<<"ID = "<<s.returnid()<<endl;
			cout<<"Name = "<<s.returnname()<<endl;
			cout<<"Rate = "<<s.returnrate()<<endl;
			cout<<"Quantity = "<<s.stock<<endl;
		}
	if(found==0)
		cout<<"\nProduct not found!!\n";
	f.close();
	getch();
}
void modify_stock()
{
	system("cls");
	fstream f1,f2;
	f1.open("masterfile.dat",ios::in|ios::binary);
	f2.open("temp.dat",ios::out|ios::binary);

	int id,found=0;
	cout<<"\nEnter the ID of the product to modify = ";
	cin>>id;
	while(f1.read((char*)&s,sizeof(s)))
	{
		if(s.returnid()==id)
		{
			found=1;
			cout<<"\nEnter the new details:\n";
			s.enter();
			cout<<"\nDetails modified!!\n";

		}
		f2.write((char*)&s,sizeof(s));
	}
	if(found==0)
		cout<<"\nProduct not found!!\n";
	f1.close();f2.close();
	remove("masterfile.dat");
	rename("temp.dat","masterfile.dat");
	getch();
}
void delete_stock()
{
	system("cls");
	fstream f1,f2;
	f1.open("masterfile.dat",ios::in|ios::binary);
	f2.open("temp.dat",ios::out|ios::binary);

	int id,found=0;
	cout<<"\nEnter the ID of the product to delete = ";
	cin>>id;
	while(f1.read((char*)&s,sizeof(s)))
	{
		if(s.returnid()==id)
		{
			found=1;
			cout<<"\nProduct deleted successfully!\n";
			continue;
		}
		f2.write((char*)&s,sizeof(s));
	}
	if(found==0)
		cout<<"\nProduct not found!!\n";
	f1.close();f2.close();
	remove("masterfile.dat");
	rename("temp.dat","masterfile.dat");
	getch();
}


void create_list()
{
	system("cls");
	ifstream t("masterfile.dat",ios::binary);
	t.seekg(0,ios::end);
	if(t.tellg()==0)
		cout<<"Can't purchase. Stock is empty!!";
	else
	{
	ofstream f("list.dat",ios::binary);
	int n;
	cout<<"\t\t\tAvailable Stock\n";
	display_stock();
	cout<<"\n\n\t\t\t\tPlace your order\n";
	cout<<"\nEnter the number of items to purchase = ";
	cin>>n;
	cout<<"\nEnter the ID and quantity of the item(s)"<<":\n";
	for(int i=1;i<=n;i++)
	{

		it.enter();
		it.transfer();
		f.write((char*)&it,sizeof(it));
	}
	}

	getch();
}
void append_list()
{
	system("cls");
	ifstream t("masterfile.dat",ios::binary);
	t.seekg(0,ios::end);
	if(t.tellg()==0)
		cout<<"Can't purchase. Stock is empty!!";
	else
	{
	ofstream f("list.dat",ios::binary|ios::app);
	int n;
	cout<<"\t\t\tAvailable Stock\n";
	display_stock();
	cout<<"\n\n\t\t\tPlace your order\n";
	cout<<"\nEnter the number of items to add to list = ";
	cin>>n;
	cout<<"\nEnter the ID and quantity of the item(s)"<<":\n";
	for(int i=1;i<=n;i++)
	{

		it.enter();
		it.transfer();
		f.write((char*)&it,sizeof(it));
	}
	}
	getch();
}
void modify_list()
{
	system("cls");
	fstream f1,f2;
	f1.open("list.dat",ios::in|ios::binary);
	f2.open("temp.dat",ios::out|ios::binary);

	int id,found=0;
	cout<<"\nEnter the ID of the item whose quantity is to be modified = ";
	cin>>id;
	while(f1.read((char*)&it,sizeof(it)))
	{
		if(it.returnid()==id)
		{
		    s.stock = s.stock + it.returnqty();
			cout<<"Enter the new quantity:\n";

			it.enterqty(id);
			cout<<"\nquantity modified!\n";
			found=1;
		}
		f2.write((char*)&it,sizeof(it));
	}
	if(found==0)
		cout<<"\nItem not found!!\n";
	f1.close();f2.close();
	remove("list.dat");
	rename("temp.dat","list.dat");

	getch();
}
void delete_list()
{
	system("cls");
	fstream f1,f2;
	f1.open("list.dat",ios::in|ios::binary);
	f2.open("temp.dat",ios::out|ios::binary);


	int id,found=0;
	cout<<"\nEnter the ID of the item to delete = ";
	cin>>id;
	while(f1.read((char*)&it,sizeof(it)))
	{
		if(it.returnid()==id)
		{
			found=1;
			cout<<"\nItem deleted successfully!\n";
			ifstream f3("masterfile.dat",ios::binary);
			ofstream f4("temp2.dat",ios::binary);
			while(f3.read((char*)&s,sizeof(s)))
			{
				if(id==s.returnid())
				{
					s.stock = s.stock + it.returnqty();
						//increase the stock by an amount of qty
				}
				f4.write((char*)&s,sizeof(s));
			}
			f3.close();
			f4.close();
			remove("masterfile.dat");
			rename("temp2.dat","masterfile.dat");
			continue;
		}
		f2.write((char*)&it,sizeof(it));
	}
	if(found==0)
		cout<<"\nItem not found!!\n";
	f1.close();f2.close();
	remove("list.dat");
	rename("temp.dat","list.dat");
	getch();
}
void search_list()
{
	system("cls");

	int id, found=0;
	cout<<"Enter the ID of the item to search = ";
	cin>>id;
	ifstream f("list.dat",ios::binary);
	while(f.read((char*)&it,sizeof(it)))
		if(id==it.returnid())
		{
			found=1;
			cout<<"\nItem found!!\n\n";
			cout<<"Details:\n";
			cout<<"ID = "<<it.returnid()<<endl;
			cout<<"Name = "<<it.returnname()<<endl;
			cout<<"Rate = "<<it.returnrate()<<endl;
			cout<<"Quantity = "<<it.returnqty()<<endl;
		}
	if(found==0)
		cout<<"\nItem not found!!\n";
	f.close();
	getch();
}

void display_bill()
{

	time_t syst;
	syst=time(NULL);
	ifstream f;
	f.open("list.dat",ios::binary);


		system("cls");
		cout<<"===========================================================================\n";
		cout<<"\t\t\t\tBILL\n";
		cout<<"===========================================================================\n";
		cout<<(ctime(&syst));
		cout<<"\n________________________________________________________________________________\n";
		cout<<"ID\t\tName\t\tRate\t\tQuantity\t Amount"<<endl;
		cout<<"________________________________________________________________________________\n";
		float subtotal=0;
		while(f.read((char*)&it,sizeof(it)))
		{
			it.display();
			subtotal=subtotal+it.returnamount();
		}
		cout<<"________________________________________________________________________________\n";
		cout<<"\nSubtotal = "<<subtotal<<endl;
		cout<<"VAT = 5%\n";
		cout<<"Total = "<<subtotal*105/100<<endl;
		cout<<"*****************************************************************************\n";
		cout<<"\t\tThank You For Shopping With Us. Visit Again!!\n";
		cout<<"*****************************************************************************\n";

		f.close();
		getch();

}



int main()
{
    int ch1,ch2,ch3;
	string user, pass;

	while(1)
	{
		system("cls");
		cout<<"*******************************************************************************\n";
		cout<<"\t\t\t\t City Supermarket\n";
		cout<<"*******************************************************************************\n\n";
		cout<<"\t\t\tElectronic Billing System\n\n";
		cout<<"How do you want to login as?\n";
		cout<<"1 - Administrator\n2 - Customer\n3 - Exit\nEnter = ";
		cin>>ch1;
		switch(ch1)
		{
			case 1: system("cls");
				cout<<"\nEnter the username and password:-\n";

				cout<<"Username: ";
				cin>>user;
				if(user != "aliasgar_akil")
				{
					cout<<"\nUsername does not match!\n";
					getch();
					break;
				}
				else{
					cout<<"Password: ";
					cin>>pass;

				if(pass != "Group_2")
				{
					cout<<"\nPassword does not match!\n";
					getch();
					break;
				}
				else
				{
					system("cls");
					cout<<"\t\t\tMENU\n\n";
					cout<<"1 - Create stock list\n2 - Append stock list\n3 - Search for a product\n4 - Display stock list\n5 - Modify product details\n6 - Delete a product\n7 - Back to login page\n";
					cout<<"Enter = ";
					cin>>ch2;
					switch(ch2)
					{
						case 1:create_stock();break;
						case 2:append_stock();break;
						case 3:search_stock();break;
						case 4:display_stock();break;
						case 5:modify_stock();break;
						case 6:delete_stock();break;
						case 7:break;
						default:cout<<"\nInvalid option!! Enter again!\n";getch();
					}
					while(ch2!=7)
					{
						system("cls");
						cout<<"\t\t\tMENU\n\n";
						cout<<"1 - Create stock list\n2 - Append stock list\n3 - Search for a product\n4 - Display stock list\n5 - Modify product details\n6 - Delete a product\n7 - Back to login page\n";
						cout<<"Enter = ";
						cin>>ch2;
						switch(ch2)
						{
						case 1:create_stock();break;
						case 2:append_stock();break;
						case 3:search_stock();break;
						case 4:display_stock();break;
						case 5:modify_stock();break;
						case 6:delete_stock();break;
						case 7:break;
						default:cout<<"\nInvalid option!! Enter again!\n";getch();
						}
					}
				}
				}
				break;

			case 2: system("cls");

				cout<<"\t\t\tMENU\n\n";
				cout<<"1 - Create shopping list\n2 - Append shopping list\n3 - Search for an item\n4 - Modify quantity\n5 - Delete an item\n6 - Display the bill\n7 - Back to login page\nEnter = ";
				cin>>ch3;

				switch(ch3)
				{
					case 1:create_list();break;
					case 2:append_list();break;
					case 3:search_list();break;
					case 4:modify_list();break;
					case 5:delete_list();break;
					case 6:display_bill();break;
					case 7:break;
					default:cout<<"\nInvalid option!! Enter again!\n";getch();
				}
				while(ch3!=7)
				{
					system("cls");

					cout<<"\t\t\tMENU\n\n";
					cout<<"1 - Create shopping list\n2 - Append shopping list\n3 - Search for an item\n4 - Modify quantity\n5 - Delete an item\n6 - Display the bill\n7 - Back to login page\nEnter = ";
					cin>>ch3;

					switch(ch3)
					{
					case 1:create_list();break;
					case 2:append_list();break;
					case 3:search_list();break;
					case 4:modify_list();break;
					case 5:delete_list();break;
					case 6:display_bill();break;
					case 7:break;
					default:cout<<"\nInvalid option!! Enter again!\n";getch();
					}
				}
				break;

			case 3:exit(0);

			default:cout<<"\nInvalid option!! Enter again!\n";
				getch();
		}
	}
    return 0;
}
