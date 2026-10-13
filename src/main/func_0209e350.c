/* func_0209e350 @ 0x0209e350, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0209e380(void *param0);

int func_0209e350(void *param0, void *param1)
{
    int r0;
    int r2;
    int r1;
    unsigned char r5_1;
    unsigned char r5_2;
    unsigned char r4_1;
    unsigned char r4_2;
    int result;

    r0 = func_0209e380(param0);
    r5_2 = *(unsigned char *) ((char *) param0 + 2);
    r4_2 = *(unsigned char *) ((char *) param1 + 2);
    r2 = (r4_2 - r5_2) * 0x3c;
    r5_1 = *(unsigned char *) ((char *) param0 + 1);
    r2 = r2 - r5_1;
    r0 = r0 * 0x5a0;
    r1 = r2 + r0;
    r4_1 = *(unsigned char *) ((char *) param1 + 1);
    result = r1 + r4_1;
    return result;
}
