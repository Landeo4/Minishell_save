/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_int_overflow_checker.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 07:44:02 by vsozonof          #+#    #+#             */
/*   Updated: 2023/05/06 16:44:00 by vsozonof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//------------------------------------------------------------------------------
//						--- Int Overflow Handler ---
//------------------------------------------------------------------------------

// This function takes a string that is supposed to be converted
// into an integer.

// In order to convert the string to an integer, we need to make sure
// no integer overflow wil occur while doing the conversion.

// Step 1 : Check the len of the string and see if it's above INT_MIN's len.
// Step 2 : Convert the string to long (A to L) and compare the integer
// with both INT_MIN and INT_MAX

// If the argument failed one of the steps, an error will be returned.

//------------------------------------------------------------------------------

int	ft_int_overflow_checker(char *str)
{
	if (ft_strlen(str) > 11)
		return (pr_error("Integer overflow/underflow detected."));
	else if (ft_integer_checker(str) != 1)
		return (0);
	return (1);
}

int	ft_integer_checker(char *str)
{
	long	n;

	n = ft_atol(str);
	if (n > INT_MAX)
		return (pr_error("Integer overflow detected."));
	else if (n < INT_MIN)
		return (pr_error("Integer underflow detected."));
	return (1);
}
