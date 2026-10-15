/* func_0205e568 @ 0x0205e568, 0x84 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char data[0x14];
    unsigned char sub[0x14];
} Elem;

typedef struct {
    unsigned int a;
    unsigned int b;
} Pair;

typedef struct {
    unsigned int arr0[4];
    Elem arr[4];
    unsigned char pad_B0[0x190 - (0x10 + 4 * 0x28)];
    Pair arr2[4];
    unsigned char bytes[8];
} UnkStruct_0205e568;

extern void func_02055b40(void *p);
extern int data_021c9ae4;
extern void func_020e9b9c(void *);

void func_0205e568(UnkStruct_0205e568 *obj)
{
    void *condition_value0;
    int i;

    for (i = 0; i < 4; i++) {
        func_02055b40(&obj->arr[i]);
        func_02055b40(obj->arr[i].sub);
    }

    for (i = 0; i < 4; i++) {
        obj->arr0[i] = 0;
        obj->arr2[i].a = 0;
        obj->arr2[i].b = 0;
    }

    if ((condition_value0 = (void *) (data_021c9ae4))) {
        func_020e9b9c(condition_value0);
    }

    for (i = 0; i < 4; i++) {
        unsigned char *base = (unsigned char *) obj + 2 * i;
        base[0x1b0] = 0x9e;
        base[0x1b1] = 0x9e;
    }
}
