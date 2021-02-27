//
// Created by buffer112 on 26.02.2021.
//

#ifndef LAB2_STACK_H
#define LAB2_STACK_H

typedef struct stack
{
    char **arr;
    int len;
    int alloc;
    int step;
} stack;

stack* createStack(int size);
void freeStack(stack* st);
int pushStack(stack *st, const char *str);
const char* pullStack(stack *st);

#endif //LAB2_STACK_H
