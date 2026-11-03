/* pockets: 6 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0206fb58 @ 0x0206fb58, 0x44 bytes, Thumb
 * func_0206fb14 @ 0x0206fb14, 0x44 bytes, Thumb
 * func_0206faf8 @ 0x0206faf8, 0x1c bytes, Thumb
 * func_0206faf0 @ 0x0206faf0, 0x8 bytes, Thumb
 * func_0206fa8c @ 0x0206fa8c, 0x64 bytes, Thumb
 * func_0206fa58 @ 0x0206fa58, 0x34 bytes, Thumb
 */

extern int func_020984e8(void);
extern void *func_02099734(int);
extern unsigned short *func_02098f48(void *p, int i);
extern unsigned char func_02098e8c(void *p, int i);
extern unsigned short data_021cfce8[16];
extern unsigned char data_021cfcd8[16];
extern void func_0209a088(unsigned short *p, unsigned char c, int i);
extern unsigned short data_021cfd08[];

void func_0206fa58(unsigned short val, unsigned short new_val);

void func_0206fb58(void)
{
    void *obj;
    int i;
    obj = func_02099734((int) func_020984e8());
    i = 0;
    while (i < 15) {
        data_021cfce8[i] = *func_02098f48(obj, i);
        data_021cfcd8[i] = func_02098e8c(obj, i);
        i++;
    }
}

void func_0206fb14(void)
{
    unsigned short local;
    int i;
    func_02099734((int) func_020984e8());
    local = 0xfff1;
    for (i = 0; i < 15; i++) {
        local = data_021cfce8[i];
        func_0209a088(&local, data_021cfcd8[i], i);
    }
}

void func_0206faf8(unsigned short *src)
{
    int i;
    for (i = 0; i < 15; i++) {
        data_021cfd08[i] = src[i];
    }
}

int func_0206faf0(void)
{
    return (int) ((int *) data_021cfd08);
}

void func_0206fa8c(int param)
{
    if (param != 0) {
        int i;
        int negOne = -1;
        for (i = 0; i < 15; i++) {
            unsigned short val = data_021cfd08[i];
            int idx;
            if ((unsigned int) val >= 0x38e4u && (unsigned int) val <= 0x3933u) {
                idx = ((int) val - 0x38e4) >> 2;
            } else {
                idx = negOne;
            }
            if (idx >= 0) {
                int arg;
                if ((unsigned int) idx < 20u) {
                    arg = 0x3934 + idx * 4;
                } else {
                    arg = 0x3934;
                }
                func_0206fa58(val, (unsigned short) arg);
            }
        }
    }
    func_0206fb14();
}

void func_0206fa58(unsigned short val, unsigned short new_val)
{
    int i;
    for (i = 0; i < 15; i++) {
        if (val == data_021cfce8[i] && data_021cfcd8[i] == 0) {
            data_021cfce8[i] = new_val;
            return;
        }
    }
}
