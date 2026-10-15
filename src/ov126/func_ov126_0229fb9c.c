/* func_ov126_0229fb9c @ 0x0229fb9c, 0x78 bytes, Thumb, module ov126
 * mwccarm 1.2/base -O4,s
 */

extern int func_0206fca4(void);
extern int func_0206fc44(void);
extern int func_02051c08(int, unsigned char *, unsigned char);
extern void func_ov126_0229fc98(unsigned char *);
extern int func_ov126_0229fc7c(unsigned char *);
extern void func_ov126_0229fc34(unsigned char *);
extern void func_ov126_0229fc14(unsigned char *);

void func_ov126_0229fb9c(unsigned char *arg0)
{
    switch (func_0206fca4() - 11) {
        case 6:
        case 10:
        case 11:
        case 12:
            func_02051c08(func_0206fc44(), (unsigned char *) arg0 + 0x4248, arg0[0xa6]);
            break;
        case 0:
            func_ov126_0229fc98(arg0);
            break;
        case 7:
            func_ov126_0229fc7c(arg0);
            break;
        case 13:
        case 14:
            func_ov126_0229fc34(arg0);
            break;
        case 15:
        case 16:
            func_ov126_0229fc14(arg0);
            break;
        default:
            break;
    }
}
