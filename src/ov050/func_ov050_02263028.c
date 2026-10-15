/* func_ov050_02263028 @ 0x02263028, 0x5c bytes, Thumb, module ov050
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov050_02263394(void *self, void *dst);
extern int func_020984e8(void);
extern int func_02099640(int a);
extern int func_0209ad9c(int a, int b);
extern int func_0209b4d4(void *object);
extern int func_0209bba0(int a);

typedef struct {
    unsigned char pad_00[0xb4];
    unsigned char *arr;
} UnkStruct_02263028;

void func_ov050_02263028(UnkStruct_02263028 *self, unsigned char *dst)
{
    if (func_ov050_02263394(self, dst) != 0) {
        return;
    }
    if (func_0209bba0(func_0209b4d4((void *) (func_0209ad9c(func_02099640(func_020984e8()), 0)))) == 1) {
        dst[4] = 0x1e;
    } else {
        if (self->arr[0x73e] == 0) {
            dst[4] = 0x1c;
            self->arr[0x73e] = 1;
        } else {
            dst[4] = 0x10;
        }
    }
}
