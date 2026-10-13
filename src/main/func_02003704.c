/* func_02003704 @ 0x02003704, 0x22 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02064294(void *ptr);
extern int func_0200363c(unsigned char byte);

int func_02003704(void *ptr)
{
    int result = 0;
    if (func_02064294(ptr) == 1 && func_0200363c(((unsigned char *) ptr)[0xf]) == 1) {
        result = 1;
    }
    return result;
}
