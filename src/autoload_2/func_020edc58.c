/* func_020edc58 @ 0x020edc58, 0xd8 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

typedef int (*Handler)(void);

extern unsigned short data_021fcfdc; // 0x021fcfdc
extern unsigned char data_021fcfd4;  // 0x021fcfd4
extern Handler **data_021fd044;      // 0x021fd044, array of Handler* indexed by channel

extern int func_020edc20(int arg);
extern void func_020edd30(int param0, unsigned int param1, unsigned int param2, unsigned char param3);
extern void func_020edec8(int err);

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
