/* func_ov121_0229ba2c @ 0x0229ba2c, 0x34 bytes, Thumb, module ov121
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b67d4(void);
extern int func_02073d90(void *p);

typedef struct UnkStruct_0229ba2c {
    unsigned char pad_00[0x64];
    int unk_64;
} UnkStruct_0229ba2c;

extern UnkStruct_0229ba2c *data_020ccf94;

int func_ov121_0229ba2c(void)
{
    if (func_020b67d4() != 0) {
        UnkStruct_0229ba2c *p = data_020ccf94;
        if (func_02073d90(p) != 0) {
            if (p->unk_64 != 0) {
                return 0;
            }
        }
        return 1;
    } else {
        return 0;
    }
}
