/* func_0202e1fc @ 0x0202e1fc, 0x11c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0201bd48(void *self);
extern int func_02082f78(void *p);
extern int func_0208308c(void *p);
extern int func_0202e318(void *self);
extern int func_0201a304(void *a, void *self);

typedef struct {
    char pad_00[0xc];
    int unk_0C;
    unsigned char unk_10;
    char pad_11[3];
    int unk_14;
} UnkStruct_0202e1fc;

extern int func_0201691c(UnkStruct_0202e1fc *param0, void *param1, int param2);
extern int data_020c8120;

extern void func_02019e04(void *self, void *other, int a3, int a4, unsigned int a5, unsigned int a6, short a7, unsigned int a8,
                          unsigned int a9);
extern int func_02080ce4(int r0);
extern int func_0202e058(void *a, void *self, unsigned short *c);
extern unsigned short func_0201c444(void *ptr);
extern void func_02089c20(void *p, int a, int b, int c, int d, int e, int f, unsigned char g, int h);
extern int func_02082578(void *a, void *b);

int func_0202e1fc(void *self)
{
    unsigned short buf;
    unsigned char *ptr;

    buf = 0x11a8;

    if (func_0201bd48(self) == 0) {
        return 0;
    }
    if (func_02082f78((char *) self + 0x828) == 0) {
        if (func_0208308c((char *) self + 0x828) == 0) {
            return 0;
        }
        if (func_0202e318(self) == 0) {
            return 0;
        }
    }
    if (func_0201a304((char *) self + 0x2ac, self) == 0) {
        return 0;
    }
    if (func_0201691c((UnkStruct_0202e1fc *) ((char *) self + 0x334), self, data_020c8120) == 0) {
        return 0;
    }

    func_02019e04((char *) self + 0x564, self, 0, 1, 0, 0, 0, 0, 0);

    ptr = *(unsigned char **) ((char *) self + 0x830);
    if (ptr != 0) {
        buf = *(unsigned short *) func_02080ce4((int) ptr);
    }

    if (func_0202e058((char *) self + 0x64c, self, &buf) == 0) {
        return 0;
    }

    func_02089c20((char *) self + 0x4cc, (int) self, 0x1000, 0x2000, 8, 0x2fc, 2, (unsigned char) func_0201c444(self), 0x1000);

    if (func_02082578(self, (char *) self + 0xea) != 0) {
        goto ok;
    }
    return 0;
ok:
    return 1;
}
