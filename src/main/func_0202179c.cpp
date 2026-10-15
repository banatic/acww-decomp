/* func_0202179c @ 0x0202179c, 0x2f8 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern "C" {
struct SELF;
typedef void *(SELF::*Method)(void **, int);
typedef int (SELF::*StateMethod)();
struct SELF {
    unsigned char pad_00[0x100];
    void *unk_100;              // 0x100
    unsigned char arr104[0x1e]; // 0x104
    unsigned char arr122[0x16]; // 0x122
    void *unk_138;              // 0x138
    unsigned char pad_13C[0x38];
    StateMethod unk_174; // 0x174
    StateMethod unk_17C; // 0x17c
};

extern int func_02073dd4(void *, int);
extern void *func_020984e8(void);
extern unsigned char *func_02099870(void *);
extern int func_02080404(void *, void **, unsigned char *, int);
extern void MI_CpuFill8(void *, int, int);
extern int func_020644cc(int);
extern void *func_02094fd4(void *);
extern unsigned char func_02081a88(void *);
extern int func_02015dd4(SELF *, int, unsigned char *, void *, unsigned char *);
extern void *func_02081d60(void *);
extern void func_02015e40(SELF *, void *, int);
extern void *func_02094fbc(void *);
extern char *func_0208150c(void *);
extern int func_020036e8(char *);
extern int func_0202da38(SELF *, unsigned char *, unsigned char *, int, int, int, int, int, int);
extern void *data_020ccf94;
extern int data_021c1d00;
extern Method data_021c1f94[10];
extern Method data_020d9250;
extern Method data_020d92a8;
extern Method data_020d9190;
extern Method data_020d9300;
extern Method data_020d9318;
extern Method data_020d9330;
extern Method data_020d92c8;
extern Method data_020d9418;
extern Method data_020d9458;
extern Method data_020d8ef8;
extern unsigned char data_020d9f68[];
extern struct {
    int word;
    unsigned char byte;
} data_020c8cb8;
extern StateMethod data_020d90f8;
extern StateMethod data_020d90f0;

int func_0202179c(SELF *self)
{
    unsigned char *filter;
    void *owner;
    int slot;
    int fallbackCount;
    int primaryCount;
    unsigned char *pa;
    unsigned char *pb;
    Method *d;
    unsigned char msg;
    unsigned char flag;
    unsigned char used[5];
    void *buf[8];
    unsigned char scratch[36];
    int remaining, index, skip, i;
    void *chosen;

    if (func_02073dd4(data_020ccf94, *(int *) ((char *) data_020ccf94 + 0x64)) != 0) {
        return 0;
    }
    if ((data_021c1d00 & 1) == 0) {
        d = data_021c1f94;
        d[0] = data_020d9250;
        d[1] = data_020d92a8;
        d[2] = data_020d9190;
        d[3] = data_020d9300;
        d[4] = data_020d9318;
        d[5] = data_020d9330;
        d[6] = data_020d92c8;
        d[7] = data_020d9418;
        d[8] = data_020d9458;
        d[9] = data_020d8ef8;
        data_021c1d00 |= 1;
    }
    if (func_020984e8() != 0) {
        filter = func_02099870(func_020984e8());
    } else {
        filter = 0;
    }
    owner = *(void **) ((char *) *(void **) ((char *) self + 0x100) + 0x830);
    chosen = 0;
    slot = 0;
    // The original skips both searches when no filter exists.
    if (filter == 0) {
        goto selected;
    }
    {
        for (i = 0; i < 8; i++) {
            buf[i] = 0;
        }
        primaryCount = func_02080404(owner, buf, filter, 1);
        if (primaryCount > 0) {
            MI_CpuFill8(used, 0, 5);
            for (remaining = 5; remaining > 0; remaining--) {
                skip = func_020644cc(remaining);
                for (index = 0; index < 5; index++) {
                    pa = &(used[index]);
                    if (used[index] != 0) {
                        continue;
                    }
                    if (skip == 0) {
                        chosen = (self->*data_021c1f94[index])(buf, primaryCount);
                        if (chosen != 0) {
                            slot = index + 1;
                        }
                        *pa = 1;
                        break;
                    }
                    skip--;
                }
                if (chosen != 0) {
                    break;
                }
            }
        }
    }
    if (chosen == 0) {
        for (i = 0; i < 8; i++) {
            buf[i] = 0;
        }
        fallbackCount = func_02080404(owner, buf, filter, 0);
        if (fallbackCount > 0) {
            MI_CpuFill8(used, 0, 5);
            for (remaining = 5; remaining > 0; remaining--) {
                skip = func_020644cc(remaining);
                for (index = 0; index < 5; index++) {
                    pb = &(used[index]);
                    if (used[index] != 0) {
                        continue;
                    }
                    if (skip == 0) {
                        chosen = (self->*data_021c1f94[index + 5])(buf, fallbackCount);
                        if (chosen != 0) {
                            slot = index + 6;
                        }
                        *pb = 1;
                        break;
                    }
                    skip--;
                }
                if (chosen != 0) {
                    break;
                }
            }
        }
    }
selected:
    if (chosen != 0) {
        func_02094fd4(scratch);
        msg = (unsigned char) func_02081a88(chosen);
        flag = 0;
        func_02015dd4(self, 2, &msg, data_020d9f68, &flag);
        func_02015e40(self, func_02081d60(chosen), 0xa);
        func_02094fbc(scratch);
    }
    self->unk_138 = chosen;
    i = func_020036e8(func_0208150c(*(void **) ((char *) *(void **) ((char *) self + 0x100) + 0x830)));
    func_0202da38(self, self->arr104, self->arr122, 0x1e, i, data_020c8cb8.word, data_020c8cb8.byte, slot, 0);
    self->unk_174 = data_020d90f8;
    self->unk_17C = data_020d90f0;
    return 1;
}
}
