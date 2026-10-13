/* func_0205e678 @ 0x0205e678, 0x78 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02055ce8(void);
extern void func_02055cf4(void);
extern void func_020ba01c(void *ptr);
extern void func_02138d6c(void *arg1, int arg2, int arg3, void (*arg4)(void), void (*arg5)(void));

struct SubElem {
    char data[0x1c];
};

struct Pair8 {
    int a;
    int b;
};

struct UnkStruct_0205e678 {
    int arr[4];               // 0x00
    char pad_10[0xb0 - 0x10]; // 0x10
    struct SubElem sub[8];    // 0xb0
    struct Pair8 p8[4];       // 0x190
    unsigned char p2[4][2];   // 0x1b0
};

struct UnkStruct_0205e678 *func_0205e678(struct UnkStruct_0205e678 *self)
{
    struct SubElem *p, *end;
    int i;

    func_02138d6c((char *) self + 0x10, 8, 0x14, func_02055cf4, func_02055ce8);

    p = &self->sub[0];
    end = &self->sub[8];
    do {
        func_020ba01c(p);
        p++;
    } while (p != end);

    for (i = 0; i < 4; i++) {
        self->arr[i] = 0;
        self->p8[i].a = 0;
        self->p8[i].b = 0;
        self->p2[i][0] = 0x9e;
        self->p2[i][1] = 0x9e;
    }

    return self;
}
