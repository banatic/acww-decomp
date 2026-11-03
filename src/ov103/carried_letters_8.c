/* carried_letters_8: 12 functions, module ov103
 * mwccarm 1.2/base -O4,s
 * func_ov103_0229d2a0 @ 0x0229d2a0, 0x30 bytes, Thumb
 * func_ov103_0229d270 @ 0x0229d270, 0x30 bytes, Thumb
 * func_ov103_0229d21c @ 0x0229d21c, 0x54 bytes, Thumb
 * func_ov103_0229d1d4 @ 0x0229d1d4, 0x48 bytes, Thumb
 * func_ov103_0229d190 @ 0x0229d190, 0x44 bytes, Thumb
 * func_ov103_0229d158 @ 0x0229d158, 0x38 bytes, Thumb
 * func_ov103_0229d11c @ 0x0229d11c, 0x3c bytes, Thumb
 * func_ov103_0229d0d8 @ 0x0229d0d8, 0x44 bytes, Thumb
 * func_ov103_0229d0b8 @ 0x0229d0b8, 0x20 bytes, Thumb
 * func_ov103_0229d080 @ 0x0229d080, 0x38 bytes, Thumb
 * func_ov103_0229d018 @ 0x0229d018, 0x68 bytes, Thumb
 * func_ov103_0229cffc @ 0x0229cffc, 0x1c bytes, Thumb
 */

struct BigStruct {
    char pad_00[0x2274];
    int unk_2274;
    char pad_2278[0x454];
    int unk_26CC;
    char pad_26D0[0x6d7];
    unsigned char unk_2DA7;
};

extern void func_ov103_0229ce84(void *self, unsigned char value);
extern int func_ov002_02209f9c(void *self);
extern unsigned char *func_ov002_02208098(void *self, unsigned char value);
extern int func_0208e484(void *ptr);
extern void func_ov103_0229c994(void *obj);
extern int func_ov103_0229cd4c(unsigned char *self, int arg1);
extern void func_ov103_0229ca48(unsigned char *self);
extern void func_ov103_0229ce18(unsigned char *self, int a, int b);
extern int func_ov002_02209f70(void *p);
extern void func_ov103_0229c8a4(void *p, unsigned char val);
extern void func_ov103_0229c2e4(void *p, int val);
extern void func_ov103_0229c2d4(char *p, int x);
extern int func_ov002_02209d8c(void *ptr);
extern void func_ov103_0229c8e8(void *self, unsigned char byte);
extern void func_ov103_0229cfa0(void *self);
extern void func_ov103_0229c964(void *self);
extern int func_0206fe54(void);
extern void func_ov103_0229c6d4(int);
extern int func_ov002_02208e28(int);
extern int func_ov002_0220909c(int data);
extern void func_ov002_022096d8(int data, int val);
extern int func_0208e4bc(int data);
extern void func_ov103_0229c6a0(int data);
extern int func_ov002_02208e18(char *ptr);
extern void func_ov103_0229c588(char *ptr);
extern int func_ov002_0220b8ac(void *p, int a);
extern void func_0208e5cc(void *p);
extern int func_ov002_0220b57c(char *);
extern int func_ov002_0220b5ec(char *, int);
extern int func_ov002_0220b59c(char *, int);
extern void func_ov002_0220a0b4(char *, int, int);
extern void func_ov002_02208090(char *, int);
extern unsigned char *func_ov002_022080a0(char *, unsigned char value);
extern void func_ov103_0229c7ec(char *);
extern void func_ov103_0229cbec(void *a);

void func_ov103_0229d2a0(void *self)
{
    if (func_ov002_02209f9c((char *) self + 0x2274)) {
        func_ov103_0229ce84(self, ((unsigned char *) self)[0x2da4]);
        func_ov002_02208098(self, 0xf);
    }
}

