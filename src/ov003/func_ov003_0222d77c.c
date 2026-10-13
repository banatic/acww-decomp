/* func_ov003_0222d77c @ 0x0222d77c, 0x54 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x64];
    int unk_64;
} UnkStruct_0222d77c;
extern UnkStruct_0222d77c *data_020ccf94;
extern char data_ov003_02260994[];
extern char data_ov003_02260ac4[];
extern int func_02073dd4(void *a, int b);
extern void *func_0209d088(void *a);
extern int NNS_G3dMdlGetMdlAlpha(void *a, int b);

int func_ov003_0222d77c(void)
{
    if (func_02073dd4(data_020ccf94, data_020ccf94->unk_64) == 0) {
        char *o = data_ov003_02260994;
        if (NNS_G3dMdlGetMdlAlpha(func_0209d088(data_ov003_02260ac4), 0) > 0x1e && *(unsigned char *) (o + 0x250) == 3 &&
            *(signed char *) (o + 0x24d) != 0x13) {
            return 1;
        }
    }
    return 0;
}
