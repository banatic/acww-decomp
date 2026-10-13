/* func_020c3abc @ 0x020c3abc, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_020c3abc UnkStruct_020c3abc;
typedef void (*VFn)(UnkStruct_020c3abc *);
struct VTable {
    VFn unk_00[3];
};
struct UnkStruct_020c3abc {
    struct VTable *vtable;
};

extern int func_0201c2a4(void *, int);
extern void func_02016108(void *, int);
extern void func_020c3dac(void *, int);

void func_020c3abc(void *self, int mode)
{
    switch (mode) {
        case 0: {
            UnkStruct_020c3abc *o = (UnkStruct_020c3abc *) ((char *) self + 0x658);
            int v;
            o->vtable->unk_00[2](o);
            v = func_0201c2a4(self, 4);
            func_02016108((char *) self + 0x658, v);
            func_020c3dac(self, 1);
            break;
        }
        case 8:
            func_020c3dac(self, 3);
            break;
    }
}
