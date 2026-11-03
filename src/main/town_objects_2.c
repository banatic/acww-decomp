/* town_objects_2: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020b27d4 @ 0x020b27d4, 0x2c bytes, Thumb
 * func_020b278c @ 0x020b278c, 0x48 bytes, Thumb
 */

extern int func_0207cec0(int address, int param);
extern int func_0207f1d8(void *object);
extern int data_021e5a2c;

int func_020b27d4(int param)
{
    int forwarded_value;

    if ((forwarded_value = (int) func_0207cec0((int) &data_021e5a2c, param)) != 0) {
        if (func_0207f1d8((void *) forwarded_value) != 2) {
            return 0;
        }
        return 1;
    }
    return 0;
}

int func_020b278c(int r0)
{
    unsigned short store;
    int flag;
    unsigned int v;
    int diff;
    store = (unsigned short) r0;
    flag = 0;
    v = *(volatile unsigned short *) &store;
    if (v >= 0x5001 && v <= 0x5008) {
        flag = 1;
    }
    if (flag == 0) {
        goto fail;
    }
    if (v >= 0x5001 && v <= 0x5008) {
        diff = v - 0x5001;
    } else {
        diff = ~0;
    }
    return func_020b27d4(diff);
fail:
    return 0;
}
