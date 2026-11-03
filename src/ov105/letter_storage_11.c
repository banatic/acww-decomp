/* letter_storage_11: 6 functions, module ov105
 * mwccarm 1.2/base -O4,s
 * func_ov105_0229f23c @ 0x0229f23c, 0x4 bytes, Thumb
 * func_ov105_0229f238 @ 0x0229f238, 0x4 bytes, Thumb
 * func_ov105_0229f1d0 @ 0x0229f1d0, 0x68 bytes, Thumb
 * func_ov105_0229f1b4 @ 0x0229f1b4, 0x1c bytes, Thumb
 * func_ov105_0229f150 @ 0x0229f150, 0x64 bytes, Thumb
 * func_ov105_0229f11c @ 0x0229f11c, 0x34 bytes, Thumb
 */

extern int func_ov105_0229c340(void *arg, int a);
extern void func_0206fc4c(int a);
extern int func_020984e8(void);
extern int func_020989e0(int object);
extern void *func_02097f58(int a, int b);
extern int func_02066830(void *dst, void *src);
extern void func_020ee470(void *arg);
extern void func_ov105_0229ea38(void);
extern void func_ov105_0229ea24(void *);
extern void func_ov002_02208090(void *, int);
extern void func_ov105_0229e9a4(void *);
extern void func_ov105_0229d49c(void *);
extern void func_ov105_0229c330(void *, int);
extern void func_ov105_0229ed98(void *);
extern void func_02002708(int);
extern void func_ov002_02207f20(void *, int, int, int, int);
extern void func_ov094_0229ad20(void *);
extern void func_ov094_0229b2b0(void *);
extern int func_ov002_02207f48(void *arg, int zero);
extern void func_ov105_0229e9d0(void *receiver);
extern void func_ov105_0229c4cc(void *arg);

int func_ov105_0229f23c(void)
{
    return 1;
}

int func_ov105_0229f238(void)
{
    return 1;
}

int func_ov105_0229f1d0(void *arg)
{
    int res;
    int i;
    char *src;
    char *base;

    if (func_ov105_0229c340(arg, 0x1000) == 0) {
        func_0206fc4c(0);
    } else {
        func_0206fc4c(1);
        res = func_020989e0(func_020984e8());
        if (res != 0) {
            src = func_02097f58(res, 0);
            i = 0;
            base = (char *) arg + 0x2db8;
            for (; i < 50; i++) {
                func_02066830(src, base + i * 0x100);
                src += 0x100;
            }
        }
    }
    func_020ee470(arg);
    return 1;
}

void func_ov105_0229f1b4(void *r0)
{
    func_ov105_0229ea38();
    func_ov105_0229ea24(r0);
    func_ov002_02208090(r0, 1);
}

void func_ov105_0229f150(void *r0)
{
    void *r4 = r0;
    int sp[2];

    func_ov105_0229e9a4(r4);
    func_ov094_0229ad20((char *) r4 + 0x2fc);
    func_ov094_0229b2b0((char *) r4 + 0xd5c);
    func_ov105_0229d49c(r4);
    func_ov002_02207f20(r4, 8, 0, 0, 0x30);
    func_02002708(6);
    func_ov002_02208090(r4, 2);
    func_ov105_0229c330(r4, 1);
    func_ov105_0229c330(r4, 2);
    func_ov105_0229ed98(r4);
}

void func_ov105_0229f11c(void *arg)
{
    int r = func_ov002_02207f48(arg, 0);
    func_ov105_0229ed98(arg);
    if (r != 0) {
        func_ov105_0229e9d0(arg);
        func_ov105_0229c4cc(arg);
        func_ov002_02208090(arg, 3);
    }
}