void func_ov103_0229d270(void *obj)
{
    if (func_0208e484((char *) obj + 0x2274) != 0) {
        func_ov002_02208098(obj, *(unsigned char *) ((char *) obj + 0x2da7));
    }
    func_ov103_0229c994(obj);
}

void func_ov103_0229d21c(unsigned char *self)
{
    if (func_ov002_02209f9c((void *) (self + 0x2274)) == 0) {
        unsigned char b = self[0x2da6];
        unsigned char a = self[0x2da4];
        if (a == b) {
            func_ov103_0229cd4c(self, b);
            func_ov103_0229ca48(self);
            func_ov002_02208098((void *) self, 5);
        } else {
            func_ov103_0229ce18(self, b, 4);
        }
    } else {
        func_ov103_0229c994((void *) self);
    }
}

void func_ov103_0229d1d4(void *p)
{
    if (func_ov002_02209f70((char *) p + 0x2274) == 0) {
        func_ov103_0229c8a4(p, *(unsigned char *) ((char *) p + 0x2da6));
        func_ov103_0229c2e4(p, 0x40);
        func_ov002_02208098(p, 0x12);
        func_ov103_0229ca48((unsigned char *) p);
    } else {
        func_ov002_02208098(p, 5);
    }
}

void func_ov103_0229d190(char *p)
{
    if (func_0208e484((void *) (p + 0x2274)) != 0) {
        func_ov002_02208098((void *) p, *(unsigned char *) (p + 0x2da7));
    }
    if (func_ov002_02209f9c((void *) (p + 0x2274)) != 0) {
        func_ov103_0229c2d4(p, 0x40);
        func_ov103_0229c994((void *) p);
    }
}

void func_ov103_0229d158(void *self)
{
    if (func_ov002_02209d8c((char *) self + 0x225c)) {
        func_ov103_0229c8e8(self, *((unsigned char *) self + 0x2da3));
        func_ov103_0229cfa0(self);
    } else {
        func_ov103_0229c964(self);
    }
}

void func_ov103_0229d11c(int r0)
{
    if (func_ov002_02208e28(r0 + 0x22d8) != 0) {
        if (func_0206fe54() != 0) {
            func_ov103_0229c6d4(r0);
            func_ov002_02208098((void *) r0, 9);
        } else {
            func_ov002_02208098((void *) r0, 4);
        }
    }
}

void func_ov103_0229d0d8(int param)
{
    if (func_ov002_0220909c(param + 0x22d8)) {
        func_ov002_022096d8(param + 0x22d8, 0);
        if (func_0208e4bc(param + 0x2274)) {
            func_ov103_0229c6a0(param);
        }
        func_ov002_02208098((void *) param, 0x16);
    }
}

void func_ov103_0229d0b8(char *ptr)
{
    if (func_ov002_02208e18(ptr + 0x22d8) != 0) {
        func_ov103_0229c588(ptr);
    }
}

void func_ov103_0229d080(struct BigStruct *this)
{
    if (func_ov002_0220b8ac(&this->unk_26CC, 0)) {
        func_ov002_02208098(this, this->unk_2DA7);
        func_0208e5cc(&this->unk_2274);
    }
}

void func_ov103_0229d018(char *param)
{
    if (func_ov002_0220b57c(param + 0x2b10) != 0) {
        if (func_0208e4bc((int) (param + 0x2274)) != 0) {
            int v1, v2;
            v1 = func_ov002_0220b5ec(param + 0x2b10, 1);
            v2 = func_ov002_0220b59c(param + 0x2b10, 1);
            func_ov002_0220a0b4(param + 0x2274, v1, v2);
        }
    } else {
        func_ov103_0229c7ec(param);
        func_ov002_02208090(param, 7);
        func_ov002_022080a0(param, 1);
    }
}

void func_ov103_0229cffc(void *a)
{
    func_ov103_0229c7ec((char *) a);
    func_ov103_0229cbec(a);
    func_ov002_02208098(a, 0);
}
