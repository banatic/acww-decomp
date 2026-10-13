/* func_ov004_0222fa60 @ 0x0222fa60, 0x50 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_020ea990(void *a, void *b);
extern int func_020e8b4c(int a, int b);

int func_ov004_0222fa60(void *a, void *b)
{
    if (b != 0 && func_020ea990((char *) b + 0x5c, (char *) a + 0x5c) < 0x299a &&
        func_020e8b4c((short) (*(short *) ((char *) a + 0x8e) + 0x8000), *(short *) ((char *) b + 0x8e)) < 0x1200) {
        return 1;
    }
    return 0;
}
