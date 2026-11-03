/* map_item_3: 17 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0204ba94 @ 0x0204ba94, 0x54 bytes, Thumb
 * func_0204ba40 @ 0x0204ba40, 0x54 bytes, Thumb
 * func_0204b9ec @ 0x0204b9ec, 0x54 bytes, Thumb
 * func_0204b998 @ 0x0204b998, 0x54 bytes, Thumb
 * func_0204b910 @ 0x0204b910, 0x88 bytes, Thumb
 * func_0204b8d4 @ 0x0204b8d4, 0x3c bytes, Thumb
 * func_0204b8c8 @ 0x0204b8c8, 0xc bytes, Thumb
 * func_0204b8bc @ 0x0204b8bc, 0xc bytes, Thumb
 * func_0204b8b0 @ 0x0204b8b0, 0xc bytes, Thumb
 * func_0204b8a4 @ 0x0204b8a4, 0xc bytes, Thumb
 * func_0204b898 @ 0x0204b898, 0xc bytes, Thumb
 * func_0204b888 @ 0x0204b888, 0xe bytes, Thumb
 * func_0204b87c @ 0x0204b87c, 0xc bytes, Thumb
 * func_0204b86c @ 0x0204b86c, 0xe bytes, Thumb
 * func_0204b860 @ 0x0204b860, 0xc bytes, Thumb
 * func_0204b7f8 @ 0x0204b7f8, 0x68 bytes, Thumb
 * func_0204b7a0 @ 0x0204b7a0, 0x56 bytes, Thumb
 */

extern int func_0204b42c(unsigned short *);
extern int func_0204b48c(int a, int b, int c);

int func_0204ba94(unsigned short *argument0)
{
    int ret = 0;
    int x = func_0204b42c((unsigned short *) argument0);

    switch (x) {
        case 0x26:
        case 0x2f:
        case 0x37:
        case 0x3f:
        case 0x47:
        case 0x4f:
        case 0x57:
        case 0x5d:
        case 0xc8:
            ret = 1;
            break;
        default:
            break;
    }

    return ret;
}

int func_0204ba40(unsigned short *argument0)
{
    int v;
    int result = 0;

    v = func_0204b42c((unsigned short *) argument0);
    switch (v) {
        case 0x27:
        case 0x30:
        case 0x38:
        case 0x40:
        case 0x48:
        case 0x50:
        case 0x58:
        case 0x5e:
        case 0xc9:
            result = 1;
            break;
        default:
            break;
    }
    return result;
}

int func_0204b9ec(unsigned short *argument0)
{
    int ret = 0;
    int x = func_0204b42c((unsigned short *) argument0);
    switch (x) {
        case 0x28:
        case 0x31:
        case 0x39:
        case 0x41:
        case 0x49:
        case 0x51:
        case 0x59:
        case 0x5f:
        case 0xca:
            ret = 1;
            break;
        default:
            break;
    }
    return ret;
}

int func_0204b998(unsigned short *argument0)
{
    int result = 0;
    switch (func_0204b42c((unsigned short *) argument0)) {
        case 41:
        case 50:
        case 58:
        case 66:
        case 74:
        case 82:
        case 90:
        case 96:
        case 203:
            result = 1;
            break;
        default:
            break;
    }
    return result;
}

int func_0204b910(unsigned short *argument0)
{
    int result = 0;
    int x = func_0204b42c((unsigned short *) argument0);

    switch (x) {
        case 0x2a:
        case 0x33:
        case 0x3b:
        case 0x43:
        case 0x4b:
        case 0x53:
        case 0x5b:
        case 0x61:
        case 0x66:
        case 0x67:
        case 0x68:
        case 0x69:
        case 0x6a:
        case 0x6b:
        case 0x6c:
        case 0x6d:
        case 0xcc:
            result = 1;
            break;
        default:
            break;
    }

    return result;
}

int func_0204b8d4(int arg)
{
    int ret = 0;
    int x = func_0204b42c((unsigned short *) arg);
    switch (x) {
        case 54:
        case 62:
        case 70:
        case 78:
        case 86:
        case 207:
            ret = 1;
            break;
    }
    return ret;
}

int func_0204b8c8(int a)
{
    return func_0204b48c(a, 0x26, 0x2a);
}

int func_0204b8bc(int a)
{
    return func_0204b48c(a, 0x5d, 0x61);
}

int func_0204b8b0(int a)
{
    return func_0204b48c(a, 0x2f, 0x56);
}

int func_0204b8a4(int a)
{
    return func_0204b48c(a, 0x57, 0x5b);
}

int func_0204b898(int a)
{
    return func_0204b48c(a, 0x66, 0x68);
}

int func_0204b888(unsigned short *ptr)
{
    if (*ptr == 0x69) {
        return 1;
    } else {
        return 0;
    }
}

int func_0204b87c(int a)
{
    return func_0204b48c(a, 0x6a, 0x6c);
}

int func_0204b86c(unsigned short *param0)
{
    if (*param0 == 0x6d) {
        return 1;
    }
    return 0;
}

int func_0204b860(int a)
{
    return func_0204b48c(a, 0xc8, 0xcf);
}

int func_0204b7f8(void *p)
{
    if (func_0204b8c8((int) p) || func_0204b8bc((int) p) || func_0204b8b0((int) p) || func_0204b8a4((int) p) || func_0204b898((int) p) || func_0204b888((unsigned short *) p) ||
        func_0204b87c((int) p) || func_0204b86c((unsigned short *) p) || func_0204b860((int) p)) {
        return 1;
    }
    return 0;
}

int func_0204b7a0(void *p)
{
    int r5 = -1;
    if (func_0204b7f8(p) != 0) {
        if (func_0204ba94((unsigned short *) p) != 0) {
            r5 = 0;
        } else if (func_0204ba40((unsigned short *) p) != 0) {
            r5 = 1;
        } else if (func_0204b9ec((unsigned short *) p) != 0) {
            r5 = 2;
        } else if (func_0204b998((unsigned short *) p) != 0) {
            r5 = 3;
        } else {
            r5 = 4;
        }
    }
    return r5;
}
