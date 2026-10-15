/* func_02003618 @ 0x02003618, 0x22 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02003704(void *);
extern int func_0208249c(int param1, unsigned char param2);

int func_02003618(int param1, int param2)
{
    int result;
    int temp;
    int i;
    int j;

    result = 0;
    temp = param1;
    i = param2;

    if (func_02003704((void *) param1) == 1) {
        result = func_0208249c(i, *(unsigned char *) (temp + 0xf));
    }

    return result;
}
