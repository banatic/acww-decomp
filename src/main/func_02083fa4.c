/* func_02083fa4 @ 0x02083fa4, 0xa8 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#pragma opt_propagation off

extern int func_0209fa30(void *);
extern void data_021f3b85(void);
extern unsigned char data_020e54a8;
extern unsigned char func_020b65c4(void);
extern int func_02084af0(void);
extern int func_02084ad0(void);

typedef struct {
    unsigned char pad_00[0x64];
    int unk_64;
} Root;

extern Root *data_020ccf94;
extern int func_02073dd4(Root *, int);
extern int func_02084b14(void *, int);
extern int func_02084d34(void *, void *, void *);
extern char data_020e1d8c;
extern void *data_020d0644;

int func_02083fa4(void *self, int (**cb)(void), int c, int d)
{
    int idx;
    int r;
    int b;

    r = func_0209fa30((void *) &data_021f3b85);
    if (d != 0) {
        b = (data_020e54a8 == 0);
        if (b == 0) {
            goto fail;
        }
        if (func_020b65c4() == 0x2c) {
            goto fail;
        }
    }
    if (r != 0) {
        goto fail;
    }
    if (func_02084af0() != 0) {
        goto fail;
    }
    if (func_02084ad0() != 0) {
        goto fail;
    }
    if (func_02073dd4(data_020ccf94, data_020ccf94->unk_64) != 0) {
        goto fail;
    }
    idx = func_02084b14(self, c);
    if (idx == -1) {
        goto fail;
    }
    if (cb != 0 && cb[idx] != 0 && cb[idx]() == 0) {
        goto fail;
    }
    return func_02084d34((char *) self + idx * 8 + 4, &data_020e1d8c, data_020d0644);

fail:
    return 0;
}
