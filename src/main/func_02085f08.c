/* func_02085f08 @ 0x02085f08, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_020e54a8;
extern struct DataCCF94 {
    unsigned char pad_00[0x64];
    int unk_64;
} *data_020ccf94;
extern int func_02073dd4(struct DataCCF94 *, int);
extern unsigned char func_020b65c4(void);
extern int func_020b5dec(unsigned int);

int func_02085f08(void)
{
    unsigned int ret;

    ret = (data_020e54a8 == 0) ? 1 : 0;
    if (ret > 0) {
        if (func_02073dd4(data_020ccf94, data_020ccf94->unk_64) != 0) {
            return 0;
        }
    }
    return func_020b5dec((unsigned int) func_020b65c4());
}
