/* held_item_link: 24 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0201259c @ 0x0201259c, 0x20 bytes, Thumb
 * func_02012588 @ 0x02012588, 0x12 bytes, Thumb
 * func_02012550 @ 0x02012550, 0x38 bytes, Thumb
 * func_02012508 @ 0x02012508, 0x48 bytes, Thumb
 * func_020124e4 @ 0x020124e4, 0x22 bytes, Thumb
 * func_02012464 @ 0x02012464, 0x80 bytes, Thumb
 * func_02012444 @ 0x02012444, 0x20 bytes, Thumb
 * func_0201240c @ 0x0201240c, 0x38 bytes, Thumb
 * func_020123ec @ 0x020123ec, 0x20 bytes, Thumb
 * func_020123b4 @ 0x020123b4, 0x38 bytes, Thumb
 * func_02012394 @ 0x02012394, 0x20 bytes, Thumb
 * func_0201235c @ 0x0201235c, 0x38 bytes, Thumb
 * func_0201233c @ 0x0201233c, 0x20 bytes, Thumb
 * func_02012304 @ 0x02012304, 0x38 bytes, Thumb
 * func_020122e4 @ 0x020122e4, 0x20 bytes, Thumb
 * func_020122ac @ 0x020122ac, 0x38 bytes, Thumb
 * func_0201228c @ 0x0201228c, 0x20 bytes, Thumb
 * func_02012280 @ 0x02012280, 0xc bytes, Thumb
 * func_02012250 @ 0x02012250, 0x30 bytes, Thumb
 * func_02012214 @ 0x02012214, 0x3c bytes, Thumb
 * func_020121f8 @ 0x020121f8, 0x1a bytes, Thumb
 * func_020121e0 @ 0x020121e0, 0x16 bytes, Thumb
 * func_020121c4 @ 0x020121c4, 0x1c bytes, Thumb
 * func_020121a8 @ 0x020121a8, 0x1a bytes, Thumb
 */

struct UnkStruct_0201259c {
    unsigned short tag;
    unsigned int data;
};

struct UnkStruct_02012588 {
    char pad_00[4];
    char unk_04;
};

struct UnkStruct_0201233c {
    unsigned short tag;
};

struct UnkStruct_0201228c {
    unsigned short unk_00;
};

extern void *func_02082d1c(void *);
extern void *func_02082d04(char *p);
extern int func_0208308c(void *p);
extern int func_02082cb8(void *p, void *q);
extern int func_02082c98(void *p);
extern void func_0205eb8c(int a, void *b, int c);
extern void func_02016638(void *a, void *b, void *c, void *d, unsigned short e);
extern void func_0205eae0(void *a, int b, int c, int d);
extern void func_02083068(int arg);
extern void *func_0205e8e4(void *);
extern void func_0205ea60(void *);
extern int func_02055d0c(void *, void *, int);
extern void func_0205e954(void *, void *);
extern void func_0205eac4(unsigned char *key, int value);
extern unsigned char data_021ca16c[];

struct UnkStruct_0201259c *func_0201259c(struct UnkStruct_0201259c *p)
{
    p->tag = 0xFFF1;
    func_02082d1c(&p->data);
    p->tag = 0xFFF1;
    return p;
}

struct UnkStruct_02012588 *func_02012588(struct UnkStruct_02012588 *p)
{
    func_02082d04(&p->unk_04);
    return p;
}

int func_02012550(void *ptr, void *arg2)
{
    if (!func_0208308c((char *) ptr + 4)) {
        return 0;
    }
    if (!func_02082cb8((char *) ptr + 4, arg2)) {
        return 0;
    }
    *(unsigned short *) ptr = 0xfff1;
    return 1;
}

int func_02012508(void *p0, void *p1, void *p2, void *p3, unsigned short p4)
{
    int ret = func_02082c98((char *) p0 + 4);
    if (ret == 0) {
        goto fail;
    }
    func_0205eb8c(ret, p2, 0);
    func_02016638((char *) p1 + 0x334, p1, p2, p3, p4);
    *(unsigned short *) p0 = *(unsigned short *) p2;
    return 1;
fail:
    return 0;
}

void func_020124e4(int a, int b, int c, int d)
{
    int ret = func_02082c98((void *) (a + 4));
    if (ret) {
        func_0205eae0((void *) ret, b, c, d);
    }
}

void func_02012464(int arg0, unsigned short *arg1, int arg2, int arg3)
{
    int cond = 0;
    unsigned short val = *arg1;

    if (val >= 0x1376 && val <= 0x1376) {
        cond = 1;
    }

    if (cond != 0 || (val >= 0x1377 && val <= 0x1377)) {
        func_020124e4(arg0, 0, arg2, arg3);
        return;
    }

    cond = 0;
    if (val >= 0x1374 && val <= 0x1374) {
        cond = 1;
    }

    if (cond != 0 || (val >= 0x1375 && val <= 0x1375)) {
        func_020124e4(arg0, 0x13, 0, 0);
        return;
    }

    if (val >= 0x1380 && val <= 0x139f) {
        func_020124e4(arg0, 0x25, 0, 0);
    }
}

