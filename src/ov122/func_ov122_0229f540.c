/* func_ov122_0229f540 @ 0x0229f540, 0x50 bytes, Thumb, module ov122
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_0220a58c(void *p, unsigned char a, unsigned char b);

extern unsigned char data_021f6c54;
extern unsigned char data_021f6c58;

int func_ov122_0229f540(char *self)
{
    if (func_ov002_0220a58c(self + 0x4010, data_021f6c58, data_021f6c54)) {
        *(unsigned char *) (self + 0xb0) = data_021f6c54;
        *(unsigned char *) (self + 0xb1) = *(unsigned char *) (self + 0xb2);
        *(unsigned char *) (self + 0xaf) = *(unsigned char *) (self + 0xb2);
        return 1;
    }
    return 0;
}
