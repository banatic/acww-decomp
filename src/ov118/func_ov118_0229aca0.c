/* func_ov118_0229aca0 @ 0x0229aca0, 0x84 bytes, Thumb, module ov118
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov118_0229a460(void *p, int);
extern int func_ov002_0220a58c(void *p, unsigned char a, unsigned char b);
extern int func_ov002_02208098(void *p, int);
extern unsigned char data_021f6c58;
extern unsigned char data_021f6c54;

int func_ov118_0229aca0(void *p)
{
    unsigned char v1, v2;
    if (!func_ov118_0229a460(p, 8)) {
        return 0;
    }
    v1 = data_021f6c58;
    v2 = data_021f6c54;
    if (func_ov002_0220a58c((unsigned char *) p + 0x678, v1, v2)) {
        *((unsigned char *) p + 0xa5) = v2;
        *((unsigned char *) p + 0xa7) = *((unsigned char *) p + 0xa4);
        *((unsigned char *) p + 0xa6) = *((unsigned char *) p + 0xa7);
        func_ov002_02208098(p, 1);
        return 1;
    } else {
        if ((int) v1 > 0xe8 && (int) v1 < 0xf5 && (int) v2 > 0x56 && (int) v2 < 0xae) {
            func_ov002_02208098(p, 2);
            return 1;
        }
        return 0;
    }
}
