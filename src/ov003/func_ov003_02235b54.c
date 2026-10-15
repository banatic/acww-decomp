/* func_ov003_02235b54 @ 0x02235b54, 0x74 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x64];
    int unk_64;
} UnkStruct_02235b54;
extern UnkStruct_02235b54 *data_020ccf94;
extern int func_02073dd4(void *a, int b);
extern int func_020a7278(void);
extern int func_ov003_02235990(void *a, int b, int c);
extern int func_ov003_02235a74(void *a);
extern int func_ov003_02235ae8(void *a);

int func_ov003_02235b54(char *self, int b, int c)
{
    signed char k;
    // The four entry tests guard the body, with return 0 last.
    if (func_02073dd4(data_020ccf94, data_020ccf94->unk_64) == 0 || func_020a7278() != 0 ||
        *(unsigned char *) (self + 0x251) == 9 || *(unsigned char *) (self + 0x251) == 0xb) {
        func_ov003_02235990(self, b, c);
        k = *(signed char *) (self + 0x24d);
        if ((k == 0x36 || k == 0x37) && *(unsigned char *) (self + 0x251) == 4) {
            return func_ov003_02235a74(self);
        }
        return func_ov003_02235ae8(self);
    }
    return 0;
}
