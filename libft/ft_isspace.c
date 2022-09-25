/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcombeau <mcombeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 13:53:06 by mcombeau          #+#    #+#             */
/*   Updated: 2022/09/25 14:52:20 by mcombeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	DESCRIPTION :
	The function ft_isspace checks whether c is a space character or not.

	RETURN VALUE:
	Non-zero if c is a space, zero if not.
*/

int	ft_isspace(int c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\v' || c == '\f')
		return (c);
	return (0);
}
