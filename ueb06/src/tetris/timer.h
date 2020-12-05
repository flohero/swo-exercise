#ifndef TIMER_H
#define TIMER_H

#define STANDARD_PACE 48

#define FRAMES_PER_SECOND 60

typedef void (*timer_func)(void);

extern void timer_start(double itvl, timer_func on_tick);

extern void timer_fire(void);

extern void timer_stop(void);

extern void timer_resume(void);

#endif
