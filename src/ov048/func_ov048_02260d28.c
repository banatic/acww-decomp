/* func_ov048_02260d28 @ 0x02260d28, 0x100 bytes, Thumb, module ov048
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov048_02260f64(void *self, int x);
extern int func_ov048_02260f00(void *self);
extern int func_02074308(void);
extern int func_020ec148(int a);
extern int func_020730c8(void);
extern void **func_020eb92c(int a);
extern int func_020eb998(void *p);
extern void *func_020eb9c4(void *p);
extern void MI_CpuCopy8(void *a, void *buf, int b);
extern void func_020eb8d8(void *p);
extern void func_ov048_022616b8(void *self, int a);

typedef struct {
    char pad_00[0x18];
    unsigned char unk_18;
} LocalBuf;

void func_ov048_02260d28(void *self)
{
    int n;
    void **tbl;
    unsigned char i;
    int flag_init;
    void *entry;
    int value;
    LocalBuf lbuf;
    int flag;

    if (func_ov048_02260f64(self, 0)) {
        return;
    }
    if (func_ov048_02260f00(self)) {
        return;
    }

    n = func_020ec148(func_02074308());
    if (n <= 0) {
        return;
    }

    tbl = func_020eb92c(func_020730c8());
    flag_init = 0;

    for (i = 0; i < n; i++) {
        entry = tbl[i];
        if (entry == 0) {
            continue;
        }

        func_020730c8();
        value = func_020eb998(entry);
        if (value != 0x1a) {
            continue;
        }

        func_020730c8();
        MI_CpuCopy8(func_020eb9c4(entry), &lbuf, value);
        if (lbuf.unk_18 != 0) {
            continue;
        }

        flag = (*((unsigned char *) entry + 2) == *((unsigned char *) self + 0x30e) &&
                *((unsigned char *) entry + 3) == *((unsigned char *) self + 0x30f) &&
                *((unsigned char *) entry + 4) == *((unsigned char *) self + 0x310) &&
                *((unsigned char *) entry + 5) == *((unsigned char *) self + 0x311) &&
                *((unsigned char *) entry + 6) == *((unsigned char *) self + 0x312) &&
                *((unsigned char *) entry + 7) == *((unsigned char *) self + 0x313))
                   ? 1
                   : flag_init;

        if (flag == 0) {
            continue;
        }

        func_020730c8();
        func_020eb8d8(entry);
        *(short *) ((char *) (*(void **) ((char *) self + 0xb8)) + 0xe6e) = 0xc8;
        func_ov048_022616b8(self, 5);
    }
}
