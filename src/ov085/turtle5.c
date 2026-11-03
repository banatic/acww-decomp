/* turtle5: 4 functions, module ov085
 * mwccarm 1.2/base -O4,s
 * func_ov085_02278a98 @ 0x02278a98, 0x20 bytes, Thumb
 * func_ov085_02278a54 @ 0x02278a54, 0x44 bytes, Thumb
 * func_ov085_02278a28 @ 0x02278a28, 0x2c bytes, Thumb
 * func_ov085_02278a00 @ 0x02278a00, 0x28 bytes, Thumb
 */

typedef struct UnkStruct_02278a54 UnkStruct_02278a54;

typedef struct UnkStruct_02278a54_2 UnkStruct_02278a54_2;

struct UnkStruct_02278a54 {
    void (**vtable)(void *);
};

struct UnkStruct_02278a54_2 {
    unsigned char pad_00[0x658];
    UnkStruct_02278a54 sub;
};

extern int func_02014868(int);
extern int func_0201c2a4(UnkStruct_02278a54_2 *obj, int a);
extern void func_02016108(UnkStruct_02278a54 *sub, int v);
extern void func_ov085_022790ec(UnkStruct_02278a54_2 *obj, int a);
extern void *func_ov085_02278efc(void *p);
extern void *func_0202ee5c(void *p);
extern void func_020edf54(void *p);
extern unsigned char data_ov085_022794f0[];

int func_ov085_02278a98(int param)
{
    int result = 0;
    if (func_02014868(param + 0x618) == 0) {
        result = 1;
    }
    return result;
}

void func_ov085_02278a54(UnkStruct_02278a54_2 *obj, int kind)
{
    switch (kind) {
        case 0: {
            void (*func)(void *) = obj->sub.vtable[2];
            int ret;
            func(&obj->sub);
            ret = func_0201c2a4(obj, 4);
            func_02016108(&obj->sub, ret);
            func_ov085_022790ec(obj, 1);
            break;
        }
        case 8:
            func_ov085_022790ec(obj, 0);
            break;
    }
}

void *func_ov085_02278a28(void *self)
{
    *(unsigned int *) self = (unsigned int) data_ov085_022794f0;
    func_ov085_02278efc((char *) self + 0x658);
    func_0202ee5c(self);
    func_020edf54(self);
    return self;
}

void *func_ov085_02278a00(void *obj)
{
    *(void **) obj = ((int *) data_ov085_022794f0);
    func_ov085_02278efc((char *) obj + 0x658);
    func_0202ee5c(obj);
    return obj;
}
