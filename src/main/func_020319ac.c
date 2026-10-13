/* func_020319ac @ 0x020319ac, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_02031c50(int a, int b);
extern int func_02031b14(int a, int b);

typedef struct ObjVTable ObjVTable;
typedef struct UnkStruct_020319ac UnkStruct_020319ac;
struct ObjVTable {
    void *unk_00;
    void *unk_04;
    int (*vfunc)(UnkStruct_020319ac *self, void *p1, void *p2, void *p3, int a, int b);
};
struct UnkStruct_020319ac {
    ObjVTable *vtable;
};

int func_020319ac(int a, int b)
{
    UnkStruct_020319ac *obj;
    void *p1;
    void *p2;
    void *p3;

    obj = func_02031c50(a, b);
    if (obj != 0) {
        if (obj->vtable->vfunc(obj, &p1, &p2, &p3, a, b) != 0) {
            return 0;
        }
    }
    return func_02031b14(a, b);
}
