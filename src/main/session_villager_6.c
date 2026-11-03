/* session_villager_6: 15 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02078a0c @ 0x02078a0c, 0x10 bytes, Thumb
 * func_020789f4 @ 0x020789f4, 0x18 bytes, Thumb
 * func_020789ac @ 0x020789ac, 0x48 bytes, Thumb
 * func_02078974 @ 0x02078974, 0x38 bytes, Thumb
 * func_0207892c @ 0x0207892c, 0x48 bytes, Thumb
 * func_020788f4 @ 0x020788f4, 0x38 bytes, Thumb
 * func_0207889c @ 0x0207889c, 0x58 bytes, Thumb
 * func_02078864 @ 0x02078864, 0x38 bytes, Thumb
 * func_0207880c @ 0x0207880c, 0x58 bytes, Thumb
 * func_020787d4 @ 0x020787d4, 0x38 bytes, Thumb
 * func_020787b4 @ 0x020787b4, 0x1e bytes, Thumb
 * func_02078794 @ 0x02078794, 0x1e bytes, Thumb
 * func_02078748 @ 0x02078748, 0x4c bytes, Thumb
 * func_02078710 @ 0x02078710, 0x38 bytes, Thumb
 * func_020786f8 @ 0x020786f8, 0x18 bytes, Thumb
 */

typedef struct UnkStruct_02078748 {
    int x;
    int y;
} UnkStruct_02078748;

extern void *data_020ccf94;
extern int func_02073d90(void *);
extern void func_02073820(void *);
extern void func_020737f0(void *, void *, int);
extern void func_02073770(void *, int, int);
extern int func_0207f294(int);
extern int func_0207cf74(int);
extern void func_020778b0(int, unsigned short);
extern unsigned short func_02077898(int a);

void func_02078a0c(unsigned char *p, int a, int b)
{
    *p = (unsigned char) (((a << 4) & 0xF0) | (b & 0x0F));
}

void func_020789f4(int *hi, int *lo, const unsigned char *byte)
{
    *hi = (*byte >> 4) & 0x0f;
    *lo = *byte & 0x0f;
}

void func_020789ac(int arg0, int arg1)
{
    int local;
    void *p;
    if (func_02073d90(data_020ccf94) != 0) {
        func_02078a0c((unsigned char *) (&local), arg0, arg1);
        p = data_020ccf94;
        func_02073820(p);
        func_020737f0(p, &local, 1);
        func_02073770(p, 0x36, 4);
    }
}

void func_02078974(void *a, int b)
{
    void *c;

    if (func_02073d90(data_020ccf94) == 0) {
        return;
    }

    c = (void *) func_0207f294((int) a);
    if (func_0207cf74((int) c) == 0) {
        return;
    }

    func_020789ac((int) c, b);
}

void func_0207892c(int a, int b)
{
    int local;
    int handle;
    if (func_02073d90((void *) ((*(int *) &data_020ccf94))) == 0) {
        return;
    }
    func_02078a0c((unsigned char *) (&local), a, b);
    handle = (*(int *) &data_020ccf94);
    func_02073820((void *) handle);
    func_020737f0((void *) handle, &local, 1);
    func_02073770((void *) handle, 0x37, 4);
}

void func_020788f4(int arg0, int arg1)
{
    int temp;
    if (func_02073d90((void *) ((*(int *) &data_020ccf94)))) {
        temp = func_0207f294(arg0);
        if (func_0207cf74(temp)) {
            func_0207892c(temp, arg1);
        }
    }
}

void func_0207889c(int a, int b, int c)
{
    if (func_02073d90(data_020ccf94) != 0) {
        int local;
        void *p;
        func_02078a0c((unsigned char *) (&local), a, b);
        p = data_020ccf94;
        func_02073820(p);
        func_020737f0(p, &local, 1);
        func_020737f0(p, &c, 1);
        func_02073770(p, 0x38, 4);
    }
}

void func_02078864(int a, int b, int c)
{
    if (func_02073d90((void *) ((*(int *) &data_020ccf94))) != 0) {
        int t = func_0207f294(a);
        if (func_0207cf74(t) != 0) {
            func_0207889c(t, b, c);
        }
    }
}

void func_0207880c(int a, int b, int c)
{
    if (func_02073d90(data_020ccf94)) {
        int temp;
        void *obj;

        func_02078a0c((unsigned char *) (&temp), a, b);
        obj = data_020ccf94;
        func_02073820(obj);
        func_020737f0(obj, &temp, 1);
        func_020737f0(obj, &c, 1);
        func_02073770(obj, 0x39, 4);
    }
}

void func_020787d4(int a, int b, int c)
{
    if (func_02073d90((void *) ((*(int *) &data_020ccf94))) != 0) {
        a = func_0207f294(a);
        if (func_0207cf74(a) != 0) {
            func_0207880c(a, b, c);
        }
    }
}

void func_020787b4(int a, int b, int c, unsigned short *d)
{
    func_02078a0c((unsigned char *) (a + 2), b, c);
    func_020778b0(a, *d);
}

void func_02078794(int a, int b, unsigned short *out, int c)
{
    func_020789f4((int *) a, (int *) b, (const unsigned char *) (c + 2));
    *out = func_02077898(c);
}

void func_02078748(int a, int b, int c)
{
    UnkStruct_02078748 local;
    int *p;
    if (func_02073d90((void *) ((*(int * *) &data_020ccf94))) == 0) {
        return;
    }
    func_020787b4((int) (&local), a, b, (unsigned short *) c);
    p = (*(int * *) &data_020ccf94);
    func_02073820((void *) p);
    func_020737f0((void *) p, (void *) (&local), 3);
    func_02073770((void *) p, 0x3e, 4);
}

void func_02078710(int a, int b, int c)
{
    if (func_02073d90(data_020ccf94) != 0) {
        int x = func_0207f294(a);
        if (func_0207cf74(x) != 0) {
            func_02078748(x, b, c);
        }
    }
}

void func_020786f8(char *p, char a, char b, char c)
{
    p[0] = ((a << 4) & 0xf0) | (b & 0xf);
    p[1] = c;
}
