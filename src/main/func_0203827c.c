/* func_0203827c @ 0x0203827c, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0xC9];
    unsigned char flag;
} UnkStruct_0203827c;

extern unsigned int data_020ccf94;
extern unsigned int func_020732d8(unsigned int);
extern void func_020383c4(UnkStruct_0203827c *);
extern void func_020380c4(UnkStruct_0203827c *);
extern void func_02038264(UnkStruct_0203827c *);

void func_0203827c(UnkStruct_0203827c *this)
{
    if (this->flag) {
        if ((func_020732d8(data_020ccf94) & 0x7C) != 0) {
            func_020383c4(this);
            func_020380c4(this);
        } else {
            func_02038264(this);
        }
    }
}
