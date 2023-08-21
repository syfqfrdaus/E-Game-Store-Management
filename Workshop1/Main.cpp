#include <iostream>
#include <mysql.h>
#include <string>
#include <sstream>
#include <conio.h>
#include <iomanip>

using namespace std;

int qstate;
MYSQL* conn;
MYSQL_ROW row;
MYSQL_RES* res;

class db_response
{
public:
	static void ConnectionFunction()
	{
		conn = mysql_init(0);
		if (conn)
		{
			cout << "Database Connected" << endl;
			system("cls");
		}
		else
			cout << "Failed To Connect!" << mysql_errno(conn) << endl;

		conn = mysql_real_connect(conn, "localhost", "root", "", "db_gamestore", 3306, NULL, 0);

		if (conn)
		{
			cout << "Database Connected To MySql" << conn << endl;
			system("pause");
		}
		else
			cout << "Failed To Connect!" << mysql_errno(conn) << endl;
	}
};

void MainMenu();//display menu
void DisplayGame();//display all game
void GameAdd();//add game to stock
void DeleteGame();//delete game from stock
void ModifyGame();//update game from stock
void DisplayReceipt();//find ways to display date
void SearchGame();//Search game
void CheckGame();//Check game that are low on stock
void DisplaySale();//Display all game sales
void CalculateSale();//Calculate Sales and Update Quantity
void GenerateReceipt(string);//Generate receipt for each purchases
void SearchReceipt();//Search receipt
void DisplayTotalSale();//Display total sales from table sale


//LOGIN : ID = admin12345
//        PASSWORD : admin12345
int main()
{
	int attempt = 0;

Login:
	db_response::ConnectionFunction();

	char c;
	string password;
	string adminId;

	system("cls");
	cout << "\nxxxxxxxxxxWELCOME TO E-GAMES STORE SALES CALCULATION SYSTEMxxxxxxxxxx\n\n\n";
	cout << "Enter Admin ID : ";
	cin >> adminId;
	cout << endl;
	cout << "Enter Password : ";
	char ch;
	while ((ch = _getch()) != 13)
	{
		password += ch;
		cout << '*';
	}
	cout << endl << endl;
	cout << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n";

	string checkUser_query = "select adminID from admin where adminID = '" + adminId + "' and adminPass = '" + password + "'";
	const char* cu = checkUser_query.c_str();
	qstate = mysql_query(conn, cu);

	if (!qstate)
	{
		res = mysql_store_result(conn);
		if (res->row_count == 1)
		{
			while (row = mysql_fetch_row(res))
				adminId = row[0];
			MainMenu();
		}
		else
		{
			cout << "\nInvalid username or password. Want to try again? (y/n): ";
			cin >> c;
			if (c == 'y' || c == 'Y')
			{
				attempt++;
				{
					if (attempt == 4)
					{
						return 0;
					}
				}
				cout << "Remaining Attempt = " << 4 - attempt << endl;
				system("pause");
				goto Login;
			}
			else
				cout << "\n\nExiting Program\n\n";
			return 0;

		}
	}
	else
		cout << "Query Execution Problem!" << mysql_errno(conn) << endl;

	return 0;
}

