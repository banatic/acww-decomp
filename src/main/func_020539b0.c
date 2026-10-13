/* func_020539b0 @ 0x020539b0, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0206e6ec(void *);
extern void *func_0206e7bc(void *, int);
extern unsigned char data_021c8c48[];

typedef struct {
    unsigned char pad_00[6];
    unsigned char unk_06;
} UnkStruct_020539b0;

unsigned char func_020539b0(int param)
{
    int idx = param;
    void *base;
    UnkStruct_020539b0 *d;
    if (param >= 1769) {
        idx = 1768;
    }
    base = func_0206e6ec(data_021c8c48);
    d = func_0206e7bc(base, idx);
    if (d) {
        return d->unk_06;
    }
    return 0;
}
