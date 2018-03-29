/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutantstack.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skholodn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 17:40:19 by skholodn          #+#    #+#             */
/*   Updated: 2017/11/09 17:40:21 by skholodn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MUTANTSTACK_H
# define MUTANTSTACK_H

#include <iostream>
#include <stack>
#include <list>


template <class T>
class MutantStack : public std::list<T>
{
	
public:
	typedef typename std::list<T>::iterator iterator;
	MutantStack() {}
	MutantStack(MutantStack const & src) : std::list<T>(src){ }
	~MutantStack() { }
	using 	std::list<T>::operator=;

//	iterator	begin() { return begin(); }
//	iterator	end() { return end(); }
};

#endif
