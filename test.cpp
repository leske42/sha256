/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 18:50:50 by mhuszar           #+#    #+#             */
/*   Updated: 2025/01/05 19:11:54 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "testing.hpp"

size_t passed = 0;

void assert_eq(uint32_t a, uint32_t b)
{
    if (a != b)
        throw ;
    passed++;
}

void assert_eq(std::string a, std::string b)
{
    if (a != b)
        throw ;
    passed++;
}

void assert_multiple(size_t a, size_t b)
{
    if (a % b != 0)
        throw ;
    passed++;
}

void display_result()
{
    std::cout << "\e[0;92mTotal tests ran and passed: " << passed << "\e[0m" << std::endl;
}