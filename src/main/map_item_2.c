/* map_item_2: 29 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0204b790 @ 0x0204b790, 0xc bytes, Thumb
 * func_0204b784 @ 0x0204b784, 0xc bytes, Thumb
 * func_0204b778 @ 0x0204b778, 0xc bytes, Thumb
 * func_0204b76c @ 0x0204b76c, 0xc bytes, Thumb
 * func_0204b760 @ 0x0204b760, 0xc bytes, Thumb
 * func_0204b710 @ 0x0204b710, 0x50 bytes, Thumb
 * func_0204b6e0 @ 0x0204b6e0, 0x2e bytes, Thumb
 * func_0204b6ac @ 0x0204b6ac, 0x34 bytes, Thumb
 * func_0204b678 @ 0x0204b678, 0x34 bytes, Thumb
 * func_0204b66c @ 0x0204b66c, 0xc bytes, Thumb
 * func_0204b65c @ 0x0204b65c, 0x10 bytes, Thumb
 * func_0204b638 @ 0x0204b638, 0x22 bytes, Thumb
 * func_0204b62c @ 0x0204b62c, 0xc bytes, Thumb
 * func_0204b620 @ 0x0204b620, 0xc bytes, Thumb
 * func_0204b5f4 @ 0x0204b5f4, 0x2c bytes, Thumb
 * func_0204b5ac @ 0x0204b5ac, 0x48 bytes, Thumb
 * func_0204b5a0 @ 0x0204b5a0, 0xc bytes, Thumb
 * func_0204b594 @ 0x0204b594, 0xc bytes, Thumb
 * func_0204b588 @ 0x0204b588, 0xc bytes, Thumb
 * func_0204b57c @ 0x0204b57c, 0xc bytes, Thumb
 * func_0204b544 @ 0x0204b544, 0x36 bytes, Thumb
 * func_0204b538 @ 0x0204b538, 0xc bytes, Thumb
 * func_0204b52c @ 0x0204b52c, 0xc bytes, Thumb
 * func_0204b520 @ 0x0204b520, 0xc bytes, Thumb
 * func_0204b4fc @ 0x0204b4fc, 0x22 bytes, Thumb
 * func_0204b4c4 @ 0x0204b4c4, 0x36 bytes, Thumb
 * func_0204b4b8 @ 0x0204b4b8, 0xc bytes, Thumb
 * func_0204b4ac @ 0x0204b4ac, 0xc bytes, Thumb
 * func_0204b4a0 @ 0x0204b4a0, 0xc bytes, Thumb
 */

extern int func_0204b48c(int a, int b, int c);
extern int func_0204b42c(unsigned short *);

int func_0204b790(int a)
{
    return func_0204b48c(a, 55, 62);
}

int func_0204b784(int a)
{
    return func_0204b48c(a, 0x3f, 0x46);
}

int func_0204b778(int a)
{
    return func_0204b48c(a, 0x47, 0x4e);
}

int func_0204b76c(int arg)
{
    return func_0204b48c(arg, 0x2f, 0x36);
}

int func_0204b760(int a)
{
    return func_0204b48c(a, 0x4f, 0x56);
}

int func_0204b710(int p)
{
    int result = 0;
    if (func_0204b790(p) == 0) {
        if (func_0204b784(p) != 0) {
            result = 1;
        } else if (func_0204b778(p) != 0) {
            result = 2;
        } else if (func_0204b76c(p) != 0) {
            result = 3;
        } else if (func_0204b760(p) != 0) {
            result = 4;
        }
    }
    return result;
}

int func_0204b6e0(unsigned short *argument0)
{
    int flag = 0;
    int r = func_0204b42c((unsigned short *) argument0);
    switch (r) {
        case 0x2b:
        case 0x62:
        case 0xd0:
        case 0xff:
            flag = 1;
            break;
        default:
            break;
    }
    return flag;
}

int func_0204b6ac(unsigned short *argument0)
{
    int r = 0;
    int v = func_0204b42c((unsigned short *) argument0);
    switch (v) {
        case 0x2c:
        case 0x63:
        case 0xd1:
        case 0x100:
            r = 1;
            break;
        default:
            break;
    }
    return r;
}

int func_0204b678(unsigned short *argument0)
{
    int result = 0;
    int v = func_0204b42c((unsigned short *) argument0);
    switch (v) {
        case 45:
        case 100:
        case 210:
        case 257:
            result = 1;
            break;
        default:
            break;
    }
    return result;
}

int func_0204b66c(int a)
{
    return func_0204b48c(a, 0x2b, 0x2e);
}

int func_0204b65c(int a)
{
    return func_0204b48c(a, 0xff, 0x102);
}

int func_0204b638(int p)
{
    if (func_0204b66c(p) || func_0204b65c(p)) {
        return 1;
    }
    return 0;
}

int func_0204b62c(int a)
{
    return func_0204b48c(a, 0x62, 0x65);
}

int func_0204b620(int a)
{
    return func_0204b48c(a, 0xd0, 0xd3);
}

int func_0204b5f4(int arg)
{
    if (func_0204b638(arg) || func_0204b62c(arg) || func_0204b620(arg)) {
        return 1;
    }
    return 0;
}

int func_0204b5ac(int p)
{
    int res = -1;
    if (func_0204b5f4(p) != 0) {
        if (func_0204b6e0((unsigned short *) p) != 0) {
            res = 1;
        } else if (func_0204b6ac((unsigned short *) p) != 0) {
            res = 2;
        } else if (func_0204b678((unsigned short *) p) != 0) {
            res = 3;
        } else {
            res = 4;
        }
    }
    return res;
}

int func_0204b5a0(int a)
{
    return func_0204b48c(a, 0x6e, 0x73);
}

int func_0204b594(int a)
{
    return func_0204b48c(a, 0x74, 0x79);
}

int func_0204b588(int a)
{
    return func_0204b48c(a, 0x7a, 0x7f);
}

int func_0204b57c(int param1)
{
    return func_0204b48c(param1, 0x80, 0x87);
}

int func_0204b544(int arg)
{
    if (func_0204b5a0(arg) || func_0204b594(arg) || func_0204b588(arg) || func_0204b57c(arg)) {
        return 1;
    } else {
        return 0;
    }
}

int func_0204b538(void *param1)
{
    return func_0204b48c((int) param1, 0, 5);
}

int func_0204b52c(int a)
{
    return func_0204b48c(a, 6, 0xb);
}

int func_0204b520(int a)
{
    return func_0204b48c(a, 12, 17);
}

int func_0204b4fc(void *param)
{
    if (func_0204b48c((int) param, 0x12, 0x19) != 0 || *(unsigned short *) param == 0x1c) {
        return 1;
    }
    return 0;
}

int func_0204b4c4(int arg)
{
    if (func_0204b538((void *) arg) || func_0204b52c(arg) || func_0204b520(arg) || func_0204b4fc((void *) arg)) {
        return 1;
    } else {
        return 0;
    }
}

int func_0204b4b8(int a)
{
    return func_0204b48c(a, 0x8a, 0x8f);
}

int func_0204b4ac(int a)
{
    return func_0204b48c(a, 0x90, 0x95);
}

int func_0204b4a0(int arg0)
{
    return func_0204b48c(arg0, 150, 155);
}
