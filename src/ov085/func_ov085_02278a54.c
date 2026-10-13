/* func_ov085_02278a54 @ 0x02278a54, 0x44 bytes, Thumb, module ov085
 * mwccarm 1.2/base -O4,s
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

extern int func_0201c2a4(UnkStruct_02278a54_2 *obj, int a);
extern void func_02016108(UnkStruct_02278a54 *sub, int v);
extern void func_ov085_022790ec(UnkStruct_02278a54_2 *obj, int a);

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
