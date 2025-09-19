/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keycodes.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohkhan <mohkhan@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 11:56:39 by mohkhan           #+#    #+#             */
/*   Updated: 2025/09/10 11:56:40 by mohkhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYCODES_H
# define KEYCODES_H

// Platform detection
# ifdef __APPLE__
	// macOS keycodes
typedef enum e_keycodes
{
	KEY_W = 13,
	KEY_A = 0,
	KEY_S = 1,
	KEY_D = 2,
	KEY_LEFT = 123,
	KEY_RIGHT = 124,
	KEY_UP = 126,
	KEY_DOWN = 125,
	KEY_ESC = 53
}	t_keycodes;

# elif defined(__linux__)

typedef enum e_keycodes
{
	// Linux keycodes
	KEY_W = 119,
	KEY_A = 97,
	KEY_S = 115,
	KEY_D = 100,
	KEY_LEFT = 65361,
	KEY_RIGHT = 65363,
	KEY_UP = 65362,
	KEY_DOWN = 65364,
	KEY_ESC = 65307
}	t_keycodes;

# endif

#endif
