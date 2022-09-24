#include <iostream>
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
};

//------------------------------------------------------------------------------------------
// тестування роботи додатка

int main()
{
	Pizzeria p("Bazzikalo", "Soborna street, 34b");

	p.AddPizza(StandardPizza("Neo", SizeType::Small, 78, { "mozzarella", "garlic", "onion", "chicken", "tomato" }));
	p.AddPizza(StandardPizza("Neo", SizeType::Medium, 95, { "mozzarella", "garlic", "onion", "chicken", "tomato" }));
	p.AddPizza(StandardPizza("Neo", SizeType::Large, 140, { "mozzarella", "garlic", "onion", "chicken", "tomato" }));
	p.DeletePizza("Neo");

	p.ShowMenu();

	p.FindPizza("tomato");
}
