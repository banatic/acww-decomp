/* func_020af788 @ 0x020af788, 0xb4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020af898(void *p);
extern int func_020af028(void *p);
extern void *func_020afad4(void *p);
extern int func_020afb48(void *p, void *buf);
extern void func_0209e474(void *ptr);
extern void func_0209e29c(void *ptr, int mode);
extern void func_0209e140(void *ptr, int mode);
extern void func_020afcf4(int a, int b);
extern int func_02073d90(unsigned int x);
extern unsigned int data_020ccf94;
extern void *MI_CpuCopy8(void *dest, const void *src, unsigned int n);

struct UnkStruct_020af788 {
    unsigned char unk_00;
    unsigned char unk_01;
    unsigned char unk_02;
    unsigned char unk_03;
};

void func_020af788(void *p)
{
    unsigned char local0[8];
    unsigned char buffer[8];
    unsigned char tmp;
    int r4;

    r4 = func_020af898(p);
    if (func_02073d90(data_020ccf94) != 0) {
        return;
    }

    if (func_020af028(p) >= r4) {
        return;
    }

    if (((struct UnkStruct_020af788 *) func_020afad4(p))->unk_03 != 0) {
        return;
    }

    *(unsigned int *) &local0[0] = 0;
    *(unsigned int *) &local0[4] = 0;

    func_0209e474(local0);
    func_0209e29c(local0, 2);
    MI_CpuCopy8(local0, buffer, 8);
    func_0209e140(buffer, 1);
    if (func_020afb48(p, buffer) != 0) {
        func_0209e29c(local0, 1);
    }

    ((struct UnkStruct_020af788 *) func_020afad4(p))->unk_03 = 1;
    tmp = local0[5];
    ((struct UnkStruct_020af788 *) func_020afad4(p))->unk_02 = tmp;
    tmp = local0[4];
    ((struct UnkStruct_020af788 *) func_020afad4(p))->unk_01 = tmp;
    tmp = local0[3];
    ((struct UnkStruct_020af788 *) func_020afad4(p))->unk_00 = tmp;

    func_0209e140(local0, 1);
    func_020afcf4(local0[4], local0[3]);
}
