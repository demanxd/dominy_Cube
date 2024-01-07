/* MIT License
 *
 * Copyright (c) 2024 Dmitry Shapovalov
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "Matrix.h"

/*auxiliary structure for processing rotation angles of cube*/
struct rotateAngle
{
    float _X = 0;
    float _Y = 0;

    rotateAngle(){};
    rotateAngle(float x,float y):_X(x),_Y(y){};

    void plusOperator(const rotateAngle& rhs)
    {
        this->_X += rhs._X;
        this->_Y += rhs._Y;

        if (_X > 360)
            _X -= 360;
        if (_Y > 360)
            _Y -= 360;
    }

    rotateAngle& operator+=(const rotateAngle& rhs)
    {
        plusOperator(rhs);
        return *this;
    }

    rotateAngle operator+(const rotateAngle& rhs )
    {
        plusOperator(rhs);
        return *this; // return the result by reference
    }
};

/*base model class*/
class model
{
public:
    static model& getInstance()
    {
        static model instance; // Guaranteed to be destroyed.
        // Instantiated on first use.
        return instance;
    }

    void identityFunction(){
        matrixIdentityFunction(this->_modelMatrix);
    }

    void rotate(rotateAngle angle) {
        this->_rotateAngle += angle;
        matrixRotateX(this->_modelMatrix, this->_rotateAngle._X);
        matrixRotateY(this->_modelMatrix, this->_rotateAngle._Y);
    }

    void translation(float x, float y, float z){
        matrixTranslate(this->_modelMatrix, x,y,z);
    }

    float* getValue(){
        return _modelMatrix;
    }

    float _modelMatrix[16];
    rotateAngle _rotateAngle;

    model() {}
};

/*modelView singletone class for easy access from any position*/
class modelView
{
public:
    static modelView& getInstance()
    {
        static modelView instance;
        return instance;
    }

    void identityFunction(){
        this->matrix.identityFunction();
    }

    void rotateUp(){
        this->matrix.rotate(rotateAngle(1.0, 0.0));
    }

    void rotateLeft(){
        this->matrix.rotate(rotateAngle(0.0, 1.0));
    }

    void translation(float x, float y, float z){
        this->matrix.translation(x, y, z);
    }

    float* getValue(){
        return matrix.getValue();
    }

private:
    model matrix;

    modelView() {}
    modelView(modelView const&);
    void operator=(modelView const&);
};

/*modelProjection singletone class for easy access from any position*/
class modelProjection
{
public:
    static modelProjection& getInstance()
    {
        static modelProjection instance;
        return instance;
    }

    float* getValue(){
        return matrix.getValue();
    }

private:
    model matrix;

    modelProjection() {}
    modelProjection(modelProjection const&);
    void operator=(modelProjection const&);
};