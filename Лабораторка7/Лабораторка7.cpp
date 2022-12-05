#define _CRT_SECURE_NO_WARNINGS 

#include <stdio.h> 
#include <malloc.h> 

typedef enum Direction_t {
    RIGHT,
    LEFT,
    UP,
    DOWN
} Direction;

typedef struct Params_t {
    int i;
    int j;
    Direction direction;
    int step;
    int counter;
} Params;

int getNext(Params& it, int width, int height);
int isValid(Params& it, int width, int height);
void direction(Params& it);
void step(Params& it);
void dirUp(Params& it);
void sort(double** mat, int width, int height);
double OutNumbers(double** mat, Params it);

void swap(double* pa, double* pb);
void swapInto(double** matrix, Params pa, Params pb);

double** alloc(int width, int height);

void inputMatrix(double** mat, int width, int height);
void outputMatrix(double** mat, int width, int height);
void readValue(int* width, int* height);
int check(int width, int height);
void workMatrix(double** matrix, int width, int height);

void funcFree(double** mat, int width);

int main() {
    int width, height;
    readValue(&width, &height);
    if (check(width, height)) {
        double** matrix = alloc(width, height);
        if (matrix != NULL) {
            workMatrix(matrix, width, height);
            funcFree(matrix, width);
        }
        else
            printf("Memory dont allocated");
    }
    else
        printf("Enter correct width and height");
    return 0;
}

void inputMatrix(double** mat, int width, int height) {
    printf("Input matrix\n");
    for (int i = 0; i < width; i++)
        for (int j = 0; j < height; j++)
            scanf_s("%lf", &(*(*(mat + i) + j)));
}

void outputMatrix(double** mat, int width, int height) {
    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; j++) {
            printf("|   %7.3lf \t", *(*(mat + i) + j));
        }
        printf("|\n");
    }
}

int check(int width, int height) {
    int ans = 1;
    if ((height < 1 && width < 1) ||
        (height == 1 && width == 1) ||
        (height == 1 && width < 2) ||
        (height < 2 && width == 1))
        ans = 0;
    return ans;
}

void readValue(int* width, int* height) {
    printf("Insert count of widths and heights:\n");
    scanf_s("%d %d", width, height);
}

double** alloc(int width, int height) {
    double** mat = (double**)malloc(width * sizeof(double*));
    if (mat != NULL) {
        for (int i = 0; i < width; i++) {
            *(mat + i) = (double*)malloc(height * sizeof(double));
            if (*(mat + i) == NULL) {
                while (--i >= 0) {
                    free(*(mat + i));
                }
                free(mat);
            }
        }
    }
    return mat;
}

void funcFree(double** mat, int width) {
    for (int i = 0; i < width; i++) {
        free(*(mat + i));
    }
    free(mat);
}

void direction(Params& it) {
    if (it.direction == UP) {
        dirUp(it);
    }
    else if (it.direction == LEFT) {
        it.i--;
        it.counter++;
        if (it.counter == it.step) {
            it.direction = DOWN;
            it.counter = 0;
            it.step++;
        }
    }
    else if (it.direction == DOWN) {
        it.j++;
        it.counter++;
        if (it.counter == it.step) {
            it.direction = RIGHT;
            it.counter = 0;
        }
    }
    else if (it.direction == RIGHT) {
        it.i++;
        it.counter++;
        if (it.counter == it.step) {
            it.direction = UP;
            it.counter = 0;
            it.step++;
        }
    }
}

void swap(double* pa, double* pb) {
    double temp = *pa;
    *pa = *pb;
    *pb = temp;
}

void swapInto(double** matrix, Params pa, Params pb) {
    return swap((*(matrix + pa.j) + pa.i), (*(matrix + pb.j) + pb.i));
}

double OutNumbers(double** mat, Params it) {
    return *(*(mat + it.j) + it.i);
}

int isValid(Params& it, int width, int height) {
    int ans = 2;
    if ((it.i < height) && (it.j < width) && (it.i >= 0) && (it.j >= 0)) {
        ans = 1;
    }
    else
    {
        ans = 0;
    }
    return ans;
}

void step(Params& it) {
    if (it.counter == it.step) {
        it.direction = LEFT;
        it.counter = 0;
    }
}

void dirUp(Params& it) {
    it.j--;
    it.counter++;
    step(it);
}

int getNext(Params& it, int width, int height) {
    int ans = 2;
    direction(it);
    if (isValid(it, width, height) == 1) {
        ans = 1;
    }
    else if (it.step > width && it.step > height) {
        ans = 0;
    }
    else if (ans != 1 && ans != 0) {
        ans = getNext(it, width, height);
    }
    return ans;
}

void sort(double** matrix, int width, int height) {
    Params begin = { height / 2, width / 2, UP, 1, 0 };
    do {
        Params cur = begin, min = begin;
        do {
            if (OutNumbers(matrix, cur) < OutNumbers(matrix, min)) {
                min = cur;
            }
        } while (getNext(cur, width, height) == 1);
        swapInto(matrix, begin, min);
    } while (getNext(begin, width, height) == 1);
}

void workMatrix(double** matrix, int width, int height) {
    inputMatrix(matrix, width, height);
    printf("Preveous matrix\n");
    outputMatrix(matrix, width, height);
    sort(matrix, width, height);
    printf("Sort matrix\n");
    outputMatrix(matrix, width, height);
}