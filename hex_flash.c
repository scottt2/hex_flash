#include <stdio.h>
#include <stdlib.h>
#include <time.h>

_Bool correct_answer(int answer, int value) {
  return answer == value;
}

void new_value(int *value) {
  *value = rand() % 255;
}

int prompt_user(int value) {
  printf("What is %02x: ", value);

  int answer;
  if (scanf("%d", &answer) != 1) {
    while (fgetc(stdin) != '\n');
    return -1;
  }

  return (answer >= 0 && answer <= 255)
    ? answer
    : -1;
}

void update_stats(double const time, int *rights, double *right_avg) {
  *right_avg += time;
  *right_avg /= (double) ++*rights;
}

int main(void) {
  srand(time(0));

  int value;
  new_value(&value);

  int rights = 0;
  double right_avg = 0;
  int wrongs = 0;

  for (;;) {
    time_t start = time(0);

    if (correct_answer(prompt_user(value), value)) {
      update_stats(((double) (time(0) - start)), &rights, &right_avg);

      printf(
        "\n\n*** Correct! ***\nYour score is %d\nYour average time is %g seconds\n\n",
        rights,
        right_avg
      );

      new_value(&value);
    } else {
      printf("Incorrect :(\n");

      if (++wrongs > 2) {
        printf("\n\nThe answer was %d.\n\n", value);
        new_value(&value);
        wrongs = 0;
      }
    }
  }
}
