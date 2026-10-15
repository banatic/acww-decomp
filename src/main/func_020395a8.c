/* func_020395a8 @ 0x020395a8, 0x80 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02039444(void *, int);
extern int func_02039ebc(void *p);
extern void func_02039f30(void *p);
extern int func_02039edc(void *p);

int func_020395a8(void *param0, void *param1)
{
    unsigned int result = 0;
    void *p;
    if (func_02039444((void *) param0, (int) param1) != 0) {
        func_02039ebc(param1);
    } else {
        unsigned int v = *(int *) ((char *) param1 + 0xac) > 0 ? 1 : result;
        if (v == 0) {
            unsigned int count;
            int i = 3;
            count = 0;
            for (; i >= 0; i--) {
                p = *(void **) ((char *) param0 + i * 4 + 0x2f4);
                if (p != 0) {
                    if (*(int *) ((char *) p + 0xc) != 0) {
                        count += 0x10;
                    }
                } else {
                    *(void **) ((char *) param0 + i * 4 + 0x2f4) = param1;
                    if (*(int *) ((char *) param1 + 0xc) == 0) {
                        count = 0;
                    }
                    *(int *) ((char *) param1 + 0x48) = count;
                    *(int *) ((char *) param1 + 0x44) = count;
                    func_02039f30(param1);
                    func_02039edc(param1);
                    result = 1;
                    break;
                }
            }
        }
    }
    return result;
}
