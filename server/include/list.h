/*
** list.h for list in /Users/pierre/Epitech/PSU/Zappy/server
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Tue Jun 13 21:38:49 2017 Pierre Monge
** Last update Fri Jun 16 00:38:42 2017 Pierre Monge
*/

#ifndef LIST_H
# define LIST_H

/*
** This is a kernel implementation set to the epitech norm
** We don't have access to kernel includes using global include "<" ">"
** this is why I decided to recode the list.h simplified
** and to use them for our projects
**
** This is a really basic implementation based on linux/list.h
**
** -- Pierre
*/

/*
** ps: removing macro multiline remove the only set a polymorphism stuff
** we should learn... Thx norm
*/

typedef struct	s_list_head
{
  struct	s_list_head *next;
  struct	s_list_head *prev;
}		t_list_head;

/*
** Returning the t_list_head element is usefull
** when the t_list_head is the first element of the structure
** It permit to cast the structure to a bigger struct
** which is sort of a container
*/
t_list_head	*list_init(t_list_head *list);

/*
** list_add - add a new entry
** new: new entry to be added
** head: list head to add it after
**
** Insert a new entry after the specified head.
** This is good for implementing stacks.
*/
t_list_head	*list_add(t_list_head *new,
			  t_list_head *prev,
			  t_list_head *next);

/*
** list_del - deletes entry from list.
** entry:	the element to delete from the list.
*/
t_list_head	*list_del(t_list_head *prev,
			  t_list_head *next);


# ifndef offsetof
#  include <stddef.h>
#  ifndef offsetof
#   define offsetof(st, m) ((size_t)(&((st *)0)->m))
#  endif
# endif

# define container_of(ptr, type, member)	\
  (type*)((char*)(ptr) - offsetof(type, member))

/*
** list_entry - get the struct for this entry
** ptr:		the &struct list_head pointer.
** type:	the type of the struct this is embedded in.
** member:	the name of the list_head within the struct.
*/
# define list_entry(ptr, type, member)		\
  container_of(ptr, type, member)

/*
** list_add_tail - add a new entry
** new:		new entry to be added
** head:	list head to add it before
**
** Insert a new entry before the specified head.
** This is useful for implementing queues.
*/
static inline t_list_head	*list_add_tail(t_list_head *new,
					       t_list_head *head)
{
  return (list_add(new, head->prev, head));
}

/*
** list_add_nose - add a new entry
** new:		new entry to be added
** head:	list head to add it before
**
** Insert a new entry after the specified head.
** This is useful for implementing stack.
*/
static inline t_list_head	*list_add_nose(t_list_head *new,
					       t_list_head *head)
{
  return (list_add(new, head, head->next));
}


/*
** list_get_first - get the first list
** head:	the head of the list
*/
static inline t_list_head	*list_get_first(t_list_head *head)
{
  return (head->next);
}

/*
** list_get_last - get the last list
** head:	the head of the list
*/
static inline t_list_head	*list_get_last(t_list_head *head)
{
  return (head->prev);
}

/*
** list_is_last - tests whether @list is the last entry in list @head
** list:	the entry to test
** head:	the head of the list
*/
static inline int	list_is_last(const t_list_head *list,
				     const t_list_head *head)
{
  return (list->next == head);
}

/*
** list_empty - tests whether a list is empty
** head:	the list to test.
*/
static inline int	list_empty(const t_list_head *head)
{
  return (head->next == head);
}

#endif /* !LIST_H */
