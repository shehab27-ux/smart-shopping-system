#include <iostream>
#include <string>

using namespace std;

string products[5] = {"Laptop", "Mouse", "Keyboard", "Monitor", "Headphones"};
int prices[5] = {1000, 25, 50, 200, 80};

struct CartNode
{
    string itemName;
    int price;
    CartNode *next;
};

CartNode *cartHead = nullptr;

string undoStack[100];
int top = -1;

void pushUndo(string item)
{
    if (top < 99)
    {
        top++;
        undoStack[top] = item;
    }
}

string popUndo()
{
    if (top == -1)
        return "";
    string item = undoStack[top];
    top--;
    return item;
}

void showProducts()
{
    cout << "\n--- Available Items ---\n";
    for (int i = 0; i < 5; i++)
    {
        cout << i + 1 << ". " << products[i] << " - $" << prices[i] << endl;
    }
}

void addToCart(int choice)
{
    if (choice < 1 || choice > 5)
    {
        cout << "Invalid item!\n";
        return;
    }

    int index = choice - 1;

    CartNode *newNode = new CartNode();
    newNode->itemName = products[index];
    newNode->price = prices[index];
    newNode->next = nullptr;

    if (cartHead == nullptr)
    {
        cartHead = newNode;
    }
    else
    {
        CartNode *temp = cartHead;
        while (temp->next != nullptr)
        {
            temp = temp->next;
        }
        temp->next = newNode;
    }

    pushUndo(products[index]);
    cout << products[index] << " added to cart!\n";
}

void viewCart()
{
    cout << "\n--- Your Shopping Cart ---\n";
    if (cartHead == nullptr)
    {
        cout << "Cart is empty.\n";
        return;
    }

    CartNode *temp = cartHead;
    int total = 0;
    while (temp != nullptr)
    {
        cout << "- " << temp->itemName << " ($" << temp->price << ")\n";
        total += temp->price;
        temp = temp->next;
    }
    cout << "--------------------------\n";
    cout << "Total Bill: $" << total << endl;
}

void undoLastAdd()
{
    string lastItem = popUndo();
    if (lastItem == "")
    {
        cout << "Nothing to undo!\n";
        return;
    }

    if (cartHead->itemName == lastItem && cartHead->next == nullptr)
    {
        delete cartHead;
        cartHead = nullptr;
    }
    else
    {
        CartNode *temp = cartHead;
        while (temp->next->next != nullptr)
        {
            temp = temp->next;
        }
        delete temp->next;
        temp->next = nullptr;
    }
    cout << "Undo successful: Removed " << lastItem << " from cart.\n";
}

int main()
{
    int choice;

    while (true)
    {
        cout << "\n==============================\n";
        cout << "    SMART SHOPPING SYSTEM     \n";
        cout << "==============================\n";
        cout << "1. View Shop Products\n";
        cout << "2. Add Item to Cart\n";
        cout << "3. View Cart & Total\n";
        cout << "4. Undo Last Add\n";
        cout << "5. Checkout & Exit\n";
        cout << "Choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            showProducts();
            break;
        case 2:
            showProducts();
            int itemChoice;
            cout << "Enter item number to add: ";
            cin >> itemChoice;
            addToCart(itemChoice);
            break;
        case 3:
            viewCart();
            break;
        case 4:
            undoLastAdd();
            break;
        case 5:
            viewCart();
            cout << "\nThank you for shopping! Exiting...\n";
            return 0;
        default:
            cout << "Invalid choice!\n";
        }
    }
}