/* public_box_states: 13 functions, module ov110
 * mwccarm 1.2/base -O4,s
 * func_ov110_0229db70 @ 0x0229db70, 0x34 bytes, Thumb
 * func_ov110_0229db48 @ 0x0229db48, 0x28 bytes, Thumb
 * func_ov110_0229db18 @ 0x0229db18, 0x30 bytes, Thumb
 * func_ov110_0229daec @ 0x0229daec, 0x2c bytes, Thumb
 * func_ov110_0229da98 @ 0x0229da98, 0x54 bytes, Thumb
 * func_ov110_0229da50 @ 0x0229da50, 0x48 bytes, Thumb
 * func_ov110_0229da00 @ 0x0229da00, 0x50 bytes, Thumb
 * func_ov110_0229d9c8 @ 0x0229d9c8, 0x38 bytes, Thumb
 * func_ov110_0229d98c @ 0x0229d98c, 0x3c bytes, Thumb
 * func_ov110_0229d948 @ 0x0229d948, 0x44 bytes, Thumb
 * func_ov110_0229d928 @ 0x0229d928, 0x20 bytes, Thumb
 * func_ov110_0229d8f4 @ 0x0229d8f4, 0x34 bytes, Thumb
 * func_ov110_0229d8b0 @ 0x0229d8b0, 0x44 bytes, Thumb
 */

extern int func_0208e484(void *);
extern void func_ov110_0229c3b8(void *, int);
extern void func_ov110_0229c9e8(void *);
extern void func_ov110_0229ca28(void *p);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern int func_ov002_02209f9c(void *ptr);
extern void func_ov110_0229d728(void *ptr, unsigned char byte);
extern void func_ov110_0229cdb4(void *);
extern int func_ov110_0229d4a8(unsigned char *self, int argument1);
extern void func_ov110_0229ce44(unsigned char *self);
extern void func_ov094_022999d8(void);
extern unsigned char *func_ov110_0229d6c4(unsigned char *self, unsigned char b, int n);
extern void func_ov110_0229ccb0(void *p, unsigned char c);
extern void func_ov110_0229c2b8(void *p, int n);
extern int func_ov002_02209f70(void *p);
extern int func_ov110_0229c2c8(void *, int);
extern void func_ov110_0229c2a8(void *, int);
extern void func_ov094_022999c0(void);
extern int func_ov002_02209d8c(void *ptr);
extern int func_ov110_0229cce8(void *ptr, unsigned char b);
extern void func_ov110_0229d840(void *ptr);
extern void func_ov110_0229cd8c(void *ptr);
extern int func_ov002_02208e28(int);
extern int func_0206fe54(void);
extern void func_ov110_0229ca7c(int);
extern int func_0208e4bc(int);
extern void func_ov002_022096d8(int, int);
extern int func_ov002_0220909c(int);
extern void func_ov110_0229ca48(int);
extern void func_ov110_0229c920(void *);
extern int func_ov002_02208e18(void *);
extern int func_ov002_0220b8ac(void *p, int b);
extern void func_0208e5cc(void *p);
extern unsigned char *func_ov002_022080a0(void *object, unsigned char value);
extern int func_ov002_02207d24(char *ptr, int flag);
extern void func_ov110_0229cbe0(void *self);

void func_ov110_0229db70(void *arg0)
{
    if (func_0208e484((char *) arg0 + 0x22e0)) {
        if (*(unsigned char *) ((char *) arg0 + 0xf5) == 0x1e) {
            func_ov110_0229c3b8(arg0, 1);
        } else {
            func_ov110_0229c9e8(arg0);
        }
    }
}

void func_ov110_0229db48(void *param)
{
    if (func_0208e484((void *) ((char *) param + 0x22e0)) != 0) {
        func_ov110_0229ca28(param);
        func_ov002_02208098((void *) (param), 4);
    }
}

void func_ov110_0229db18(char *s)
{
    if (func_ov002_02209f9c(s + 0x22e0) == 0) {
        return;
    }
    func_ov110_0229d728(s, *(unsigned char *) (s + 0xf5));
    func_ov002_02208098((void *) (s), 0xc);
}

