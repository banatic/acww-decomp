/* func_0208ffac @ 0x0208ffac, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct data_021d369c {
    unsigned char pad_00[0xC];
    unsigned int unk_0C;
};
extern struct data_021d369c data_021d369c;

int func_0208ffac(void)
{
    return (data_021d369c.unk_0C == 1);
}