void MainMenu()
{

	system("cls");
	//menu
	int menu, stockMenu, stocksubMenu, receiptMenu;
	string gameID;
	do
	{
	JMainMenu:
		system("cls");
		cout << "\nxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n";
		cout << "xxxxxxxxxxxxxWELCOME TO E-GAMES STORE SALES CALCULATION SYSTEMxxxxxxxxxxxx\n\n";
		cout << "------------------------------------MAIN MENU-----------------------------\n\n";
		cout << "  1.DISPLAY SALES\n";
		cout << "  2.STOCK MENU\n";
		cout << "  3.CUSTOMER PURCHASE MENU\n";
		cout << "  PRESS ANY OTHER KEY TO EXIT\n\n";
		cout << "PLEASE ENTER YOUR MENU OF CHOICE : ";
		cin >> menu;
		cout << endl;
		if (menu == 1)//Sale menu
		{
			DisplaySale();
			DisplayTotalSale();
		}
		else if (menu == 2)//stock menu
		{
			system("cls");
		JStockMenu:
			cout << "\n---------------STOCK MENU---------------\n\n";
			cout << "  1.DISPLAY GAME STOCK MENU\n";
			cout << "  2.MODIFY GAME DATA MENU\n";
			cout << "  3.CHECK GAME\n";
			cout << "  4.RETURN TO MAIN MENU\n\n";
			cout << "  PLEASE ENTER YOUR CHOICE : ";
			cin >> stockMenu;

			if (stockMenu == 1)
			{
			JStockDispMenu:
				cout << "\n----------DISPLAY GAME STOCK MENU----------\n";
				cout << "\n  1. Display All Game In Stock\n";
				cout << "  2. Search Game\n";
				cout << "  3. Return to Main Menu\n";
				cout << "  Please Enter Your Choice : ";
				cin >> stocksubMenu;

				if (stocksubMenu == 1)
				{
					DisplayGame();
					system("pause");
				}
				else if (stocksubMenu == 2)
				{
					SearchGame();
				}
				else if (stocksubMenu == 3)
					goto JMainMenu;
				else
					cout << "\nPlease Enter A Valid Choice!\n\n";
				goto JStockDispMenu;

			}
			else if (stockMenu == 2)
			{
			JStockModifyMenu:
				cout << "\n----------MODIFY GAME DATA MENU----------\n\n";
				cout << "  1. Add New Game Title\n";
				cout << "  2. Edit Stock Game Data\n";
				cout << "  3. Delete Game Data\n";
				cout << "  4. Return to Main Menu\n";
				cout << "  Please Enter Your Choice : ";
				cin >> stocksubMenu;

				if (stocksubMenu == 1)
				{
					GameAdd();
				}
				else if (stocksubMenu == 2)
				{
					ModifyGame();
				}
				else if (stocksubMenu == 3)
				{
					DeleteGame();
				}
				else if (stocksubMenu == 4)
					goto JMainMenu;
				else
					cout << "\nPlease Enter A Valid Choice!\n\n";
				goto JStockModifyMenu;
			}

			else if (stockMenu == 3)
			{
				CheckGame();
			}
			else if (stockMenu == 4)
				goto JMainMenu;
			else
				cout << "Please Enter A Valid Choice!\n\n";
			goto JStockMenu;


		}
		else if (menu == 3)//customer or receipt menu
		{
			system("cls");
		JReceiptMenu:
			cout << "\n----------CUSTOMER PURCHASE MENU----------\n\n";
			cout << "  1. Display All Receipt\n";
			cout << "  2. Search Receipt\n";
			cout << "  3. Generate Receipt\n";
			cout << "  4. Return to Main Menu\n";
			cout << "  Please Enter Your Choice : ";
			cin >> receiptMenu;

			if (receiptMenu == 1)
			{
				DisplayReceipt();
			}
			else if (receiptMenu == 2)
			{
				SearchReceipt();
			}
			else if (receiptMenu == 3)
			{
				CalculateSale();
			}
			else if (receiptMenu == 4)
			{
				goto JMainMenu;
			}
			else
				cout << "\nPlease Enter A Valid Choice!\n\n";
			goto JReceiptMenu;
		}

	} while (menu >= 1 && menu <= 3);
	return;

}

void DisplayGame()
{
	cout << "\n\n---------------List of all Game in Stock-------------------\n\n";

	qstate = mysql_query(conn, "SELECT * FROM game");
	if (!qstate)
	{

		cout << setw(10) << "GameID" << setw(20) << "GameTitle" << setw(10) << "Quantity" << setw(10) << "Price" << endl;
		res = mysql_store_result(conn);
		while (row = mysql_fetch_row(res))
		{
			cout << setw(10) << row[0] << setw(20) << row[1] << setw(10) << row[2] << setw(10) << row[3] << endl;
		}
		cout << "\n-----------------------------------------------------------\n";
	}
	else
	{
		cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
	}
	return;
}

