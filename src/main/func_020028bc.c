/* func_020028bc @ 0x020028bc, 0x12c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

void func_020028bc(unsigned mode, int a, int b, int c)
{
    switch (mode) {
        case 0:
            *((volatile unsigned short *) 0x0400000A) =
                (c << 2) | (((b << 7) | ((*((volatile unsigned short *) 0x0400000A) & 0x43) | (a << 14))) | 0x500);
            break;
        case 1:
            *((volatile unsigned short *) 0x0400000C) =
                (c << 2) | (((b << 7) | ((*((volatile unsigned short *) 0x0400000C) & 0x43) | (a << 14))) | 0x600);
            break;
        case 2:
            *((volatile unsigned short *) 0x0400000E) =
                (c << 2) | (((b << 7) | ((*((volatile unsigned short *) 0x0400000E) & 0x43) | (a << 14))) | 0x700);
            break;
        case 3:
            *((volatile unsigned short *) 0x04001008) =
                (c << 2) | (((b << 7) | ((*((volatile unsigned short *) 0x04001008) & 0x43) | (a << 14))) | 0xC00);
            break;
        case 4:
            *((volatile unsigned short *) 0x0400100A) =
                (c << 2) | (((b << 7) | ((*((volatile unsigned short *) 0x0400100A) & 0x43) | (a << 14))) | 0xD00);
            break;
        case 5:
            *((volatile unsigned short *) 0x0400100C) =
                (c << 2) | (((b << 7) | ((*((volatile unsigned short *) 0x0400100C) & 0x43) | (a << 14))) | 0xE00);
            break;
        case 6:
            *((volatile unsigned short *) 0x0400100E) =
                (c << 2) | (((b << 7) | ((*((volatile unsigned short *) 0x0400100E) & 0x43) | (a << 14))) | 0xF00);
            break;
        default:
            break;
    }
}
