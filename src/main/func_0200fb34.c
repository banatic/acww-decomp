/* func_0200fb34 @ 0x0200fb34, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x8e];
    short unk_8E;
} UnkStruct_0200fb34;
extern void func_020113e0(short *t, int b);
extern void func_020110a0(UnkStruct_0200fb34 *p, short *t);
void func_0200fb34(UnkStruct_0200fb34 *p, int b)
{
    short t;
    t = p->unk_8E;
    func_020113e0(&t, b);
    func_020110a0(p, &t);
}
