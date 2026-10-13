/* func_0201eaa8 @ 0x0201eaa8, 0xb4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x830];
    void *ptr;
} UnkStruct_0201eaa8;

typedef struct {
    unsigned char pad_00[0x100];
    UnkStruct_0201eaa8 *sub;
    unsigned char pad_104[0x1e];
    unsigned char b;
} Main;

typedef struct {
    unsigned int unk_00;
    unsigned char unk_04;
} DataAtC8D60;

typedef struct {
    void *p;
    unsigned char b;
} UnkStruct_0201eaa8_2;

extern void *func_0208675c(int);
extern void *func_0208150c(void *);
extern int func_02003704(void *);
extern void func_02015e10(void *, void *, int);
extern int func_020036e8(void *);
extern void func_0202da38(void *, char *, char *, int, int, int, int, int, int);
extern int memcmp(const void *, const void *, unsigned int);
extern DataAtC8D60 data_020c8d60;

extern unsigned char data_021f3aa4[];

void func_0201eaa8(Main *self, UnkStruct_0201eaa8_2 *out)
{
    void *p1;
    void *p2;
    int e;
    int h;

    p1 = func_0208675c((unsigned int) data_021f3aa4);
    p2 = func_0208150c(self->sub->ptr);

    if (*(unsigned short *) p1 == *(unsigned short *) p2 && memcmp((char *) p1 + 2, (char *) p2 + 2, 0xc) == 0 &&
        *(unsigned char *) ((char *) p1 + 0xf) == *(unsigned char *) ((char *) p2 + 0xf)) {
        h = 0xc;
    } else {
        h = 0xf;
    }

    if (func_02003704(p1) != 0) {
        func_02015e10(self, p1, 1);
    }

    e = func_020036e8(func_0208150c(self->sub->ptr));

    func_0202da38(self, (char *) self + 0x104, (char *) self + 0x122, 0x1e, e, data_020c8d60.unk_00, 1, h,
                  data_020c8d60.unk_04);

    out->p = (char *) self + 0x104;
    out->b = self->b;
}
