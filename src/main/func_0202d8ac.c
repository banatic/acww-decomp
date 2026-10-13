/* func_0202d8ac @ 0x0202d8ac, 0x1e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0202d8ac UnkStruct_0202d8ac;
typedef struct UnkStruct_0202d8ac_2 UnkStruct_0202d8ac_2;
typedef void (*MethodPtr)(UnkStruct_0202d8ac *, int, int);

struct UnkStruct_0202d8ac_2 {
    char pad_00[0xA4];
    MethodPtr method;
};

struct UnkStruct_0202d8ac {
    UnkStruct_0202d8ac_2 *inner;
};

extern UnkStruct_0202d8ac *func_02015d90(void *a);

void func_0202d8ac(void *arg0, int arg1)
{
    UnkStruct_0202d8ac *s = func_02015d90(arg0);
    if (s) {
        s->inner->method(s, 1, arg1);
    }
}
