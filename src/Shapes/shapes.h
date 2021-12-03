#include <iostream>
#include <fstream>
#include <time.h>
#include <math.h>
using namespace std;

#ifndef SHAPE_CLASS_H
#define SHAPE_CLASS_H

/*
 The intention of this library is to allow my small brain to make shapes easily
 Since I already did the work previously so this will just make everything make
 sense to me.
 
 It includes:
    - Vector 3s
    - Triangles
    - Faces
    - Series of points
    - Series of series of points
 */


//-----------------------------------//
//       3 DIMENSIONAL VECTORS       //
//-----------------------------------//

class vec3 {
public:
    vec3(float x, float y, float z);
    vec3();
    vec3(float zed);

    float getx() { return x; }
    float gety() { return y; }
    float getz() { return z; }

    void setx(float num) { x = num; }
    void sety(float num) { y = num; }
    void setz(float num) { z = num; }
    void setPts(vec3 pt);
    void addPt(vec3 pt);
    void scalePt(vec3 pt);

private:
    float x;
    float y;
    float z;
};

vec3 getMiddle(vec3 pt1, vec3 pt2);





//-----------------------------------//
//             TRIANGLES             //
//-----------------------------------//

//Triangles consist of 3 points and can be manipulated in many different ways
class triangle {
public:
    vec3 pt1;
    vec3 pt2;
    vec3 pt3;

    triangle(vec3 pt1, vec3 pt2, vec3 pt3);
    triangle();

    void rotateAcrossAxis(char axis);

    //These allow us to set points with vectors as input variables
    void setPt1(vec3 newpt);
    void setPt2(vec3 newpt);
    void setPt3(vec3 newpt);
    void translate(vec3 vector);
};



//-----------------------------------//
//               FACES               //
//-----------------------------------//


class face {
public:
    //Make a face from two existing triangles
    face(triangle* t1, triangle* t2);
    //Make a face with no triangles
    face();
    //Make a face with 4 points (counter clockwise)
    face(vec3 pt1, vec3 pt2, vec3 pt3, vec3 pt4);
    //Make a face with 6 points (counter clockwise)
    face(vec3 pt1, vec3 pt2, vec3 pt3, vec3 pt4, vec3 pt5, vec3 pt6);

    triangle* t1;
    triangle* t2;

    //This forces a position for a certain axis of points in a face
    //Don't do this, it's kinda dumb.
    void forceAxis(char axis, int num);

    //ALL rotations are by the (0, 0, 0) point
    //Basically we ignore x and flip z with y
    void rotateY90();
    //Basically we ignore y and flip x with z
    void rotateX90();

    //Flips the shapes entirely, both triangles have their own methods.
    void flip();

    //This allows us to translate every
    //point of a shape by a vector 3.
    void translate(vec3 pt);

    //This allows us to scale every
    //point of a shape by a vector 3.
    void scale(vec3 pt);

    //This allows us to remove our dependencies from the triangles
    //We were using prior
    void removeConstructors();


};



//-----------------------------------//
//          SERIES OF POINTS         //
//-----------------------------------//


class seriesOfPoints {
public:
    vec3* pt;
    int size;

    seriesOfPoints(vec3 pt[], const int size);

    seriesOfPoints();

    void setPt(int num, vec3 newpt);

    void addPt(vec3 newpt);

    void translate(vec3 vector);

    void scale(vec3 vector);

    void print();
    
    void nullOut();
};

//-----------------------------------//
//    SERIES OF SERIES OF POINTS     //
//-----------------------------------//


class seriesOfMultiplePoints {
public:
    seriesOfPoints* series;
    int size;

    seriesOfMultiplePoints(vec3 pt[], const int size);

    seriesOfMultiplePoints();

    void addSeries(seriesOfPoints ser);
    
    void print();
    
    void removeConstructorsOnEnd();
};


void makeBox();

#endif
