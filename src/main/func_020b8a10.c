/* func_020b8a10 @ 0x020b8a10, 0x2a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_02062f90(void *buf, unsigned int val);
extern void func_0208aa48(void *a, void *b);
extern void *func_02062f4c(void *b);

typedef struct {
    unsigned char pad_00[8];
    unsigned char data[0xEC];
    unsigned int unk_F4;
} UnkStruct_020b8a10;

void func_020b8a10(UnkStruct_020b8a10 *param)
{
    unsigned char buffer[40];
    func_02062f90(buffer, param->unk_F4);
    func_0208aa48(param->data, buffer);
    func_02062f4c(buffer);
}
