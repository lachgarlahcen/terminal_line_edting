#ifndef FT_SELECT_H
# define FT_SELECT_H
# include <stdio.h>
# include <stdlib.h>
# include <termcap.h>
# include <unistd.h>
# include <termios.h>
# include <signal.h>
# include <sys/ioctl.h>
# include "libft/libft.h"
# define BUFF_SIZE 4096
# define LEFT_K 4479771
# define TOP_K 4283163
# define RIGHT_K 4414235
# define BOTTOM_K 4348699
# define SPACE_K 32
# define DEL_K 2117294875
# define BACK_K 127
# define ESC_K 27
# define TAB_K 9
# define DELALL_K 42
# define REV_K 5921563
# define HOME_K 4741915
# define END_K 4610843
# define COLS (tgetnum("co"))
# define ROWS (tgetnum("li"))
# define SO (tgetstr("so", NULL))
# define SE (tgetstr("se", NULL))
# define CL (tgetstr("cl", NULL))
# define CM (tgetstr("cm", NULL))
# define VE (tgetstr("ve", NULL))
# define VI (tgetstr("vi", NULL))
# define US (tgetstr("us", NULL))
# define TE (tgetstr("te", NULL))
# define TI (tgetstr("ti", NULL))
# define CE (tgetstr("ce", NULL))
# define CR (tgetstr("cr", NULL))
# define LE (tgetstr("le", NULL))
# define ND (tgetstr("nd", NULL))
# define CD (tgetstr("cd", NULL))
# define CH (tgetstr("ch", NULL))
# define SC (tgetstr("sc", NULL))
# define RC (tgetstr("rc", NULL))
# define AL (tgetstr("AL", NULL))
# define DO (tgetstr("do", NULL))
# define NORM (tgetstr("me", NULL))
# define MSG1 (ft_putstr_fd("Error occured\n", 2))
# define MSG2 (ft_putstr_fd("Not enough room.\n", 2))
# define MSG3 (ft_putstr_fd("No arguments received.\n", 2))
# define ERROR_EXIT {MSG1;exit(0);}
# define WRONG_SIZE ({MSG2;return;})
# define NO_ARG {MSG3;exit(0);}

typedef struct		s_line
{
	int		cur;
	int		len;
	long	key;
	struct winsize w;
	struct 	s_point *init_p;
	struct 	s_point *cur_p;
	char	chars[BUFF_SIZE];
}					t_line;
typedef	 struct	s_key
{
	long key;
	void (*f)(t_line *l);
} 			t_key;
typedef struct 	s_point
{
	int r;
	int c;
}				t_point;

void		right_key(t_line *l);
void		left_key(t_line *l);
void		esc_key(t_line *l);
void		delete(t_line *l);
void		mines(t_point *p, t_line *l);
void		plus(t_point *p, t_line *l, int b);
void		default_term_mode(void);


#endif