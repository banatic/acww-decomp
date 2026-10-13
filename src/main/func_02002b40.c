/* func_02002b40 @ 0x02002b40, 0x8e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void DC_FlushRange(int, int);
extern void func_02113088(int, int, int);
extern void GX_LoadBG2Scr(int, int, int);
extern void func_02112ee8(int, int, int);
extern void func_021130f0(int, int, int);
extern void func_02113020(int, int, int);
extern void func_02112f50(int, int, int);
extern void func_02112e80(int, int, int);

int func_02002b40(int a0, int a1, int a2, int a3)
{
    DC_FlushRange(a0, a2);
    switch (a1) {
        case 0:
            func_02113088(a0, a3, a2);
            break;
        case 1:
            GX_LoadBG2Scr(a0, a3, a2);
            break;
        case 2:
            func_02112ee8(a0, a3, a2);
            break;
        case 3:
            func_021130f0(a0, a3, a2);
            break;
        case 4:
            func_02113020(a0, a3, a2);
            break;
        case 5:
            func_02112f50(a0, a3, a2);
            break;
        case 6:
            func_02112e80(a0, a3, a2);
            break;
        default:
            break;
    }
    return 1;
}
