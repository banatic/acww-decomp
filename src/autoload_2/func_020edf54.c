/* func_020edf54 @ 0x020edf54, 0x1c bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int *sSubOBJExtPltt;
extern int func_020e9c48(unsigned int *param1, unsigned int param2);

int func_020edf54(unsigned int param1)
{
    return func_020e9c48(sSubOBJExtPltt, param1);
}
