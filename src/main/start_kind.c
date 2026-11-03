/* start_kind: 10 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020a1320 @ 0x020a1320, 0xc bytes, Thumb
 * func_020a1314 @ 0x020a1314, 0xc bytes, Thumb
 * func_020a1308 @ 0x020a1308, 0xc bytes, Thumb
 * func_020a12fc @ 0x020a12fc, 0xc bytes, Thumb
 * func_020a12e8 @ 0x020a12e8, 0x14 bytes, Thumb
 * func_020a12d4 @ 0x020a12d4, 0x14 bytes, Thumb
 * func_020a12c0 @ 0x020a12c0, 0x14 bytes, Thumb
 * func_020a12ac @ 0x020a12ac, 0x14 bytes, Thumb
 * func_020a1298 @ 0x020a1298, 0x14 bytes, Thumb
 * func_020a128c @ 0x020a128c, 0xc bytes, Thumb
 */

extern unsigned char data_021f3c30[];

void func_020a1320(void)
{
    (*(unsigned int *) data_021f3c30) = 1;
}

void func_020a1314(void)
{
    (*(int *) data_021f3c30) = 2;
}

void func_020a1308(void)
{
    (*(int *) data_021f3c30) = 3;
}

void func_020a12fc(void)
{
    unsigned int *ptr;
    ptr = (unsigned int *) data_021f3c30;
    *ptr = 4;
}

int func_020a12e8(void)
{
    if ((*(int *) data_021f3c30)) {
        return 1;
    }
    return 0;
}

int func_020a12d4(void)
{
    if ((*(unsigned int *) data_021f3c30) == 1) {
        return 1;
    }
    return 0;
}

int func_020a12c0(void)
{
    if ((*(int *) data_021f3c30) == 2) {
        return 1;
    } else {
        return 0;
    }
}

int func_020a12ac(void)
{
    if ((*(int *) data_021f3c30) == 3) {
        return 1;
    } else {
        return 0;
    }
}

int func_020a1298(void)
{
    if ((*(int *) data_021f3c30) == 4) {
        return 1;
    } else {
        return 0;
    }
}

void func_020a128c(void)
{
    (*(int *) data_021f3c30) = 0;
}
