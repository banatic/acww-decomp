/* sound_emitter_3: 13 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0200443c @ 0x0200443c, 0x8 bytes, Thumb
 * func_0200442c @ 0x0200442c, 0xe bytes, Thumb
 * func_0200441c @ 0x0200441c, 0x10 bytes, Thumb
 * func_02004414 @ 0x02004414, 0x8 bytes, Thumb
 * func_0200440c @ 0x0200440c, 0x8 bytes, Thumb
 * func_02004404 @ 0x02004404, 0x8 bytes, Thumb
 * func_020043c4 @ 0x020043c4, 0x40 bytes, Thumb
 * func_02004384 @ 0x02004384, 0x40 bytes, Thumb
 * func_02004330 @ 0x02004330, 0x54 bytes, Thumb
 * func_02004328 @ 0x02004328, 0x8 bytes, Thumb
 * func_02004320 @ 0x02004320, 0x8 bytes, Thumb
 * func_0200431c @ 0x0200431c, 0x4 bytes, Thumb
 * func_0200430c @ 0x0200430c, 0x10 bytes, Thumb
 */

typedef int (*FuncPtr)(void *);

struct UnkStruct_0200441c {
    FuncPtr *vtable;
};

typedef struct {
    int x, y, z;
} Vector;

typedef int (*func_t)(void *);

struct Vtable {
    func_t func;
};

struct UnkStruct_0200430c {
    struct Vtable *vtable;
};

extern int func_020f545c(int receiver, unsigned int value, unsigned int flag);
extern int func_020f5748(int a, int b, int c, int d);
extern void func_020f4f44(char *);
extern void func_020f4d4c(void *);
extern void func_020f5360(void *, int);
extern int *data_021c67a4;   // placeholder for 0x021c67a4
extern int data_021c67b8[3]; // placeholder for 0x021c67b8
extern void func_020f52a0(int a, int b, int *vec);
void func_020f5054(int r0, int r1, void *r2);
extern void func_020f4fb8(void *obj, Vector *v);
extern void func_020f4f80(char *);
extern void func_020f503c(void *receiver, short value);

void func_0200443c(int argument0, unsigned int value, unsigned int flag)
{
    func_020f545c(argument0, value, flag);
}

int func_0200442c(int a, int b, int c, int d)
{
    return func_020f5748(a, b, c, d);
}

int func_0200441c(struct UnkStruct_0200441c *obj)
{
    return obj->vtable[4](obj);
}

void func_02004414(char *argument0)
{
    func_020f4f44((char *) argument0);
}

void func_0200440c(void *argument0)
{
    func_020f4d4c((void *) argument0);
}

void func_02004404(void *argument0, int argument1)
{
    func_020f5360((void *) argument0, (int) argument1);
}

void func_020043c4(int a, int b, int *p)
{
    int diff[3];
    if (p == 0) {
        return;
    }
    if (data_021c67a4 == 0) {
        return;
    }
    diff[0] = p[0] - data_021c67b8[0];
    diff[1] = p[1] - data_021c67b8[1];
    diff[2] = p[2] - data_021c67b8[2];
    func_020f52a0(a, b, diff);
}

void func_02004384(int r0, int r1, int *r2)
{
    if (r2 != 0 && (*(void * *) &data_021c67a4) != 0) {
        int sp[3];
        sp[0] = r2[0] - data_021c67b8[0];
        sp[1] = r2[1] - data_021c67b8[1];
        sp[2] = r2[2] - data_021c67b8[2];
        func_020f5054(r0, r1, sp);
    }
}

void func_02004330(void *obj, Vector *src)
{
    Vector local;

    if (!src) {
        return;
    }
    if (!(*(int *) &data_021c67a4)) {
        return;
    }

    local = *src;
    local.x -= (*(Vector *) data_021c67b8).x;
    local.y -= (*(Vector *) data_021c67b8).y;
    local.z -= (*(Vector *) data_021c67b8).z;

    func_020f4fb8(obj, &local);
}

void func_02004328(char *argument0)
{
    func_020f4f80((char *) argument0);
}

void func_02004320(void *receiver, short value)
{
    func_020f503c(receiver, value);
}

int func_0200431c(void)
{
    return 1;
}

int func_0200430c(struct UnkStruct_0200430c *obj)
{
    return obj->vtable->func(obj);
}
