/* etc_board_3: 4 functions, module ov003
 * mwccarm 1.2/base -O4,s
 * func_ov003_0220c1a4 @ 0x0220c1a4, 0x4 bytes, Thumb
 * func_ov003_0220c184 @ 0x0220c184, 0x20 bytes, Thumb
 * func_ov003_0220c160 @ 0x0220c160, 0x24 bytes, Thumb
 * func_ov003_0220c114 @ 0x0220c114, 0x4c bytes, Thumb
 */

extern unsigned int data_ov003_0223c5f4[];
extern unsigned char data_ov003_0223c5a0;
extern void func_0203edd0(void *a);
extern int func_020ea990(void *a, void *b);
extern int func_020e8b4c(int a, int b);

int func_ov003_0220c1a4(void)
{
    return 1;
}

int func_ov003_0220c184(void *self)
{
    unsigned int idx;
    unsigned char *p;
    int result;

    idx = *(unsigned int *) ((char *) self + 8);
    data_ov003_0223c5f4[idx] = 0;
    p = &data_ov003_0223c5a0;
    *p = *p - 1;
    return 1;
}

void func_ov003_0220c160(void)
{
    unsigned int i;
    unsigned int zero;

    if (data_ov003_0223c5a0 == 0) {
        i = 0;
        zero = 0;
        do {
            data_ov003_0223c5f4[i] = zero;
            i++;
        } while (i < 8);
    }
}

int func_ov003_0220c114(void *a, void *b)
{
    func_0203edd0(a);
    if (b != 0 && func_020ea990((char *) b + 0x5c, (char *) a + 0x5c) < 0x2333 &&
        func_020e8b4c(0xffff8000, *(short *) ((char *) b + 0x8e)) <= 0x1100) {
        return 1;
    } else {
        return 0;
    }
}
