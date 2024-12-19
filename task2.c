#include <stdio.h>
#include <math.h>
#include "common.h"

#define N_ROUNDS 100000

static const double a_probability = 0.5;
static const  double b_probability = 0.5;

static int weights[4] = { 6, -5, -4, 8 };

static double probabilities[4] = {
    (1 - a_probability)*(1 - b_probability),
    (1 - a_probability)*b_probability,
    a_probability*(1 - b_probability),
    a_probability*b_probability
};

int scores[N_ROUNDS];
int total_score = 0;
double expected_value = 0;
double score_avg = 0;
double dispersion = 0;
double expected_sko = 0;
double real_sko = 0;

int run_round()
{
    int row = random_bit(a_probability);
    int column = random_bit(b_probability);

    return weights[row*2 + column];
}


void calculate_expected_value()
{
    for (int i = 0; i < 4; i++) {
        expected_value += weights[i] * probabilities[i];
    }
}

void calculate_dispersion()
{
    for (int i = 0; i < 4; i++) {
        double diff = (weights[i] - expected_value);
        dispersion += diff*diff * probabilities[i];
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

int main()
{
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
}
