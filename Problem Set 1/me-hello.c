#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Ask user its name
    string name = get_string("What's your name? ");

    // Simple print of giving a hello
    printf("hello, %s\n", name);
}
