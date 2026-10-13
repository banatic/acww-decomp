/* func_02088be0 @ 0x02088be0, 0x22 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0209df64(unsigned char *buf);
struct UnkStruct_02088be0 {
    unsigned char pad_00[4];
    unsigned char unk_04;
    unsigned char unk_05;
    unsigned char unk_06;
};
void func_02088be0(struct UnkStruct_02088be0 *param)
{
    unsigned char buf[3];
    func_0209df64(buf);
    param->unk_06 = buf[2];
    param->unk_05 = buf[1];
    param->unk_04 = buf[0];
}
