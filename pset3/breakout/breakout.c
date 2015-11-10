//
// breakout.c
//
// Computer Science 50
// Problem Set 3
//

// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Stanford Portable Library
#include <spl/gevents.h>
#include <spl/gobjects.h>
#include <spl/gwindow.h>

// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400

// constant for velocity
#define VEL 4

// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 10

// radius of ball in pixels
#define RADIUS 10

// lives
#define LIVES 3

// prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);
void updateScoreboard(GWindow window, GLabel label, int points);
GObject detectCollision(GWindow window, GOval ball);
void removeGWindow(GWindow gw, GObject gobj);

int main(void)
{
    // seed pseudorandom number generator
    srand48(time(NULL));

    // instantiate window
    GWindow window = newGWindow(WIDTH, HEIGHT);

    // instantiate bricks
    initBricks(window);

    // instantiate ball, centered in middle of window
    GOval ball = initBall(window);

    // instantiate paddle, centered at bottom of window
    GRect paddle = initPaddle(window);

    // instantiate scoreboard, centered in middle of window, just above ball
    GLabel label = initScoreboard(window);

    // number of bricks initially
    int bricks = COLS * ROWS;

    // number of lives initially
    int lives = LIVES;

    // number of points initially
    int points = 0;
    
    //second variable to keep track of 2nd while loop
    int lives2 = LIVES;
    
    // keep playing until game over
    while (lives > 0 && bricks > 0)
    {
        //define velocities for x and y of ball so it moves in more than 1 direction (RIP Zayn Malik)
        
        //for resetting position of ball
        double x = WIDTH/2;
        double y = HEIGHT/2;
        //random x so it points in different directions
        double velx = ((drand48()*(VEL*2)-VEL));
        double vely = 4.0;
        
        
        
        
        //infinite loop while you're able to play the game
        while(lives2 > 0)
        {
        //if you reach max points, this while loop ends
        if(points == 50)
        {
            lives2 = 0;
        }
        //update scoreboard for each iteration of the while loop
        updateScoreboard(window,label,points);
        //record mouse movement
        GEvent event = getNextEvent(MOUSE_EVENT);
        //create object to check collisions
        GObject object = detectCollision(window,ball);
        
        //move ball forever
        move(ball,velx,vely);
        //check bounds with window borders to 'bounce'
        if (getY(ball) + getHeight(ball) >= getHeight(window))
        
        
        
        
        {
            
            //this is bottom window
            lives2 -= 1;
            waitForClick();
            velx = ((drand48()*(VEL*2)-VEL));
            setLocation(ball,x,y);
            
            
            
        }
        else if(getY(ball) <= 0)
        {   
            //top window`
            vely = -vely;
        }
        else if(getX(ball) + getWidth(ball) >= getWidth(window))
        {
            //east window
            velx = -velx;
        }
        else if(getX(ball) <= 0)
        {
            //west window
            velx = -velx;
            
        }
        //check paddle and bricks, do not execute if NULL (seg fault)
        if (object != NULL)
        {
            //bounce if object touches paddle
            if(object == paddle)
            {
                
                vely = -abs(vely);
            }
            //if brick, delete brick and bounce, +1 to points, -1 to brick
            else if(strcmp(getType(object),"GRect") == 0)
            {
                removeGWindow(window,object);
                points += 1;
                bricks -= 1;
                pause(20);
                vely = -vely;
                
            }
            //do not do anything if collides with anything else
            else if(strcmp(getType(object),"GLabel") == 0)
            {
            
            }
        }
        //pause after every movement so it's not blazingly fast
        pause(10);
        //paddle to follow mouse pointer
        if (event != NULL)
        {
            if (getEventType(event) == MOUSE_MOVED)
            {
                double x = getX(event) - 25;
                double y = getY(paddle);
                setLocation(paddle, x, y);
            }
        }
        
        }
        //set lives to 0 to stop top loop
        lives = 0;
    
    

    }
    
    // wait for click before exiting
    waitForClick();

    // game over
    closeGWindow(window);
    return 0;
}

/**
 * Initializes window with a grid of bricks.
 */
void initBricks(GWindow window)
{
    //create bricks to break at the top of window
    
    //for as many rows do the column loop
    for (int i = 0, dist=15; i < ROWS; i++)
    {
        //create the 10 columns and repeat to create the bricks at the top
        for (int j=0,space=39; j < COLS; j++)
        {
            GRect brick = newGRect(0,0,30,8);
            add(window,brick);
            setFilled(brick,true);
            //change color of bricks according to rows loop index
            if(i == 0)
            {
                setColor(brick,"3CA255");
            }
            else if(i == 1)
            {
                setColor(brick,"3CA26E");
            }
            else if(i == 2)
            {
                setColor(brick,"3CA287");
            }
            else if(i == 3)
            {
                setColor(brick,"3CA2A0");
            }
            else if(i == 4)
            {
                setColor(brick,"3CA2BC");
            }
            //after each loop, move printed bricks
            setLocation(brick,(10+(space*j)),50+(dist*i));
        }
    }
}

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
    
    //create ball positioned at center of window
    GOval ball = newGOval(0,0,10,10);
    add(window,ball);
    setColor(ball,"BLACK");
    setFilled(ball,true);
    
    double x = WIDTH/2-(getX(ball)+5);
    double y = HEIGHT/2-(getX(ball)+5);
    setLocation(ball,x,y);
    return ball;
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
 
GRect initPaddle(GWindow window)
{
    //create paddle centered at bottom of window
    GRect paddle = newGRect(((WIDTH/3)+(40)),560,50,8);
    add(window,paddle);
    setColor(paddle,"3CA3ED");
    setFilled(paddle,true);
    
    return paddle;
    
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
    GLabel label = newGLabel("Scoreboard");
    setFont (label,"SansSerif-18");
    add(window,label);
    setLocation(label,10,20);
    return label;
}

/**
 * Updates scoreboard's label, keeping it centered in window.
 */
void updateScoreboard(GWindow window, GLabel label, int points)
{
    // update label
    char s[12];
    sprintf(s, "%i", points);
    setLabel(label, s);

    // center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
}

/**
 * Detects whether ball has collided with some object in window
 * by checking the four corners of its bounding box (which are
 * outside the ball's GOval, and so the ball can't collide with
 * itself).  Returns object if so, else NULL.
 */
GObject detectCollision(GWindow window, GOval ball)
{
    // ball's location
    double x = getX(ball);
    double y = getY(ball);

    // for checking for collisions
    GObject object;

    // check for collision at ball's top-left corner
    object = getGObjectAt(window, x, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's top-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-left corner
    object = getGObjectAt(window, x, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // no collision
    return NULL;
}
