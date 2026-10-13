/* func_ov047_022623cc @ 0x022623cc, 0x84 bytes, Thumb, module ov047
 * mwccarm 1.2/base -O4,s
 */

extern void *data_020ccf94;

extern int func_020e8840(void *p);
extern void func_ov047_022624f4(void *obj, int n);
extern int func_02073d90(void *);
extern short *func_0209d358(int a, int b);
extern int func_0209dcac(void);

int func_ov047_022623cc(void *obj)
{
    unsigned short *p = (unsigned short *) ((char *) obj + 0x72e);

    if (*p != 0xff) {
        if (func_020e8840(p) == 0) {
            func_ov047_022624f4(obj, 5);
        }
        return 1;
    }
    if (func_02073d90(data_020ccf94) != 0 || *func_0209d358(0, 0x4a) != 0 || func_0209dcac() == 2 || func_0209dcac() == 3) {
        return 1;
    }
    if (func_020e8840((char *) obj + 0x732) == 0) {
        *(unsigned short *) ((char *) obj + 0x738) = 0x18;
        func_ov047_022624f4(obj, 2);
    }
    return 1;
}
