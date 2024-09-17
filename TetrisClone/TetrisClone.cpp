#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <cstdlib>
#include <random>
#include <chrono>
#include <thread>

using namespace std;
using namespace sf;


const float gridWIDTH = 300;
const float gridHEIGHT = gridWIDTH * 2;
const float WIDTH = gridWIDTH + 300;
const float HEIGHT = gridHEIGHT + 200;


enum Colour
{
    Yellow, Orange, Green, Red, Blue, Purple, LightBlue, None
};
struct gridIndex
{
    int y;
    int x;
};

class Grid
{
    //20x10
private:
    Colour grid[20][10];

    //graphics
    RectangleShape background;
    RectangleShape rects[20][10];
    Texture textures[6];
public:
    Grid()
    {
        for (int i = 0; i < 20; i++)
        {
            for (int x = 0; x < 10; x++)
            {
                grid[i][x] = None;
            }
        }

        textures[0].loadFromFile("None.jpg");
        textures[1].loadFromFile("Blue.jpg");
        textures[2].loadFromFile("Green.jpg");
        textures[3].loadFromFile("Purple.jpg");
        textures[4].loadFromFile("Red.jpg");
        textures[5].loadFromFile("Yellow.jpg");


        background.setSize(Vector2f(gridWIDTH, gridHEIGHT));
        background.setPosition(Vector2f(150.f, 100.f));
        background.setFillColor(Color(0, 0, 102));
        background.setOutlineThickness(10);
        background.setOutlineColor(Color(102, 102, 255));


        for (auto i = 0; i < 20; i++)
        {
            for (auto x = 0; x < 10; x++)
            {
                rects[i][x].setPosition(Vector2f(static_cast<float>(x * gridWIDTH / 10 + background.getPosition().x), static_cast<float>(i * gridHEIGHT / 20 + background.getPosition().y)));
                rects[i][x].setSize(Vector2f(static_cast<float>(gridWIDTH / 10), static_cast<float>(gridHEIGHT / 20)));
                //rects[i][x].setFillColor(Color(138, 43, 226, 0));
                //rects[i][x].setOutlineThickness(rects[i][x].getSize().x / 50);
                //rects[i][x].setOutlineColor(Color(100, 100, 100));
                rects[i][x].setTexture(&textures[0]);
            }
        }

    }
    void    printGrid()
    {
        for (int i = 0; i < 20; i++)
        {
            for (int x = 0; x < 10; x++)
            {
                /*switch (grid[i][x])
                {
                case Yellow:
                    cout << "Yellow\t";
                    break;
                case Orange:
                    cout << "Orange\t";
                    break;
                case Green:
                    cout << "Green\t";
                    break;
                case Red:
                    cout << "Red\t";
                    break;
                case Blue:
                    cout << "Blue\t";
                    break;
                case Purple:
                    cout << "Purple\t";
                    break;
                case LightBlue:
                    cout << "LightBlue\t";
                    break;
                case None:
                    cout << ".\t";
                    break;
                }
                */
                if (grid[i][x] != None)
                {
                    cout << "[] ";
                }
                else
                {
                    cout << ".  ";
                }
            }

            cout << endl;
        }
    }
    void    setSegmentColour(int y, int x, Colour colour)
    {
        grid[y][x] = colour;
    }
    int     clearFilledLines()
    {
        int linesCleared = 0;
        bool first = true;
        int time = 0;
        for (int i = 0; i < 20; i++)
        {
            bool lineFilled = true;

            for (int x = 0; x < 10; x++)
            {
                if (grid[i][x] == None) lineFilled = false;
            }

            if (lineFilled)
            {
                if (first)
                {
                    std::this_thread::sleep_for(std::chrono::nanoseconds(10));
                    std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::nanoseconds(10000));
                    first = false;
                }
                linesCleared++;
                for (int z = i; z >= 1; z--)
                {
                    for (int x = 0; x < 10; x++)
                    {
                        grid[z][x] = grid[z - 1][x];
                    }
                }

                /*for (int x = 0; x < 10; x++)
                {
                    grid[i - 1][x] = None;
                }*/


            }

        }

        return linesCleared;
    }
    Colour  getSegment(int y, int x)
    {
        return grid[y][x];
    }
    void    updateGraphics()
    {
        for (int i = 0; i < 20; i++)
        {
            for (int x = 0; x < 10; x++)
            {
                switch (grid[i][x])
                {
                case Yellow:
                    //rects[i][x].setFillColor(Color::Yellow);
                    rects[i][x].setTexture(&textures[5]);
                    break;
                case None:
                    //rects[i][x].setFillColor(Color(138, 43, 226, 0));
                    //rects[i][x].setOutlineThickness(rects[i][x].getSize().x / 50);
                    //rects[i][x].setOutlineColor(Color(100, 100, 100));
                    rects[i][x].setTexture(&textures[0]);
                    break;
                case Orange:
                    //rects[i][x].setFillColor(Color(255, 165, 0));
                    rects[i][x].setTexture(&textures[5]);
                    break;
                case Green:
                    //rects[i][x].setFillColor(Color::Green);
                    rects[i][x].setTexture(&textures[2]);
                    break;
                case Red:
                    //rects[i][x].setFillColor(Color::Red);
                    rects[i][x].setTexture(&textures[4]);
                    break;
                case Blue:
                    //rects[i][x].setFillColor(Color::Blue);
                    rects[i][x].setTexture(&textures[1]);
                    break;
                case Purple:
                    //rects[i][x].setFillColor(Color(77, 0, 77));
                    rects[i][x].setTexture(&textures[3]);
                    break;
                case LightBlue:
                    //rects[i][x].setFillColor(Color(179, 204, 255));
                    rects[i][x].setTexture(&textures[1]);
                    break;
                }
            }
        }
    }
    void    clear()
    {
        for (int i = 0; i < 20; i++)
        {
            for (int x = 0; x < 10; x++)
            {
                grid[i][x] = None;
            }
        }
    }
    void    draw(RenderWindow* window)
    {
        window->draw(background);
        for (int i = 0; i < 20; i++)
        {
            for (int x = 0; x < 10; x++)
            {
                //cout << getSegment(i, x) << "\t";
                window->draw(rects[i][x]);
            }
            //cout << endl;
        }

    }
};

class Block
{
public:
    Colour          shape[4];
    gridIndex       positions[4];
    gridIndex       firstPos;
    Colour          shapeColour;
    bool            still = false;

