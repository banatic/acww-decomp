/* func_020906dc @ 0x020906dc, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0209036c(void *a, void *b, int c);

void func_020906dc(void *p0, int p1)
{
    char *ptr;
    int i;
    ptr = (char *) p0 + 4;
    i = 0;
    while (i < 4) {
        if (*(void **) ptr == 0) {
            func_0209036c(ptr, p0, p1);
            return;
        }
        ptr += 0x148;
        i++;
    }
}
