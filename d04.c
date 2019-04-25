#include <assert.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "dmb/vec.h"
#include "dmb/io.h"

const bool SLEEP = 0;
const bool AWAKE = 1;

bool is_shift_start(char *s) {
  return strstr(s, "begins shift") != NULL;
}

bool is_sleep(char *s) {
  return strstr(s, "falls asleep") != NULL;
}

typedef bool State;

typedef struct Date {
// i am an optimist 
  uint64_t year;
  uint8_t  month;
  uint8_t  day;
} Date;

typedef struct Time {
  uint8_t  hour;
  uint8_t  minute;
} Time;

typedef struct Event {
  State state;
  Date  date;
  Time  time;
} Event;

typedef uint32_t GuardId;

GuardId parse_shift_start(char *s) {
  uint32_t y, m, d, H, M, id;

  int n_scanned = sscanf(
    s, "[%d-%d-%d %d:%d] Guard #%d begins shift",
         &y,&m,&d,&H,&M,       &id
  );

  assert(n_scanned == 6);

  return id;
}

Event parse_sleep(char *s) {
  uint32_t y, m, d, H, M;

  int n_scanned = sscanf(s, 
    "[%d-%d-%d %d:%d] falls asleep", 
      &y,&m,&d,&H,&M
  ); 
  assert(n_scanned == 5);

  Event ev = {
    .state = SLEEP,
    .date = { .year = y, .month = m, .day = d },
    .time = { .hour = H, .minute = M }
  };

  return ev;
}

Event parse_awake(char *s) {
  uint32_t y, m, d, H, M;

  int n_scanned = sscanf(s, 
    "[%d-%d-%d %d:%d] wakes up", 
      &y,&m,&d,&H,&M
  ); 

  assert(n_scanned == 5);

  Event ev = {
    .state = AWAKE,
    .date = { .year = y, .month = m, .day = d },
    .time = { .hour = H, .minute = M }
  };

  return ev;
}

Event parse_event(char *s) {
  return (is_sleep(s) ? parse_sleep : parse_awake)(s);
}

void parse_and_print(char *s) {
  int guard_id = -1;

  if (is_shift_start(s)) {
    guard_id = parse_shift_start(s);
    printf("%d starting\n", guard_id);
  } else {
    Event e = parse_event(s);
    printf(" awake?: %d", e.state);

    Date D = e.date;
    printf(" %llu-%d-%d", D.year, D.month, D.day);

    Time T = e.time;
    printf(" %d:%d\n", T.hour, T.minute);
  }
}

int main(int argc, char *argv[]) {
  Vec *lines = IO_read_input(argv[1]);
  V_each(lines, parse_and_print);
}