    virtual void    setPositions(gridIndex firstPosition, Grid* grid) {}
    virtual void    rotate(Grid* grid) {}
    void            setColor(Colour colour)
    {
        shapeColour = colour;
        for (int i = 0; i < 4; i++)
        {
            shape[i] = colour;
        }
    }
    void            fall(Grid* grid)
    {


        bool clear = true;
        bool hitSelf = false;
        for (int i = 0; i < 4; i++)
        {

            hitSelf = false;
            gridIndex testPos{ positions[i].y + 1, positions[i].x };
            for (int x = 0; x < 4; x++)
            {

                if (testPos.y == positions[x].y && testPos.x == positions[x].x)
                {


                    hitSelf = true;
                }

            }


            if (grid->getSegment(positions[i].y + 1, positions[i].x) != None)
            {

                if (!hitSelf)
                {
                    clear = false;
                    still = true;
                }
            }

        }

        if (clear)
        {
            for (int i = 0; i < 4; i++)
            {
                grid->setSegmentColour(positions[i].y, positions[i].x, None);
            }

            for (int i = 0; i < 4; i++)
            {
                positions[i].y++;
                grid->setSegmentColour(positions[i].y, positions[i].x, shapeColour);
                
            }

        }


    }
    bool            checkHitBlock(Grid* grid, gridIndex currentPoss[4], gridIndex tests[4])
    {
        bool clear = true;
        bool hitSelf = false;
        for (int i = 0; i < 4; i++)
        {

            hitSelf = false;
            for (int x = 0; x < 4; x++)
            {

                if (tests[i].y == currentPoss[x].y && tests[i].x == currentPoss[x].x)
                {


                    hitSelf = true;
                }

            }


            if (grid->getSegment(tests[i].y + 1, tests[i].x) != None)
            {

                if (!hitSelf)
                {
                    clear = false;

                }
            }

        }

        return !clear;

    }
    void            smash(Grid* grid)
    {
        gridIndex tests[4];
        for (int i = 0; i < 4; i++)
        {
            gridIndex test;
            test.x = positions[i].x;
            test.y = positions[i].y + 1;
            tests[i] = test;
        }
        setStill();
        //cout << endl << endl << checkHitBlock(grid, positions, tests) << endl << endl;
        while (!checkHitBlock(grid, positions, tests))
        {
            //cout << "ah";
            for (int i = 0; i < 4; i++)
            {
                tests[i].y++;
            }
        }

        

        for (int i = 0; i < 4; i++)
        {
            grid->setSegmentColour(positions[i].y, positions[i].x, None);
            //tests[i].y--;
            //cout << tests[i].y << "\t";
            positions[i] = tests[i];
            grid->setSegmentColour(positions[i].y, positions[i].x, shapeColour);
            
        }
        still = true;
        //cout << endl;

    }
    void            slide(int direction, Grid* grid)
    {
        bool canMove = true;




        for (int i = 0; i < 4; i++)
        {

            if (direction == 1 && positions[i].x + 1 > 9)
            {
                canMove = false;
            }
            else if (direction == -1 && positions[i].x - 1 < 0)
            {
                canMove = false;
            }
        }
        if (canMove)
        {
            gridIndex test[4];
            for (int i = 0; i < 4; i++)
            {
                test[i] = positions[i];
                test[i].x += direction;
                
            }

            for (int i = 0; i < 4; i++)
            {
                bool hitSelf = false;
                bool aboveStart = false;
                if (test[i].y < 0) aboveStart = true;
                for (int x = 0; x < 4; x++)
                {
                    if (test[i].x == positions[x].x && test[i].y == positions[x].y) hitSelf = true;
                }
                
                
                if (grid->getSegment(test[i].y, test[i].x) != None && !hitSelf && !aboveStart) canMove = false;

                

            }

            

        }
        
        cout << endl << canMove << endl;
        if (canMove)
        {
            for (int i = 0; i < 4; i++)
            {
                if (positions[i].y >= 0 && positions[i].y <= 19 &&
                    positions[i].x >= 0 && positions[i].x <= 9)
                {
                    grid->setSegmentColour(positions[i].y, positions[i].x, None);
                }
            }
            for (int i = 0; i < 4; i++)
            {
                positions[i].x += direction;
            }
            for (int i = 0; i < 4; i++)
            {
                if (positions[i].y >= 0 && positions[i].y <= 20 &&
                    positions[i].x >= 0 && positions[i].x <= 10)
                {
                    grid->setSegmentColour(positions[i].y, positions[i].x, shapeColour);
                }
            }
        }

    }
    bool            getStill() { return still; }
    void            setStill() { still = false; }
    bool            moveAway(gridIndex testPositions[4], Grid* grid)
    {
        int moveAway = 0; //0 for still 1 for move right -1 for move left
        for (int i = 0; i < 4; i++)
        {
            if (testPositions[i].x > 9)
            {
                moveAway = -1;
            }
            else if (testPositions[i].x < 0)
            {
                moveAway = 1;
            }
        }

        while (moveAway != 0)
        {
            for (int i = 0; i < 4; i++)
            {
                grid->setSegmentColour(positions[i].x, positions[i].y, None);

            }
            for (int i = 0; i < 4; i++)
            {
                //cout << grid->getSegment(positions[i].x, positions[i].y);
            }


            for (int i = 0; i < 4; i++)
            {
                positions[i].x += moveAway;
                testPositions[i].x += moveAway;
            }

            moveAway = 0;
            for (int i = 0; i < 4; i++)
            {
                if (testPositions[i].x > 9)
                {
                    moveAway = -1;
                }
                else if (testPositions[i].x < 0)
                {
                    moveAway = 1;
                }
            }
        }


        if (moveAway != 0) cout << "true\n";
        if (moveAway == 0) return true;
        else return false;
    }
    Colour          getColor() { return shapeColour; }
};

class I : public Block
{
public:
    I() {}
    I(Colour colour)
    {
        setColor(colour);
    }
    ~I() {}
    void setPositions(gridIndex firstPosition, Grid* grid)
    {

        firstPos.x = firstPosition.x;
        firstPos.y = firstPosition.y;

        for (int i = firstPosition.x; i < firstPosition.x + 4; i++)
        {

            positions[i - firstPosition.x].x = i;
            positions[i - firstPosition.x].y = firstPosition.y;
            if (positions[i - firstPosition.x].y >= 0 && positions[i - firstPosition.x].y <= 20 &&
                positions[i - firstPosition.x].x >= 0 && positions[i - firstPosition.x].x <= 10)
            {
                grid->setSegmentColour(positions[i - firstPosition.x].y, positions[i - firstPosition.x].x, shapeColour);
            }
        }


    }
    void rotate(Grid* grid)
    {
        gridIndex testPoss[4];
        gridIndex initialPoss[4];
        if (!still)
        {
            for (int i = 0; i < 4; i++)
            {
                initialPoss[i] = positions[i];
                testPoss[i] = positions[i];
            }

            for (int i = 0; i < 4; i++)
            {
                if (positions[i].y >= 0 && positions[i].y <= 20 &&
                    positions[i].x >= 0 && positions[i].x <= 10)
                {
                    grid->setSegmentColour(positions[i].y, positions[i].x, None);
                    
                }
            }
            if (positions[0].x < positions[1].x)
            {
                positions[0].x++;
                positions[0].y++;

                positions[2].x--;
                positions[2].y--;

                positions[3].x -= 2;
                positions[3].y -= 2;
            }
            else if (positions[0].x > positions[1].x)
            {
                positions[0].x--;
                positions[0].y--;

                positions[2].x++;
                positions[2].y++;

                positions[3].x += 2;
                positions[3].y += 2;
            }
            else if (positions[0].y < positions[1].y)
            {
                positions[0].x--;
                positions[0].y++;

                positions[2].x++;
                positions[2].y--;

                positions[3].x += 2;
                positions[3].y -= 2;
            }
            else
            {
                positions[0].x++;
                positions[0].y--;

                positions[2].x--;
                positions[2].y++;

                positions[3].x -= 2;
                positions[3].y += 2;
            }

            for (int i = 0; i < 4; i++)
            {
                testPoss[i] = positions[i];
                positions[i] = initialPoss[i];
            }

            bool hitsBlock = checkHitBlock(grid, positions, testPoss);

            if (!hitsBlock)
            {
                moveAway(testPoss, grid);

                
                
                if (positions[0].x < positions[1].x)
                {
                    positions[0].x++;
                    positions[0].y++;

                    positions[2].x--;
                    positions[2].y--;

                    positions[3].x -= 2;
                    positions[3].y -= 2;
                }
                else if (positions[0].x > positions[1].x)
                {
                    positions[0].x--;
                    positions[0].y--;

                    positions[2].x++;
                    positions[2].y++;

                    positions[3].x += 2;
                    positions[3].y += 2;
                }
                else if (positions[0].y < positions[1].y)
                {
                    positions[0].x--;
                    positions[0].y++;

                    positions[2].x++;
                    positions[2].y--;

                    positions[3].x += 2;
                    positions[3].y -= 2;
                }
                else
                {
                    positions[0].x++;
                    positions[0].y--;

                    positions[2].x--;
                    positions[2].y++;

                    positions[3].x -= 2;
                    positions[3].y += 2;
                }

            }

            for (int i = 0; i < 4; i++)
            {
                if (positions[i].y >= 0 && positions[i].y <= 20 &&
                    positions[i].x >= 0 && positions[i].x <= 10)
                {
                    grid->setSegmentColour(positions[i].y, positions[i].x, shapeColour);
                }
            }


        }

    }
};


