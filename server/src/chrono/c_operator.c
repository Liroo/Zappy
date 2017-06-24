/*
** chrono_operator.c for chrono_operator in /Users/pierre/Epitech/PSU/Zappy/server
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Wed Jun 21 15:37:11 2017 Pierre Monge
** Last update Thu Jun 22 21:27:34 2017 Pierre Monge
*/

#include "chrono.h"


int	compare_time(struct timespec ts1, struct timespec ts2)
{
  if (ts1.tv_sec > ts2.tv_sec)
    return (1);
  else if (ts1.tv_sec < ts2.tv_sec)
    return (-1);
  if (ts1.tv_nsec > ts2.tv_nsec)
    return (1);
  else if (ts1.tv_nsec < ts2.tv_nsec)
    return (-1);
  return (0);
}

struct timespec		add_time(struct timespec ts1, struct timespec ts2)
{
  struct timespec	ret;

  if (ts1.tv_nsec + ts2.tv_nsec >= BILLION)
    {
      ret.tv_sec = ts1.tv_sec + ts2.tv_sec + 1;
      ret.tv_nsec = ts1.tv_nsec + ts2.tv_nsec - BILLION;
    }
  else
    {
      ret.tv_sec = ts1.tv_sec + ts2.tv_sec;
      ret.tv_nsec = ts1.tv_nsec + ts2.tv_nsec;
    }
  return (ret);
}

struct timespec		sub_time(struct timespec ts1, struct timespec ts2)
{
  struct timespec	ret;

  if (ts1.tv_nsec - ts2.tv_nsec < 0)
    {
      ret.tv_sec = ts1.tv_sec - ts2.tv_sec - 1;
      ret.tv_nsec = ts1.tv_nsec - ts2.tv_nsec + BILLION;
    }
  else
    {
      ret.tv_sec = ts1.tv_sec - ts2.tv_sec;
      ret.tv_nsec = ts1.tv_nsec - ts2.tv_nsec;
    }
  return (ret);
}
