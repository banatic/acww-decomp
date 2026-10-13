/* func_0207ae34 @ 0x0207ae34, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0207ae34 {
    char pad_00[0x64];
    int unk_64;
};

extern struct UnkStruct_0207ae34 *data_020ccf94;
extern void *func_0208150c(void *);
extern int func_02003704(void *);
extern void func_0207d128(void *);
extern int func_02073dd4(struct UnkStruct_0207ae34 *, int);

void func_0207ae34(char *p)
{
    int i;

    if (func_02073dd4(data_020ccf94, data_020ccf94->unk_64) != 0) {
        return;
    }

    for (i = 0; i < 8; i++) {
        if (func_02003704(func_0208150c(p)) != 0) {
            func_0207d128(p);
        }
        p += 0x7EC;
    }
}
