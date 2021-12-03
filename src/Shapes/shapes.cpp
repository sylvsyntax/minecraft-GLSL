#include "shapes.h"
using namespace std;

# define M_PI           3.14159265358979323846  /* pi */

//-----------------------------------//
//       3 DIMENSIONAL VECTORS       //
//-----------------------------------//

vec3::vec3(float x, float y, float z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }
vec3::vec3() {
        this->x = 0;
        this->y = 0;
        this->z = 0;
    }
vec3::vec3(float zed) {
        this->x = zed;
        this->y = zed;
        this->z = zed;
    }

vec3::setPts(vec3 pt) {
        x = pt.getx();
        y = pt.gety();
        z = pt.getz();
    }
vec3::addPt(vec3 pt) {
        x += pt.x;
        y += pt.y;
        z += pt.z;
    }
vec3::scalePt(vec3 pt) {
        x *= pt.x;
        y *= pt.y;
        z *= pt.z;
    }



vec3 getMiddle(vec3 pt1, vec3 pt2) {
    vec3 returnval;
    returnval.setx((pt1.getx() + pt2.getx()) / 2);
    returnval.sety((pt1.gety() + pt2.gety()) / 2);
    returnval.sety((pt1.getz() + pt2.getz()) / 2);
    return returnval;
}





//-----------------------------------//
//             TRIANGLES             //
//-----------------------------------//

triangle::triangle(vec3 pt1, vec3 pt2, vec3 pt3) {
        this->pt1 = pt1;
        this->pt2 = pt2;
        this->pt3 = pt3;
    }

triangle::triangle() {
        pt1 = vec3(0);
        pt2 = vec3(0);
        pt3 = vec3(0);
    }

triangle::rotateAcrossAxis(char axis) {
        vec3 temp;
        switch (axis) {
            //Flipping on z allows for making a face of equal size
            //This only works if the triangle is facing on the x axis
        case 'x':
            temp = pt1;
            pt1 = pt2;
            pt2 = temp;
            pt3 = vec3(pt1.getx(), pt2.gety(), pt3.getz());
            return;
        case 'y':

            return;
        case 'z':

            return;
            //Flips the shape by switching pt 1 and pt 3 so it can read properly.
        case 'b':
            temp = pt3;
            pt3 = pt1;
            pt1 = temp;
        }
    }

    //These allow us to set points with vectors as input variables
triangle::setPt1(vec3 newpt) {
        pt1 = newpt;
    }
triangle::setPt2(vec3 newpt) {
        pt2 = newpt;
    }
triangle::setPt3(vec3 newpt) {
        pt3 = newpt;
    }

triangle::translate(vec3 vector) {
        pt1.addPt(vector);
        pt2.addPt(vector);
        pt3.addPt(vector);
    }
};



//-----------------------------------//
//               FACES               //
//-----------------------------------//


face::face(triangle* t1, triangle* t2) {
        this->t1 = t1;
        this->t2 = t2;
    }
    //Make a face with no triangles
face::face() {
        t1 = new triangle;
        t2 = new triangle;
    }
    //Make a face with 4 points (counter clockwise)
face::face(vec3 pt1, vec3 pt2, vec3 pt3, vec3 pt4) {
        t1 = new triangle(pt1, pt2, pt4);
        t2 = new triangle(pt4, pt2, pt3);
    }
    //Make a face with 6 points (counter clockwise)
face::face(vec3 pt1, vec3 pt2, vec3 pt3, vec3 pt4, vec3 pt5, vec3 pt6) {
        t1 = new triangle(pt1, pt2, pt3);
        t2 = new triangle(pt4, pt5, pt6);
    }

    //This forces a position for a certain axis of points in a face
    //Don't do this, it's kinda dumb.
