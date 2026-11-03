/* villager_town_2: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0207b4a8 @ 0x0207b4a8, 0xd4 bytes, Thumb
 * func_0207b41c @ 0x0207b41c, 0x8c bytes, Thumb
 */

typedef struct {
    unsigned char pad_00[0x24];
    unsigned char flags : 3;
    unsigned char : 5;
} UnkStruct_0207b4a8;

extern unsigned char data_021dc7bc;
extern void *func_02098844(unsigned char *, int);
extern void *func_02099870(void *);
extern int func_020951bc(void *);
extern void *func_02099640(void *);
extern int func_0209bd44(void *);
extern int func_0209bc40(void *);
extern int func_02003704(void *);
extern int func_0209bba0(void *);
extern int func_0209bc20(void *);
extern int func_0209e380(int, int);
extern void func_0209af04(void *);
extern void func_0209bb90(void *, int);
extern int func_02059e1c(int, int, void *);
extern unsigned int func_0208150c(void *);
extern int func_02071efc(int, int);
extern void func_02080cd8(void *, short *);
extern void func_0207d71c(void *);
extern unsigned int func_0207f1c8(void *);
extern int func_0209b5e8(int);
extern int func_0209b91c(void *);
extern int func_0209b908(int);
extern void func_02095238(void *);
extern void func_0207f454(void *);

void func_0207b4a8(int unused, int p)
{
    int i;
    void *a;
    UnkStruct_0207b4a8 *r4;
    unsigned char *r6;
    int r7;
    int mode;

    for (i = 0; i < 4; i++) {
        a = func_02098844(&data_021dc7bc, i);
        if (func_020951bc(func_02099870(a)) != 0) {
            r4 = (UnkStruct_0207b4a8 *) ((char *) func_02099640(a) + 0xa4);
            r6 = (unsigned char *) r4 + 0x10;
            if (func_0209bd44(r6) != 0) {
                if (func_0209bc40(r6) == 0x15) {
                    if (func_02003704(r4) != 0) {
                        r7 = (int) ((char *) r4 + 0x1c);
                        if (func_0209bba0(r6) == 0) {
                            if (func_0209e380(func_0209bc20(r6), p) < 0) {
                                func_0209af04(r4);
                            }
                        } else {
                            if (r4->flags != 0) {
                                r7 = func_0209e380(r7, p);
                                func_0209bb90(r6, 4);
                                if (r7 != 0) {
                                    mode = r4->flags;
                                    if (func_02059e1c(mode, (int) func_02099870(a), r4) != 0) {
                                        func_0209af04(r4);
                                    }
                                }
                            } else {
                                func_0209af04(r4);
                            }
                        }
                    }
                }
            }
        }
    }
}

void func_0207b41c(void *p, int flag)
{
    int i;
    int j;
    int a;
    int b;
    int c;
    short s;

    i = 0;
    j = 0;
    for (i = 0; i < 8; i++) {
        if (func_02003704((void *) func_0208150c(p)) != 0) {
            if (flag == 0) {
                if (func_02071efc(i, j) != 0) {
                    s = 0x12a8;
                    func_02080cd8(p, &s);
                }
            }
            func_0207d71c(p);
            a = func_0209b5e8((int) func_0207f1c8(p));
            b = func_0209b91c((void *) a);
            c = func_0209bd44((void *) b);
            if (c != 0) {
                if (func_0209bba0((void *) b) == 0) {
                    func_02095238((void *) func_0209b908(a));
                }
            }
            func_0207f454(p);
        }
        p = (char *) p + 0x7ec;
    }
}