class J : public Block
{
public:
    J() {}
    J(Colour colour)
    {
        setColor(colour);
    }
    ~J() {}
    void setPositions(gridIndex firstPosition, Grid* grid)
    {
        firstPos.x = firstPosition.x;
        firstPos.y = firstPosition.y;

        positions[0].x = firstPosition.x;
        positions[0].y = firstPosition.y;

        for (int i = firstPosition.x; i < firstPosition.x + 4; i++)
        {
            positions[i - firstPosition.x + 1].x = i;
            positions[i - firstPosition.x + 1].y = firstPosition.y + 1;
            if (positions[i - firstPosition.x].y >= 0 && positions[i - firstPosition.x].y <= 20 &&
                positions[i - firstPosition.x].x >= 0 && positions[i - firstPosition.x].x <= 10)
            {
                grid->setSegmentColour(positions[i - firstPosition.x].y, positions[i - firstPosition.x].x, shapeColour);
            }
        }
    }
    void rotate(Grid* grid)
    {

        gridIndex testPoss[4];
        gridIndex initialPoss[4];
        if (!still)
        {

            for (int i = 0; i < 4; i++)
            {
                initialPoss[i] = positions[i];
                testPoss[i] = positions[i];
            }

            for (int i = 0; i < 4; i++)
            {
                if (positions[i].y >= 0 && positions[i].y <= 20 &&
                    positions[i].x >= 0 && positions[i].x <= 10)
                {
                    grid->setSegmentColour(positions[i].y, positions[i].x, None);
                }
            }
            if (positions[1].x < positions[2].x)
            {
                positions[1].x++;
                positions[1].y++;

                positions[0].y += 2;

                positions[3].x--;
                positions[3].y--;
            }
            else if (positions[1].x > positions[2].x)
            {
                positions[1].x--;
                positions[1].y--;

                positions[0].y -= 2;

                positions[3].x++;
                positions[3].y++;
            }
            else if (positions[1].y > positions[2].y)
            {
                positions[1].x++;
                positions[1].y--;

                positions[0].x += 2;

                positions[3].x--;
                positions[3].y++;
            }
            else
            {
                positions[1].x--;
                positions[1].y++;

                positions[0].x -= 2;

                positions[3].x++;
                positions[3].y--;
            }

            for (int i = 0; i < 4; i++)
            {
                testPoss[i] = positions[i];
                positions[i] = initialPoss[i];
            }

            bool hitsBlock = checkHitBlock(grid, positions, testPoss);

            if (!hitsBlock)
            {
                moveAway(testPoss, grid);
                if (positions[1].x < positions[2].x)
                {
                    positions[1].x++;
                    positions[1].y++;

                    positions[0].y += 2;

                    positions[3].x--;
                    positions[3].y--;
                }
                else if (positions[1].x > positions[2].x)
                {
                    positions[1].x--;
                    positions[1].y--;

                    positions[0].y -= 2;

                    positions[3].x++;
                    positions[3].y++;
                }
                else if (positions[1].y > positions[2].y)
                {
                    positions[1].x++;
                    positions[1].y--;

                    positions[0].x += 2;

                    positions[3].x--;
                    positions[3].y++;
                }
                else
                {
                    positions[1].x--;
                    positions[1].y++;

                    positions[0].x -= 2;

                    positions[3].x++;
                    positions[3].y--;
                }
            }

            for (int i = 0; i < 4; i++)
            {
                if (positions[i].y >= 0 && positions[i].y <= 20 &&
                    positions[i].x >= 0 && positions[i].x <= 10)
                {
                    grid->setSegmentColour(positions[i].y, positions[i].x, shapeColour);
                }
            }
            
        }


    }
};


class L : public Block
{
public:
    L() {}
    L(Colour colour)
    {
        setColor(colour);
    }
    ~L() {}
    void setPositions(gridIndex firstPosition, Grid* grid)
    {
        firstPos.x = firstPosition.x;
        firstPos.y = firstPosition.y;

        for (int i = firstPosition.x; i < firstPosition.x + 3; i++)
        {
            positions[i - firstPosition.x].x = i;
            positions[i - firstPosition.x].y = firstPosition.y;
            if (positions[i - firstPosition.x].y >= 0 && positions[i - firstPosition.x].y <= 20 &&
                positions[i - firstPosition.x].x >= 0 && positions[i - firstPosition.x].x <= 10)
            {
                grid->setSegmentColour(positions[i - firstPosition.x].y, positions[i - firstPosition.x].x, shapeColour);
            }
        }

        positions[3].x = positions[2].x;
        positions[3].y = positions[2].y - 1;
        if (positions[3].y >= 0 && positions[3].y <= 20 &&
            positions[3].x >= 0 && positions[3].x <= 10)
        {
            grid->setSegmentColour(positions[3].y, positions[3].x, shapeColour);
        }
    }
    void rotate(Grid* grid)
    {

        gridIndex testPoss[4];
        gridIndex initialPoss[4];
        if (!still)
        {

            for (int i = 0; i < 4; i++)
            {
                initialPoss[i] = positions[i];
                testPoss[i] = positions[i];
            }

            for (int i = 0; i < 4; i++)
            {
                if (positions[i].y >= 0 && positions[i].y <= 20 &&
                    positions[i].x >= 0 && positions[i].x <= 10)
                {
                    grid->setSegmentColour(positions[i].y, positions[i].x, None);
                }
            }

            if (positions[0].x < positions[1].x)
            {
                positions[0].x++;
                positions[0].y++;

                positions[2].x--;
                positions[2].y--;

                positions[3].x -= 2;
            }
            else if (positions[0].x > positions[1].x)
            {
                positions[0].x--;
                positions[0].y--;

                positions[2].x++;
                positions[2].y++;

                positions[3].x += 2;
            }
            else if (positions[0].y > positions[1].y)
            {
                positions[0].x++;
                positions[0].y--;

                positions[2].x--;
                positions[2].y++;

                positions[3].y += 2;
            }
            else
            {
                positions[0].x--;
                positions[0].y++;

                positions[2].x++;
                positions[2].y--;

                positions[3].y -= 2;
            }

            for (int i = 0; i < 4; i++)
            {
                testPoss[i] = positions[i];
                positions[i] = initialPoss[i];
            }

            bool hitsBlock = checkHitBlock(grid, positions, testPoss);

            if (!hitsBlock)
            {
                moveAway(testPoss, grid);


                if (positions[0].x < positions[1].x)
                {
                    positions[0].x++;
                    positions[0].y++;

                    positions[2].x--;
                    positions[2].y--;

                    positions[3].x -= 2;
                }
                else if (positions[0].x > positions[1].x)
                {
                    positions[0].x--;
                    positions[0].y--;

                    positions[2].x++;
                    positions[2].y++;

                    positions[3].x += 2;
                }
                else if (positions[0].y > positions[1].y)
                {
                    positions[0].x++;
                    positions[0].y--;

                    positions[2].x--;
                    positions[2].y++;

                    positions[3].y += 2;
                }
                else
                {
                    positions[0].x--;
                    positions[0].y++;

                    positions[2].x++;
                    positions[2].y--;

                    positions[3].y -= 2;
                }

            }

            for (int i = 0; i < 4; i++)
            {
                if (positions[i].y >= 0 && positions[i].y <= 20 &&
                    positions[i].x >= 0 && positions[i].x <= 10)
                {
                    grid->setSegmentColour(positions[i].y, positions[i].x, shapeColour);
                }
            }
                
            

        }

    }
};


