/* outdoor_villager_acts_4: 2 functions, module ov068
 * mwccarm 1.2/base -O4,s
 * func_ov068_02267964 @ 0x02267964, 0x50 bytes, Thumb
 * func_ov068_0226793c @ 0x0226793c, 0x26 bytes, Thumb
 */

typedef struct {
    unsigned char pad_00[0x20];
    int unk_20;
} UnkStruct_0226793c;

extern int func_0203e0a8(void *p, int v);
extern int func_02019e00(void *p);
extern int func_02019de8(void *p);
extern int func_02019c6c(void *p, int v, unsigned short s);
extern unsigned short data_020c80f8;
extern void func_ov068_0226cce8(UnkStruct_0226793c *s, int a, int flag);
extern void func_0203eddc(int a);

void func_ov068_02267964(void *r5, void *r4)
{
    func_0203e0a8(r4, 0);
    if (func_02019e00((char *) r4 + 0x564) == 3) {
        if (func_02019de8((char *) r4 + 0x564) != 0) {
            func_02019c6c((char *) r4 + 0x564, 1, data_020c80f8);
            *(int *) ((char *) r5 + 0x20) = 0x28;
            *(char *) ((char *) r5 + 0x1c) = 1;
        }
    }
}

void func_ov068_0226793c(UnkStruct_0226793c *s, int a)
{
    if (s->unk_20 == 0) {
        func_ov068_0226cce8(s, a, 0);
        func_0203eddc(a);
    } else {
        func_0203e0a8((void *) a, 0);
    }
}
