/* func_020b5d5c @ 0x020b5d5c, 0x84 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_020b5d5c {
    char pad_00[0x64];
    int unk_64;
} UnkStruct_020b5d5c;
extern UnkStruct_020b5d5c *data_020ccf94;
extern int func_02073dd4(UnkStruct_020b5d5c *p, int a);
extern int func_02073918(UnkStruct_020b5d5c *p, int a);
extern int func_020a7330(int a);
extern int func_020b65c4(void);
int func_020b5d5c(void)
{
    int i;
    int ret;
    UnkStruct_020b5d5c *p;
    p = data_020ccf94;
    if (func_02073dd4(data_020ccf94, p->unk_64) == 0) {
        ret = func_020b65c4();
        if ((((ret == 12) || (ret == 13)) || (ret == 14)) || (((unsigned char) (ret + 210)) <= 1)) {
            return 0;
        }
    } else {
        for (i = 3; i >= 0; i--) {
            if (func_02073dd4(p, i) != 0) {
                if (func_02073918(p, i) == 0) {
                    ret = func_020a7330(i);
                    if ((((ret == 12) || (ret == 13)) || (ret == 14)) || (((unsigned char) (ret + 210)) <= 1)) {
                        return 0;
                    }
                }
            }
        }
    }
    return 1;
}
