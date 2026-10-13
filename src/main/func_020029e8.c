/* func_020029e8 @ 0x020029e8, 0xa0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#define REG16(addr) (*(volatile unsigned short *) (addr))

void func_020029e8(int layer, int priority)
{
    switch (layer) {
        case 0:
            REG16(0x0400000a) = (REG16(0x0400000a) & ~3) | priority;
            break;
        case 1:
            REG16(0x0400000c) = (REG16(0x0400000c) & ~3) | priority;
            break;
        case 2:
            REG16(0x0400000e) = (REG16(0x0400000e) & ~3) | priority;
            break;
        case 3:
            REG16(0x04001008) = (REG16(0x04001008) & ~3) | priority;
            break;
        case 4:
            REG16(0x0400100a) = (REG16(0x0400100a) & ~3) | priority;
            break;
        case 5:
            REG16(0x0400100c) = (REG16(0x0400100c) & ~3) | priority;
            break;
        case 6:
            REG16(0x0400100e) = (REG16(0x0400100e) & ~3) | priority;
            break;
        default:
            break;
    }
}
