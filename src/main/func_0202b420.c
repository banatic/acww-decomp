/* func_0202b420 @ 0x0202b420, 0xf0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0207f1c8(void *);
extern void func_0209b5ec(void);
extern unsigned int func_0209c330(void);
extern void func_0202b52c(unsigned short *, unsigned int);
extern int func_020644b4(int);
extern int func_0204c878(unsigned char *);
extern int func_0205be38(void);
extern int func_0202b510(int);
extern void func_020984e8(void);
extern int func_02099734(void);
extern int func_02098cf8(int, int);
extern int func_0208150c(void *);
extern unsigned int func_020036e8(void);
extern struct {
    unsigned int field0;
    unsigned char field4;
} data_020c89a0;
extern void func_0202da38(unsigned char *, unsigned char *, unsigned char *, int, unsigned int, unsigned int, unsigned char,
                          int, int);
extern void func_02015fb0(unsigned char *, int, int, int, int, int);

int func_0202b420(unsigned char *param0)
{
    void *structPtr;
    void *r6;
    unsigned short local;
    int r4;
    int r0;
    int r1;

    structPtr = *(void **) (param0 + 0x100);
    r6 = *(void **) ((unsigned char *) structPtr + 0x830);

    func_0207f1c8(r6);
    func_0209b5ec();
    func_0202b52c(&local, func_0209c330());

    *(unsigned short *) (param0 + 0x124) = local;
    if (*(unsigned short *) (param0 + 0x124) == 0xfff1) {
        goto FAIL;
    }

    r4 = func_020644b4(0xccd) + 0xccd;
    r0 = func_0204c878(param0 + 0x124);
    r4 = r0 * r4;
    r0 = func_0205be38();
    r1 = (r4 >> 14) + 3 * r0;
    *(int *) (param0 + 0x1a0) = r1;
    r0 = *(int *) (param0 + 0x1a0);
    r0 = func_0202b510(r0);
    *(int *) (param0 + 0x1a0) = r0;

    func_020984e8();
    r0 = func_02098cf8(func_02099734(), 1);
    if (*(int *) (param0 + 0x1a0) > r0) {
        goto FAIL;
    }

    func_0208150c(r6);
    r0 = func_020036e8();

    func_0202da38(param0, param0 + 0x104, param0 + 0x122, 0x1e, r0, data_020c89a0.field0, data_020c89a0.field4, 0, 0);

    func_02015fb0(param0, *(int *) (param0 + 0x1a0), 1, 0xa, 0, 0);

    return 1;

FAIL:
    return 0;
}
