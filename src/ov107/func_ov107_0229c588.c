/* func_ov107_0229c588 @ 0x0229c588, 0x26 bytes, Thumb, module ov107
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov107_0229c2c8(void *, int);
extern void func_ov002_02208098(void *, int);
extern void func_ov107_0229c4f0(void *);

typedef struct {
    char pad_00[0xBE];
    char unk_BE;
} Struct_ov107_0229c588;

void func_ov107_0229c588(void *p)
{
    func_ov107_0229c2c8(p, 1);
    ((Struct_ov107_0229c588 *) p)->unk_BE = 5;
    func_ov002_02208098(p, 0x11);
    func_ov107_0229c4f0(p);
}
