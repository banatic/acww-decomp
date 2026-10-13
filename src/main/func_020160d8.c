/* func_020160d8 @ 0x020160d8, 0x2a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0201c274(void *);

typedef void (*FuncPtr)(void *);
typedef struct VirtualObj {
    FuncPtr *vtable;
} VirtualObj;

typedef struct SomeObj {
    unsigned char pad_00[0x50];
    void *unk_50;
} SomeObj;

void func_020160d8(SomeObj *obj, void *value)
{
    void *ret;
    obj->unk_50 = value;
    if (obj->unk_50) {
        ret = func_0201c274(obj->unk_50);
        if (ret) {
            ((VirtualObj *) ret)->vtable[2](ret);
            ((VirtualObj *) obj->unk_50)->vtable[35](obj->unk_50);
        }
    }
}
