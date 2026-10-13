/* func_0209f538 @ 0x0209f538, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02066a30(void *p);
extern char data_020e3758;

typedef struct {
    void *unk_00;
} UnkStruct_0209f538;

void *func_0209f538(void *p)
{
    func_02066a30(p);
    ((UnkStruct_0209f538 *) p)->unk_00 = (void *) &data_020e3758;
    return p;
}
