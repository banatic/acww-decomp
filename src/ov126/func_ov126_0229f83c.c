/* func_ov126_0229f83c @ 0x0229f83c, 0xaa bytes, Thumb, module ov126
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_0206fca4(void);
extern void func_ov126_0229f7dc(int);
extern void func_ov126_0229fb58(int);
extern void func_ov126_0229fb10(int);
extern void func_ov126_0229fa80(int);
extern void func_ov126_0229fa38(int);
extern void func_ov126_0229f9b8(int);
extern void func_ov126_0229f9a0(int);
extern void *func_ov126_0229f968(int);
extern void func_ov126_0229f930(int);
extern void func_ov126_0229f90c(int);
extern void func_ov126_0229f8e8(int);

void func_ov126_0229f83c(int arg)
{
    unsigned int result = func_0206fca4();

    if (result != 0xc && result != 0xd && result != 0xe) {
        func_ov126_0229f7dc(arg);
    }

    switch (result) {
        case 0xb:
            func_ov126_0229fb58(arg);
            break;
        case 0xc:
            func_ov126_0229fb10(arg);
            break;
        case 0xd:
            func_ov126_0229fa80(arg);
            break;
        case 0xe:
            func_ov126_0229fa38(arg);
            break;
        case 0xf:
            func_ov126_0229f9b8(arg);
            break;
        case 0x10:
            func_ov126_0229f9a0(arg);
            break;
        case 0x11:
            break;
        case 0x12:
            func_ov126_0229f968(arg);
            break;
        case 0x13:
            break;
        case 0x14:
            func_ov126_0229f930(arg);
            break;
        case 0x15:
            break;
        case 0x16:
            break;
        case 0x17:
            break;
        case 0x18:
        case 0x19:
            func_ov126_0229f90c(arg);
            break;
        case 0x1a:
        case 0x1b:
            func_ov126_0229f8e8(arg);
            break;
        default:
            break;
    }
}
