/* villager_talk_lines_2: 3 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0201eb5c @ 0x0201eb5c, 0xfc bytes, Thumb
 * func_0201eaa8 @ 0x0201eaa8, 0xb4 bytes, Thumb
 * func_0201ea44 @ 0x0201ea44, 0x64 bytes, Thumb
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

struct UnkStruct_0201ea44;

struct UnkStruct_0201ea44_2 {
    unsigned char pad_00[0x830];
    unsigned int val;
};

struct UnkStruct_0201ea44 {
    unsigned char pad_00[0x100];
    struct UnkStruct_0201ea44_2 *ptr;
    unsigned char arr[30];
    unsigned char byte;
};

struct UnkStruct_0201ea44_4 {
    unsigned char *ptr;
    unsigned char byte;
};

struct UnkStruct_0201ea44_3 {
    unsigned int word;
    unsigned char byte;
};

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
extern void *func_0208675c(int);
extern unsigned char data_021f3aa4[];

void func_0201eb5c(UnkStruct_0201eb5c_2 *self, UnkStruct_0201eb5c_3 *out)
{
    void *orig;
    void *r4;
    int r;
    int val1, val2;

    orig = self->inner->p;
    r4 = func_020867a0(((int *) data_021f3aa4));
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
        func_02015e10((UnkStruct_0201eb5c_2 *) self, p1, 1);
    }

    e = func_020036e8(func_0208150c(self->sub->ptr));

    func_0202da38((UnkStruct_0201eb5c_2 *) self, (char *) self + 0x104, (char *) self + 0x122, 0x1e, e,
                  (void *) ((*(DataAtC8D60 *) &data_020c8d60).unk_00), 1, h, (*(DataAtC8D60 *) &data_020c8d60).unk_04);

    out->p = (char *) self + 0x104;
    out->b = self->b;
}

void func_0201ea44(struct UnkStruct_0201ea44 *a, struct UnkStruct_0201ea44_4 *b)
{
    unsigned int v;
    int x;
    v = a->ptr->val;
    x = func_020036e8((void *) ((int) func_0208150c((void *) v)));
    func_0202da38((UnkStruct_0201eb5c_2 *) a, (char *) a->arr, (char *) (&a->byte), 30, x,
                  (void *) ((*(struct UnkStruct_0201ea44_3 *) &data_020c8d60).word), 1, 0,
                  (*(struct UnkStruct_0201ea44_3 *) &data_020c8d60).byte);
    b->ptr = a->arr;
    b->byte = a->byte;
}
