/* process: 4 functions, module autoload_2
 * mwccarm 1.2/base -O4,p
 * func_020edc58 @ 0x020edc58, 0xd8 bytes, ARM
 * func_020edc20 @ 0x020edc20, 0x38 bytes, ARM
 * func_020edbec @ 0x020edbec, 0x34 bytes, ARM
 * func_020edbbc @ 0x020edbbc, 0x30 bytes, ARM
 */

typedef int (*Handler)(void);

extern unsigned short data_021fcfdc; // 0x021fcfdc
extern unsigned char data_021fcfd4;  // 0x021fcfd4
extern Handler **data_021fd044;      // 0x021fd044, array of Handler* indexed by channel
extern void func_020edd30(int param0, unsigned int param1, unsigned int param2, unsigned char param3);
extern void func_020edec8(int err);
extern int (*data_021fcfe8)(int);
extern void (*data_021fcfec)(int);

int func_020edc20(int arg);

int func_020edc58(int chan, unsigned int p1, unsigned int p2, unsigned char p3)
{
    int retv;

    data_021fcfdc = (short) chan;
    data_021fcfd4 = 1;
    func_020edc20(chan);

    data_021fcfd4 = 2;
    func_020edd30(chan, p1, p2, p3);

    data_021fcfd4 = 3;
    retv = (*data_021fd044[chan])();

    if (retv != 0) {
        goto error;
    }

    data_021fcfd4 = 0;
    data_021fcfdc = 0xffff;
    return 0;

error:
    data_021fcfd4 = 4;
    func_020edec8(retv);
    data_021fcfd4 = 0;
    data_021fcfdc = 0xffff;
    return retv;
}

int func_020edc20(int arg)
{
    if (data_021fcfe8 == 0) {
        return 2;
    }
    return data_021fcfe8(arg);
}

void func_020edbec(int arg)
{
    if (data_021fcfec == 0) {
        return;
    }
    data_021fcfec(arg);
}

int func_020edbbc(int a, int b, unsigned int argument2, unsigned char argument3)
{
    if (b == 0) {
        return 0;
    }
    return func_020edc58(a, b + 0x14, argument2, argument3);
}