face::forceAxis(char axis, int num) {
        switch (axis) {
        case 'x':
            t1->pt1 = vec3(num, t1->pt1.gety(), t1->pt1.getz());
            t1->pt2 = vec3(num, t1->pt2.gety(), t1->pt2.getz());
            t1->pt3 = vec3(num, t1->pt3.gety(), t1->pt3.getz());
            t2->pt1 = vec3(num, t2->pt1.gety(), t2->pt1.getz());
            t2->pt2 = vec3(num, t2->pt2.gety(), t2->pt2.getz());
            t2->pt3 = vec3(num, t2->pt3.gety(), t2->pt3.getz());
            return;
        case 'y':
            t1->pt1 = vec3(t1->pt1.getx(), num, t1->pt1.getz());
            t1->pt2 = vec3(t1->pt2.getx(), num, t1->pt2.getz());
            t1->pt3 = vec3(t1->pt3.getx(), num, t1->pt3.getz());
            t2->pt1 = vec3(t2->pt1.getx(), num, t2->pt1.getz());
            t2->pt2 = vec3(t2->pt2.getx(), num, t2->pt2.getz());
            t2->pt3 = vec3(t2->pt3.getx(), num, t2->pt3.getz());
            return;
        case 'z':
            t1->pt1 = vec3(t1->pt1.getx(), t1->pt1.gety(), num);
            t1->pt2 = vec3(t1->pt2.getx(), t1->pt2.gety(), num);
            t1->pt3 = vec3(t1->pt3.getx(), t1->pt3.gety(), num);
            t2->pt1 = vec3(t2->pt1.getx(), t2->pt1.gety(), num);
            t2->pt2 = vec3(t2->pt2.getx(), t2->pt2.gety(), num);
            t2->pt3 = vec3(t2->pt3.getx(), t2->pt3.gety(), num);
            return;
        }
    }

    //ALL rotations are by the (0, 0, 0) point
    //Basically we ignore x and flip z with y
face::rotateY90() {
        t2->pt3.setPts(vec3(t2->pt3.getx(), t2->pt3.getz(), t2->pt3.gety()));
        t1->pt1.setPts(vec3(t1->pt1.getx(), t1->pt1.getz(), t1->pt1.gety()));
        t2->pt2.setPts(vec3(t2->pt2.getx(), t2->pt2.getz(), t2->pt2.gety()));
    }
    //Basically we ignore y and flip x with z
face::rotateX90() {
        t2->pt3.setPts(vec3(t2->pt3.getz(), t2->pt3.gety(), t2->pt3.getx()));
        t2->pt1.setPts(vec3(t2->pt1.getz(), t2->pt1.gety(), t2->pt1.getx()));
        t1->pt2.setPts(vec3(t1->pt2.getz(), t1->pt2.gety(), t1->pt2.getx()));
    }

    //Flips the shapes entirely, both triangles have their own methods.
face::flip() {
        t1->rotateAcrossAxis('b');
        t2->rotateAcrossAxis('b');
    }

    //This allows us to translate every
    //point of a shape by a vector 3.
face::translate(vec3 pt) {
        t1->pt1.addPt(pt);
        t1->pt2.addPt(pt);
        t1->pt3.addPt(pt);
        t2->pt1.addPt(pt);
        t2->pt2.addPt(pt);
        t2->pt3.addPt(pt);
    }

    //This allows us to scale every
    //point of a shape by a vector 3.
face::scale(vec3 pt) {
        t1->pt1.scalePt(pt);
        t1->pt2.scalePt(pt);
        t1->pt3.scalePt(pt);
        t2->pt1.scalePt(pt);
        t2->pt2.scalePt(pt);
        t2->pt3.scalePt(pt);
    }

    //This allows us to remove our dependencies from the triangles
    //We were using prior
face::removeConstructors() {
        triangle* newptr1 = new triangle;
        triangle* newptr2 = new triangle;
        newptr1->pt1.setPts(t1->pt1);
        newptr1->pt2.setPts(t1->pt2);
        newptr1->pt3.setPts(t1->pt3);
        newptr2->pt1.setPts(t2->pt1);
        newptr2->pt2.setPts(t2->pt2);
        newptr2->pt3.setPts(t2->pt3);
        t1 = newptr1;
        t2 = newptr2;
    }



//-----------------------------------//
//          SERIES OF POINTS         //
//-----------------------------------//


seriesOfPoints::seriesOfPoints(vec3 pt[], const int size) {
        this->pt = new vec3[size];
        this->size = size;
    }

seriesOfPoints::seriesOfPoints() {
        this->pt = new vec3;
        this->size = 0;
    }

seriesOfPoints::setPt(int num, vec3 newpt) {
        pt[num] = newpt;
    }

seriesOfPoints::addPt(vec3 newpt) {
        vec3* oldpt;
        oldpt = pt;
        pt = nullptr;
        size++;

        pt = new vec3[size];        //pointer error here
        for (int i = 0; i < size - 1; i++) {
            pt[i] = oldpt[i];
        }
        pt[size - 1] = newpt;
        delete[] oldpt;
        oldpt = nullptr;
    }

seriesOfPoints::translate(vec3 vector) {
        for (int i = 0; i < size; i++) {
            pt[i].addPt(vector);
        }
    }