class O : public Block
{
public:
    O() {}
    O(Colour colour)
    {
        setColor(colour);
    }
    ~O() {}
    void setPositions(gridIndex firstPosition, Grid* grid)
    {


        firstPos.x = firstPosition.x;
        firstPos.y = firstPosition.y;

        positions[0].x = firstPos.x;
        positions[0].y = firstPos.y;

        positions[1].x = firstPos.x + 1;
        positions[1].y = firstPos.y;

        positions[2].x = firstPos.x;
        positions[2].y = firstPos.y + 1;

        positions[3].x = firstPos.x + 1;
        positions[3].y = firstPos.y + 1;

        for (int i = 0; i < 4; i++)
        {
            if (positions[i].y >= 0 && positions[i].y <= 20 &&
                positions[i].x >= 0 && positions[i].x <= 10)
            {
                grid->setSegmentColour(positions[i].y, positions[i].x, shapeColour);
            }
        }

    }
    void rotate(Grid* grid)
    {

        for (int i = 0; i < 4; i++)
        {
            if (positions[i].y >= 0 && positions[i].y <= 20 &&
                positions[i].x >= 0 && positions[i].x <= 10)
            {
                grid->setSegmentColour(positions[i].y, positions[i].x, shapeColour);
            }
        }
    }
};


class S : public Block
{
public:
    S() {}
    S(Colour colour)
    {
        setColor(colour);
    }
    ~S() {}
    void setPositions(gridIndex firstPosition, Grid* grid)
    {
        firstPos.x = firstPosition.x;
        firstPos.y = firstPosition.y;

        positions[0].x = firstPos.x;
        positions[0].y = firstPos.y;

        positions[1].x = firstPos.x + 1;
        positions[1].y = firstPos.y;

        positions[2].x = firstPos.x + 1;
        positions[2].y = firstPos.y - 1;

        positions[3].x = firstPos.x + 2;
        positions[3].y = firstPos.y - 1;
        for (int i = 0; i < 4; i++)
        {
            if (positions[i].y >= 0 && positions[i].y <= 20 &&
                positions[i].x >= 0 && positions[i].x <= 10)
            {
                grid->setSegmentColour(positions[i].y, positions[i].x, shapeColour);
            }
        }
    }
    void rotate(Grid* grid)
    {

        gridIndex testPoss[4];
        gridIndex initialPoss[4];
        if (!still)
        {
            for (int i = 0; i < 4; i++)
            {
                initialPoss[i] = positions[i];
                testPoss[i] = positions[i];
            }

            for (int i = 0; i < 4; i++)
            {
                if (positions[i].y >= 0 && positions[i].y <= 20 &&
                    positions[i].x >= 0 && positions[i].x <= 10)
                {
                    grid->setSegmentColour(positions[i].y, positions[i].x, None);
                }
            }

            if (positions[0].x < positions[1].x)
            {
                positions[0].x++;
                positions[0].y++;

                positions[2].x--;
                positions[2].y++;

                positions[3].x -= 2;
            }
            else if (positions[0].x > positions[1].x)
            {
                positions[0].x--;
                positions[0].y--;

                positions[2].x++;
                positions[2].y--;

                positions[3].x += 2;
            }
            else if (positions[0].y > positions[1].y)
            {
                positions[0].x++;
                positions[0].y--;

                positions[2].x++;
                positions[2].y++;

                positions[3].y += 2;
            }
            else
            {
                positions[0].x--;
                positions[0].y++;

                positions[2].x--;
                positions[2].y--;

                positions[3].y -= 2;
            }

            for (int i = 0; i < 4; i++)
            {
                testPoss[i] = positions[i];
                positions[i] = initialPoss[i];
            }

            bool hitsBlock = checkHitBlock(grid, positions, testPoss);

            if (!hitsBlock)
            {
                moveAway(testPoss, grid);

                if (positions[0].x < positions[1].x)
                {
                    positions[0].x++;
                    positions[0].y++;

                    positions[2].x--;
                    positions[2].y++;

                    positions[3].x -= 2;
                }
                else if (positions[0].x > positions[1].x)
                {
                    positions[0].x--;
                    positions[0].y--;

                    positions[2].x++;
                    positions[2].y--;

                    positions[3].x += 2;
                }
                else if (positions[0].y > positions[1].y)
                {
                    positions[0].x++;
                    positions[0].y--;

                    positions[2].x++;
                    positions[2].y++;

                    positions[3].y += 2;
                }
                else
                {
                    positions[0].x--;
                    positions[0].y++;

                    positions[2].x--;
                    positions[2].y--;

                    positions[3].y -= 2;
                }

            }

            for (int i = 0; i < 4; i++)
            {
                if (positions[i].y >= 0 && positions[i].y <= 20 &&
                    positions[i].x >= 0 && positions[i].x <= 10)
                {
                    grid->setSegmentColour(positions[i].y, positions[i].x, shapeColour);
                }
            }
        }

    }
};


class T : public Block
{
public:
    T() {}
    T(Colour colour)
    {
        setColor(colour);
    }
    ~T() {}
    void setPositions(gridIndex firstPosition, Grid* grid)
    {
        firstPos.x = firstPosition.x;
        firstPos.y = firstPosition.y;

        positions[0].x = firstPos.x;
        positions[0].y = firstPos.y;

        positions[1].x = firstPos.x + 1;
        positions[1].y = firstPos.y;

        positions[2].x = firstPos.x + 1;
        positions[2].y = firstPos.y - 1;

        positions[3].x = firstPos.x + 2;
        positions[3].y = firstPos.y;
        for (int i = 0; i < 4; i++)
        {
            if (positions[i].y >= 0 && positions[i].y <= 20 &&
                positions[i].x >= 0 && positions[i].x <= 10)
            {
                grid->setSegmentColour(positions[i].y, positions[i].x, shapeColour);
            }
        }
    }
    void rotate(Grid* grid)
    {

        gridIndex testPoss[4];
        gridIndex initialPoss[4];
        if (!still)
        {

            for (int i = 0; i < 4; i++)
            {
                initialPoss[i] = positions[i];
                testPoss[i] = positions[i];
            }

            for (int i = 0; i < 4; i++)
            {
                if (positions[i].y >= 0 && positions[i].y <= 20 &&
                    positions[i].x >= 0 && positions[i].x <= 10)
                {
                    grid->setSegmentColour(positions[i].y, positions[i].x, None);
                }
            }

            if (positions[0].x < positions[1].x)
            {
                positions[0].x++;
                positions[0].y++;

                positions[2].x--;
                positions[2].y++;

                positions[3].x--;
                positions[3].y--;
            }
            else if (positions[0].x > positions[1].x)
            {
                positions[0].x--;
                positions[0].y--;

                positions[2].x++;
                positions[2].y--;

                positions[3].x++;
                positions[3].y++;
            }
            else if (positions[0].y > positions[1].y)
            {
                positions[0].x++;
                positions[0].y--;

                positions[2].x++;
                positions[2].y++;

                positions[3].x--;
                positions[3].y++;
            }
            else
            {
                positions[0].x--;
                positions[0].y++;

                positions[2].x--;
                positions[2].y--;

                positions[3].x++;
                positions[3].y--;
            }

            for (int i = 0; i < 4; i++)
            {
                testPoss[i] = positions[i];
                positions[i] = initialPoss[i];
            }

            bool hitsBlock = checkHitBlock(grid, positions, testPoss);

            if (!hitsBlock)
            {
                moveAway(testPoss, grid);

                if (positions[0].x < positions[1].x)
                {
                    positions[0].x++;
                    positions[0].y++;

                    positions[2].x--;
                    positions[2].y++;

                    positions[3].x--;
                    positions[3].y--;
                }
                else if (positions[0].x > positions[1].x)
                {
                    positions[0].x--;
                    positions[0].y--;

                    positions[2].x++;
                    positions[2].y--;

                    positions[3].x++;
                    positions[3].y++;
                }
                else if (positions[0].y > positions[1].y)
                {
                    positions[0].x++;
                    positions[0].y--;

                    positions[2].x++;
                    positions[2].y++;

                    positions[3].x--;
                    positions[3].y++;
                }
                else
                {
                    positions[0].x--;
                    positions[0].y++;

                    positions[2].x--;
                    positions[2].y--;

                    positions[3].x++;
                    positions[3].y--;
                }
            }

            for (int i = 0; i < 4; i++)
            {
                if (positions[i].y >= 0 && positions[i].y <= 20 &&
                    positions[i].x >= 0 && positions[i].x <= 10)
                {
                    grid->setSegmentColour(positions[i].y, positions[i].x, shapeColour);
                }
            }
        }

    }
};


