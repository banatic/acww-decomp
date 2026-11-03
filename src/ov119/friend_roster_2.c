/* friend_roster_2: 10 functions, module ov119
 * mwccarm 1.2/base -O4,s
 * func_ov119_0229ae68 @ 0x0229ae68, 0x1c bytes, Thumb
 * func_ov119_0229ae50 @ 0x0229ae50, 0x16 bytes, Thumb
 * func_ov119_0229ae28 @ 0x0229ae28, 0x28 bytes, Thumb
 * func_ov119_0229ae10 @ 0x0229ae10, 0x18 bytes, Thumb
 * func_ov119_0229adc4 @ 0x0229adc4, 0x4a bytes, Thumb
 * func_ov119_0229ad84 @ 0x0229ad84, 0x3e bytes, Thumb
 * func_ov119_0229ad5c @ 0x0229ad5c, 0x26 bytes, Thumb
 * func_ov119_0229acb4 @ 0x0229acb4, 0xa8 bytes, Thumb
 * func_ov119_0229ac80 @ 0x0229ac80, 0x34 bytes, Thumb
 * func_ov119_0229ac3c @ 0x0229ac3c, 0x42 bytes, Thumb
 */

extern int func_020ec1e8(void);
extern int func_020984e8(void);
extern int func_02099658(int);
extern void *func_02077d00(void *entries);
extern int func_02077c3c(void *);
extern int func_02077e50(int);
extern void func_02077cb4(void *entries);
extern void *func_020eb844(void);
extern void *func_02077d68(void *);
extern int func_020eb04c(void *);
extern int func_020eb058(void *, void *);
extern int func_020eb040(void *);
extern void MI_CpuCopy8(void *, const void *, unsigned int);
extern int func_02077e74(int, int);

unsigned char func_ov119_0229ae10(unsigned char *p);

int func_ov119_0229ae68(void *receiver)
{
    int x = func_020ec1e8();

    switch (x) {
        case 3:
        case 4:
            return 1;
        default:
            return 0;
    }
}

void *func_ov119_0229ae50(void *receiver)
{
    return func_02077d00((void *) func_02099658(func_020984e8()));
}

void *func_ov119_0229ae28(int x)
{
    void *base;
    int idx;
    base = func_ov119_0229ae50((void *) x);
    idx = (int) func_ov119_0229ae10((unsigned char *) x);
    if (idx >= 32) {
        return 0;
    } else {
        return (void *) ((char *) base + idx * 36);
    }
}

unsigned char func_ov119_0229ae10(unsigned char *p)
{
    return *(p + (*(p + 0xa0) + (*(p + 0x9c) << 3)) + 0xbc);
}

void func_ov119_0229adc4(unsigned char *p)
{
    unsigned char *base;
    int i;
    int count;

    base = func_ov119_0229ae50((void *) p);
    count = 0;
    for (i = 0; i < 0x20; i++) {
        if (func_02077e50(func_02077c3c(base + i * 0x24))) {
            (p + count)[0xbc] = i;
            count++;
        }
    }
    for (; count < 0x20; count++) {
        (p + count)[0xbc] = 0x20;
    }
}

int func_ov119_0229ad84(void *receiver)
{
    char *ptr = func_ov119_0229ae50((void *) receiver);
    int found_zero = 0;
    int i;
    for (i = 0; i < 32; i++) {
        if (func_02077e50(func_02077c3c(ptr + i * 0x24)) != 0) {
            if (found_zero) {
                return 1;
            }
        } else {
            found_zero = 1;
        }
    }
    return 0;
}

void func_ov119_0229ad5c(int r0)
{
    int r4 = r0;
    if (func_ov119_0229ae68((void *) r0) != 0) {
        func_ov119_0229adc4((unsigned char *) r4);
    } else {
        func_02077cb4((void *) func_02099658((int) func_020984e8()));
    }
}

int func_ov119_0229acb4(void *param)
{
    void *dst;
    void *base;
    int flag;
    int tmp;
    char buf[12];
    int i;

    dst = func_020eb844();
    base = func_ov119_0229ae50((void *) param);

    flag = 0;
    for (i = 0; i < 32; i++) {
        MI_CpuCopy8((char *) dst + i * 12, buf, 12);

        if (func_020eb04c(buf) || func_02077e50((int) ((void *) func_02077c3c((char *) base + i * 36)))) {
            void *item;

            item = (char *) base + i * 36;

            if (func_020eb058(buf, func_02077d68((void *) func_02077c3c(item)))) {
                tmp = func_020eb040(buf);
                if (tmp == func_020eb040(func_02077d68((void *) func_02077c3c(item)))) {
                    continue;
                }
            }

            MI_CpuCopy8(buf, func_02077d68((void *) func_02077c3c(item)), 12);
            flag = 1;
        }
    }

    return flag;
}

int func_ov119_0229ac80(void *receiver)
{
    int i;
    char *p;
    p = func_ov119_0229ae50(receiver);
    for (i = 0; i < 32; i++) {
        if (func_02077e50(func_02077c3c((void *) p)) == 0) {
            return i;
        }
        p += 0x24;
    }
    return -1;
}

int func_ov119_0229ac3c(int r1, int r6)
{
    int r5;
    int r4;
    int r0;

    r5 = (int) func_ov119_0229ae50((void *) r1);
    r4 = 0;
    while (r4 < 0x20) {
        r0 = func_02077c3c((void *) r5);
        if (func_02077e50((int) ((void *) r0)) != 0) {
            r0 = func_02077c3c((void *) r5);
            if (func_02077e74(r6, r0) != 0) {
                return 1;
            }
        }
        r5 += 0x24;
        r4++;
    }
    return 0;
}
