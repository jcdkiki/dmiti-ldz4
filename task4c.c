#include <stdio.h>
#include <math.h>
#include "common.h"

#define N_ROUNDS 100000
#define N_EPOCH 1000

static const int weights[4] = { 6, -5, -4, 8 };

int scores[N_ROUNDS];
int total_score = 0;
double expected_value = 0;
double score_avg = 0;
double dispersion = 0;
double expected_sko = 0;
double real_sko = 0;
int a_balls[2] = { 1000, 1000 };
int b_balls[2] = { 1000, 1000 };

double a_probability()
{
    return (double)a_balls[1] / (double)(a_balls[0] + a_balls[1]);
}

double b_probability()
{
    return (double)b_balls[1] / (double)(b_balls[0] + b_balls[1]);
}

double probabilities(int i)
{
    switch (i) {
        case 0: return (1 - a_probability())*(1 - b_probability());
        case 1: return (1 - a_probability())*b_probability();
        case 2: return a_probability()*(1 - b_probability());
        case 3: return a_probability()*b_probability();
    }
    return 0;
}

int run_round()
{
    int row = random_bit(a_probability());
    int column = random_bit(b_probability());

    return weights[row*2 + column];
}

void calculate_expected_value()
{
    for (int i = 0; i < 4; i++) {
        expected_value += weights[i] * probabilities(i);
    }
}

void calculate_dispersion()
{
    for (int i = 0; i < 4; i++) {
        double diff = (weights[i] - expected_value);
        dispersion += diff*diff * probabilities(i);
    }
}

void calculate_real_sko()
{
    for (int i = 0; i < N_ROUNDS; i++) {
        double diff = (scores[i] - score_avg);
        real_sko += diff*diff;
    }

    real_sko = sqrt(real_sko / N_ROUNDS);
}

void train()
{
    for (int i = 0; i < N_EPOCH; i++) {
        int row = random_bit(a_probability());
        int column = random_bit(b_probability());
        int result = weights[row*2 + column];

        a_balls[row] += result;
        b_balls[column] -= result;
    }
}

int main()
{
    train();

    for (int i = 0; i < N_ROUNDS; i++) {
        scores[i] = run_round();
        total_score += scores[i];
    }

    score_avg = (double)total_score / (double)N_ROUNDS;

    calculate_expected_value();
    calculate_dispersion();
    
    expected_sko = sqrt(dispersion);
    calculate_real_sko();
    
    printf("всего очков:      %d\n", total_score);
    printf("в среднем за ход: %lf\n", score_avg);
    printf("мат. ожидание:    %lf\n", expected_value);
    printf("дисперсия:        %lf\n", dispersion);
    printf("ожидаемое СКО:    %lf\n", expected_sko);
    printf("полученное СКО:   %lf\n", real_sko);

    printf("\nшары:\n");
    printf("  игрок А: %d красных, %d синих\n", a_balls[0], a_balls[1]);
    printf("  игрок Б: %d красных, %d синих\n", b_balls[0], b_balls[1]);
}
