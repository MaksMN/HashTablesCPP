#pragma once

#include <string.h>
#include "sha1.h"

#define NAMELENGTH 10 // Зафикcируем длину имени

typedef char UserName[NAMELENGTH]; // тип имя фрукта

class Chat
{ // хэш таблица
public:
    Chat();
    ~Chat();
    void reg(UserName u_name, char _pass[], int pass_length);

    void del(UserName u_name);
    bool login(UserName u_name, char _pass[], int pass_length);

private:
    enum enPairStatus
    {
        free,
        engaged,
        deleted
    };

    struct Pair
    { // пара ключ-значение

        Pair() : user_name(""),
                 user_pass(0),
                 status(enPairStatus::free)
        {
        }
        Pair(UserName u_name, uint *u_pass) : user_pass(u_pass),
                                              status(enPairStatus::engaged)
        {
            for (int i{0}; i < NAMELENGTH; i++)
                user_name[i] = u_name[i];
            memcpy(user_name, u_name, NAMELENGTH);
        }
        Pair &operator=(const Pair &other)
        {
            user_pass = other.user_pass;
            memcpy(user_name, other.user_name, NAMELENGTH);
            status = other.status;

            return *this;
        }

        bool operator==(const Pair &other)
        {
            return status == other.status &&
                   (status != enPairStatus::engaged || (user_pass == other.user_pass && !strcmp(user_name, other.user_name)));
        }

        UserName user_name;
        uint *user_pass;

        enPairStatus status;
    };

    int hash_func(UserName u_name, int offset);

    Pair *array;
    int mem_size;
    int count;
};