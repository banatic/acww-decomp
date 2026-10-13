/* func_02092898 @ 0x02092898, 0x2a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020e8ed8(int, int);

void func_02092898(char *a, int b)
{
    char *p;
    short v1, v2;
    if (b == 1) {
        p = *(char **) (a + 8);
        if (p != 0) {
            v1 = *(short *) (a + 0x3c);
            v2 = *(short *) (a + 0x40);
            *(unsigned short *) (p + 0x20) = (unsigned short) func_020e8ed8(v1, v2);
            *(unsigned int *) (a + 0x78) = 0;
        }
    }
}
