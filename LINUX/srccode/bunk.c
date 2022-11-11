#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdint.h>
#include <inttypes.h>
#include <string.h>
#include <unistd.h>

// Assigning only 8 bits
int8_t option_value = 0;
// File name
char file_name[101];
// Criterion can be a decimal
float criterion;
int attended = 0;
int total = 0;

void calculate();
void create();
int load(int call);
void insert(int call);
void update();
void delete ();
void myflush(FILE *in);
void mypause(void);

int main(int argc, char *argv[])
{
    // Incorrect Usage
    if (argc != 2)
    {
        printf("Usage\nLINUX: ./bunk {criterion}\nWINDOWS: bunk {criterion}\n");
        exit(1);
    }
    // Incorrect criterion range
    if (atof(argv[1]) > 100 || atof(argv[1]) <= 0)
    {
        printf("\033[0;31mError 101 : Criterion out of range\033[0;37m\n");
        exit(1);
    }
    criterion = atof(argv[1]);
    option_value = 0;

    while (option_value != 6)
    {
        printf("\n\n\t\033[0;36m***BUNK***\n");
        printf("\t  ______\n");
        printf("\n\n\033[0;37m 1. CALCULATE");
        printf("\n 2. CREATE");
        printf("\n 3. LOAD");
        printf("\n 4. UPDATE");
        printf("\n 5. DELETE");
        printf("\n 6. EXIT");
        printf("\n\nEnter your choice number: ");
        scanf("%"SCNd8, &option_value);

        switch (option_value)
        {
            case 1:
                calculate();
                break;
            case 2:
                create();
                break;
            case 3:
                load(0);
                break;
            case 4:
                update();
                break;
            case 5:
                delete ();
                break;
            case 6:
                printf("\n");
                return 0;
            default:
                printf("\nOption value out of range\n\n");
                return 1;
        }
        if (option_value == 1 || option_value == 5)
        {
            printf("\n\033[0;37mDo you want to exit the program (\033[0;32my\033[0;37m/\033[0;31mn\033[0;37m): ");
            char *x = malloc(sizeof(char));
            scanf("%s", x);
            if (tolower(*x) == 'y')
            {
                exit(0);
            }
            free(x);
            printf("\n\t\033[0;33m    ***---***---***\033[0;37m\n\n");
        }
    }
    return 0;
}

void calculate()
{
    printf("Make sure to LOAD the file\n");
    if (attended == 0 || total == 0)
    {
        printf("\033[0;31mFile not loaded\n\033[0;37m");
        myflush(stdin);
        mypause();
    }
    printf("\033[0;37mDo you want to LOAD the file (\033[0;32my\033[0;37m/\033[0;31mn\033[0;37m): ");
    char *x = malloc(sizeof(char));
    scanf("%s", x);
    if (tolower(*x) == 'y')
    {
        load(0);
    }
    free(x);
    float attendance = ((float)attended / (float)total) * 100.0;
    printf("\n\a\033[1:37mCurrent attendance percentage: \033[0:37m");

    if (attendance < criterion)
    {
        printf("\033[1;31m%.2f", attendance);
        int count = 0;
        while (attendance < criterion)
        {
            count++;
            attendance = (((float)attended + count) / ((float)total + count)) * 100.0;
        }
        count--;
        printf("\n\033[1;31mYou need to attened %d more classes to get back on track\n\033[0;37m", count);
    }
    else
    {
        printf("\033[1;32m%.2f", attendance);
        int count = 0;
        while (attendance >= criterion)
        {
            count++;
            attendance = (((float)attended) / ((float)total + count)) * 100.0;
        }
        count--;
        if (count >= 1)
        {
            printf("\n\033[1;32mYou can take leave for %d %s\n\033[0;37m", count, (count > 1) ? "days" : "day");
        }
        else
        {
            printf("\n\033[1;37mYou are on track, but can't take any leave\n");
        }
    }
    myflush(stdin);
    mypause();
}

void create()
{
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    printf("\t---------\n\n");
    printf("Name of Profile: ");
    scanf("%s", file_name);
    strcat(file_name, ".txt");
    FILE *fptr = fopen(file_name, "r");
    if (fptr != NULL)
    {
        printf("\033[0;31mFile already exists\033[0;37m\n");
        printf("\033[0;37mWarning: Do you want to overwrite the file (\033[0;32my\033[0;37m/\033[0;31mn\033[0;37m): ");
        char *x = malloc(sizeof(char));
        scanf("%s", x);
        if (tolower(*x) != 'y')
        {
            free(x);
            return;
        }
        free(x);
        FILE *file = fopen(file_name, "w");
        fclose(file);
        printf("\a\033[0;32mFile Overwritten\033[0;37m\n");
        myflush(stdin);
        mypause();
        printf("\a\033[0;34mThe program will terminate after file creation to save the file.\n\033[0;37m");
        myflush(stdin);
        mypause();
        insert(0);
        exit(0);
    }
    FILE *file = fopen(file_name, "w");
    fclose(file);
    printf("\a\033[0;32mFile Created\033[0;37m\n\n");
    printf("\a\033[0;34mThe program will terminate after file creation to save the file.\n\033[0;37m");
    myflush(stdin);
    mypause();
    insert(0);
    exit(0);
}

