/* func_0203919c @ 0x0203919c, 0x60 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *data_020ccf94;
extern void *func_020738bc(void *a, void *b);
extern int func_020b65c4(void);
extern void MI_CpuCopy8(void *a, void *b, int c);

extern unsigned char data_020ca154[];
extern unsigned char data_021c675c[];

int func_0203919c(char *p)
{
    char *result;
    unsigned char c;
    int res;

    result = (char *) func_020738bc(data_020ccf94, p + 0x14);
    c = *result;
    if (c) {
        res = func_020b65c4();
        if (res == 0x2e || res == 0x0c || res == 0x0d || res == 0x0e || res == 0x2f) {
            c = 0;
        } else {
            MI_CpuCopy8(result, (void *) data_021c675c, 0x2e);
        }
        MI_CpuCopy8((void *) data_020ca154, result, 1);
    }
    return c;
}
