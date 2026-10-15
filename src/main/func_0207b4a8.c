/* func_0207b4a8 @ 0x0207b4a8, 0xd4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

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

typedef struct {
    unsigned char pad_00[0x24];
    unsigned char flags : 3;
    unsigned char : 5;
} UnkStruct_0207b4a8;

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
