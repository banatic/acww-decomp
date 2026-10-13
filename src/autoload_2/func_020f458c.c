/* func_020f458c @ 0x020f458c, 0x38 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void NNS_SndHeapLoadState(int, int);
extern char data_0213efb4;
typedef struct {
    char pad_00[0x28];
    int unk_28;
    int unk_2C;
} Global_021fd1bc;
extern Global_021fd1bc data_021fd1bc;

void *func_020f458c(void *p)
{
    int x;
    *(void **) p = &data_0213efb4;
    x = data_021fd1bc.unk_28;
    data_021fd1bc.unk_2C = 0;
    NNS_SndHeapLoadState(x, 0);
    return p;
}
