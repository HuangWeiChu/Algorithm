#include <bits/stdc++.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <string>

#define GLEW_STATIC
using namespace std;

vector <pair<int,int>> vectorPoint;
vector <pair<int,int>> pointresult;

int findout(pair<int,int> p1, pair<int,int> p2, pair<int,int> p) {
    int check = ((p1.first - p.first) * (p2.second - p.second)) - ((p2.first - p.first) * (p1.second - p.second));
    
    if (check > 0) {
        return 1;
    } else if (check < 0) {
        return -1;
    } else {
        return 0;
    }
}

void quickHull(vector<pair<int,int>> a, pair<int,int> p1, pair<int,int> p2, int side) {
    int index = -1;
    int distanceMax = 0;
    
    for (int i = 0;i<a.size();i++) {
        int temp = (abs( ((p2.second - p1.second) * a[i].first) - ((p2.first - p1.first) * a[i].second) + (p2.first * p1.second) - (p2.second * p1.first) )) / sqrt(pow( (p2.second - p1.second), 2 ) + pow( (p2.first - p1.first), 2 ));
        
        if ((findout(p1, p2, a[i]) == side) && (temp > distanceMax)) {
            index = i;
            distanceMax = temp;
        }
    }
    
    //找到起始點
    if (index == -1) {
        pair<int,int> point1 = make_pair(p1.first, p1.second);
        pair<int,int> point2 = make_pair(p2.first, p2.second);
        
        auto it1 = find(pointresult.begin(), pointresult.end(), point1);
        if (it1 == pointresult.end()) {
            pointresult.push_back(point1);
        }
        auto it2 = find(pointresult.begin(), pointresult.end(), point2);
        if (it2 == pointresult.end()) {
            pointresult.push_back(point2);
        } else {
            quickHull(a, p1, a[index], findout(a[index], p1, p2));
            quickHull(a, p2, a[index], findout(a[index], p2, p1));
        }
    }
}

bool Sort(pair<int,int> a, pair<int,int> b) {
    if ((a.first - midpoint.first >= 0) && (b.first - midpoint.first < 0))
        return true;
    if ((a.first - midpoint.first < 0) && (b.first - midpoint.first >= 0))
        return true;
    if ((a.first - midpoint.first == 0) && (b.first - midpoint.first == 0)) {
        if ((a.second - midpoint.second >= 0) || (b.second - midpoint.second >= 0))
            return a.second > b.second;
        return b.second > a.second;
    }
    
    int det = (a.first - midpoint.first) * (b.second - midpoint.second) - (b.first - midpoint.first) * (a.second - midpoint.second);
    if(det < 0)
        return true;
    if(det > 0)
        return false;
    
    int d1 = (a.first - midpoint.first) * (a.first - midpoint.first) + (a.second - midpoint.second) * (a.second - midpoint.second);
    int d2 = (b.first - midpoint.first) * (b.first - midpoint.first) + (b.second - midpoint.second) * (b.second - midpoint.second);
    
    return d1 > d2
}

void drawline() {
    glColor3f(0.0, 0.0, 1.0);
    
    pointresult.push_back(pointresult[0]);
    for (int i = 0; i<(int) pointresult.size()-1; ++i) {
        glLineWidtg(3.0);
        
        glBegin(GL_LINES);
            int x1  = pointresult[i].first;
            int y1  = pointresult[i].second;
            int x2  = pointresult[i+1].first;
            int y2  = pointresult[i+1].second;
            glVertex2f((float) x1 / (float) 110, (float) y1 / (float) 110);
            glVertex2f((float) x2 / (float) 110, (float) y2 / (float) 110);
        glEnd();
    }
    glFlush();
}

void drawCartesian() {
    glColor3f(1.0, 1.0, 1.0);
    
    glLineWidth(3.0);
    
    glBegin(GL_LINES);
        glVertex2f(-1.0, 0.0);
        glVertex2f(1.0, 0.0);
    glEnd();
    glFlush();
    
    glBegin(GL_LINES);
        glVertex2f(0.0, -1.0);
        glVertex2f(0.0, 1.0);
    glEnd();
    glFlush();
}

void drawpoint() {
    glColor3f(1.0, 1.0, 1.0);
    
    for (int i = 0; i<(int) vectorPoint.size(); ++i) {
        glPointSize(4.0);
        
        glBegin(GL_LINES);
            int x  = vectorPoint[i].first;
            int y  = vectorPoint[i].second;
            glVertex2f((float) x / (float) 110, (float) y / (float) 110);
        glEnd();
    }
    glFlush();
}

int main() {
    
    if (glfwInit()) {
        GLFWwindow * window = glfwCreatWindow(1080, 720, "Convex htll Algorithm", NULL, NULL);
        glewExperimental = true;
        glewInit();
        glfwMakeContexCurreent(window);
        
        string command;
        do {
            vectorPoint.clear();
            pointresult.clear();
            
            glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUDDER_BIT);
            drawCartesian();
            glfwSwapBuffers(window);
            glfwPollEvents();
            
            int mpoints;
            cout<<"Enter many point = ";
            cin>>mpoints;
            
            int xTemp;
            int yTemp;
            
            for (int i = 0; i < mpoints; ++i) {
                ifstream ifptr("sample.txt",ifstream::in);
                if(ifptr.is_open()) {
                    while(!ifptr.eof()) {
                        ifptr >> xTemp;
                        ifptr >> yTemp;
                        pait<int, int> temppoint(xTemp,yTemp);
                        auto it = find(vectorPoint.begin(),vectorPoint.end(),temppoint);
                        
                        if(it == vectorPoint.end()) {
                            vectorPoint.push_back(temppoint);
                            printf("file results = (%d,%d)\n", xTemp, yTemp);
                        }
                    }
                }
                ifptr.close();
            }
            
            int midpointX = 0, midpointY = 0;
            for(int i = 0; i < (int) vectorPoint.size(); ++i) {
                midpointX += vectorPoint[i].first;
                midpointY += vectorPoint[i].second;
            }
            
            midpointX = midpointX / (int)vectorPoint.size();
            midpointY = midpointY / (int)vectorPoint.size();
            midpoint = make_pair(midpointX, midpointY);
            
            clock+t t1, t2;
            t1 = clock();
            
            int indexMin = 0, indexMax = 0;
            for (int i = 1; i < mpoints; i++) {
                indexMin = vectorPoint[i].first < vectorPoint[indexMin].first? i : indexMin;
                indexMin = vectorPoint[i].first < vectorPoint[indexMax].first? i : indexMax;
            }
            
            quickHull(vectorPoint, vectorPoint[indexMin], vectorPoint[indexMax], 1);
            quickHull(vectorPoint, vectorPoint[indexMin], vectorPoint[indexMax], -1);
            
            t2 = clock();
            float diff ((float)t2 - (float)t1);
            float seconds = diff / CLOCKS_PER_SEC;
            printf("computes results (outside input & output) = %f seconds \n", seconds);
            
            sort(pointresult.begin(), pointresult.end(), Sort);
            
            printf("Convex hull results = \n");
            for(int i = 0;i < (int) pointresult.size(); ++i) {
                cout << "(" <<pointresult[i].first << ", " << pointresult[i].second << ") \n";
            }
            
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUDDER_BIT);
            drawCartesian();
            drawpoint();
            drawline();
            glfwSwapBuffers(window);
            glfwPollEvents();
            
            printf("\nThe result of the convex htll hae been drawn.\n");
            printf("Reset again? (y/n)\n");
            cin >> comand;
        }while(comand == "y");
        
        glfwTerminate();
    }
    return 0;
}