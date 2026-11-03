/* field_actor_states_3: 19 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020084ac @ 0x020084ac, 0x60 bytes, Thumb
 * func_02008490 @ 0x02008490, 0x1a bytes, Thumb
 * func_02008458 @ 0x02008458, 0x36 bytes, Thumb
 * func_02008444 @ 0x02008444, 0x14 bytes, Thumb
 * func_02008418 @ 0x02008418, 0x2c bytes, Thumb
 * func_020083d8 @ 0x020083d8, 0x40 bytes, Thumb
 * func_020083bc @ 0x020083bc, 0x1a bytes, Thumb
 * func_02008380 @ 0x02008380, 0x3c bytes, Thumb
 * func_02008364 @ 0x02008364, 0x1a bytes, Thumb
 * func_02008350 @ 0x02008350, 0x14 bytes, Thumb
 * func_0200832c @ 0x0200832c, 0x24 bytes, Thumb
 * func_02008304 @ 0x02008304, 0x26 bytes, Thumb
 * func_02008300 @ 0x02008300, 0x2 bytes, Thumb
 * func_020082fc @ 0x020082fc, 0x2 bytes, Thumb
 * func_020082f8 @ 0x020082f8, 0x2 bytes, Thumb
 * func_020082f4 @ 0x020082f4, 0x2 bytes, Thumb
 * func_020082f0 @ 0x020082f0, 0x2 bytes, Thumb
 * func_020082ec @ 0x020082ec, 0x2 bytes, Thumb
 * func_020082e8 @ 0x020082e8, 0x2 bytes, Thumb
 */

typedef struct BigStruct {
    char pad_00[0x7f0];
    int unk_7F0;
    char pad_7F4[0x7fc - (0x7f0 + 4)];
    int unk_7FC;
} BigStruct;

typedef struct {
    unsigned char pad_00[12];
    unsigned short value;
    unsigned char pad_0E[14];
} UnkStruct_02008380;

struct UnkStruct_02008364 {
    char pad_00[0xc];
    unsigned short unk_0C;
};

extern int func_0200faf0(void *p, int x);
extern int func_02056f94(void *p);
extern void func_020109a0(void *self, int a, int b, unsigned short c);
extern int func_0200f328(void *p, int a);
extern void func_0200f268(void *p, int a);
extern void func_020085cc(int);
extern void func_02010d64(int);
extern unsigned int func_0200e92c(void *);
extern void func_0200e90c(void *, int, int, int);
extern int func_0200e894(void *, void *);
extern int func_0200e91c(void *);
extern int func_02008258(BigStruct *p, int x);
extern int func_0200c9a8(BigStruct *p, int a, int b, int c);
extern void func_02010f5c(int a);
extern void func_020109fc(int a, int b, unsigned short c, unsigned short d);
extern void func_0200eebc(int a);
extern int func_0200d4e8(int, int, int, int);
extern int func_0206fbc0(void);
extern int func_0203e19c(void);
extern int func_0201100c(void *);
extern int func_02010ca4(void *);

int func_02008458(void *a0, int a1, int a2);

void func_020084ac(void *a0)
{
    if (func_0200faf0(a0, 0x800) == 0) {
        return;
    }
    if (func_02056f94((char *) a0 + 0x2d0) == 0) {
        return;
    }
    if (*(int *) ((char *) a0 + 0x704) == 0x7e) {
        func_020109a0(a0, 0x7f, 0, 0);
        func_0200f328(a0, 0x6e);
    } else {
        func_02008458(a0, 6, -1);
        func_0200f268(a0, 0xd);
    }
}

void func_02008490(int arg)
{
    func_020085cc(arg);
    func_02010d64(arg);
    func_020084ac((void *) arg);
}

int func_02008458(void *a0, int a1, int a2)
{
    unsigned char buffer[0x20];
    int result;
    func_0200e92c(buffer);
    func_0200e90c(buffer, 0x86, a1, a2);
    result = func_0200e894(a0, buffer);
    func_0200e91c(buffer);
    return result;
}

void func_02008444(int a, void *message, int previous)
{
    func_020109a0((void *) a, 0x80, 3, 0);
}

void func_02008418(void *obj, unsigned short val)
{
    int state;

    state = *(int *) ((char *) obj + 0x7f0);
    if (state == 0x85) {
        return;
    }
    if (state == 0x86) {
        *(unsigned short *) ((char *) obj + 0x0c84) = val;
    } else {
        func_02008458(obj, 6, (unsigned short) val);
    }
}

void func_020083d8(BigStruct *p)
{
    if (func_02056f94((void *) ((char *) p + 0x2d0))) {
        p->unk_7FC = func_02008258(p, p->unk_7F0);
        func_0200c9a8(p, 3, 5, -1);
    }
}

void func_020083bc(int a)
{
    func_02010f5c(a);
    func_02010d64(a);
    func_020083d8((BigStruct *) a);
}

int func_02008380(void *param0, unsigned short param1, void *param2, void *param3)
{
    UnkStruct_02008380 stackVar;
    int result;

    func_0200e92c(&stackVar);
    func_0200e90c(&stackVar, 0x90, (int) param2, (int) param3);
    stackVar.value = param1;
    result = func_0200e894(param0, &stackVar);
    func_0200e91c(&stackVar);
    return result;
}

void func_02008364(int a, struct UnkStruct_02008364 *b, int previous)
{
    unsigned short val = b->unk_0C;
    func_020109fc(a, 0, val, val);
    func_0200eebc(a);
}

void func_02008350(int a1, int a2)
{
    func_0200d4e8(a1, 3, 5, a2);
}

void func_0200832c(int arg0)
{
    int r4;
    int r0;

    r4 = arg0;
    r0 = func_0206fbc0();
    if (r0 != 0) {
        func_0203e19c();
        func_0200d4e8(r4, 3, 1, -1);
    }
}

void func_02008304(void *p)
{
    func_0201100c(p);
    func_02010f5c((int) p);
    func_02010d64((int) p);
    func_02010ca4(p);
    func_0200832c((int) p);
}

void func_02008300(void *object, void *message, int previous) {}

void func_020082fc(void *object, int event) {}

void func_020082f8(void) {}

void func_020082f4(void *object) {}

void func_020082f0(void *object, void *message, int previous) {}

void func_020082ec(void *object, int event) {}

void func_020082e8(void *object) {}
