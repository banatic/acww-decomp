/* func_020b2470 @ 0x020b2470, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b3f58(void);
struct nibble {
    unsigned char low : 4;
    unsigned char high : 4;
};
extern struct nibble data_021f4bac[];
int func_020b2470(void)
{
    return data_021f4bac[func_020b3f58()].high;
}
