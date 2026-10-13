/* func_ov114_0229c628 @ 0x0229c628, 0x68 bytes, Thumb, module ov114
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov114_0229c60c(void *p);
extern int func_ov002_0220a4d4(void *p);
extern int data_ov114_0229daa4[];

int func_ov114_0229c628(void *p)
{
    if (func_ov114_0229c60c(p) != -1) {
        return 8;
    }
    {
        unsigned char type = ((unsigned char *) p)[0x12bc];
        if (type == 4) {
            return func_ov002_0220a4d4((char *) p + 0x121c);
        }
        if (type < 4) {
            int val = data_ov114_0229daa4[type];
            if (type == 2 && ((unsigned char *) p)[0x12bb] == 0) {
                return val + 2;
            }
            if (type == 3 && ((unsigned char *) p)[0x12bb] == 1) {
                return val + 2;
            }
            return val;
        } else {
            return 0x9e;
        }
    }
}
