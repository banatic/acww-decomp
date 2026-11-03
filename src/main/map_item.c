/* map_item: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0204b468 @ 0x0204b468, 0x22 bytes, Thumb
 * func_0204b430 @ 0x0204b430, 0x36 bytes, Thumb
 */

extern int func_0204b48c(void *, int, int);
extern int func_0204b4b8(int);
extern int func_0204b4ac(int);
extern int func_0204b4a0(int);

int func_0204b468(void *p)
{
    return func_0204b48c(p, 0x9C, 0xA3) || (*(unsigned short *) p == 0xA5);
}

int func_0204b430(int arg)
{
    if (func_0204b4b8(arg) || func_0204b4ac(arg) || func_0204b4a0(arg) || func_0204b468((void *) arg)) {
        return 1;
    } else {
        return 0;
    }
}