void GameAdd()
{

	string gameTitle = "";
	int quantity = 0;
	int price = 0;
	string SPrice;
	string SQuantity;

	cout << "\n----------ADDING NEW GAME----------\n";
	cin.ignore(1, '\n');
	cout << "Please enter the Game Title: \n";
	getline(cin, gameTitle);

JQuantity:
	cout << "Please enter the Game Quantity: \n";
	cin >> quantity;
	if (quantity < 0)
	{
		cout << "Please Enter Quantity With Positive Value\n";
		goto JQuantity;
	}
	else
	{
	JPrice:
		cout << "Please enter the Game Price: \n";
		cin >> price;
		if (price < 0)
		{
			cout << "Please Enter Price With Positive Value\n";
			goto JPrice;
		}
		else
		{
			SQuantity = to_string(quantity);
			SPrice = to_string(price);
			string insert_query = "insert into game (GameTitle, Quantity, Price) values ('" + gameTitle + "','" + SQuantity + "','" + SPrice + "')";
			const char* q = insert_query.c_str();
			qstate = mysql_query(conn, q);

			if (!qstate)
			{
				string insert_query2 = "insert into sale (GameTitle, QuantitySold, Sales) VALUES('" + gameTitle + "', '0', '0')";
				const char* q2 = insert_query2.c_str();
				qstate = mysql_query(conn, q2);

				cout << "Game Added!\n";
			}
			else
			{
				cout << "ERROR! ERROR CODE: " << mysql_errno(conn) << endl;
			}

			char c;
			cout << "Add Another Game ? (y/n): ";
			cin >> c;
			if (c == 'y' || c == 'Y')
				GameAdd();
			else
				return;
		}
	}
}

void DeleteGame()
{
	string gameTitle;
	char c;
	cout << "\n-----------------------DELETE GAME-------------------------";

	DisplayGame();

	cin.ignore(1, '\n');
	cout << "Enter the GameTitle for the game you wish to remove :\n";
	getline(cin, gameTitle);


	string delete_query = "delete from sale where gameTitle = '" + gameTitle + "'";
	const char* q = delete_query.c_str();
	qstate = mysql_query(conn, q);
	string delete_query2 = "delete from receipt where gameTitle = '" + gameTitle + "'";
	const char* q2 = delete_query2.c_str();
	qstate = mysql_query(conn, q2);
	string delete_query3 = "delete from game where gameTitle = '" + gameTitle + "'";
	const char* q3 = delete_query3.c_str();
	qstate = mysql_query(conn, q3);

	if (!qstate)
	{
		cout << "Game Deleted!\n";
	}
	else
	{
		cout << "ERROR! ERROR CODE: " << mysql_errno(conn) << endl;
	}

	cout << "Do you want to delete other game? (y/n): ";
	cin >> c;

	if (c == 'y' || c == 'Y')
		DeleteGame();
	else
		return;

}

void ModifyGame()
{
	string gameID;
	int select;

	cout << "\n--------------------Modify Game Data--------------------\n";

	DisplayGame();

	cout << "Enter The GameID You Wish To Modify : \n";
	cin >> gameID;

	string checkUser_query = "select * from game where GameID = '" + gameID + "'";
	const char* cu = checkUser_query.c_str();
	qstate = mysql_query(conn, cu);

	if (!qstate)
	{
		res = mysql_store_result(conn);
		if ((row = mysql_fetch_row(res)) == NULL)
		{
			goto JDataNULL;
		}
		else
		{
		JEditMenu:
			cout << "Which Type Do You Wish To Modify\n";
			cout << "1. Quantity\n";
			cout << "2. Price\n";
			cin >> select;


			if (select == 1)
			{
				int quantity = 0;
				string SQuantity;
				cout << "Enter The Quantity To Add Into Current Stock\n";
				cin >> quantity;

				SQuantity = to_string(quantity);
				string update_query = "update game set Quantity = Quantity + '" + SQuantity + "' WHERE GameID = '" + gameID + "'";
				const char* q = update_query.c_str();
				qstate = mysql_query(conn, q);
			}
			else if (select == 2)
			{
			JVPrice:
				string SPrice;
				int price = 0;
				cout << "Enter New Price\n";
				cin >> price;
				if (price < 0)
				{
					cout << "Please Enter Price With Positive Value\n";
					goto JVPrice;
				}
				else
				{
					SPrice = to_string(price);
					string update_query = "update game set Price = '" + SPrice + "' where GameID = '" + gameID + "'";
					const char* q = update_query.c_str();
					qstate = mysql_query(conn, q);
				}
			}
			else
			{
				cout << "\nPlease Enter Valid Choice\n\n";
				goto JEditMenu;
			}
		}
	}
	else
	{
	JDataNULL:
		cout << "GameID Was Not Found in Database!\n";
		cout << "ERROR! ERROR CODE: " << mysql_errno(conn) << endl;
	}

	char c;
	cout << "Do you want to edit other detail? (y/n): ";
	cin >> c;

	if (c == 'y' || c == 'Y')
		ModifyGame();
	else
		return;

}

