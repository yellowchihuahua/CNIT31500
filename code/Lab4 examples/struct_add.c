#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

// Vector2D struct and functions
typedef struct Vector2D
{
    float x, y;
} Vector2D;

// return a new Vector2D, v3,  based on the sum of v1 and v2
Vector2D add_vector2d(const Vector2D* v1, const Vector2D* v2)
{
    Vector2D tmp;
    tmp.x = v1->x + v2->x;
    tmp.y = v1->y + v2->y;
    return tmp;
}

// return a new Vector2D, v3,  based on the difference of v1 and v2
Vector2D subtract_vector2d(const Vector2D* v1, const Vector2D* v2)
{
    Vector2D tmp;
    tmp.x = v1->x - v2->x;
    tmp.y = v1->y - v2->y;
    return tmp;
}

// find Euclidean distance by taking the square root of the sum-of-squares of each element in the vector (2 elements in this case: Ex. sqrt(1^2 + 1^2))
float magnitude_vector2d(const Vector2D* v)
{
    return sqrt(v->x * v->x + v->y * v->y);
}

// find distance between two vectors by getting the magnitude of the difference vector
float distance_vector2d(const Vector2D* v1, const Vector2D* v2)
{
    Vector2D tmp = subtract_vector2d(v1, v2);
    return magnitude_vector2d(&tmp);
}

// print Vector2D elements
void print_vector2d(const Vector2D* v)
{
    printf("[%f, %f]\n", v->x, v->y);
}

// Vector2DList (dynamic Vector2D array) struct and functions
// notice the Vector2D pointer. We don't know how large the array will ultimately be, so we leave it a pointer for dynamic allocation (resizing)
typedef struct Vector2DList
{
    unsigned int length;
    Vector2D* vectors;
} Vector2DList;

// initialize Vector2DList, since it has a pointer; we want to make sure it's assigned initialized before we use it
void init_v2dv(Vector2DList* v2dv)
{
    v2dv->length = 0;
    v2dv->vectors = NULL;
}

// we increment length, then reallocate an extra "block" of space for a Vector2D struct
void push_back_v2dv(Vector2DList* v2dv, const Vector2D* data)
{
    v2dv->length++;
    v2dv->vectors = (Vector2D*)realloc(v2dv->vectors, v2dv->length * sizeof(Vector2D));
    v2dv->vectors[v2dv->length - 1] = *data;
}

// we decrement length, then reallocate one less "block" of space for Vector2D
void pop_back_v2dv(Vector2DList* v2dv)
{
    if (v2dv->length == 0) {
        return;  // No elements to remove
    }

    v2dv->length--;
    if (v2dv->length > 0) {
        v2dv->vectors = (Vector2D*)realloc(v2dv->vectors, v2dv->length * sizeof(Vector2D));
    } else {
        // If no more elements left, free the memory and set pointer to NULL
        free(v2dv->vectors);
        v2dv->vectors = NULL;
    }
}

// print each Vector2D
void print_v2dv(Vector2DList* v2dv)
{
    for(int i = 0; i < v2dv->length; i++)
        print_vector2d(&v2dv->vectors[i]);
}

// free the memory space our pointers are using
void free_v2dv(Vector2DList* v2dv)
{
    if(v2dv->vectors)
        free(v2dv->vectors);

    free(v2dv);
}

int main()
{
    // we can initialize these object like arrays, we simply assign proper data types
    Vector2D v1 = {1,0}, v2 = {0,1}, v3;

    // we can also assign the values later (but this is not always the safest option)
    // v1.x = 1; v1.y = 0;
    // v2.x = 0; v2.y = 1;
    v3 = add_vector2d(&v1, &v2);
    v3 = subtract_vector2d(&v3, &v2);

    // dynamic memory allocation... if we aren't pointing to an existing variable, we need to create memory space for the pointer to store information. In this case I only want one list, but the above function show you can reallocate space when necessary.
    // this is optional, but in this way the associated pointers start as NULL.
    Vector2DList proto;
    Vector2DList* v2dv = &proto;
    init_v2dv(v2dv);
    
    // add a Vector2D to Vector2DList
    push_back_v2dv(v2dv, &v1);
    print_v2dv(v2dv);
    printf("%d\n", v2dv->length);

    // add a Vector2D to Vector2DList
    push_back_v2dv(v2dv, &v2);
    print_v2dv(v2dv);
    printf("%d\n", v2dv->length);

    // remove last Vector2D of Vector2DList
    pop_back_v2dv(v2dv);
    print_v2dv(v2dv);
    printf("%d\n", v2dv->length);
    
    // remove last Vector2D of Vector2DList
    pop_back_v2dv(v2dv);
    print_v2dv(v2dv);
    printf("%d\n", v2dv->length);

    // Free the allocated memory before program exit
    free_v2dv(v2dv);

    return 0;
}