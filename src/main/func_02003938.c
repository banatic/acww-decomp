/* func_02003938 @ 0x02003938, 0x32 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02003938(void *p);

int func_02003938(void *p)
{
    int result;
    int field38;

    if (*(unsigned char *) ((char *) p + 0x31) != 0 && *(int *) ((char *) p + 0x2c) == 0 && *(int *) ((char *) p + 0x3c) > 0) {
        result = 1;
    } else {
        result = 0;
    }

    if (result != 0) {
        field38 = *(int *) ((char *) p + 0x38);
        if (field38 != 5 && field38 != *(int *) ((char *) p + 0x34)) {
            result = 0;
        }
    }

    return result;
}
