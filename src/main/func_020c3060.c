/* func_020c3060 @ 0x020c3060, 0x3a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0201af58(void *dst, void *src, int a, short b);
extern int func_0201ae8c(void *buf);

int func_020c3060(void *src, void *dest, int param)
{
    char buffer[16];
    int result;

    result = 0;
    func_0201af58(buffer, (char *) src + 0x5c, param, *(short *) ((char *) src + 0x94));
    if (func_0201ae8c(buffer) != 1) {
        ((int *) dest)[0] = ((int *) buffer)[0];
        ((int *) dest)[1] = ((int *) buffer)[1];
        ((int *) dest)[2] = ((int *) buffer)[2];
        result = 1;
    }
    return result;
}