void DisplayReceipt()
{
	cout << "\n------------------------------List of Receipt------------------------------\n\n";

	qstate = mysql_query(conn, "SELECT receipt.*, game.Price FROM receipt JOIN game where receipt.GameTitle = game.GameTitle");
	if (!qstate)
	{
		cout << setw(20) << "GameTitle" << setw(15) << "PurchaseDate" << setw(15) << "CustName" << setw(10) << "Price" << endl;

		res = mysql_store_result(conn);
		while (row = mysql_fetch_row(res))
		{
			cout << setw(20) << row[1] << setw(15) << row[2] << setw(15) << row[3] << setw(10) << row[4] << endl;
		}
	}
	else
	{
		cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
	}
	cout << "\n---------------------------------------------------------------------------\n";
	system("pause");
	return;
}

void SearchGame()
{
	int choose;
	string gameId, gameName;

	cout << "\n----------SEARCH GAME IN STOCK----------\n\n";

	cin.ignore(1, '\n');
	cout << "Please Enter The Game Name :";
	getline(cin, gameName);

	cout << "\n--------------------SEARCH RESULT--------------------\n";
	string seach_query = "select GameID, GameTitle, Quantity, Price from game where GameTitle like '%" + gameName + "%'";
	const char* q = seach_query.c_str();
	qstate = mysql_query(conn, q);

	if (!qstate)
	{
		cout << setw(10) << "GameID" << setw(20) << "GameTitle" << setw(10) << "Quantity" << setw(10) << "Price" << endl;

		res = mysql_store_result(conn);
		while (row = mysql_fetch_row(res))
		{
			cout << setw(10) << row[0] << setw(20) << row[1] << setw(10) << row[2] << setw(10) << row[3] << endl;
		}

		char select;
		cout << endl << "Do you want to search again?(y/n): ";
		cin >> select;

		if (select == 'y' || select == 'Y')
			SearchGame();
		else
			return;
	}
	else
	{
		cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
	}
}

void CheckGame()
{
	cout << "\n----------LIST OF GAME THAT ARE LOW ON STOCK----------\n\n";
	cout << "GAME WITH QUANTITY LESS THAN 10\n\n";

	string search_query = "select GameID, GameTitle, Quantity from game where Quantity <= 10";
	const char* q = search_query.c_str();
	qstate = mysql_query(conn, q);

	if (!qstate)
	{
		cout << setw(10) << "GameID" << setw(20) << "GameTitle" << setw(10) << "Quantity" << endl;

		res = mysql_store_result(conn);
		while (row = mysql_fetch_row(res))
		{
			cout << setw(10) << row[0] << setw(20) << row[1] << setw(10) << row[2] << endl;
		}
		cout << endl;
		system("pause");
	}
	else
	{
		cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
	}
}

void DisplaySale()
{
	system("cls");
	cout << "\n\n\n---------------E-GAMES STORE SALES---------------\n\n";

	qstate = mysql_query(conn, "SELECT * FROM sale");
	if (!qstate)
	{

		cout << setw(20) << "GameTitle" << setw(20) << "QuantitySold" << setw(10) << "Sales" << endl;
		res = mysql_store_result(conn);
		while (row = mysql_fetch_row(res))
		{
			cout << setw(20) << row[0] << setw(20) << row[1] << setw(10) << row[2] << endl;
		}
	}
	else
	{
		cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
	}
	return;

}

