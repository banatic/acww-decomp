/* func_0200277c @ 0x0200277c, 0x74 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02001b34(int);
extern void func_02001afc(int);

void func_0200277c(unsigned int n)
{
    switch (n) {
        case 0:
            func_02001b34(2);
            break;
        case 1:
            func_02001b34(4);
            break;
        case 2:
            func_02001b34(8);
            break;
        case 7:
            func_02001b34(16);
            break;
        case 3:
            func_02001afc(1);
            break;
        case 4:
            func_02001afc(2);
            break;
        case 5:
            func_02001afc(4);
            break;
        case 6:
            func_02001afc(8);
            break;
        case 8:
            func_02001afc(16);
            break;
    }
}
