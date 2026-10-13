/* func_ov045_02260644 @ 0x02260644, 0x24 bytes, Thumb, module ov045
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned int unk_00;
    unsigned int word1;
} UnkStruct_02260644;

extern void func_0209e474(void *);

int func_ov045_02260644(void)
{
    UnkStruct_02260644 s;
    s.unk_00 = 0;
    s.word1 = 0;
    func_0209e474(&s);
    if (((unsigned char *) &s)[2] >= 6u) {
        return 0;
    } else {
        return 1;
    }
}
