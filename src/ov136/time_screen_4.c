/* time_screen_4: 11 functions, module ov136
 * mwccarm 1.2/base -O4,s
 * func_ov136_0229d168 @ 0x0229d168, 0x1c bytes, Thumb
 * func_ov136_0229d164 @ 0x0229d164, 0x4 bytes, Thumb
 * func_ov136_0229d160 @ 0x0229d160, 0x4 bytes, Thumb
 * func_ov136_0229d150 @ 0x0229d150, 0x10 bytes, Thumb
 * func_ov136_0229d0f4 @ 0x0229d0f4, 0x5a bytes, Thumb
 * func_ov136_0229d0cc @ 0x0229d0cc, 0x28 bytes, Thumb
 * func_ov136_0229d094 @ 0x0229d094, 0x38 bytes, Thumb
 * func_ov136_0229d064 @ 0x0229d064, 0x30 bytes, Thumb
 * func_ov136_0229d044 @ 0x0229d044, 0x20 bytes, Thumb
 * func_ov136_0229d00c @ 0x0229d00c, 0x38 bytes, Thumb
 * func_ov136_0229cfec @ 0x0229cfec, 0x20 bytes, Thumb
 */

extern void func_ov136_0229cfd4(int arg);
extern void func_ov136_0229d184(int arg);
extern void func_ov136_0229cfcc(int arg);
extern void func_020ee470(void *argument0);
extern void func_ov136_0229cf54(void);
extern void func_ov136_0229cf34(void *);
extern void func_ov136_0229cf14(void *);
extern void func_ov002_02207f20(void *, int, int, int, int);
extern void func_02002708(int);
extern void func_ov136_0229c564(void *, int);
extern int func_ov002_0220ab84(void *, int);
extern void func_ov002_02208090(void *, int);
extern int func_ov002_02207f48(void *obj, int value);
extern unsigned char *func_ov002_022080a0(void *object, unsigned char value);
extern void func_ov136_0229c974(void *obj);
extern int func_020ee45c(int);
extern void func_ov092_02299324(int, int, int);
extern void func_ov002_02207f04(int, int, int, int, int);
extern int func_ov002_02207f3c(void *a, int b);
extern void func_020027f0(int n);
extern void func_ov002_02207e80(void *param1, int param2, int param3, int param4);
extern void func_ov134_0229bd38(void *p, int a, int b, int c, int d);
extern void func_ov134_0229bcf0(void *);
extern void func_ov002_0220af74(void *);

void func_ov136_0229d044(void *param1);

int func_ov136_0229d168(int arg)
{
    func_ov136_0229cfd4(arg);
    func_ov136_0229d184(arg);
    func_ov136_0229cfcc(arg);
    return 1;
}

int func_ov136_0229d164(void)
{
    return 1;
}

int func_ov136_0229d160(void)
{
    return 1;
}

int func_ov136_0229d150(void *argument0)
{
    func_020ee470(argument0);
    return 1;
}

void func_ov136_0229d0f4(void *p)
{
    func_ov136_0229cf54();
    func_ov136_0229cf34(p);
    func_ov136_0229cf14(p);
    func_ov002_02207f20(p, 0xa, 4, 0, 0x30);
    func_02002708(6);
    func_02002708(4);
    func_ov136_0229d044(p);
    func_ov136_0229c564(p, 1);
    func_ov002_0220ab84((char *) p + 0xf8, 0x21);
    func_ov002_02208090(p, 1);
}

void func_ov136_0229d0cc(void *obj)
{
    if (func_ov002_02207f48(obj, 0)) {
        func_ov002_022080a0((void *) (obj), 2);
        func_ov136_0229c974(obj);
    }
    func_ov136_0229d044(obj);
}

void func_ov136_0229d094(int self)
{
    int tmp;

    tmp = func_020ee45c(self);
    func_ov092_02299324(tmp, 0x44, 1);
    func_ov002_02207f04(self, 10, 0, 0, 0x30);
    func_ov136_0229d044((void *) self);
    func_ov002_02208090((void *) self, 3);
}

void func_ov136_0229d064(void *a)
{
    if (func_ov002_02207f3c(a, 0)) {
        func_020027f0(6);
        func_020027f0(4);
        func_ov002_022080a0((void *) (a), 5);
    } else {
        func_ov136_0229d044(a);
    }
}

void func_ov136_0229d044(void *param1)
{
    func_ov002_02207e80(param1, 6, 0, 0);
    func_ov002_02207e80(param1, 4, 0, 0);
}

void func_ov136_0229d00c(void *p)
{
    func_ov134_0229bd38((char *) p + 0x2c4, 1, 6, 4, 3);
    ((char *) p)[0x2b77] = 0;
    *(unsigned short *) ((char *) p + 0x2b74) = 0;
}

void func_ov136_0229cfec(void *arg0)
{
    func_ov134_0229bcf0((char *) arg0 + 0x2c4);
    func_ov002_0220af74((char *) arg0 + 0xf8);
}
