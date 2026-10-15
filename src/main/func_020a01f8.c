/* func_020a01f8 @ 0x020a01f8, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *data_020ccf94;
extern void *func_02073144(void *);
extern void *func_020984e8(void);
extern void *func_02099658(void *);
extern void *func_02077d00(void);
extern void *func_02077c3c(void *);
extern void *func_02077d68(void *);
extern void MI_CpuCopy8(void *, void *, unsigned int);

void func_020a01f8(void)
{
    char *base;
    char *p;
    int i;
    void *src;

    base = (char *) func_02073144(data_020ccf94);
    p = (char *) (func_02099658(func_020984e8()), func_02077d00());
    i = 0;
    do {
        src = (func_02077d68((void *) func_02077c3c(p)));
        MI_CpuCopy8(base + i * 12, src, 12);
        p += 36;
        i++;
    } while (i < 32);
}
