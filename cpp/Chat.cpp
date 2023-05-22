#include "../headers/Chat.h"

Chat::Chat()
{
    count = 0;
    mem_size = 8;
    array = new Pair[mem_size];
}
Chat::~Chat()
{
    delete[] array;
}
void Chat::reg(UserName u_name, char _pass[], int pass_length)
{
    uint *pass_sha1 = sha1(_pass, pass_length);
    int index = -1, i = 0;
    // берем пробы по всем i от 0 до размера массива
    for (; i < mem_size; i++)
    {
        index = hash_func(u_name, i);
        if (array[index].status == enPairStatus::free)
        {
            // найдена пустая ячейка, занимаем ее
            break;
        }
    }
    if (i >= mem_size)
        return; // все перебрали, нет места

    // кладем в свободную ячейку пару
    array[index] = Pair(u_name, pass_sha1);
    count++;
}
int Chat::hash_func(UserName u_name, int offset)
{
    // вычисляем индекс
    int sum = 0, i = 0;
    for (; i < NAMELENGTH; i++)
    {
        sum += u_name[i];
    }
    const double A = 0.7;
    const int M = 10;
    return (int(M * (A * sum - int(A * sum))) + int(offset * offset)) % mem_size;
}

bool Chat::login(UserName u_name, char _pass[], int pass_length)
{
    uint *pass_sha1 = sha1(_pass, pass_length);

    for (int i = 0; i < mem_size; i++)
    {
        int index = hash_func(u_name, i);
        if ((array[index].status == enPairStatus::engaged) &&
            (!strcmp(array[index].user_name, u_name)) &&
            (*array[index].user_pass == *pass_sha1))
        {
            return true;
        }
        else if (array[index].status == enPairStatus::free)
        {
            return false;
        }
    }
    return false;
}