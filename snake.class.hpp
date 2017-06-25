/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   snake.class.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thumavu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/25 13:40:58 by thumavu           #+#    #+#             */
/*   Updated: 2017/06/25 13:41:01 by thumavu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SNAKE_CLASS_HPP
# define SNAKE_CLASS_HPP

# include <iostream>
# include <vector>
# include <cstdlib>
# include <ncurses.h>

struct snakepart{
    int width;
    int height;
    snakepart(int column, int row);
    snakepart();
};

class snake_class{
    public:
        snake_class();
        ~snake_class();
        void    start(); //start the entire snake game & called explicitly

    private:
        //initialised in the constructore
        int     points; //points or score 
        int     maxwidth; 
        int     maxheight; 
        int     del; //delay

        char    direction; //left,right,up, down or exit
        char    partchar; //the snake charecter
        char    oldalchar; //the edge of the terminal
        char    foo; //food
        bool    get; //becomes true if the snake gets the food
       
        snakepart food; // the location of the food
        std::vector<snakepart> snake; // will represent the part of the snake class structure

        void    putfood(); //calculate the part of the food: NOTE: not at the adges
        bool    collision(); //if the snake eats itself or hits the wall
        void    movesnake(); //gets the charecter and move the snake

};
#endif