void func_02012444(unsigned short *p, int b, int c)
{
    if (p[0] != 0xFFF1) {
        func_02012464((int) p, p, b, c);
    }
}

void func_0201240c(int arg0, unsigned short *arg1, int arg2, int arg3)
{
    int cond = 0;
    unsigned short val = *arg1;

    if (val >= 0x1376 && val <= 0x1376) {
        cond = 1;
    }

    if (cond != 0 || (val >= 0x1377 && val <= 0x1377)) {
        func_020124e4(arg0, 1, arg2, arg3);
    }
}

void func_020123ec(unsigned short *p, int a, int b)
{
    if (*p != 0xfff1) {
        func_0201240c((int) p, p, a, b);
    }
}

void func_020123b4(int arg0, unsigned short *arg1, int arg2, int arg3)
{
    int cond = 0;
    unsigned short val = *arg1;

    if (val >= 0x1376 && val <= 0x1376) {
        cond = 1;
    }

    if (cond != 0 || (val >= 0x1377 && val <= 0x1377)) {
        func_020124e4(arg0, 15, arg2, arg3);
    }
}

void func_02012394(unsigned short *p, int a, int b)
{
    if (*p != 0xFFF1) {
        func_020123b4((int) p, (unsigned short *) p, a, b);
    }
}

void func_0201235c(int arg0, unsigned short *arg1, int arg2, int arg3)
{
    int cond = 0;
    unsigned short val = *arg1;

    if (val >= 0x1376 && val <= 0x1376) {
        cond = 1;
    }

    if (cond != 0 || (val >= 0x1377 && val <= 0x1377)) {
        func_020124e4(arg0, 16, arg2, arg3);
    }
}

void func_0201233c(struct UnkStruct_0201233c *p, int a, int b)
{
    if (p->tag == 0xFFF1) {
        return;
    }
    func_0201235c((int) p, (unsigned short *) p, a, b);
}

void func_02012304(int arg0, unsigned short *arg1, int arg2, int arg3)
{
    int cond = 0;
    unsigned short val = *arg1;

    if (val >= 0x1376 && val <= 0x1376) {
        cond = 1;
    }

    if (cond != 0 || (val >= 0x1377 && val <= 0x1377)) {
        func_020124e4(arg0, 17, arg2, arg3);
    }
}

void func_020122e4(unsigned short *p, int a, int b)
{
    if (*p != 0xfff1) {
        func_02012304((int) p, (unsigned short *) p, a, b);
    }
}

void func_020122ac(int arg0, unsigned short *arg1, int arg2, int arg3)
{
    int cond = 0;
    unsigned short val = *arg1;

    if (val >= 0x1376 && val <= 0x1376) {
        cond = 1;
    }

    if (cond != 0 || (val >= 0x1377 && val <= 0x1377)) {
        func_020124e4(arg0, 18, arg2, arg3);
    }
}

void func_0201228c(struct UnkStruct_0201228c *a, int b, int c)
{
    if (a->unk_00 != 0xfff1) {
        func_020122ac((int) a, (unsigned short *) a, b, c);
    }
}

void func_02012280(int arg)
{
    func_02083068(arg + 4);
}

void func_02012250(char *p, char *q)
{
    void *res = (void *) func_02082c98(p + 4);
    int value;
    int *sub;

    if (res) {
        value = *(int *) (q + 0x198);
        sub = (int *) ((char *) func_0205e8e4(res) + 0x9c);
        sub[4] = value;
        func_0205ea60(res);
    }
}

void func_02012214(void *param0, void *param1)
{
    void *res;

    if (*(unsigned char *) ((char *) param0 + 0x3C) == 0) {
        return;
    }

    res = (void *) func_02082c98((char *) param0 + 4);

    if (param1 != 0) {
        func_02055d0c((char *) param1 + 0xEC, (char *) param0 + 0xC, 14);
    }

    if (res != 0) {
        func_0205e954(res, (char *) param0 + 0xC);
    }
}

int func_020121f8(int *p)
{
    int *q = p + 1;
    int r = func_02082c98((void *) q);
    if (r) {
        return *(int *) (r + 4);
    }
    return 0;
}

char *func_020121e0(char *arg1, int arg2)
{
    char *p;
    p = (char *) func_02082c98((void *) (arg1 + 4));
    if (p) {
        *(int *) (p + 4) = arg2;
    }
    return p;
}

int func_020121c4(char *p)
{
    int r = func_02082c98(p + 4);
    if (r) {
        return (int) func_0205e8e4((void *) r);
    }
    return 0;
}

void func_020121a8(int param0, int param1)
{
    int result;

    result = func_02082c98((void *) (param0 + 4));
    if (result) {
        func_0205eac4((unsigned char *) result, param1);
    }
}
