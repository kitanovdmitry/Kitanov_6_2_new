#include <iostream>

using namespace std;
int indent = 0;

struct our_struct
{
    int int_field;
    our_struct* left, * right;
};

void add_elem(our_struct*& address, int value, int i)
{
    if (address == 0)
    {
        address = new our_struct;

        if (address != 0)
        {
            address->int_field = value;
            address->left = 0;
            address->right = 0;
        }
        else
        {
            cout << "Adding of " << value << " error. No memory available\n";
        }
    }
    else
    {
        if (value == (address->int_field))
        {
            cout << value << " is duplicate\n";
            return;
        }

        switch(i)
        {
        case 0://1
            add_elem(address->left, value, i);
            break;
        case 1://2
            add_elem(address->right, value, i);
            break;
        case 2://3
            add_elem(address->left, value, i);
            break;
        case 3://4
            add_elem(address->right, value, i);
            break;
        case 4:
            add_elem(address->left, value, i);
            break;
        case 5:
            add_elem(address->right, value, i);
            break;
        }
    }
}

void free_memory (our_struct* elem_address)

{

if (!elem_address) return;
free_memory(elem_address -> left);
free_memory(elem_address -> right);
delete elem_address;

return;
}

void print(our_struct* address)

{

if (address == 0) return;
indent += 5;
print(address->left);

for (int i = 0; i < indent; i++)
{
    cout << " ";
}

cout << address->int_field << "\n";
print(address->right);
indent -= 5;
return;
}

int main()
{
    int number_of_elements = 0;
    cout << "Enter a number of elements in the structure:\n";
    cin >> number_of_elements;

    our_struct* start_elem = 0;
    int elem_value[6];

    for (int i = 0; i < number_of_elements; i++)
    {
            cout << "Enter a value of the " << i+1 << " element\n";
            cin >> elem_value[i];
            add_elem(start_elem, elem_value[i], i);
    }

    print(start_elem);
    free_memory(start_elem);
    return 0;
}

