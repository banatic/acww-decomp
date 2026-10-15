/* func_0203cb3c @ 0x0203cb3c, 0x90 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0206490c(void *a, void *b, int c, ...);
extern char data_020da8c4[];
extern int data_021c6974;
extern unsigned short data_021c6970;
extern char data_021c6978[];
extern void func_020051b0(void *);
extern void __register_global_object(void *, void *, void *);

int func_0203cb3c(void *a, unsigned short *pv)
{
    unsigned int ok = 0;
    unsigned short v;
    int idx;

    v = *pv;
    if (v >= 0x1144 && v <= 0x1187) {
        ok = 1;
    }
    idx = ok > 0 ? (int) (v - 0x1144) : -1;
    if (idx != -1) {
        if (func_0206490c(a, (void *) -1, (int) data_020da8c4, idx) != 0) {
            return 1;
        }
        return 0;
    }
    if ((data_021c6974 & 1) == 0) {
        data_021c6970 = 0x1144;
        __register_global_object((void *) (&data_021c6970), (((void *) func_020051b0)), (void *) (data_021c6978));
        data_021c6974 |= 1;
    }
    return func_0203cb3c(a, &data_021c6970);
}