class Z : public Block
{
public:
    Z() {}
    Z(Colour colour)
    {
        setColor(colour);
    }
    ~Z() {}
    void setPositions(gridIndex firstPosition, Grid* grid)
    {
        firstPos.x = firstPosition.x;
        firstPos.y = firstPosition.y;

        positions[0].x = firstPos.x;
        positions[0].y = firstPos.y;

        positions[1].x = firstPos.x + 1;
        positions[1].y = firstPos.y;

        positions[2].x = firstPos.x + 1;
        positions[2].y = firstPos.y + 1;

        positions[3].x = firstPos.x + 2;
        positions[3].y = firstPos.y + 1;
        for (int i = 0; i < 4; i++)
        {
            if (positions[i].y >= 0 && positions[i].y <= 20 &&
                positions[i].x >= 0 && positions[i].x <= 10)
            {
                grid->setSegmentColour(positions[i].y, positions[i].x, shapeColour);
            }
        }
    }
    void rotate(Grid* grid)
    {
        if (!still)
        {
            
            for (int i = 0; i < 4; i++)
            {
                if (positions[i].y >= 0 && positions[i].y <= 20 &&
                    positions[i].x >= 0 && positions[i].x <= 10)
                {
                    grid->setSegmentColour(positions[i].y, positions[i].x, None);
                }
            }

            if (positions[0].x < positions[1].x)
            {
                positions[0].x++;
                positions[0].y++;

                positions[2].x++;
                positions[2].y--;

                positions[3].y -= 2;
            }
            else if (positions[0].x > positions[1].x)
            {
                positions[0].x--;
                positions[0].y--;

                positions[2].x--;
                positions[2].y++;

                positions[3].y += 2;
            }
            else if (positions[0].y > positions[1].y)
            {
                positions[0].x++;
                positions[0].y--;

                positions[2].x--;
                positions[2].y--;

                positions[3].x -= 2;
            }
            else
            {
                positions[0].x--;
                positions[0].y++;

                positions[2].x++;
                positions[2].y++;

                positions[3].x += 2;
            }


            for (int i = 0; i < 4; i++)
            {
                if (positions[i].y >= 0 && positions[i].y <= 20 &&
                    positions[i].x >= 0 && positions[i].x <= 10)
                {
                    grid->setSegmentColour(positions[i].y, positions[i].x, None);
                }
            }
        }
    }
};


enum States { MainMenu, Playing, Lost, Pause };


class Game
{
private:
    Block* next;
    Block* hold = 0;
    Grid grid;
    int timer = 0;
    int fallTimeStep = 500;
    bool fastDescend = false;
    int currentShapeChoice = -1;
    int nextShapeChoice = -1;
    int clearedLines = 0;
    int level = 0;
    int testLevelVal = 10;
    bool availableSwapToHold = true;
    bool lockClick = false;
    bool availableSmash = true;
    States currentState = Playing;
    I i;
    J j;
    L l;
    O o;
    S s;
    T t;
    Z z;


    //graphics
    Font defaultFont;

    Texture backTexture;
    RectangleShape background;

    RectangleShape nextBufferStore;
    Texture nextBuffer;
    RectangleShape textureFrameNextBuffer;
    Text NEXT;

    RectangleShape holdBufferStore;
    Texture holdBuffer;
    RectangleShape textureFrameHoldBuffer;
    Text HOLD;
    int holdChoice = -1;

    //controlers
    RectangleShape pauseBut;
    RectangleShape fastBut;
    RectangleShape smashBut;
    RectangleShape rotateBut;
    RectangleShape leftBut;
    RectangleShape rightBut;

