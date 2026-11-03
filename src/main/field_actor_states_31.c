/* field_actor_states_31: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02009a44 @ 0x02009a44, 0x58 bytes, Thumb
 * func_02009a24 @ 0x02009a24, 0x1e bytes, Thumb
 */

struct Triple {
    unsigned int a, b, c;
};

typedef struct {
    int a, b, c;
} UnkStruct_02009a24;

extern unsigned int func_0200e92c(void *ptr);
extern void func_0200e90c(void *ptr, int a, int b, short c);
extern void func_02009a9c(void *ptr, struct Triple data, int arg);
extern int func_0200e894(void *ptr1, void *ptr2);
extern int func_0200e91c(void *ptr);

int func_02009a44(unsigned char *obj, unsigned int *data, int a3, int a4, short a5)
{
    char bufA[12];
    char bufB[20];

    if (*(unsigned int *) (obj + 0x7f0) == 0x6f) {
        return 0;
    }

    func_0200e92c(bufA);

    func_0200e90c(bufA, 0x6f, a4, a5);

    func_02009a9c(bufB, *(struct Triple *) data, a3);

    {
        int result = func_0200e894(obj, bufA);
        func_0200e91c(bufA);
        return result;
    }
}

void func_02009a24(int *dst, UnkStruct_02009a24 s, int p4, int p5)
{
    dst[0] = s.a;
    dst[1] = s.b;
    dst[2] = s.c;
    dst[3] = 0;
    dst[4] = p4;
    dst[5] = p5;
}
