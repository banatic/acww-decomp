/* villager_talk_scene_2: 7 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0202d8f8 @ 0x0202d8f8, 0x9c bytes, Thumb
 * func_0202d8ec @ 0x0202d8ec, 0xc bytes, Thumb
 * func_0202d8cc @ 0x0202d8cc, 0x1e bytes, Thumb
 * func_0202d8ac @ 0x0202d8ac, 0x1e bytes, Thumb
 * func_0202d88c @ 0x0202d88c, 0x1e bytes, Thumb
 * func_0202d86c @ 0x0202d86c, 0x1e bytes, Thumb
 * func_0202d84c @ 0x0202d84c, 0x1e bytes, Thumb
 */

struct UnkStruct_0202d8f8 {
    char pad_00[0x13c];
    unsigned char flag;
};

struct UnkStruct_0202d8cc;

typedef struct UnkStruct_0202d8cc UnkStruct_0202d8cc;

struct Vtbl {
    unsigned char pad_00[0xA4];
    void (*method)(UnkStruct_0202d8cc *, unsigned long long);
};

struct UnkStruct_0202d8cc {
    struct Vtbl *vtable;
};

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

typedef struct SomeObj SomeObj;

typedef struct SomeObjVtable SomeObjVtable;

struct SomeObj {
    SomeObjVtable *vtable;
};

struct SomeObjVtable {
    char pad_00[0xa4];
    void (*method)(SomeObj *obj, int a, int b);
};

typedef void (*func_t)(void *, int, int);

typedef struct Task Task;

typedef struct TaskFuncs TaskFuncs;

struct TaskFuncs {
    void (*funcs[42])(Task *, int, int);
};

struct Task {
    TaskFuncs *funcs;
};

extern int func_020984e8(void);
extern int func_02099870(int);
extern int func_02080728(void *, int);
extern int func_02080500(void *);
extern int func_020807c0(void *, int index);
extern int func_02081e94(int, int, int, int);
extern void func_02078974(void *, int);
extern void func_02081e14(int, int, int, int);
extern void func_020788f4(void *, int);
extern int func_02014a44(int arg0, int arg1);
extern UnkStruct_0202d8cc *func_02015d90(void *);

void func_0202d8f8(struct UnkStruct_0202d8f8 *obj, int *out2, int *out3, void *arg4, int flag)
{
    if (obj->flag != 0) {
        return;
    }
    if (flag == 0) {
        if (func_020984e8() != 0) {
            flag = func_02099870((int) func_020984e8());
        }
    }
    if (flag == 0) {
        return;
    }
    if (arg4 == 0) {
        return;
    }
    if (*out2 == 0) {
        *out3 = func_02080728(arg4, flag);
        if (*out3 != -1) {
            return;
        }
        *out3 = func_02080500(arg4);
        if (*out3 == -1) {
            return;
        }
        *out2 = func_020807c0(arg4, *out3);
        func_02081e94(*out2, flag, 0, 0);
        func_02078974(arg4, *out3);
    } else {
        func_02081e14(*out2, flag, 0, 0);
        func_020788f4(arg4, *out3);
    }
}

int func_0202d8ec(int arg0)
{
    return func_02014a44(arg0, 0);
}

void func_0202d8cc(void *object)
{
    UnkStruct_0202d8cc *obj;

    obj = func_02015d90(object);
    if (obj != 0) {
        obj->vtable->method(obj, 0);
    }
}

void func_0202d8ac(void *arg0, int arg1)
{
    UnkStruct_0202d8ac *s = (UnkStruct_0202d8ac *) func_02015d90(arg0);
    if (s) {
        s->inner->method(s, 1, arg1);
    }
}

void func_0202d88c(void *a, int b)
{
    SomeObj *obj;
    obj = (SomeObj *) func_02015d90(a);
    if (obj) {
        obj->vtable->method(obj, 2, b);
    }
}

void func_0202d86c(void *a, int b)
{
    void *ret;

    ret = (void *) func_02015d90(a);
    if (ret) {
        (*(func_t *) ((char *) *(void **) ret + 0xa4))(ret, 3, b);
    }
}

void func_0202d84c(Task *task, int param)
{
    Task *t = (Task *) func_02015d90((void *) task);
    if (t) {
        t->funcs->funcs[41](t, 4, param);
    }
}