void CalculateSale()
{
	string gameTitle;
	int storeQuantity = 0;
	int store = 0;

	DisplayGame();

	cin.ignore(1, '\n');
	cout << "Enter the GameTitle for game that customer wish to buy\n";
	getline(cin, gameTitle);

	string search_query = "select GameID, GameTitle, Quantity, Price from game  where GameTitle like '" + gameTitle + "'";
	const char* q = search_query.c_str();
	qstate = mysql_query(conn, q);

	if (!qstate)
	{
		cout << setw(10) << "GameID" << setw(20) << "GameTitle" << setw(10) << "Quantity" << setw(10) << "Price" << endl;

		res = mysql_store_result(conn);
		while (row = mysql_fetch_row(res))
		{
			cout << setw(10) << row[0] << setw(20) << row[1] << setw(10) << row[2] << setw(10) << row[3] << endl;
			storeQuantity = atoi(row[2]);
		}

		if (storeQuantity > 0)
		{
			cout << "Game is available\n";

			string update_query = "update sale set QuantitySold = QuantitySold + 1, sales = Sales + (select price from game WHERE game.GameTitle = '" + gameTitle + "') WHERE sale.GameTitle = '" + gameTitle + "'";
			const char* q = update_query.c_str();
			qstate = mysql_query(conn, q);
			string update_query2 = "update game set Quantity = Quantity -1 WHERE GameTitle = '" + gameTitle + "'";
			const char* q2 = update_query2.c_str();
			qstate = mysql_query(conn, q2);

			GenerateReceipt(gameTitle);
		}
		else
		{
			cout << "Sorry game is out of stock\n";
		}
	}
	else
	{
		cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
	}

}

void GenerateReceipt(string gameTitle)
{
	string purchaseDate, custName;

	cout << "\n----------GENERATE RECEIPT----------\n\n";

	cout << "The game Title is " << gameTitle << endl;
	//cin.ignore(1, '\n');
	cout << "Please Enter the Purchase Date(dd-mm-yyyy) :\n";
	getline(cin, purchaseDate);
	//cin.ignore(1, '\n');
	cout << "Please Enter the Customer Name : \n";
	getline(cin, custName);

	string insert_query = "insert into receipt (GameTitle, PurchaseDate, CustName) values ('" + gameTitle + "',STR_TO_DATE('" + purchaseDate + "', '%d-%m-%Y'),'" + custName + "' )";
	const char* q = insert_query.c_str();
	qstate = mysql_query(conn, q);

	if (!qstate)
	{
		cout << endl << "Receipt Successfully Generated" << endl;
	}
	else
	{
		cout << "ERROR!" << mysql_errno(conn) << endl;
	}

}

void SearchReceipt()
{
	string name;

	cin.ignore(1, '\n');
	cout << "--------------------SEARCH RECEIPT--------------------\n\n";
	cout << "Enter Customer Name: \n";
	getline(cin, name);

	cout << "\n------------------------------SEARCH RESULT------------------------------\n";
	string search_query = "SELECT receipt.*, game.Price FROM receipt JOIN game where receipt.GameTitle = game.GameTitle and receipt.CustName like '%" + name + "%';";
	const char* q = search_query.c_str();
	qstate = mysql_query(conn, q);


	if (!qstate)
	{
		cout << setw(20) << "GameTitle" << setw(15) << "PurchaseDate" << setw(15) << "CustName" << setw(10) << "Price" << endl;

		res = mysql_store_result(conn);
		while (row = mysql_fetch_row(res))
		{
			cout << setw(20) << row[1] << setw(15) << row[2] << setw(15) << row[3] << setw(10) << row[4] << endl;
		}
		cout << "-------------------------------------------------------------------------\n";
		system("pause");
	}
	else
	{
		cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
	}

	return;


}

void DisplayTotalSale()
{
	cout << "\nTHE TOTAL SALES FOR ALL GAMES IS = ";

	qstate = mysql_query(conn, "SELECT SUM(Sales)FROM sale");

	if (!qstate)
	{
		res = mysql_store_result(conn);
		while (row = mysql_fetch_row(res))
		{
			cout << row[0] << endl;
		}
		cout << "-------------------------------------------------\n\n";
		system("pause");
		system("cls");
	}
	else
	{
		cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
	}
}
