/* func_ov119_0229acb4 @ 0x0229acb4, 0xa8 bytes, Thumb, module ov119
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020eb844(void);
extern void *func_ov119_0229ae50(void *);
extern void *func_02077c3c(void *);
extern void *func_02077d68(void *);
extern int func_020eb04c(void *);
extern int func_020eb058(void *, void *);
extern int func_020eb040(void *);
extern int func_02077e50(void *);
extern void MI_CpuCopy8(void *, const void *, unsigned int);

int func_ov119_0229acb4(void *param)
{
    void *dst;
    void *base;
    int flag;
    int tmp;
    char buf[12];
    int i;

    dst = func_020eb844();
    base = func_ov119_0229ae50(param);

    flag = 0;
    for (i = 0; i < 32; i++) {
        MI_CpuCopy8((char *) dst + i * 12, buf, 12);

        if (func_020eb04c(buf) || func_02077e50(func_02077c3c((char *) base + i * 36))) {
            void *item;

            item = (char *) base + i * 36;

            if (func_020eb058(buf, func_02077d68(func_02077c3c(item)))) {
                tmp = func_020eb040(buf);
                if (tmp == func_020eb040(func_02077d68(func_02077c3c(item)))) {
                    continue;
                }
            }

            MI_CpuCopy8(buf, func_02077d68(func_02077c3c(item)), 12);
            flag = 1;
        }
    }

    return flag;
}
