/* npc_plc: 4 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020c3b00 @ 0x020c3b00, 0x1c bytes, Thumb
 * func_020c3abc @ 0x020c3abc, 0x44 bytes, Thumb
 * func_020c3a90 @ 0x020c3a90, 0x2c bytes, Thumb
 * func_020c3a68 @ 0x020c3a68, 0x28 bytes, Thumb
 */

typedef struct UnkStruct_020c3abc UnkStruct_020c3abc;

typedef void (*VFn)(UnkStruct_020c3abc *);

struct VTable {
    VFn unk_00[3];
};

struct UnkStruct_020c3abc {
    struct VTable *vtable;
};

struct UnkStruct_020c3a90 {
    char pad_00;
};

struct UnkStruct_020c3a90_2 {
    void *vtable;
    char pad_04[0x654];
    struct UnkStruct_020c3a90 sub;
};

typedef struct {
    void *unk_00;
    char pad_04[0x654];
    char unk_658[1];
} UnkStruct_020c3a68;

extern int func_0201c350(int a, int b, int c);
extern int func_0201c2a4(void *, int);
extern void func_02016108(void *, int);
extern void func_020c3dac(void *, int);
extern int data_020e877c;
extern void *func_020c3c64(void *p);
extern void *func_0202ee5c(void *p);
extern void func_020edf54(void *p);

int func_020c3b00(int a, int b)
{
    int result = 0;
    if (func_0201c350(a, b, 0x2000) == 1) {
        result = 1;
    }
    return result;
}

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

void *func_020c3a90(void *p)
{
    struct UnkStruct_020c3a90_2 *s = (struct UnkStruct_020c3a90_2 *) p;
    s->vtable = &data_020e877c;
    func_020c3c64(&s->sub);
    func_0202ee5c(p);
    func_020edf54(p);
    return p;
}

UnkStruct_020c3a68 *func_020c3a68(UnkStruct_020c3a68 *obj)
{
    obj->unk_00 = ((char *) &data_020e877c);
    func_020c3c64(obj->unk_658);
    func_0202ee5c(obj);
    return obj;
}
