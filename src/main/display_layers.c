/* display_layers: 3 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020027f0 @ 0x020027f0, 0x18 bytes, Thumb
 * func_0200277c @ 0x0200277c, 0x74 bytes, Thumb
 * func_02002708 @ 0x02002708, 0x74 bytes, Thumb
 */

extern void func_0200284c(int param1, int param2, int param3);
extern void func_02001b34(int);
extern void func_02001afc(int);
extern void func_02001b44(int);
extern void func_02001b0c(int);

void func_0200277c(unsigned int n);

void func_020027f0(int param1)
{
    int r4;
    int r1;
    int r2;

    r4 = param1;
    func_0200277c(param1);
    func_0200284c(r4, 0, 0);
}

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
