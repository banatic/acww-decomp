/* func_020168ac @ 0x020168ac, 0x36 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0201b380(int arg);
extern int func_0201b37c(int arg);
extern int func_0201b378(int arg);

int func_020168ac(int unused, int selector, int arg)
{
    int result = selector;
    switch (selector) {
        case 0:
            result = func_0201b380(arg);
            break;
        case 1:
            result = func_0201b37c(arg);
            break;
        case 2:
            result = func_0201b378(arg);
            break;
    }
    return result;
}
