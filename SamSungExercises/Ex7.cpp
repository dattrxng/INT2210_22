#include <bits/stdc++.h>
using namespace std;


bool isValid(int screen[][8], int m, int n, int x, int y,
             int prevC, int newC)
{
    if (x < 0 || x >= m || y < 0 || y >= n
        || screen[x][y] != prevC || screen[x][y] == newC)
        return false;
    return true;
}


void floodFill(int screen[][8], int m, int n, int x, int y,
               int prevC, int newC)
{
    queue<pair<int, int> > queue;


    pair<int, int> p(x, y);
    queue.push(p);

    screen[x][y] = newC;


    while (queue.size() > 0) {
        pair<int, int> currPixel = queue.front();
        queue.pop();

        int posX = currPixel.first;
        int posY = currPixel.second;


        if (isValid(screen, m, n, posX + 1, posY, prevC,
                    newC)) {

            screen[posX + 1][posY] = newC;
            p.first = posX + 1;
            p.second = posY;
            queue.push(p);
        }

        if (isValid(screen, m, n, posX - 1, posY, prevC,
                    newC)) {
            screen[posX - 1][posY] = newC;
            p.first = posX - 1;
            p.second = posY;
            queue.push(p);
        }

        if (isValid(screen, m, n, posX, posY + 1, prevC,
                    newC)) {
            screen[posX][posY + 1] = newC;
            p.first = posX;
            p.second = posY + 1;
            queue.push(p);
        }

        if (isValid(screen, m, n, posX, posY - 1, prevC,
                    newC)) {
            screen[posX][posY - 1] = newC;
            p.first = posX;
            p.second = posY - 1;
            queue.push(p);
        }
    }
}


