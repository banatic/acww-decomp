/* func_ov055_02260a78 @ 0x02260a78, 0x34 bytes, Thumb, module ov055
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x618];
    int unk_618;
} UnkStruct_02260a78;

extern int func_02014868(const void *);
extern int func_020b5e10(void);
extern void func_020b6434(int, int, int, int);
extern void func_ov055_02260b24(void *, int);

int func_ov055_02260a78(UnkStruct_02260a78 *self)
{
    if (func_02014868(&self->unk_618) == 0) {
        int two = 2;
        func_020b6434(func_020b5e10(), 0x2C, two, two);
        func_ov055_02260b24(self, 2);
    }
    return 1;
}
