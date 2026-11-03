/* anim_slots_3: 6 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0205cf84 @ 0x0205cf84, 0x28 bytes, Thumb
 * func_0205cf6c @ 0x0205cf6c, 0x18 bytes, Thumb
 * func_0205cf4c @ 0x0205cf4c, 0x20 bytes, Thumb
 * func_0205cf44 @ 0x0205cf44, 0x8 bytes, Thumb
 * func_0205cf3c @ 0x0205cf3c, 0x8 bytes, Thumb
 * func_0205cf34 @ 0x0205cf34, 0x8 bytes, Thumb
 */

extern void func_0205c814(void *);
extern void func_0205cda0(void *param);
extern int func_020e9abc(void *);
extern unsigned char data_021c9af8[];
extern unsigned char data_021c9b58[];
extern void func_0205cd60(void *);
extern void func_0205c7f8(void);
extern int data_021c9b44;
extern int data_020dd6ac;
extern int func_02064328(int *obj, int *tbl, unsigned int hi, unsigned int raw);

void func_0205cf84(void *ptr)
{
    func_0205c814(ptr);
    func_0205cda0((void *) data_021c9b58);
    ptr = *(void **) data_021c9af8;
    if (ptr != 0) {
        func_020e9abc(ptr);
    }
}

void func_0205cf6c(void)
{
    void *ptr;
    ptr = (void *) data_021c9b58;
    func_0205cd60(ptr);
    func_0205c7f8();
}

int *func_0205cf4c(unsigned int raw)
{
    func_02064328(&data_021c9b44, &data_020dd6ac, raw >> 5, raw);
    return &data_021c9b44;
}

int func_0205cf44(void)
{
    return 5568;
}

int func_0205cf3c(void)
{
    return 624;
}

int func_0205cf34(void)
{
    return 624;
}
