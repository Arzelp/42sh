/*
** my.h for my h in /include/
**
** Made by Frederic ODDOU
** Login oddou_f <frederic.oddou@epitech.eu>
**
** Started on  Sat Apr 16 11:25:05 2016 Frederic ODDOU
** Last update Sat Apr 16 11:25:05 2016 Frederic ODDOU
*/

#ifndef MY_H_
# define MY_H_

# include <stdbool.h>
# include <stdarg.h>

# define READ_SIZE (4096)

int		my_putchar(char 			c);
int		my_putstr_e(char 			*str);
int		my_putstr(char 				*str);

int		my_putnbr(int 				nbr,
			  int 				abso);
int		my_putnbr_u(unsigned int 		nbr);
int		my_putnbr_lld(long long 		nbr,
			      int 			abso);
int		my_putnbr_llu(unsigned long long	nbr);
int		my_putnbr_ld(long int 			nbr,
			     int 			abso);
int		my_putnbr_lu(unsigned long int 		nbr);
int		my_putnbr_hd(short int 			nbr,
			     int 			abso);
int		my_putnbr_hu(unsigned short int 	nbr);
int		my_putnbr_hhd(signed char 		nbr,
			      int 			abso);
int		my_putnbr_hhu(unsigned char 		nbr);

void		my_fptr(int 				i,
			va_list 			args,
			int 				*val,
			int 				*params);
void		my_fptr_diez(int 			i,
			     va_list 			args,
			     int *val, int *params);
void		my_fptr_next(int i, va_list args, int *val, int *params);
int		my_printf(const char *format, ...);
void		my_printf_exe(const char *format, va_list args, int *val);
int		my_printf_i(int i, int choice, int type);
int		my_printf_diez(const char *fmt, va_list ag, int *v, int *par);
int		my_printf_pourcent(const char *fmt, va_list ag, int *v, int i);
const char	*my_printf_check(const char *format, int i);
int		tab_printf_choice_long(const char *c);
int		tab_printf_choice_char(const char *c);
int		tab_printf_choice(const char *c);
void		my_printf_s(va_list list, int *val, int space, int where);
void		my_printf_c(va_list list, int *val, int space, int where);
void		my_printf_d(va_list list, int *val, int space, int where);
void		my_printf_o(va_list list, int *val, int space, int where);
void		my_printf_x(va_list list, int *val, int space, int where);
void		my_printf_X(va_list list, int *val, int space, int where);
void		my_printf_p(va_list list, int *val, int space, int where);
void		my_printf_b(va_list list, int *val, int space, int where);
void		my_printf_S(va_list list, int *val, int space, int where);
void		my_printf_u(va_list list, int *val, int space, int where);
void		my_printf_n(va_list list, int *val, int space, int where);
void		my_printf_lld(va_list list, int *val, int space, int where);
void		my_printf_llu(va_list list, int *val, int space, int where);
void		my_printf_ld(va_list list, int *val, int space, int where);
void		my_printf_lu(va_list list, int *val, int space, int where);
void		my_printf_hhd(va_list list, int *val, int space, int where);
void		my_printf_hhu(va_list list, int *val, int space, int where);
void		my_printf_hd(va_list list, int *val, int space, int where);
void		my_printf_hu(va_list list, int *val, int space, int where);
int		my_printf_S_space(char 		*var);
int		my_printf_count(const char 	*str);
int		my_printf_count_i(const char 	*str);
int		my_printf_count_neg(const char 	*str);
int		my_printf_count_plus(const char *str);
int		my_printf_count_zero(const char *str);
int		my_printf_cmoins(int where, int var);
int		my_printf_cplus(int where, int var);
int		my_printf_cspace(int where, int var);
void		my_printf_Do(va_list list, int *val, int space, int where);
void		my_printf_Dx(va_list list, int *val, int space, int where);
void		my_printf_DX(va_list list, int *val, int space, int where);
void		my_printf_lo(va_list list, int *val, int space, int where);
void		my_printf_lx(va_list list, int *val, int space, int where);
void		my_printf_lX(va_list list, int *val, int space, int where);
void		my_printf_lb(va_list list, int *val, int space, int where);
void		my_printf_Dlo(va_list list, int *val, int space, int where);
void		my_printf_Dlx(va_list list, int *val, int space, int where);
void		my_printf_DlX(va_list list, int *val, int space, int where);
int		my_add_space(int 	space);
int		my_inbr_int(int 				nbr,
				    int 				size);
int		my_inbr_unsignedlonglong(unsigned long long	nbr,
						 unsigned int		size);
int		my_inbr_longlong(long long			nbr,
					 int				size);
int		my_inbr_long(long 				nbr,
				     int 				size);
int		my_putnbr_base(long long	nb,
			       char 		*base);
int	my_add_zero(int 	space);
int	my_print_p_m(int	plus,
		     int	moins,
		     int	where,
		     int	var);



char		*get_next_line(const int	fd);
int		my_tab_len(char			**tab);
char		**my_tab_cpy(char		**tab);
bool		my_tab_free(char		**tab);
bool		my_tab_realloc(char		**tab,
			       char		*str);
bool		my_tab_delete_elem(char		**tab,
				   char		*str);

#endif
