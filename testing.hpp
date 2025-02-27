/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 18:51:18 by mhuszar           #+#    #+#             */
/*   Updated: 2025/01/05 22:59:12 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <climits>
#include <cstddef>
#include <cstdint>
#include <string>

extern std::size_t passed;

//for testing
void assert_eq(uint32_t a, uint32_t b);
void assert_eq(std::string a, std::string b);
void display_result();