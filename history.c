#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "history.h"

static HIST_ENTRY **the_history = (HIST_ENTRY **)NULL;

/* If HISTORY_STIFLED is non-zero, then this is the maximum number of
   entries to remember. 最大历史数量  */
int max_input_history = 100;

/* The current location of the interactive history pointer.  Just makes
   life easier for outside callers. */
static int history_offset = 0;

/* The number of strings currently stored in the input_history list. */
int history_length = 0;

/* The current number of slots allocated to the input_history. */
static int history_size = 0;

/* The number of slots to increase the_history by. */
#define DEFAULT_HISTORY_GROW_SIZE 50
#define savestring(x) strcpy (malloc (1 + strlen (x)), (x))
int history_base = 1;

void
add_history (string)
     char *string;
{
  HIST_ENTRY *temp;

  if (history_length == max_input_history)
    {
      int i;
      /* 历史存储长度超过最大长度后，移除移除第一个位置的历史记录来
         来腾出空间	  */
      if (the_history[0])
	{
	  free (the_history[0]->line);
	  free (the_history[0]);
	}

      /* Copy the rest of the entries, moving down one slot. */
      for (i = 0; i < history_length; i++)
		the_history[i] = the_history[i + 1];

      history_base++;

    }
  else
    {
      if (!history_size)
	{
	  history_size = DEFAULT_HISTORY_GROW_SIZE;
	  the_history = (HIST_ENTRY **)malloc (history_size * sizeof (HIST_ENTRY *));
	  history_length = 1;

	}
      else
	{
	  if (history_length == (history_size - 1))
	    {
	      history_size += DEFAULT_HISTORY_GROW_SIZE;
	      the_history = (HIST_ENTRY **)
		realloc (the_history, history_size * sizeof (HIST_ENTRY *));
	    }
	  history_length++;
	}
}

  temp = (HIST_ENTRY *)malloc (sizeof (HIST_ENTRY));
  temp->line = savestring (string);
  temp->data = (char *)NULL;

  the_history[history_length] = (HIST_ENTRY *)NULL;
  the_history[history_length - 1] = temp;
}

/* Move history_offset forward to the next history entry, and return
   a pointer to that entry.  If there is no next entry then return a
   NULL pointer. */
HIST_ENTRY *
next_history ()
{
  if (history_offset == history_length)
    return ((HIST_ENTRY *)NULL);
  else
    return (the_history[history_offset++]);
}

/* 遍历命令历史记录 */
void list_history()
{
    HIST_ENTRY* get_com = NULL;
    while(( get_com = next_history()) != NULL){
        HIST_ENTRY* com = get_com;
        printf("  %d  %s", history_offset, com->line);
    }
	history_offset = 0;
}