void func_ov110_0229daec(void *arg0)
{
    if (func_0208e484((char *) arg0 + 0x22e0)) {
        func_ov002_02208098((void *) (arg0), *(unsigned char *) ((char *) arg0 + 0xf8));
    }
    func_ov110_0229cdb4(arg0);
}

void func_ov110_0229da98(unsigned char *self)
{
    unsigned char b;
    if (func_ov002_02209f9c((void *) (self + 0x22e0)) == 0) {
        b = self[0xf7];
        if (self[0xf5] == b) {
            func_ov110_0229d4a8(self, b);
            func_ov110_0229ce44(self);
            func_ov002_02208098((void *) (self), 4);
            func_ov094_022999d8();
        } else {
            func_ov110_0229d6c4(self, b, 4);
        }
    } else {
        func_ov110_0229cdb4((void *) self);
    }
}

void func_ov110_0229da50(void *p)
{
    if (func_ov002_02209f70((char *) p + 0x22e0) == 0) {
        func_ov110_0229ccb0(p, *(unsigned char *) ((char *) p + 0xf7));
        func_ov110_0229c2b8(p, 0x40);
        func_ov002_02208098((void *) (p), 0xf);
        func_ov110_0229ce44((unsigned char *) p);
    } else {
        func_ov002_02208098((void *) (p), 4);
    }
}

void func_ov110_0229da00(void *arg)
{
    char *self = (char *) arg;

    if (func_0208e484(self + 0x22e0)) {
        func_ov002_02208098((void *) (self), *(unsigned char *) (self + 0xf8));
    }

    if (func_ov002_02209f9c(self + 0x22e0)) {
        if (func_ov110_0229c2c8(self, 0x40)) {
            ((void) (func_ov110_0229c2a8(self, 0x40)), func_ov094_022999c0());
        }
        func_ov110_0229cdb4(self);
    }
}

void func_ov110_0229d9c8(void *p)
{
    if (func_ov002_02209d8c((unsigned char *) p + 0x22c8)) {
        func_ov110_0229cce8(p, ((unsigned char *) p)[0xf4]);
        ((void) (func_ov110_0229d840(p)), func_ov094_022999d8());
    } else {
        func_ov110_0229cd8c(p);
    }
}

void func_ov110_0229d98c(int param)
{
    if (func_ov002_02208e28(param + 0x2344) != 0) {
        if (func_0206fe54() != 0) {
            func_ov110_0229ca7c(param);
            func_ov002_02208098((void *) (param), 6);
        } else {
            func_ov002_02208098((void *) (param), 2);
        }
    }
}

void func_ov110_0229d948(int arg0)
{
    if (func_ov002_0220909c(arg0 + 0x2344) != 0) {
        func_ov002_022096d8(arg0 + 0x2344, 0);
        if (func_0208e4bc(arg0 + 0x22e0) != 0) {
            func_ov110_0229ca48(arg0);
        }
        func_ov002_02208098((void *) (arg0), 0x13);
    }
}

void func_ov110_0229d928(void *self)
{
    if (func_ov002_02208e18((char *) self + 0x2344)) {
        func_ov110_0229c920(self);
    }
}

void func_ov110_0229d8f4(void *p)
{
    if (func_ov002_0220b8ac((char *) p + 0x2738, 1)) {
        func_ov002_02208098((void *) (p), *(unsigned char *) ((char *) p + 0xf8));
        func_0208e5cc((char *) p + 0x22e0);
    }
}

void func_ov110_0229d8b0(volatile unsigned char *self)
{
    if (self[0xFC] != 0) {
        self[0xFC] = self[0xFC] - 1;
    } else {
        self[0x8C] = 4;
        func_ov002_022080a0((void *) ((void *) self), 1);
        func_ov002_02207d24((char *) (self + 0x21F8), 0);
        func_ov110_0229cbe0((void *) self);
    }
}
