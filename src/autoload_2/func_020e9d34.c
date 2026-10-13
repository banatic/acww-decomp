/* func_020e9d34 @ 0x020e9d34, 0x10 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern int NNS_FndGetTotalFreeSizeForExpHeap(unsigned int);

struct func_020e9d34_arg {
    char pad_00[0x14];
    unsigned int value;
};

int func_020e9d34(struct func_020e9d34_arg *self)
{
    return NNS_FndGetTotalFreeSizeForExpHeap(self->value);
}
