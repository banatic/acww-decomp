/* func_020371f0 @ 0x020371f0, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02035638(unsigned short value);

typedef struct {
    unsigned char pad_00[0xc];
    unsigned short val;
} UnkStruct_020371f0;

void func_020371f0(UnkStruct_020371f0 *s)
{
    if (s->val == 0xffff) {
        return;
    }
    func_02035638(s->val);
    s->val = 0xffff;
}
