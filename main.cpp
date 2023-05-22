#include <iostream>
#include <string>
#include "headers/Chat.h"

int main(int argc, const char *argv[])
{
    Chat c;

    char login1[] = "user1";
    char pass1[] = "pass1";

    char login2[] = "user2";
    char pass2[] = "pass2";

    char wrongLogin[] = "wLogin";
    char wrongPass[] = "wPass";

    c.reg(login1, pass1, 6);
    c.reg(login2, pass2, 6);

    // Верные логин и пароль
    bool userLogin1 = c.login(login1, pass1, 6); 
    bool userLogin2 = c.login(login2, pass2, 6);

    // Неверные логин пароль в разных комбинациях
    bool wrongLogin1 = c.login(wrongLogin, wrongPass, 6);
    bool wrongLogin2 = c.login(login1, wrongPass, 6);
    bool wrongLogin3 = c.login(wrongLogin, pass2, 6);

    return 0;
}