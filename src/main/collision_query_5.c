/* collision_query_5: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020319e4 @ 0x020319e4, 0x24 bytes, Thumb
 * func_020319ac @ 0x020319ac, 0x38 bytes, Thumb
 */

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

extern int func_02031a08(int, int);
extern void *func_02031c50(void);
extern int func_02031b14(int a, int b);

int func_020319ac(int a, int b);

int func_020319e4(int param1, int param2)
{
    int result;
    int r5 = param1;
    int r4 = param2;

    if (func_02031a08(param1, param2) != 0) {
        result = 0;
    } else {
        result = func_020319ac(r5, r4);
    }
    return result;
}

int func_020319ac(int a, int b)
{
    UnkStruct_020319ac *obj;
    void *p1;
    void *p2;
    void *p3;

    obj = func_02031c50();
    if (obj != 0) {
        if (obj->vtable->vfunc(obj, &p1, &p2, &p3, a, b) != 0) {
            return 0;
        }
    }
    return func_02031b14(a, b);
}
