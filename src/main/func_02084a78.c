/* func_02084a78 @ 0x02084a78, 0x58 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x64];
    int unk_64;
} UnkStruct_02084a78;
extern UnkStruct_02084a78 *data_020ccf94;
extern int data_020d0644;

extern int func_020b65c4(void);
extern void func_0208602c(void);
extern void func_020860c8(void);
extern int func_02087ea0(void);
extern int func_02073dd4(UnkStruct_02084a78 *, int);
extern int func_02084d5c(void *, void *, int);
extern char data_020e1d8c[];

int func_02084a78(void)
{
    if (func_020b65c4() != 0) {
        goto ret0;
    }
    func_0208602c();
    func_020860c8();
    if (func_02087ea0() == 0) {
        goto ret0;
    }
    if (func_02073dd4(data_020ccf94, data_020ccf94->unk_64) != 0) {
        goto ret0;
    }
    {
        unsigned short local = 0xd011;
        return func_02084d5c(&local, data_020e1d8c, data_020d0644);
    }
ret0:
    return 0;
}