int load(int call)
{
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    printf("\t---------\n\n");
    attended = 0;
    total = 0;
    printf("Name of Profile: ");
    scanf("%s", file_name);
    strcat(file_name, ".txt");
    FILE *fptr = fopen(file_name, "r");
    if (fptr == NULL)
    {
        printf("\033[0;31mFile not found\n\n");
        if (call == 1)
        {
            myflush(stdin);
            mypause();
            return 1;
        }
        printf("\033[0;37mDo you want to create a new file (\033[0;32my\033[0;37m/\033[0;31mn\033[0;37m): ");
        char *x = malloc(sizeof(char));
        scanf("%s", x);
        if (tolower(*x) != 'y')
        {
            free(x);
            return 0;
        }
        free(x);
        FILE *file = fopen(file_name, "w");
        fclose(file);
        printf("\a\033[0;32mFile Created\033[0;37m\n\n");
        printf("\a\033[0;34mThe program will terminate after file creation to save the file.\n\033[0;37m");
        myflush(stdin);
        mypause();
        insert(0);
        exit(0);
    }
    int flag = 0;
    char c;
    while (fread(&c, sizeof(char), 1, fptr))
    {
        if (c == ' ')
        {
            flag = 1;
            continue;
        }
        if (flag == 0)
        {
            int value = c - 48;
            attended *= 10;
            attended += value;
        }
        else
        {
            int value = c - 48;
            total *= 10;
            total += value;
        }
    }
    printf("You have attended %d sessions out of %d sessions\n", attended, total);
    myflush(stdin);
    mypause();
    fclose(fptr);
    return 0;
}

void insert(int call)
{
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    printf("\t---------\n\n");
    FILE *fptr = fopen(file_name, "w");
    int *hours_attended = malloc(sizeof(int));
    int *total_hours = malloc(sizeof(int));
    char *h_a = malloc(sizeof(char) * 101);
    char *t_h = malloc(sizeof(char) * 101);
    while (1)
    {
        printf("How many sessions did you have: ");
        scanf("%d", total_hours);
        printf("How many sessions did you attend: ");
        scanf("%d", hours_attended);
        if (*hours_attended <= *total_hours)
        {
            break;
        }
        printf("\a\033[0;31mReally?\033[0;37m\n\n");
    }
    sprintf(h_a, "%d", *hours_attended);
    sprintf(t_h, "%d", *total_hours);

    fputs(h_a, fptr);
    fputs(" ", fptr);
    fputs(t_h, fptr);

    free(hours_attended);
    free(total_hours);
    free(h_a);
    free(t_h);
    if (call == 1)
    {
        return;
    }
    printf("\a\033[0;32mData Inserted\n\033[0;37m");
    myflush(stdin);
    mypause();
    return;
}

void update()
{
    int response = load(1);
    if (response == 1)
    {
        return;
    }
    printf("\nDo you want to update the record (\033[0;32my\033[0;37m/\033[0;31mn\033[0;37m): ");
    char *x = malloc(sizeof(char));
    scanf("%s", x);
    if (tolower(*x) != 'y')
    {
        free(x);
        return;
    }
    free(x);
    insert(1);
    printf("\a\033[0;32mUpdated Successfully\033[0;37m\n");
    printf("\a\033[0;34mThe program will terminate after file creation to save the file.\n\033[0;37m");
    myflush(stdin);
    mypause();
    exit(0);
}

void delete ()
{
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    printf("\t---------\n\n");
    printf("Name of Profile: ");
    scanf("%s", file_name);
    strcat(file_name, ".txt");
    FILE *fptr = fopen(file_name, "r");
    if (fptr == NULL)
    {
        printf("\033[0;31mFile not found\n\n\a\033[0;37m");
        myflush(stdin);
        mypause();
        return;
    }
    fclose(fptr);
    printf("\nDo you want to delete the record [This is cannot be undone] (\033[0;32my\033[0;37m/\033[0;31mn\033[0;37m): ");
    char *x = malloc(sizeof(char));
    scanf("%s", x);
    if (tolower(*x) != 'y')
    {
        free(x);
        return;
    }
    free(x);
    if (remove(file_name) == 0)
    {
        printf("\a\033[0;32mDeleted successfully\a\033[0;37m\n");
    }
    else
    {
        printf("\a\033[0;31mUnable to delete the file\033[0;37m\n");
    }
    myflush(stdin);
    mypause();
}

void myflush(FILE *in)
{
    int ch;

    do
    {
        ch = fgetc(in);
    }
    while (ch != EOF && ch != '\n');

    clearerr(in);
}

void mypause(void)
{
    printf("\033[0;34mPress [Enter] to continue . . .\033[0;37m");
    fflush(stdout);
    getchar();
}