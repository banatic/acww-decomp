/* func_ov145_02299f7c @ 0x02299f7c, 0x4c bytes, Thumb, module ov145
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov145_02299f30(void *obj);
extern int func_ov145_02299eec(void *obj);
extern void func_ov145_02299e44(void *obj);
extern void func_ov002_0220a0b4(void *sub, int a, int b);
extern void func_ov002_0220a374(void *sub, int v);

struct UnkStruct_02299f7c {
    char _dummy;
};
typedef struct UnkStruct_02299f7c UnkStruct_02299f7c;

typedef struct SomeObj {
    unsigned char pad_00[0xc2];
    unsigned char flag;
    unsigned char pad_C3[5];
    UnkStruct_02299f7c sub;
} SomeObj;

void func_ov145_02299f7c(SomeObj *obj)
{
    int a, b;
    a = func_ov145_02299f30(obj);
    b = func_ov145_02299eec(obj);
    func_ov002_0220a0b4(&obj->sub, a, b);
    if (obj->flag == 4) {
        func_ov002_0220a374(&obj->sub, 7);
    } else {
        func_ov002_0220a374(&obj->sub, 1);
    }
    func_ov145_02299e44(obj);
}
