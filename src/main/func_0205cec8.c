/* func_0205cec8 @ 0x0205cec8, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char lo;
    unsigned char hi;
} pair_t;

extern pair_t *data_020dd414[];
extern void func_0205cf10(int a, int b);

unsigned char func_0205cec8(int a, int b)
{
    func_0205cf10(a, b);
    return data_020dd414[a][b].hi;
}
