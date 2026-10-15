/* func_0201eb5c @ 0x0201eb5c, 0xfc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0201eb5c UnkStruct_0201eb5c;
struct UnkStruct_0201eb5c {
    char pad_00[0x830];
    void *p;
};

typedef struct UnkStruct_0201eb5c_2 UnkStruct_0201eb5c_2;
struct UnkStruct_0201eb5c_2 {
    char pad_00[0x100];
    UnkStruct_0201eb5c *inner;
    char buf[0x1e];
    unsigned char byte;
};

typedef struct UnkStruct_0201eb5c_3 {
    char *buf;
    unsigned char byte;
} UnkStruct_0201eb5c_3;

extern int data_021f3aa4;
extern int data_021dc7a8;
extern void *data_020c8d60;

extern void *func_020867a0(void *);
extern int func_0203fdc4(int);
extern int func_0209f150(void *, int);
extern int func_02003704(void *);
extern void *func_0208150c(void *);
extern int func_020036e8(void *);
extern void func_02015e10(UnkStruct_0201eb5c_2 *, void *, int);
extern int func_0202da38(UnkStruct_0201eb5c_2 *, char *, char *, int, int, void *, int, int, int);
extern int memcmp(const void *, const void *, unsigned int);

void func_0201eb5c(UnkStruct_0201eb5c_2 *self, UnkStruct_0201eb5c_3 *out)
{
    void *orig;
    void *r4;
    int r;
    int val1, val2;

    orig = self->inner->p;
    r4 = func_020867a0(&data_021f3aa4);
    r = func_0203fdc4(0x11);
    if (r < 0) {
        r = 0;
    }

    if (r == 0) {
        val1 = 2;
        val2 = 3;
    } else if (r >= 1 && r <= 5) {
        val1 = 3;
        val2 = 5;
    } else {
        if (func_0209f150(&data_021dc7a8, 0x11) != 0 && func_02003704(r4) != 0) {
            void *ptr;
            ptr = func_0208150c(orig);
            if (*(unsigned short *) r4 == *(unsigned short *) ptr && memcmp((char *) r4 + 2, (char *) ptr + 2, 12) == 0 &&
                *((unsigned char *) r4 + 0xf) == *((unsigned char *) ptr + 0xf)) {
                val1 = 1;
                val2 = 0xb;
            } else {
                val1 = 3;
                val2 = 8;
            }
            func_02015e10(self, r4, 0);
        } else {
            val1 = 2;
            val2 = 0x12;
        }
    }

    func_0202da38(self, (char *) self + 0x104, (char *) self + 0x122, 0x1e, func_020036e8(func_0208150c(self->inner->p)),
                  data_020c8d60, 1, val2, (unsigned char) val1);

    out->buf = (char *) self + 0x104;
    out->byte = *(unsigned char *) ((char *) self + 0x122);
}
