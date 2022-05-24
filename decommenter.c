#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

enum State
{
    NORMAL,    // normal state
    STRING,    // the text is inside double quote
    CHARACTER, // test inside single quote
    COMMENT,   // inside comment
};

enum State state = NORMAL;    // Set initial state to NORMAL
int commentEnteringLine = -1; // Line where comment started
int currentLine = 1;

/*
 * Handles STRING LITERAL state
 */
enum State stringLiteralStateHandler(int c)
{
    putchar(c);
    if (c == '"') // if ending comes
        return NORMAL;
    return STRING;
};

/**
 * Handles the CHARACTER LITERAL state
 */
enum State characterLiteralStateHandler(int c)
{
    putchar(c);
    if (c == '\'') // if closing comes
        return NORMAL;
    return CHARACTER;
};

/**
 * Handles the NORMAL state
 */
enum State normalStateHandler(int c)
{

    if (c == '"' || c == '\'')
    {
        putchar(c);
        return c == '"' ? STRING : CHARACTER;
    }

    if (c == '/')
    {
        char temp = getchar();

        if (temp == '*')
        {
            putchar(' ');
            commentEnteringLine = currentLine;
            return COMMENT;
        }

        putchar(c);
        if (temp == EOF)
            return NORMAL;

        putchar(temp);
    }
    else
    {
        putchar(c);
    }

    return NORMAL;
}

/*
    Handles the COMMENT state
*/
enum State commentStateHandler(int c)
{
    if (c == '*')
    {
        char temp = getchar();
        if (temp == EOF)
            return COMMENT;
        if (temp == '/')
            return NORMAL;
    }

    if (c == '\n')
    {
        putchar(c);
    }

    return COMMENT;
}

int main()
{
    int c;

    while ((c = getchar()) != EOF)
    {
        if (c == '\n')
            currentLine++;

        switch (state)
        {
        case NORMAL:
            state = normalStateHandler(c);
            break;
        case COMMENT:
            state = commentStateHandler(c);
            break;
        case STRING:
            state = stringLiteralStateHandler(c);
            break;
        case CHARACTER:
            state = characterLiteralStateHandler(c);
            break;
        }
    }

    if (state == COMMENT)
    {
        fprintf(stderr, "Error: line %d: unterminated comment", commentEnteringLine);
        exit(-1);
    }

    exit(0);
}