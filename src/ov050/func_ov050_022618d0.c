/* func_ov050_022618d0 @ 0x022618d0, 0x38 bytes, Thumb, module ov050
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_ov050_022650b4[];
extern unsigned char data_ov050_02265e9c[];
extern unsigned char data_021ebcd4[];

int func_020683e4(void *a, int b, unsigned char *c, unsigned char *d);
int func_02060c80(unsigned char *a, unsigned char b);

struct FuncOv050Obj {
    unsigned char pad_00[0x40];
    void *unk_40;
};

void func_ov050_022618d0(struct FuncOv050Obj *obj, int index, unsigned int offset)
{
    unsigned char value;
    unsigned char local;
    value = *(data_ov050_022650b4 + (index << 2) + offset);
    local = value;
    func_020683e4(obj->unk_40, 2, &local, data_ov050_02265e9c);
    func_02060c80(data_021ebcd4, value);
}
