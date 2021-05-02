#include <iostream>

using namespace std;
int indent = 0;

struct our_struct
{
    int int_field;
    our_struct* left, * right;
};

void add_elem(int elem_value, our_struct*& address_elem, int i)
{
    if(!address_elem)
    {
        address_elem = new our_struct;
        address_elem -> int_field = elem_value;
        if (elem_value == 2)
        {
            address_elem -> left = 0;
            address_elem -> right = 0;
        }
        else
        {
            address_elem -> left = 0;
            address_elem -> right = 0;
        }
        return;
    }
    else
    {
        switch(i)
        {
        case 0: //1
            add_elem(elem_value, address_elem -> left, i);
            break;
        case 1: //2
            add_elem(elem_value, address_elem -> right, i);
            break;
        case 2: //3
            add_elem(elem_value, address_elem -> right, i);
            break;
        case 3:// 4
            add_elem(elem_value, address_elem -> left, i);
            break;
        case 4:// 5
            add_elem(elem_value, address_elem -> left, i);
            break;
        case 5:// 6
            add_elem(elem_value, address_elem -> right, i);
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

void print(our_struct* elem_address)

{

if (!elem_address) return;
indent += 5;
print(elem_address-> left);

for (int i = 0; i < indent; i++)
{
    cout << " ";
}

cout << elem_address -> int_field << "\n";
print(elem_address -> right);
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
    }


    for (int i = 0; i < number_of_elements; i++)
    {
                add_elem(elem_value[i], start_elem, i);
    }

    print(start_elem);
    free_memory(start_elem);
    return 0;
}
