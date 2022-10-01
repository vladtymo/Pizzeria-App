#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

/* 5. Піцерія
	Створити ієрархію класів для подання інформації про піцу.
	Піцу клієнт може замовляти
		стандартну(яку пропонує піцерія),
		складену за смаком клієнта(клієн сам складає піцу)
	Створити програму для роботи піцерії
		Додавання(вилучення. редагування) піци у(з)  базу
		Додавання(вилучення. редагування) продуктів у(з)  базу
		Збереження бази піц у файлі
		Завантаження бази піц з файлу
		Перегляд готових піц(складників, ціни)
		Пошук піц по складникам
		Замовлення піци клієнтом(ами), враховуючи можливе складання піци клієнтом
		Розрахунок клієнта(друк чеку, прийом оплати)
*/

enum SizeType { Small, Medium, Large };
enum OperationType { Exit, Add, Delete, Show, Find, Save, Load };

struct Pizza
{
	// властивості піци
	SizeType size;
	vector<string> ingredients; // { "meat", "peper", "onion" }
	double price;

	Pizza(SizeType size, double price, vector<string> ingredients)
		: size(size), price(price), ingredients(ingredients)
	{ }
};

struct StandardPizza : public Pizza
{
	string name;

	StandardPizza(string name, SizeType size, double price, vector<string> ingredients)
		: Pizza(size, price, ingredients), name(name)
	{ }
};

class Pizzeria
{
private:
	string name;
	string address;
	vector<StandardPizza> pizzaList; // {"4 Cheese", 120, Medium}, {"Neo", 88, Large}, {"Margherita", 95, Small}

public:
	Pizzeria(string name, string address) : name(name), address(address)
	{
		pizzaList.push_back(StandardPizza(
			"Quattro Formaggi",
			SizeType::Medium,
			110,
			{
				"mozzarella",
				"gorgonzola",
				"parmigiano",
				"goat cheese",
				"salt" 
			}
		));
		pizzaList.push_back(StandardPizza(
			"Margherita",
			SizeType::Large,
			135,
			{
				"mozzarella",
				"basil",
				"tomato",
				"garlic"
			}
		));
		pizzaList.push_back(StandardPizza(
			"Neapolitan ",
			SizeType::Medium,
			90,
			{
				"tomato",
				"extra virgin olive oil",
				"buffalo mozzarella",
				"oregano"
			}
		));
	}

	// додати нову піцу в меню
	void AddPizza(StandardPizza pizza)
	{
		pizzaList.push_back(pizza);
	}

	// видалити піцу з меню
	void DeletePizza(string name)
	{
		for (auto i = pizzaList.begin(); i < pizzaList.end(); ++i)
		{
			if (i->name == name)
			{
				pizzaList.erase(i);
				return;
			}
		}
	}

	// відобразити меню піц
	void ShowMenu() const
	{
		cout << "===================== MENU =====================\n";
		for (auto pizza : pizzaList)
		{
			cout << pizza.name << endl;
			// TODO: відобразити всі властивості в зручному форматі
		}
		cout << "================================================\n";
	}

	void FindPizza(string ingredient)
	{
		for (auto pizza : pizzaList)
		{
			for (auto i : pizza.ingredients)
			{
				if (i == ingredient)
				{
					cout << pizza.name << endl;
					// TODO: покращити вивід інформації
					break;
				}
			}
		}
	}

	// TODO: створити метод для замовлення стандартної піци
	// метод приймає назву та розмір піци і повертає її ціну
	// якщо даної піци не існує, то показати відповідне повідомлення
	double Order(string name, SizeType size);

	// TODO: створити метод для замовлення власної піци передавши свій список інгредієнтів
	double Order(SizeType size, vector<string> ingredients);

	void Save()
	{
		// out file stream
		ofstream out("data.txt");

		for (auto pizza : pizzaList)
		{
			out << pizza.name << " " << pizza.size << " " << pizza.price << endl;
			for (auto ing : pizza.ingredients)
			{
				out << ing << " ";
			}
			out << endl;
		}

		out.close();
	}
};

class AppMenu {
public:

	void Show()
	{
		cout << "============ MENU ============\n";
		cout << Add << " - Add New Pizza\n";
		cout << Delete << " - Delete Pizza\n";
		cout << OperationType::Show << " - Show Pizza Menu\n";
		cout << Find << " - Find Pizza by Ingredients\n";
		cout << Save << " - Save\n";
		cout << Load << " - Load\n";
		cout << Exit << " - Exit\n";
	}
	OperationType ChooseOperation()
	{
		int value = 0;
		cout << "Enter operation: ";
		cin >> value;

		while (value < 0 || value > 6)
		{
			cout << "Invalid operation! Please, try again: ";
			cin >> value;
		}

		return (OperationType)value;
	}
};

class Program
{
private:
	AppMenu menu;
	Pizzeria pizzeria;

public:
	Program() : pizzeria("Bazzikalo", "Soborna street, 34b")
	{
		cout << "Program started!";
	}

	void Start()
	{
		menu.Show();
		OperationType operation = Exit;

		string name;

		do
		{
			operation = menu.ChooseOperation();

			switch (operation)
			{
			case Add:
				// TODO: enter data from keyboard
				pizzeria.AddPizza(StandardPizza("Neo", SizeType::Small, 78, { "mozzarella", "garlic", "onion", "chicken", "tomato" }));
				break;
			case Delete:
				cout << "Pizza name to delete: ";
				cin >> name;
				pizzeria.DeletePizza(name);
				break;
			case Show:
				pizzeria.ShowMenu();
				break;
			case Find:
				cout << "Ingrediaent name to find: ";
				cin >> name;
				pizzeria.FindPizza(name);
				break;
			case Save:
				pizzeria.Save();
				break;
			case Load:
				break;
			}

		} while (operation != Exit);
	}

	// TODO: add, delete, find methods...
};

//------------------------------------------------------------------------------------------
// тестування роботи додатка

int main()
{
	Program program;
	program.Start();
}
