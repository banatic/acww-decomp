/* letter_view: 7 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0206dbc0 @ 0x0206dbc0, 0x18 bytes, Thumb
 * func_0206dba8 @ 0x0206dba8, 0x18 bytes, Thumb
 * func_0206db74 @ 0x0206db74, 0x34 bytes, Thumb
 * func_0206db5c @ 0x0206db5c, 0x18 bytes, Thumb
 * func_0206db50 @ 0x0206db50, 0xc bytes, Thumb
 * func_0206db30 @ 0x0206db30, 0x20 bytes, Thumb
 * func_0206db18 @ 0x0206db18, 0x18 bytes, Thumb
 */

struct UnkStruct_0206dbc0 {
    unsigned char pad_00[0x6c];
    unsigned char flag;
};

typedef struct {
    void *vtbl;
} UnkStruct_0206db30;

extern int func_020a8a70(void *, int, int, int);
extern void func_020a8c1c(void *);
extern void *func_020a887c(UnkStruct_0206db30 *self);
extern void func_020edb3c(UnkStruct_0206db30 *self);
extern unsigned char data_020df270[];

void func_0206dbc0(struct UnkStruct_0206dbc0 *p, int b)
{
    func_020a8a70(p, b, 0, 0);
    p->flag = 1;
}

void func_0206dba8(void *obj, int p2, int p3)
{
    func_020a8a70(obj, p2, 1, p3);
    ((unsigned char *) obj)[0x6c] = 1;
}

void func_0206db74(void *arg0)
{
    unsigned char *p;
    unsigned char *q;

    func_020a8c1c(arg0);
    p = (unsigned char *) arg0 + 0x6d;
    *p = 0;
    p = (unsigned char *) arg0 + 0x6e;
    *p = 0;
    p = (unsigned char *) arg0 + 0x6f;
    *p = 0;
    p = (unsigned char *) arg0 + 0x70;
    *p = 0;
    p = (unsigned char *) arg0 + 0x71;
    *p = 0;
    q = (unsigned char *) arg0 + 0x6c;
    *q = 1;
}

void func_0206db5c(char *param0, char param1, char param2, char param3)
{
    param0[0x6d] = param1;
    param0[0x6e] = param2;
    param0[0x6f] = param3;
}

// placeholder, not used
void func_0206db50(char *r0, char r1, char r2)
{
    r0[0x70] = r1;
    r0[0x71] = r2;
}

UnkStruct_0206db30 *func_0206db30(UnkStruct_0206db30 *self)
{
    self->vtbl = (void *) data_020df270;
    func_020a887c(self);
    func_020edb3c(self);
    return self;
}

void *func_0206db18(void *obj)
{
    *(void **) obj = ((char *) data_020df270);
    func_020a887c((UnkStruct_0206db30 *) obj);
    return obj;
}
