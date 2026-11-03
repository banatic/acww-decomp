/* outdoor_villager_watch_2: 4 functions, module ov068
 * mwccarm 1.2/base -O4,s
 * func_ov068_02266cf0 @ 0x02266cf0, 0x2 bytes, Thumb
 * func_ov068_02266cec @ 0x02266cec, 0x2 bytes, Thumb
 * func_ov068_02266cb0 @ 0x02266cb0, 0x3c bytes, Thumb
 * func_ov068_02266c70 @ 0x02266c70, 0x40 bytes, Thumb
 */

struct UnkStruct_02266c70 {
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
    int unk_10;
    short unk_14;
};

extern void func_ov068_02266c34(int *, int, int, int, int, int, int, int, int);
extern int data_020c814c;
extern unsigned char data_021fbee8[];
extern void func_ov068_02266be4(void *p, int a, int b, int c, int d, int e, int f, int g, int h);

void func_ov068_02266cf0(void *object) {}

void func_ov068_02266cec(void *object) {}

void func_ov068_02266cb0(int *p, int something)
{
    func_ov068_02266c34(p, something, 1, 0, 0, (unsigned int) data_021fbee8, 4, data_020c814c, 1);
    p[1] = 2;
    p[3] = -1;
    p[4] = -1;
}

void func_ov068_02266c70(struct UnkStruct_02266c70 *self, int arg1)
{
    self->unk_00 = 0;
    func_ov068_02266be4(self, arg1, 1, 0, 0, (unsigned int) data_021fbee8, 4, data_020c814c, 1);
    self->unk_04 = 2;
    self->unk_0C = -1;
    self->unk_10 = -1;
    self->unk_14 = 0;
}
