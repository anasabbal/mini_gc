#include <stdio.h>
#include <stdlib.h>


#define STACK_MAX 256
#define INIT_OBJ_NUM_MAX 8

typedef enum {
    OBJ_INT,
    OBJ_PAIR
}ObjectType;

typedef struct sObject{
    ObjectType type;
    unsigned char marked;

    union {
        // OBJ_INT
        int value;
        // OBJ_PAIR
        struct {
            struct sObject *head;
            struct sObject *tail;
        };
    };
}Object;
// A structure for a minimal Virtual Machine
typedef struct {
    Object *stack[STACK_MAX];
    int stackSize;
}VM;
// Creating new virtual machine
VM *newVM(){
    VM *vm = malloc(sizeof (VM));
    printf("[+] Creating Virtual Machine with stack size %d", vm->stackSize);
    vm->stackSize = 0;
    return vm;
}
void assert(int condition, const char *message){

    printf("[+] Message is %c\n", &message);
    printf("[+] Condition is %d\n", &condition);
    if(!condition){
        printf("%s\n", message);
        exit(1);
    }
}
void push(VM *vm, Object *value){
    assert(vm->stackSize < STACK_MAX, "Stack overflow !");
    vm->stack[vm->stackSize++] = value;
}
Object *pop(VM *vm){
    assert(vm->stackSize > 0, "Stack underflow !");
    return vm->stack[--vm->stackSize];
}
Object *newObject(VM *vm, ObjectType type){
    Object *object = malloc(sizeof(Object));
    object->type = type;
    return object;
}
void pushInt(VM *vm, int intValue){
    Object *object = newObject(vm, OBJ_INT);
    object->value = intValue;
    push(vm, object);
}
Object *pushPair(VM *vm){
    Object *object = newObject(vm, OBJ_PAIR);
    object->tail = pop(vm);
    object->head = pop(vm);

    push(vm, object);
    return object;
}
void mark(Object *object){
    if (object->marked)
        return;

    object->marked = 1;

    if(object->type == OBJ_PAIR){
        mark(object->head);
        mark(object->tail);
    }
}
void markAll(VM *vm){
    for(int i = 0; i < vm->stackSize; i++){
        mark(vm->stack[i]);
    }
}
void test1(){
    printf("[+] Test 1: Objects on stack are preserved.\n");
    VM *vm = newVM();
    pushInt(vm, 1);
    pushInt(vm, 2);
}
void test2(){


}
int main() {
    test1();
}
