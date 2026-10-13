/* func_ov004_0223ac98 @ 0x0223ac98, 0xcc bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov004_0223ac7c(void *);
extern void func_02064328(char *, void *, int);
extern int func_ov004_0223ad64(int);
extern void *func_02064b2c(char *, void *, int, int);
extern void *func_021077e8(void *);
extern void *NNS_G3dGetTexPatAnmSet(void *);
extern void *func_02107bf8(void *, int);
extern int func_020575e4(void *, void *, void *, void *, void *, void *, int);
extern char data_ov004_02256074;
extern char data_ov004_02256094;
extern char data_ov004_022560b4;
extern char data_ov004_022560d0;
extern char data_ov004_022560ec;
extern char data_ov004_022560f4;

int func_ov004_0223ac98(char *self, int ch, int prog)
{
    char nameA[0x28];
    char nameB[0x28];
    int sel;
    func_ov004_0223ac7c(self);
    sel = -1;
    if (ch != 0xff) {
        func_02064328(nameA, &data_ov004_02256074, ch);
        func_02064328(nameB, &data_ov004_02256094, ch);
    } else {
        sel = func_ov004_0223ad64(prog);
        func_02064328(nameA, &data_ov004_022560b4, sel);
        func_02064328(nameB, &data_ov004_022560d0, sel);
        sel = prog;
    }
    *(void **) (self + 8) = func_021077e8(func_02064b2c(nameA, *(void **) self, 4, 0));
    *(void **) (self + 0xc) = func_02107bf8(NNS_G3dGetTexPatAnmSet(func_02064b2c(nameB, *(void **) self, 4, 0)), 0);
    if (func_020575e4(self + 0x10, *(void **) (self + 4), &data_ov004_022560ec, &data_ov004_022560f4, *(void **) (self + 8),
                      *(void **) (self + 0xc), 0) != 0) {
        *(int *) (self + 0xa0) = ch;
        *(short *) (self + 0xa4) = sel;
        *(short *) (self + 0xa6) = 0;
        return 1;
    }
    return 0;
}
