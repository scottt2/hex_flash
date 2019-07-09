#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifdef _WIN32
#include <conio.h>
#else
#include <stdio.h>
#define clrscr() printf("\e[1;1H\e[2J")
#endif

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
  clrscr();
  srand(time(0));

  printf("\n\n*** Welcome to Hex Flash ***\n\n");
  printf("The world's worst game! (TM)\n\n");
  printf("--- Handy Dandy hex table ---\n");
  for (int i = 0; i < 16; i++) {
    printf("%01x:\t%d\t%d\n", i, i*16, i);
  }
  printf("_____________________________\n\n");
  printf("Instructions: Type the decimal version of each hex octal.\n");

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
