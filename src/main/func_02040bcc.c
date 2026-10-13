/* func_02040bcc @ 0x02040bcc, 0x2e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020409c8(int, int);

int func_02040bcc(int arg0, int arg1)
{
    int result = 0;
    unsigned char *p = (unsigned char *) func_020409c8(arg0, 1);
    int i = result;
    for (; i < 5; i++) {
        if (arg1 == p[2]) {
            result = i + 1;
            break;
        }
        p += 6;
    }
    return result;
}
