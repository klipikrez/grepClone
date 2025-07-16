#include <stdio.h>
#include <string.h>
#include <unistd.h>

void ErrorMessage(char message[]);
void GrepClone(char search[], char path[]);
void HighlightPrint(char text[], char substring[]);

int main(int argc, char *argv[])
{

    switch (argc)
    {
    case 3:
    {
        GrepClone(argv[1], argv[2]);
        break;
    }
    default:
    {
        ErrorMessage("invalid arguments.\n/grepClone [searchString] [path to file]");
    }
    }

    return 0;
}

void GrepClone(char search[], char path[])
{
    if (search == NULL)
    {
        ErrorMessage("search string is null");
        return;
    }
    if (strlen(search) == 0)
    {
        ErrorMessage("search string is empty");
        return;
    }
    if (path == NULL)
    {
        ErrorMessage("path is null");
        return;
    }
    if (strlen(path) == 0)
    {
        ErrorMessage("path is empty");
        return;
    }
    if (access(path, F_OK) != 0)
    {
        ErrorMessage("path is invalid :(");
        return;
    }

    FILE *file = fopen(path, "r");
    if (!file)
    {
        ErrorMessage("file cant be opened");
        return;
    }

    char line[5052];
    int lineNumber = 0;
    while (fgets(line, sizeof(line), file))
    {
        lineNumber++;
        if (strstr(line, search))
        {
            printf("\e[32m");
            printf("\n[%d]: ", lineNumber);
            printf("\e[0m");
            HighlightPrint(line, search);
        }
    }

    return;
}

void HighlightPrint(char text[], char substring[])
{
    char *writer = text;
    int substringLength = strlen(substring);

    while (*writer)
    {
        char *match = strstr(writer, substring); // gde se pojavljuje substring u nasem tekstu

        if (!match) // ako nema onda samo ispisi i izadji
        {
            printf("%s", writer);
            break;
        }

        // pre crvene
        fwrite(writer, 1, match - writer, stdout);

        // crveno
        printf("\e[31m");
        fwrite(match, 1, substringLength, stdout);
        printf("\e[0m");

        writer = match + substringLength;
    }
}

void ErrorMessage(char message[])
{
    printf("\e[31mERROR:\e[0m %s\n", message);
    return;
}