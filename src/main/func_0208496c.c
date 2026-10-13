/* func_0208496c @ 0x0208496c, 0x7c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020984e8(void);
extern int func_020b65c4(void);
extern int func_02084ad0(void);
extern int func_02099020(void *ptr, int size);
extern int func_020b65b8(void);
extern int func_020b67e8(int param);
extern int func_02084d5c(void *addr, void *ptr, int val);

struct DataCCF94 {
    char pad_00[0x64];
    int unk_64;
};
extern struct DataCCF94 *data_020ccf94;
extern unsigned char data_020e1d8c[];
extern int data_020d0644;

int func_0208496c(void)
{
    void *r4;
    unsigned short local;

    r4 = func_020984e8();
    if (func_020b65c4() != 0) {
        goto fail;
    }
    if (func_02084ad0() != 0) {
        goto fail;
    }
    if (func_02073dd4(data_020ccf94, data_020ccf94->unk_64) != 0) {
        goto fail;
    }
    if (r4 == 0) {
        goto fail;
    }
    if (func_02099020(r4, 0x23) == 0) {
        goto fail;
    }
    if (func_020b67e8(func_020b65b8()) != 0 || func_020b65b8() == 6) {
        local = 0xd019;
        return func_02084d5c(&local, data_020e1d8c, data_020d0644);
    }
fail:
    return 0;
}

extern int func_02073dd4(void *ptr, int field);
