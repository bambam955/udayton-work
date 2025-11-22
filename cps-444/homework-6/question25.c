#include <stdio.h>
#include "question25.h"

#define CSIZE 4

void enter_scores(struct student *s)
{
    printf("Enter three scores for %s %s: ", s->name.first, s->name.second);
    for (int i = 0; i < 3; ++i)
    {
        scanf("%f", &s->grades[i]);
    }
}

void calc_avg_score(struct student *s)
{
    float total = 0;
    for (int i = 0; i < 3; ++i)
    {
        total += s->grades[i];
    }

    s->avg_score = total / 3;
}

void print_student(struct student *s)
{
    printf("Name: %s %s, Grades: %.1f %.1f %.1f, Avg grade: %.2f\n",
           s->name.first, s->name.second, s->grades[0], s->grades[1], s->grades[2], s->avg_score);
}

void question25()
{
    // part c
    struct student students[CSIZE] =
        {
            {{"Gary", "Edward"}},
            {{"Larry", "Howard"}},
            {{"Jerry", "Coward"}},
            {{"Harry", "Cowherd"}},
        };

    for (int i = 0; i < CSIZE; ++i)
    {
        // part d
        enter_scores(&students[i]);
        // part e
        calc_avg_score(&students[i]);
    }

    // part f
    for (int i = 0; i < CSIZE; ++i)
    {
        print_student(&students[i]);
    }

    // part g
    for (int i = 0; i < 3; ++i)
    {
        float total = 0;
        for (int j = 0; j < CSIZE; ++j)
        {
            total += students[j].grades[i];
        }
        printf("Class avg, grade %d: %.2f\n", i + 1, total / CSIZE);
    }
    float avg_avg_total = 0;
    for (int i = 0; i < CSIZE; ++i)
    {
        avg_avg_total += students[i].avg_score;
    }
    printf("Class avg for all grades: %.2f\n", avg_avg_total / CSIZE);
}
