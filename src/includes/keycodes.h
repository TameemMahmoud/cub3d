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
#define KEYCODES_H

// Platform detection
#ifdef __APPLE__
    // macOS keycodes
    #define KEY_W 13
    #define KEY_A 0
    #define KEY_S 1
    #define KEY_D 2
    #define KEY_LEFT 123
    #define KEY_RIGHT 124
    #define KEY_UP 126
    #define KEY_DOWN 125
    #define KEY_ESC 53
    #define PLATFORM_NAME "macOS"
#elif defined(__linux__)
    // Linux keycodes
    #define KEY_W 119
    #define KEY_A 97
    #define KEY_S 115
    #define KEY_D 100
    #define KEY_LEFT 65361
    #define KEY_RIGHT 65363
    #define KEY_UP 65362
    #define KEY_DOWN 65364
    #define KEY_ESC 65307
    #define PLATFORM_NAME "Linux"
#else
    // Default/fallback keycodes (same as macOS)
    #define KEY_W 13
    #define KEY_A 0
    #define KEY_S 1
    #define KEY_D 2
    #define KEY_LEFT 123
    #define KEY_RIGHT 124
    #define KEY_UP 126
    #define KEY_DOWN 125
    #define KEY_ESC 53
    #define PLATFORM_NAME "Unknown"
#endif

#endif
