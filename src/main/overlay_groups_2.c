/* overlay_groups_2: 4 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02070094 @ 0x02070094, 0x24 bytes, Thumb
 * func_02070070 @ 0x02070070, 0x24 bytes, Thumb
 * func_0207004c @ 0x0207004c, 0x24 bytes, Thumb
 * func_0207000c @ 0x0207000c, 0x40 bytes, Thumb
 */

extern unsigned int data_021cfca0;
extern unsigned char data_020df328[];
extern int func_0206ffbc(int);

int func_02070094(void)
{
    if ((*(unsigned char *) data_020df328) != 1) {
        return 0;
    }
    if (data_021cfca0 != 0) {
        return 0;
    }
    return 1;
}

int func_02070070(void)
{
    if ((*(unsigned char *) data_020df328) == 0) {
        return 0;
    }
    if (data_021cfca0 != 0) {
        return 1;
    }
    return 0;
}

int func_0207004c(int param)
{
    int result;
    if (func_02070094() == 0) {
        result = 0;
    } else {
        data_020df328[1] = (unsigned char) param;
        data_020df328[0] = 2;
        result = 1;
    }
    return result;
}

int func_0207000c(int param)
{
    if (data_020df328[0] != 1) {
        return 0;
    }
    if ((*(int *) &data_021cfca0) == 0) {
        return 0;
    }
    if (func_0206ffbc(param) != 0) {
        return 0;
    }
    data_020df328[1] = param;
    data_020df328[0] = 2;
    return 1;
}
