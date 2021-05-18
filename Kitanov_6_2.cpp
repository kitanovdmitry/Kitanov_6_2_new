/*
Автор: Китанов Дмитрий
Группа: СБС-001-01, 2-я подгруппа
Задача №6, вариант 2
Цель: построить динамическую конструкцию в соответствии с заданием
*/
#include <iostream>
#include <climits>

using namespace std;

struct our_struct
{
    int int_field;
    our_struct* left, * right;
};

void Add_Elem(our_struct*& address, int val1, int val2, int val3, int val4, int val5)
{
    static const size_t NumElems = 5;

    // создаём новую ячейку
    our_struct* ptrs[NumElems];
    for (size_t i = 0; i < NumElems; ++i)
    {
        ptrs[i] = new our_struct;
    }

    ptrs[0]->int_field = val1;
    ptrs[0]->left = ptrs[1];
    ptrs[0]->right = ptrs[2];

    ptrs[1]->int_field = val2;
    ptrs[1]->left = ptrs[3];
    ptrs[1]->right = ptrs[2];

    ptrs[2]->int_field = val3;
    ptrs[2]->left = ptrs[1];
    ptrs[2]->right = ptrs[4];

    ptrs[3]->int_field = val4;
    ptrs[3]->left = nullptr;
    ptrs[3]->right = ptrs[4];

    ptrs[4]->int_field = val5;
    ptrs[4]->left = ptrs[3];
    ptrs[4]->right = nullptr;

    // вставляем новую ячейку в цепочку ячеек
    if (address == nullptr)
        {
            address = ptrs[0];
        }
    else
    {
        our_struct *p = address;
        // спускаемся по левым элементам до начала следующей ячейки
        while (p->left->left->left != nullptr)
        {
            p = p->left->left->left;
        }
        // настраиваем указатели последней ячейки на первый элемент новой ячейки
        p->left->left->left = p->right->right->right = ptrs[0];
    }
    return;
}

void Free_Memory (our_struct*& elem_address, int numbers_of_elements)

{
    if (!elem_address) return;
    our_struct* sup_address = elem_address;
    int numbers_of_cells = numbers_of_elements / 5;

    for (int i = 0; i < numbers_of_cells; i++)
    {
        if ((i == 0) && (numbers_of_cells > 1))
        {
            for (int j = 0; j < (numbers_of_cells - 1); j ++)
            {
                sup_address = sup_address->left->left->left;
            }
        }

        delete sup_address->left->left;
        delete sup_address->right->right;
        delete sup_address->left;
        delete sup_address->right;
        delete sup_address;

        if (numbers_of_cells > 1)
        {
            sup_address = elem_address;
        }
    }
    return;
}

void Print_Cell(our_struct* address, int number_of_elemets)

{
    our_struct* sup_address = 0;
    int counter = 0;

    if (address == 0) return;

    for (int i = 0; i < number_of_elemets; i++)
    {
        if ((counter == 0) && (i == 0))
        {
            sup_address = address;
        }
        else if (counter > 2)
            {
                if (counter == 3)
                {
                    sup_address = address;
                }
                sup_address = sup_address->right;
            }
            else sup_address = sup_address->left;

        if ((counter == 1) && (i != 0))
        {
            address = sup_address;
        }

        if ((i != (number_of_elemets - 1)) && (i != (number_of_elemets - 3)))
        {
            cout << " element = " << sup_address->int_field << "\n";
            cout << "and has point to " << sup_address->left->int_field << " and to " << sup_address->right->int_field <<"\n";
        }
        else
        {
            if (i == (number_of_elemets - 3))
            {
                cout << " element = " << sup_address->int_field << "\n";
                cout << "and has point to 1-st elem of next cell and to " << sup_address->right->int_field <<"\n";
            }
            else
            {
                cout << " element = " << sup_address->int_field << "\n";
                cout << "and has point to 1-st elem of next cell and to " << sup_address->left->int_field <<"\n";
            }
        }

        if (counter < 4)
        {
            counter = counter + 1;
        }
        else counter = 0;
    }
    return;
}

int main()
{
    int number_of_elements;
    bool typeFail;

    do
    {
        cout << "Enter a number of elements in the structure:(5 or 10)\n";
        cin >> number_of_elements;

        typeFail = cin.fail();
        cin.clear();
        cin.ignore(INT_MAX, '\n');
    }
    while (((number_of_elements % 5) != 0) || (number_of_elements > 10) || (number_of_elements <= 0) || (typeFail));

    cout << "Numbers of elements = " << number_of_elements << "\n";

    our_struct* start_elem = 0;
    int *elem_value;
    elem_value = new int [number_of_elements];

    for (int i = 0; i < number_of_elements; i++)
    {
        do
        {
            cout << "Enter a value of the " << i+1 << " element\n";
            cin >> elem_value[i];

            typeFail = cin.fail();
            cin.clear();
            cin.ignore(INT_MAX, '\n');
        }
        while (typeFail);
    }

    for (int i = 0; i < number_of_elements; i++)
    {
        if (((i+1)%5) == 0)
        {
            Add_Elem(start_elem, elem_value[i-4], elem_value[i-3], elem_value[i-2], elem_value[i-1], elem_value[i]);
        }
    }

    Print_Cell(start_elem, number_of_elements);
    Free_Memory(start_elem, number_of_elements);
    delete[] elem_value;
    return 0;
}
