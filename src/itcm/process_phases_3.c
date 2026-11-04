/* process_phases_3: 6 functions, module itcm
 * mwccarm 1.2/base -O4,s
 * func_01ffd444 @ 0x01ffd444, 0x8 bytes, ARM
 * func_01ffd41c @ 0x01ffd41c, 0x28 bytes, ARM
 * func_01ffd418 @ 0x01ffd418, 0x4 bytes, ARM
 * func_01ffd410 @ 0x01ffd410, 0x8 bytes, ARM
 * func_01ffd3e8 @ 0x01ffd3e8, 0x28 bytes, ARM
 * func_01ffd3e4 @ 0x01ffd3e4, 0x4 bytes, ARM
 */

int func_01ffd444(void *object)
{
    return 1;
}

int func_01ffd41c(unsigned char *p)
{
    if (p[0x0f] != 0) {
        goto L0;
    }
    if ((p[0x13] & 2) == 0) {
        goto L1;
    }
L0:
    return 0;
L1:
    return 1;
}

void func_01ffd418(void *object) {}

int func_01ffd410(void *object)
{
    return 1;
}

int func_01ffd3e8(unsigned char *p)
{
    if (p[0x0f] != 0) {
        goto L0;
    }
    if ((p[0x13] & 8) == 0) {
        goto L1;
    }
L0:
    return 0;
L1:
    return 1;
}

void func_01ffd3e4(void *object) {}
