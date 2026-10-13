/* func_0209110c @ 0x0209110c, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020fa3d0(void *arg);
extern int func_020fa3bc(void *arg);

struct UnkStruct_0209110c {
    char pad_00[0x50];
    void *unk_50;
};

int func_0209110c(struct UnkStruct_0209110c *param)
{
    if (func_020fa3d0(param->unk_50) && func_020fa3bc(param->unk_50)) {
        return 1;
    } else {
        return 0;
    }
}