seriesOfPoints::scale(vec3 vector) {
        for (int i = 0; i < size; i++) {
            pt[i].scalePt(vector);
        }
    }

seriesOfPoints::print() {
        for (int i = 0; i < size; i++) {
            vec3 vec = pt[i];
            cout << "pt " << i << " -- x: " << vec.getx() << "| y: " << vec.gety() << "| z: " << vec.getz() << "\n";
        }
    }
    
    void nullOut() {
        size = 0;
        delete[] pt;
        pt = nullptr;
    }

//-----------------------------------//
//          SERIES OF POINTS         //
//-----------------------------------//



    seriesOfMultiplePoints::seriesOfMultiplePoints(vec3 pt[], const int size) {
        this->series = new seriesOfPoints[size];
        this->size = size;
    }

    seriesOfMultiplePoints::seriesOfMultiplePoints() {
        this->series = new seriesOfPoints();
        this->size = 0;
    }

    seriesOfMultiplePoints::addSeries(seriesOfPoints ser) {
        seriesOfPoints* oldser;
        oldser = series;
        series = nullptr;
        size++;

        series = new seriesOfPoints[size];        //pointer error here
        for (int i = 0; i < size - 1; i++) {
            series[i] = oldser[i];
        }
        series[size - 1] = ser;
        delete[] oldser;
        oldser = nullptr;
    }
    
seriesOfMultiplePoints::print() {
        for (int f = 0; f < size; f++) {
            for (int i = 0; i < series[f].size; i++) {
                vec3 vec = series[f].pt[i];
                cout << "pt " << i << " -- x: " << vec.getx() << "| y: " << vec.gety() << "| z: " << vec.getz() << "\n";
            }
        }
    }
    
seriesOfMultiplePoints::removeConstructorsOnEnd() {
        int sizeLast = series[size - 1].size;
        seriesOfPoints *newser = new seriesOfPoints(new vec3[sizeLast], sizeLast);
        
        for(int i = 0; i < sizeLast; i++){
            newser->pt[i] = series[size - 1].pt[i];
        }
        series[size - 1] = *newser;
    }

makeBox(){
        face box[6];

        //-----------------------------------//
        //       BUILDING THE SHAPE          //
        //-----------------------------------//

        //This Assigns the first face to the box. The bottom left triangle
        /*
                      /|
                    /  |
                  /____|

         */
        vec3 defaultpt1 = vec3(0, 1, 0);
        vec3 defaultpt2 = vec3(1, 0, 0);
        vec3 defaultpt3 = vec3(0);

        //And these are the default triangles used for nef. The singular face we will manipulate to build this box.
        triangle trg = triangle(defaultpt1, defaultpt2, defaultpt3);
        triangle trg2 = triangle(defaultpt1, defaultpt2, defaultpt3);
        //The rotation is done to complete the face.
        trg2.rotateAcrossAxis('x');

        //Then we assign the triangles to the face that we will be manipulating
        face nef = face(&trg, &trg2);
        box[0] = nef;
        box[0].removeConstructors();

        //This makes the bottom of the box
        //Essentially we rotate it 90 degrees backwards so it's facing inside
        //Than we flip the shape by switching the direction of the triangles
        nef.rotateY90();
        nef.flip();
        box[1] = nef;
        box[1].removeConstructors();

        //We can then move the shape up
        //And flip it again
        nef.translate(vec3(0, 1, 0));
        nef.flip();
        box[2] = nef;
        box[2].removeConstructors();

        //Now we reset to the default position and flip
        //the triangles again
        trg = triangle(defaultpt1, defaultpt2, defaultpt3);
        trg2 = triangle(defaultpt1, defaultpt2, defaultpt3);
        trg2.rotateAcrossAxis('x');

        //We translate the shape backwards and flip it so it makes the back wall
        nef.translate(vec3(0, 0, 1));
        nef.flip();
        box[3] = nef;
        box[3].removeConstructors();

        //Than we move the shape the opposite direction
        //Repeating the steps back to normal so its facing
        //the original position
        nef.translate(vec3(0, 0, -1));
        nef.flip();

        //Now we can rotate the shape sideways and flip it
        nef.rotateX90();
        nef.flip();
        box[4] = nef;
        box[4].removeConstructors();

        //Than we translate it by the x value so it can be in
        //the propper position, and we flip it so it faces
        //the right direction
        nef.translate(vec3(1, 0, 0));
        nef.flip();
        box[5] = nef;
        box[5].removeConstructors();
}