    Texture pauseButText;
    Texture fastButText;
    Texture smashButText;
    Texture rotateButText;
    Texture leftButText;
    Texture rightButText;



public:
    int timeInc = 0;
    bool blockOut = false;
    int evalRandNext(int choice)
    {
        int colorChoice = rand() % 7;

        Colour chosenColor;
        switch (colorChoice)
        {
        case 0:
            chosenColor = Yellow;
            break;
        case 1:
            chosenColor = Orange;
            break;
        case 2:
            chosenColor = Green;
            break;
        case 3:
            chosenColor = Red;
            break;
        case 4:
            chosenColor = Blue;
            break;
        case 5:
            chosenColor = Purple;
            break;
        case 6:
            chosenColor = LightBlue;
            break;
        default:
            break;
        }

        i.~I();
        j.~J();
        l.~L();
        o.~O();
        s.~S();
        t.~T();
        z.~Z();

        i = I(chosenColor);
        j = J(chosenColor);
        l = L(chosenColor);
        o = O(chosenColor);
        s = S(chosenColor);
        t = T(chosenColor);
        z = Z(chosenColor);
        //choice = 1;
        //cout << endl << endl << choice << endl << endl;
        //if (choice == 3) choice = 4;
        switch (choice)
        {
        case 0:
            next = &i;
            next->setPositions({ 0, 3 }, &grid);
            break;
        case 1:
            next = &j;
            next->setPositions({ 0, 3 }, &grid);
            break;
        case 2:
            next = &l;
            next->setPositions({ 0, 3 }, &grid);
            break;
        case 3:
            next = &o;
            next->setPositions({ 0, 3 }, &grid);
            break;
        case 4:
            next = &s;
            next->setPositions({ 0, 3 }, &grid);
            break;
        case 5:
            next = &t;
            next->setPositions({ 1, 3 }, &grid);
            break;
        case 6:
            next = &z;
            next->setPositions({ 0, 3 }, &grid);
            break;
        }
        //cout << choice;
        return choice;
    }
    Game()
    {
        currentState = MainMenu;

        defaultFont.loadFromFile("ChargeVectorBlack-7BKqV.ttf");
        NEXT.setFont(defaultFont);
        HOLD.setFont(defaultFont);
        NEXT.setCharacterSize(HEIGHT / 50);
        HOLD.setCharacterSize(HEIGHT / 50);
        NEXT.setPosition(Vector2f(150 + gridWIDTH + 50, 100.f - NEXT.getLocalBounds().height - 30));
        HOLD.setPosition(Vector2f(WIDTH / 15, 100.f - HOLD.getLocalBounds().height - 30));
        NEXT.setFillColor(Color(160, 32, 240));
        HOLD.setFillColor(Color(160, 32, 240));
        NEXT.setString("NEXT");
        HOLD.setString("HOLD");
        

        backTexture.loadFromFile("background.jpg");
        background.setTexture(&backTexture);
        background.setPosition(Vector2f(0, 0));
        background.setSize(Vector2f(WIDTH, HEIGHT));

        //next store
        nextBufferStore.setPosition(Vector2f(150 + gridWIDTH + 50, 100.f));
        nextBufferStore.setSize(Vector2f(WIDTH / 10, WIDTH / 10));
        nextBufferStore.setFillColor(Color::Black);
        nextBufferStore.setOutlineThickness(7);
        nextBufferStore.setOutlineColor(Color(102, 102, 255));

        textureFrameNextBuffer.setPosition(Vector2f(nextBufferStore.getPosition().x + 7, nextBufferStore.getPosition().y + 7));
        textureFrameNextBuffer.setSize(Vector2f(nextBufferStore.getSize().x - 14, nextBufferStore.getSize().y - 14));

        holdBufferStore.setPosition(Vector2f(WIDTH / 15, 100.f));
        holdBufferStore.setSize(Vector2f(WIDTH / 10, WIDTH / 10));
        holdBufferStore.setFillColor(Color::Black);
        holdBufferStore.setOutlineThickness(7);
        holdBufferStore.setOutlineColor(Color(102, 102, 255));

        textureFrameHoldBuffer.setPosition(Vector2f(holdBufferStore.getPosition().x + 7, holdBufferStore.getPosition().y + 7));
        textureFrameHoldBuffer.setSize(Vector2f(holdBufferStore.getSize().x - 14, holdBufferStore.getSize().y - 14));

        holdBuffer.loadFromFile("empty.PNG");
        textureFrameHoldBuffer.setTexture(&holdBuffer);

        int elapsedSeconds = time(nullptr);
        srand(elapsedSeconds);
        grid = Grid();

        nextShapeChoice = rand() % 7;
        currentShapeChoice = rand() % 7;
        while (currentShapeChoice == nextShapeChoice) currentShapeChoice = rand() % 7;
        holdChoice = evalRandNext(currentShapeChoice);
        //currentShapeChoice = evalRandNext(currentShapeChoice);



        //init contolers
        pauseButText.loadFromFile("pause.PNG");
        rotateButText.loadFromFile("rotate.PNG");
        rightButText.loadFromFile("right.PNG");
        leftButText.loadFromFile("left.PNG");
        fastButText.loadFromFile("fastDescend.PNG");
        smashButText.loadFromFile("smash.PNG");


        pauseBut.setTexture(&pauseButText);
        rotateBut.setTexture(&rotateButText);
        rightBut.setTexture(&rightButText);
        leftBut.setTexture(&leftButText);
        fastBut.setTexture(&fastButText);
        smashBut.setTexture(&smashButText);

        pauseBut.setPosition(Vector2f(100 + gridWIDTH + WIDTH / 7, 100 + gridHEIGHT));
        pauseBut.setSize(Vector2f(WIDTH / 10, WIDTH / 10));

        rotateBut.setPosition(Vector2f(150 - WIDTH / 7, 100 + gridHEIGHT));
        rotateBut.setSize(Vector2f(WIDTH / 10, WIDTH / 10));

        fastBut.setPosition(Vector2f(150, 100 + gridHEIGHT + HEIGHT / 30));
        fastBut.setSize(Vector2f(WIDTH / 10, WIDTH / 10));

        smashBut.setPosition(Vector2f(100 + gridWIDTH + WIDTH / 7 - WIDTH / 7, 100 + gridHEIGHT + HEIGHT / 30));
        smashBut.setSize(Vector2f(WIDTH / 10, WIDTH / 10));

        leftBut.setPosition(Vector2f(150 + WIDTH / 10 + WIDTH / 25, 100 + gridHEIGHT + HEIGHT / 30));
        leftBut.setSize(Vector2f(WIDTH / 10, WIDTH / 10));

        rightBut.setPosition(Vector2f(100 + gridWIDTH + WIDTH / 7 - WIDTH / 7 - WIDTH / 10 - WIDTH / 25, 100 + gridHEIGHT + HEIGHT / 30));
        rightBut.setSize(Vector2f(WIDTH / 10, WIDTH / 10));
    }
    States getCurrentState()
    {
        return currentState;
    }
    void setNextBufferTexture()
    {
        switch (nextShapeChoice)
        {
        case 0:
            nextBuffer.loadFromFile("I.PNG");
            break;
        case 1:
            nextBuffer.loadFromFile("J.PNG");
            break;
        case 2:
            nextBuffer.loadFromFile("L.PNG");
            break;
        case 3:
            nextBuffer.loadFromFile("O.PNG");
            break;
        case 4:
            nextBuffer.loadFromFile("S.PNG");
            break;
        case 5:
            nextBuffer.loadFromFile("T.PNG");
            break;
        case 6:
            nextBuffer.loadFromFile("Z.PNG");
            break;
        }
        textureFrameNextBuffer.setTexture(&nextBuffer);
    }
    void play()
    {
        if (blockOut) { currentState = Lost; }

        if (fastDescend) fallTimeStep = 100;
        else fallTimeStep = 500;
        timer += timeInc;

        //cout << fallTimeStep << endl;
        if (timer % fallTimeStep == 0)
        {

            next->fall(&grid);
            if (next->getStill())
            {
                cout << checkBlockOut();
                if (checkBlockOut()) { blockOut = true; timer++; timeInc = 0; }
                fastDescend = false;

                if (clearedLines >= testLevelVal)
                {
                    level++;
                    testLevelVal += 10;
                }

                availableSwapToHold = true;

                int increaseVal = grid.clearFilledLines();
                clearedLines += increaseVal;


                ////evaluate next
                currentShapeChoice = nextShapeChoice;

                nextShapeChoice = rand() % 7;
                while (nextShapeChoice == currentShapeChoice)
                {
                    nextShapeChoice = rand() % 7;
                }


                evalRandNext(currentShapeChoice);
                availableSmash = true;


            }
            //if (next->getStill()) cout << endl << endl << "true" << endl << endl;
            //else cout << endl << endl << "false" << endl << endl;

        }

        grid.updateGraphics();
        
    }
    void setFastDescend(bool n) { fastDescend = n; }
    bool checkBlockOut()
    {
        for (int i = 0; i < 4; i++)
        {
            if ((next->positions[i].y == 0 || next->positions[i].y == 1)) return true;
            else return false;
            //cout << next->positions[i].y << "\t";
        }
        //cout << endl;
        
    }
    bool getFastDescend() { return fastDescend; }
    void setHoldBufferStore()
    {
        cout << endl << holdChoice << endl;
        switch (holdChoice)
        {
        case -1:
            holdBuffer.loadFromFile("empty.PNG");
            break;
        case 0:
            holdBuffer.loadFromFile("I.PNG");
            break;
        case 1:
            holdBuffer.loadFromFile("J.PNG");
            break;
        case 2:
            holdBuffer.loadFromFile("L.PNG");
            break;
        case 3:
            holdBuffer.loadFromFile("O.PNG");
            break;
        case 4:
            holdBuffer.loadFromFile("S.PNG");
            break;
        case 5:
            holdBuffer.loadFromFile("T.PNG");
            break;
        case 6:
            holdBuffer.loadFromFile("Z.PNG");
            break;
        }
        textureFrameNextBuffer.setTexture(&nextBuffer);
        
    }
    void swapToHold()
    {

        if (availableSwapToHold)
        {
            holdChoice = currentShapeChoice;
            cout << holdChoice << endl;
            setHoldBufferStore();
            if (hold == 0)
            {
                for (int i = 0; i < 4; i++)
                {
                    grid.setSegmentColour(next->positions[i].y, next->positions[i].x, None);
                }
                hold = next;
                

                
                

                //new Next
                
                currentShapeChoice = nextShapeChoice;

                nextShapeChoice = rand() % 7;
                while (nextShapeChoice == currentShapeChoice)
                {
                    nextShapeChoice = rand() % 7;
                }


                evalRandNext(currentShapeChoice);
            }
            else
            {
                for (int i = 0; i < 4; i++)
                {
                    grid.setSegmentColour(next->positions[i].y, next->positions[i].x, None);
                }
                //cout << hold->positions;
                gridIndex tempPos = next->positions[0];

                Block* temp = next;
                next = hold;
                next->setPositions(tempPos, &grid);
                next->setColor(hold->getColor());
                hold = temp;
            }
            availableSwapToHold = false;
        }
        
        
    }
    void slideNext(int direction) { next->slide(direction, &grid); }
    void rotateNext() { next->rotate(&grid); }
    void smashNext() { if (availableSmash) { next->smash(&grid); availableSmash = false; } }
    void editLockClock(bool New) { lockClick = New; }
    void manageContollers(RenderWindow* window)
    {

            
        Vector2f mousePos;
        mousePos.x = Mouse::getPosition(*window).x;
        mousePos.y = Mouse::getPosition(*window).y;



        pauseBut.setSize(Vector2f(WIDTH / 10, WIDTH / 10));
        rotateBut.setSize(Vector2f(WIDTH / 10, WIDTH / 10));
        fastBut.setSize(Vector2f(WIDTH / 10, WIDTH / 10));
        smashBut.setSize(Vector2f(WIDTH / 10, WIDTH / 10));
        leftBut.setSize(Vector2f(WIDTH / 10, WIDTH / 10));
        rightBut.setSize(Vector2f(WIDTH / 10, WIDTH / 10));
        holdBufferStore.setSize(Vector2f(WIDTH / 10, WIDTH / 10));

        if (mousePos.x >= pauseBut.getPosition().x && mousePos.x <= pauseBut.getPosition().x + pauseBut.getSize().x &&
            mousePos.y >= pauseBut.getPosition().y && mousePos.y <= pauseBut.getPosition().y + pauseBut.getSize().y)
        {
            pauseBut.setSize(Vector2f(pauseBut.getSize().x + 2, pauseBut.getSize().y + 2));
            if (Mouse::isButtonPressed(Mouse::Button::Left) && !lockClick)
            {
                lockClick = true;
                if (timeInc == 0)
                {
                    timeInc = 1; currentState = Playing;
                }
                else
                {
                    timeInc = 0; currentState = Pause;
                }
            }

        }

        if (mousePos.x >= rotateBut.getPosition().x && mousePos.x <= rotateBut.getPosition().x + rotateBut.getSize().x &&
            mousePos.y >= rotateBut.getPosition().y && mousePos.y <= rotateBut.getPosition().y + rotateBut.getSize().y)
        {
            rotateBut.setSize(Vector2f(rotateBut.getSize().x + 2, rotateBut.getSize().y + 2));
            if (Mouse::isButtonPressed(Mouse::Button::Left) && !lockClick) { next->rotate(&grid); lockClick = true; }
        }

        if (mousePos.x >= rightBut.getPosition().x && mousePos.x <= rightBut.getPosition().x + rightBut.getSize().x &&
            mousePos.y >= rightBut.getPosition().y && mousePos.y <= rightBut.getPosition().y + rightBut.getSize().y)
        {
            rightBut.setSize(Vector2f(rightBut.getSize().x + 2, rightBut.getSize().y + 2));
            if (Mouse::isButtonPressed(Mouse::Button::Left) && !lockClick) { next->slide(1, &grid); lockClick = true; }
        }

        if (mousePos.x >= leftBut.getPosition().x && mousePos.x <= leftBut.getPosition().x + leftBut.getSize().x &&
            mousePos.y >= leftBut.getPosition().y && mousePos.y <= leftBut.getPosition().y + leftBut.getSize().y)
        {
            leftBut.setSize(Vector2f(leftBut.getSize().x + 2, leftBut.getSize().y + 2));
            if (Mouse::isButtonPressed(Mouse::Button::Left) && !lockClick) { next->slide(-1, &grid); lockClick = true; }
        }

        if (mousePos.x >= fastBut.getPosition().x && mousePos.x <= fastBut.getPosition().x + fastBut.getSize().x &&
            mousePos.y >= fastBut.getPosition().y && mousePos.y <= fastBut.getPosition().y + fastBut.getSize().y)
        {
            fastBut.setSize(Vector2f(fastBut.getSize().x + 2, fastBut.getSize().y + 2));
            if (Mouse::isButtonPressed(Mouse::Button::Left) && !lockClick)
            {
                lockClick = true;
                cout << "ah\n";
                if (!fastDescend) fastDescend = true;
                else fastDescend = false;
            }
        }

        if (mousePos.x >= smashBut.getPosition().x && mousePos.x <= smashBut.getPosition().x + smashBut.getSize().x &&
            mousePos.y >= smashBut.getPosition().y && mousePos.y <= smashBut.getPosition().y + smashBut.getSize().y)
        {
            smashBut.setSize(Vector2f(smashBut.getSize().x + 2, smashBut.getSize().y + 2));
            if (Mouse::isButtonPressed(Mouse::Button::Left) && !lockClick) { smashNext(); lockClick = true; }
        }

        if (mousePos.x >= holdBufferStore.getPosition().x && mousePos.x <= holdBufferStore.getPosition().x + holdBufferStore.getSize().x &&
            mousePos.y >= holdBufferStore.getPosition().y && mousePos.y <= holdBufferStore.getPosition().y + holdBufferStore.getSize().y)
        {
            holdBufferStore.setSize(Vector2f(leftBut.getSize().x + 2, leftBut.getSize().y + 2));
            if (Mouse::isButtonPressed(Mouse::Button::Left) && !lockClick) { swapToHold(); }
        }
        
    }
    void draw(RenderWindow* window)
    {
        window->draw(background);
        grid.draw(window);
        window->draw(nextBufferStore);
        setNextBufferTexture();
        window->draw(textureFrameNextBuffer);
        window->draw(pauseBut);
        window->draw(rotateBut);
        window->draw(fastBut);
        window->draw(smashBut);
        window->draw(leftBut);
        window->draw(rightBut);
        window->draw(holdBufferStore);
        window->draw(textureFrameHoldBuffer);
        window->draw(NEXT);
        window->draw(HOLD);
    }
    void lostMenu(RenderWindow* window)
    {

        RectangleShape fade;
        RectangleShape menuContainer;
        Text BLOCKOUT;
        Text rePlay;
        Text CLOSE;
        Text mainMenu;

        fade.setPosition(Vector2f(0, 0));
        fade.setSize(Vector2f(WIDTH, HEIGHT));
        fade.setFillColor(Color(0, 0, 0, 150));


        menuContainer.setSize(Vector2f(WIDTH / 1.5, HEIGHT / 4));
        menuContainer.setPosition(Vector2f(WIDTH / 2 - menuContainer.getSize().x / 2, HEIGHT / 2 - menuContainer.getSize().y / 2));
        menuContainer.setFillColor(Color(160, 32, 240));
        menuContainer.setOutlineThickness(10);
        menuContainer.setOutlineColor(Color::Black);

        BLOCKOUT.setFont(defaultFont);
        BLOCKOUT.setCharacterSize(HEIGHT / 20);
        BLOCKOUT.setString("BLOCK OUT!");
        BLOCKOUT.setPosition(Vector2f(WIDTH / 2 - BLOCKOUT.getLocalBounds().width / 2, menuContainer.getPosition().y + menuContainer.getSize().y / 10));
        BLOCKOUT.setFillColor(Color::Black);


        rePlay.setFont(defaultFont);
        rePlay.setCharacterSize(HEIGHT / 30);
        rePlay.setString("RETRY");
        rePlay.setPosition(Vector2f(WIDTH / 2 - BLOCKOUT.getLocalBounds().width / 2, menuContainer.getPosition().y + menuContainer.getSize().y / 5 + BLOCKOUT.getLocalBounds().height));
        rePlay.setFillColor(Color::Black);


        mainMenu.setFont(defaultFont);
        mainMenu.setCharacterSize(HEIGHT / 30);
        mainMenu.setString("MAIN MENU");
        mainMenu.setPosition(Vector2f(WIDTH / 2 - BLOCKOUT.getLocalBounds().width / 2, menuContainer.getPosition().y + menuContainer.getSize().y / 4 + BLOCKOUT.getLocalBounds().height + rePlay.getLocalBounds().height));
        mainMenu.setFillColor(Color::Black);

        CLOSE.setFont(defaultFont);
        CLOSE.setCharacterSize(HEIGHT / 30);
        CLOSE.setString("CLOSE");
        CLOSE.setPosition(Vector2f(WIDTH / 2 - BLOCKOUT.getLocalBounds().width / 2, menuContainer.getPosition().y + menuContainer.getSize().y / 2.5 + BLOCKOUT.getLocalBounds().height + rePlay.getLocalBounds().height + mainMenu.getLocalBounds().height));
        CLOSE.setFillColor(Color::Black);


        Vector2f  mousePos;
        mousePos.x = Mouse::getPosition(*window).x;
        mousePos.y = Mouse::getPosition(*window).y;



        if (mousePos.x >= rePlay.getPosition().x && mousePos.x <= rePlay.getPosition().x + rePlay.getLocalBounds().width &&
            mousePos.y >= rePlay.getPosition().y && mousePos.y <= rePlay.getPosition().y + rePlay.getLocalBounds().height)
        {
            rePlay.setCharacterSize(HEIGHT / 28);
            rePlay.setFillColor(Color::Blue);
            if (Mouse::isButtonPressed(Mouse::Button::Left))
            {
                currentState = Playing;
                grid.clear();
                grid.updateGraphics();
                timer = 0;
                timeInc = 1;
                blockOut = false;
                hold = 0;
                holdChoice = -1;
                setHoldBufferStore();
                nextShapeChoice = rand() % 7;
                currentShapeChoice = rand() % 7;
                while (currentShapeChoice == nextShapeChoice) currentShapeChoice = rand() % 7;
                holdChoice = evalRandNext(currentShapeChoice);
                
            }
        }

        if (mousePos.x >= mainMenu.getPosition().x && mousePos.x <= mainMenu.getPosition().x + mainMenu.getLocalBounds().width &&
            mousePos.y >= mainMenu.getPosition().y && mousePos.y <= mainMenu.getPosition().y + mainMenu.getLocalBounds().height)
        {
            mainMenu.setCharacterSize(HEIGHT / 28);
            mainMenu.setFillColor(Color::Blue);
            if (Mouse::isButtonPressed(Mouse::Button::Left))
            {
                currentState = MainMenu;
                grid.clear();
                grid.updateGraphics();
                timer = 0;
                timeInc = 1;
                blockOut = false;
                hold = 0;
                holdChoice = -1;
                setHoldBufferStore();
                nextShapeChoice = rand() % 7;
                currentShapeChoice = rand() % 7;
                while (currentShapeChoice == nextShapeChoice) currentShapeChoice = rand() % 7;
                holdChoice = evalRandNext(currentShapeChoice);
            }
        }

        if (mousePos.x >= CLOSE.getPosition().x && mousePos.x <= CLOSE.getPosition().x + CLOSE.getLocalBounds().width &&
            mousePos.y >= CLOSE.getPosition().y && mousePos.y <= CLOSE.getPosition().y + CLOSE.getLocalBounds().height)
        {
            CLOSE.setCharacterSize(HEIGHT / 28);
            CLOSE.setFillColor(Color::Blue);
            if (Mouse::isButtonPressed(Mouse::Button::Left)) window->close();
        }

        window->draw(background);
        grid.draw(window);
        window->draw(nextBufferStore);
        setNextBufferTexture();
        window->draw(textureFrameNextBuffer);
        window->draw(pauseBut);
        window->draw(rotateBut);
        window->draw(fastBut);
        window->draw(smashBut);
        window->draw(leftBut);
        window->draw(rightBut);
        window->draw(holdBufferStore);
        window->draw(textureFrameHoldBuffer);
        window->draw(NEXT);
        window->draw(HOLD);

        window->draw(fade);
        window->draw(menuContainer);
        window->draw(CLOSE);
        window->draw(rePlay);
        window->draw(mainMenu);
        window->draw(BLOCKOUT);
    }
    void mainMenu(RenderWindow* window)
    {
        Texture backTexture;
        RectangleShape backgroundFrame;

        Text PLAY;
        Text CLOSE;
        PLAY.setFont(defaultFont);
        CLOSE.setFont(defaultFont);

        backTexture.loadFromFile("menuBack.PNG");
        backgroundFrame.setTexture(&backTexture);
        backgroundFrame.setPosition(Vector2f(0, 0));
        backgroundFrame.setSize(Vector2f(WIDTH, HEIGHT));

        PLAY.setString("PLAY");
        CLOSE.setString("CLOSE");

        PLAY.setCharacterSize(HEIGHT / 20);
        CLOSE.setCharacterSize(HEIGHT / 20);

        PLAY.setFillColor(Color(255, 68, 204));
        CLOSE.setFillColor(Color(255, 68, 204));
        
        PLAY.setPosition(Vector2f(WIDTH / 7, HEIGHT / 2)); 
        CLOSE.setPosition(Vector2f(WIDTH / 7, HEIGHT / 1.7 + PLAY.getLocalBounds().height));

        Vector2f mousePos;
        mousePos.x = Mouse::getPosition(*window).x;
        mousePos.y = Mouse::getPosition(*window).y;

        if (mousePos.x >= PLAY.getPosition().x && mousePos.x <= PLAY.getPosition().x + PLAY.getLocalBounds().width &&
            mousePos.y >= PLAY.getPosition().y && mousePos.y <= PLAY.getPosition().y + PLAY.getLocalBounds().width)
        {
            PLAY.setCharacterSize(HEIGHT / 19);
            PLAY.setFillColor(Color::Blue);
            if (Mouse::isButtonPressed(Mouse::Button::Left)) {
                currentState = Playing; timeInc = 1;
            }
        }
        if (mousePos.x >= CLOSE.getPosition().x && mousePos.x <= CLOSE.getPosition().x + CLOSE.getLocalBounds().width &&
            mousePos.y >= CLOSE.getPosition().y && mousePos.y <= CLOSE.getPosition().y + CLOSE.getLocalBounds().width)
        {
            CLOSE.setCharacterSize(HEIGHT / 19);
            CLOSE.setFillColor(Color::Blue);
            if (Mouse::isButtonPressed(Mouse::Button::Left)) window->close();
        }

        window->draw(backgroundFrame);
        window->draw(PLAY);
        window->draw(CLOSE);

    }
};

