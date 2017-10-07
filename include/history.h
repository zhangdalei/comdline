#ifndef HISTORY_H_INCLUDED
#define HISTORY_H_INCLUDED

/* The structure used to store a history entry. */
typedef struct _hist_entry {
  char *line;
  char *data;
} HIST_ENTRY;

extern void add_history ();
extern HIST_ENTRY *next_history ();
extern void list_history();

extern int history_length;
extern int max_input_history;

#endif // HISTORY_H_INCLUDED
