/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   snake.class.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thumavu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/25 13:40:45 by thumavu           #+#    #+#             */
/*   Updated: 2017/06/25 13:40:50 by thumavu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "snake.class.hpp"
#include <unistd.h>

snakepart::snakepart(int column, int row){
    width = column;
    height = row;
}

snakepart::snakepart(){
    width = 0;
    height = 0;
}

snake_class::snake_class(){
    initscr(); //initialise the screen part of ncurses
    nodelay(stdscr, true); //the getch will not wait until the user press the key 
    keypad(stdscr, true); //allows us to use the keyboard
    noecho(); //at this point you can't enter anything at the screan you can only read
    curs_set(0); //curser to unvisible
    getmaxyx(stdscr, maxheight, maxwidth); //standard screen that set the max width and height
   
    //init a few variables
    partchar = (char)35; // char for the snake
    oldalchar = (char)219; // is a full rectangle
    foo  = '*'; // this is the char for the food
    food.width = 0; 
    food.height = 0;

    // will represent the snake. and will push back an alement to an array
    for (int i = 0; i < 4; i++){
        snake.push_back(snakepart(40 + i, 10)); 
    }

    points = 0;
    del = 110000; // it uses micro secands to delay
    get = false; // we init the food
    direction = 'l';
    srand(time(0)); //rendom generator
    putfood(); //will put food

    // creates the boader or the canvas of the game.
    for (int i = 0; i < maxwidth - 1; i++){
        move(0, i);
        addch(oldalchar); 
    }
    for (int i = 0; i < maxwidth - 1; i++){
        move(maxheight - 2, i);
        addch(oldalchar); 
    }
    for (int i = 0; i < maxheight - 1; i++){
        move(i, 0);
        addch(oldalchar); 
    }
    for (int i = 0; i < maxheight - 1; i++){
        move(i, maxwidth - 2);
        addch(oldalchar); 
    }//////////////////////
    
    //draw the snake to the screen
    for(int i = 0; i < snake.size(); i++){
        move(snake[i].height, snake[i].width);
        addch(partchar); 
    }

    move(maxheight - 1, 0);
    printw("%d", points);
    move(food.height, food.width);
    addch(foo);
    refresh(); //refresh the screen
}

snake_class::~snake_class(){
    nodelay(stdscr, false);
    getch(); // the will not auto exit
    endwin();
}

void snake_class::putfood(){
    while (1){
        int tmp_width = rand()%maxwidth + 1;
        int tmp_height = rand()%maxheight + 1;

        for (int i = 0; i < snake.size(); i++)
            //check if the food is in the boarder same as width or height 
            if(snake[i].width == tmp_width && snake[i].height == tmp_height)
                continue;
        //checks if the food is out of bound of the width or height 
        if(tmp_width >= maxwidth - 2 || tmp_height >= maxheight - 3)
            continue;

        food.width = tmp_width;
        food.height = tmp_height;
        break;
    }
    move(food.height, food.width);
    addch(foo);
    refresh();    
}

bool snake_class::collision(){
    if (snake[0].width == 0 || snake[0].width == maxwidth - 1 || snake[0].height == 0 || snake[0].height == maxheight -2)
        return true;

    //because the head will never collide with the 2nd and the 3rd square
    for (int i = 2; i < snake.size(); i++)
        if (snake[0].width == snake[i].width && snake[i].height == snake[0].height)
            return true;
    /*  
        if the head collides with the FOOD then get is true, 
        We update the position of the food and
        the points of the food, same as the size of the snake
    */  
    if (snake[0].width == food.width && snake[0].height == food.height){
        get =  true;
        putfood();
        points += 10;
        move(maxheight - 1, 0);
        printw("%d", points);
        if ((points%100) == 0)
            del -= 10000;
    }else
        get = false;
    return false;
}

void snake_class::movesnake(){
    int tmp = getch(); // function that allows key_board inputs
    
    switch(tmp){
        case KEY_LEFT:
            if (direction != 'r')
                direction = 'l';
            break;

        case KEY_RIGHT:
            if (direction != 'l')
                direction = 'r';
            break;

        case KEY_UP:
            if (direction != 'd')
                direction = 'u';
            break;

        case KEY_DOWN:
            if (direction != 'u')
                direction = 'd';
            break;

        case KEY_BACKSPACE:
                direction = 'q';
            break;
    }

    /*
        if we do not get the food, delete the last square of the element
    */
    if (!get){
        move(snake[snake.size() - 1].height, snake[snake.size() -1].width);
        addch(' ');
        refresh();
        snake.pop_back();
    }

    if (direction == 'l')
        snake.insert(snake.begin(), snakepart(snake[0].width - 1, snake[0].height)); 
    else if (direction == 'r')
        snake.insert(snake.begin(), snakepart(snake[0].width + 1, snake[0].height));
    else if (direction == 'u')
        snake.insert(snake.begin(), snakepart(snake[0].width, snake[0].height - 1));
    else if (direction == 'd')
        snake.insert(snake.begin(), snakepart(snake[0].width, snake[0].height + 1));
    
    move(snake[0].height, snake[0].width);
    addch(partchar);
    refresh();
}

/*
    start() function 
*/
void snake_class::start(){
    while(1){
        if (collision()){
            move(12, 36);
            printw("game over!");
            break;
        }

        movesnake();
        if (direction == 'q')
            break;
        // suspends execution of the calling thread for (at least) usec microseconds
        usleep(del);
    }
}