int main()
{
    Game game;

    RenderWindow window(VideoMode(WIDTH, HEIGHT), "Tetris", Style::Titlebar | Style::Close);
    Event ev;
    //window.setFramerateLimit(5);

    

    while (window.isOpen())
    {
        while (window.pollEvent(ev)) {
            switch (ev.type) {
            case Event::Closed:
                window.close();
                break;
            case Event::KeyPressed:
                if (ev.key.code == Keyboard::Escape) {
                    window.close();
                }
                if (ev.key.code == Keyboard::Right && game.timeInc) {
                    game.slideNext(1);
                }
                if (ev.key.code == Keyboard::Left && game.timeInc) {
                    game.slideNext(-1);
                }
                if (ev.key.code == Keyboard::Down && game.timeInc) {
                    if (!game.getFastDescend())
                    {
                        game.setFastDescend(true);
                    }
                    else
                    {
                        game.setFastDescend(false);
                    }
                }
                if (ev.key.code == Keyboard::Space && game.timeInc) {
                    game.rotateNext();
                }
                if (ev.key.code == Keyboard::S && game.timeInc) {
                    game.smashNext();
                }
                if (ev.key.code == Keyboard::H && game.timeInc) {
                    game.swapToHold();
                
                }
            case Event::MouseButtonReleased:
                if (ev.mouseButton.button == Mouse::Left)
                {
                    game.editLockClock(false);
                }
            }
        }
        window.clear();

        switch (game.getCurrentState())
        {
        case MainMenu:
            game.mainMenu(&window);
            break;
        case Playing:
            game.manageContollers(&window);
            game.play();
            game.draw(&window);
            break;
        case Lost:
            game.lostMenu(&window);
            break;
        default:
            break;
        }



        window.display();
    }
}