/* func_02002708 @ 0x02002708, 0x74 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02001b44(int);
extern void func_02001b0c(int);

void func_02002708(unsigned int n)
{
    switch (n) {
        case 0:
            func_02001b44(2);
            break;
        case 1:
            func_02001b44(4);
            break;
        case 2:
            func_02001b44(8);
            break;
        case 7:
            func_02001b44(16);
            break;
        case 3:
            func_02001b0c(1);
            break;
        case 4:
            func_02001b0c(2);
            break;
        case 5:
            func_02001b0c(4);
            break;
        case 6:
            func_02001b0c(8);
            break;
        case 8:
            func_02001b0c(16);
            break;
    }
}
