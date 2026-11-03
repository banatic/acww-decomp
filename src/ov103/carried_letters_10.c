/* carried_letters_10: 8 functions, module ov103
 * mwccarm 1.2/base -O4,s
 * func_ov103_0229d93c @ 0x0229d93c, 0x8 bytes, Thumb
 * func_ov103_0229d90c @ 0x0229d90c, 0x30 bytes, Thumb
 * func_ov103_0229d8d4 @ 0x0229d8d4, 0x38 bytes, Thumb
 * func_ov103_0229d8b4 @ 0x0229d8b4, 0x1e bytes, Thumb
 * func_ov103_0229d8a0 @ 0x0229d8a0, 0x14 bytes, Thumb
 * func_ov103_0229d890 @ 0x0229d890, 0x10 bytes, Thumb
 * func_ov103_0229d82c @ 0x0229d82c, 0x64 bytes, Thumb
 * func_ov103_0229d7bc @ 0x0229d7bc, 0x70 bytes, Thumb
 */

extern void func_ov103_0229ce0c(void *);
extern void func_ov094_0229a084(void *);
extern void func_ov094_0229af20(void *);
extern void func_ov094_0229bbc0(void *);
extern void func_ov002_022091cc(void *object);
extern void func_ov094_0229a05c(void *object);
extern int func_ov002_02207d5c(void *object);
extern void func_ov103_0229ca9c(void *);
extern void func_020029e8(int, int);
extern void func_020028bc(int, int, int, int);
extern void func_ov094_0229a29c(int a, int b);
extern int func_ov094_0229a098(void *receiver);
extern int func_ov002_02208054(void *self, int flag);
extern void func_ov103_0229cfc0(void *self);
extern int func_ov103_0229cd98(void *self, unsigned char a, unsigned char b, int c);
extern void func_ov103_0229cf18(void *self, int result);
extern unsigned char data_021fbdd8;
extern unsigned char data_021fbddc;
extern unsigned char data_021f6c58;
extern unsigned char data_021f6c54;
extern unsigned char *func_ov002_02208098(void *p, unsigned char value);
extern void func_ov002_02207ce4(void *p, int n);
extern void func_ov002_02207d00(void *p);
extern int func_ov103_0229c2f4(void *p, int n);
extern int func_ov103_0229cb1c(void *receiver);
extern int func_ov103_0229cb08(void *p, int n);
extern void func_ov103_0229ced0(void *p, unsigned char c);
extern void func_ov103_0229c444(void *p, unsigned char c);

void func_ov103_0229d8d4(void *r0);

void func_ov103_0229d93c(void *arg0)
{
    func_ov103_0229d8d4((void *) arg0);
}

void func_ov103_0229d90c(void *p)
{
    func_ov103_0229ce0c(p);
    func_ov094_0229a084((char *) p + 0xb54);
    func_ov094_0229af20((char *) p + 0xcc);
    func_ov094_0229bbc0((char *) p + 0xb2c);
}

void func_ov103_0229d8d4(void *r0)
{
    void *r4 = r0;
    func_ov002_022091cc((char *) r4 + 0x22d8);
    func_ov094_0229a05c((char *) r4 + 0xb54);
    if (func_ov002_02207d5c((char *) r4 + 0x218c)) {
        func_ov103_0229ca9c(r4);
    }
}

void func_ov103_0229d8b4(void)
{
    func_020029e8(6, 2);
    func_020028bc(6, 0, 0, 0);
}

void func_ov103_0229d8a0(int a)
{
    func_ov094_0229a29c(a + 0xb54, 0);
}

int func_ov103_0229d890(int a)
{
    return func_ov094_0229a098((void *) (a + 0xB54));
}

void func_ov103_0229d82c(void *self)
{
    unsigned int flag;
    int result;

    if (func_ov002_02208054(self, 1)) {
        func_ov103_0229cfc0(self);
        return;
    }

    flag = (data_021fbdd8 && data_021fbddc) ? 1 : 0;
    if (flag > 0) {
        result = func_ov103_0229cd98(self, data_021f6c58, data_021f6c54, 1);
        if (result != 0x15) {
            func_ov103_0229cf18(self, result);
        }
    }
}

void func_ov103_0229d7bc(void *arg)
{
    if (data_021fbdd8 == 0) {
        func_ov002_02208098(arg, 0);
        func_ov002_02207ce4((char *) arg + 0x218c, 0x3c);
    } else {
        if (func_ov103_0229c2f4(arg, 4) != 0) {
            if (func_ov103_0229cb1c(arg) != 0) {
                func_ov103_0229ced0(arg, ((unsigned char *) arg)[0x2da1]);
                return;
            }
            if (func_ov103_0229cb08(arg, 9) != 0) {
                func_ov103_0229c444(arg, ((unsigned char *) arg)[0x2da1]);
                return;
            }
        }
        func_ov002_02207d00((char *) arg + 0x218c);
    }
}
