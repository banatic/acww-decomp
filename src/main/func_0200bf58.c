/* func_0200bf58 @ 0x0200bf58, 0xb4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[12];
    volatile int id;
} Child;

extern int func_0205cb80(unsigned char *);
extern void func_0201a48c(unsigned char *, unsigned char *, int, int, int);
extern void func_02010f5c(unsigned char *);
extern int func_02056f94(unsigned char *);
extern void func_02010a24(unsigned char *, int, int, int, int, int, int, int);
extern void func_0201a698(unsigned char *, void *, int);
extern int func_0200c3b0(unsigned char *, int, int, int);
extern unsigned char data_020c7600[];

void func_0200bf58(unsigned char *self)
{
    func_0201a48c(self + 0x90c, self + 0x6e0, *(signed short *) (self + 0x8e), func_0205cb80(self + 0x700),
                  (*(unsigned int *) (self + 0x2d8) << 4) >> 16);
    func_02010f5c(self);
    if (func_02056f94(self + 0x2d0) != 0) {
        Child *p = *(Child **) (self + 0x908);
        if (p->id != 0x137) {
            func_02010a24(self, 0x12, 0, 0, 0x1000, 0, 0, p->id);
            func_0201a698(self + 0x90c, p, 1);
        } else {
            func_0200c3b0(self, data_020c7600[*(unsigned char *) (self + 0x7d4) - 1], 5, -1);
        }
    }
}
