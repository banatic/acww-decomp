/* func_020a55dc @ 0x020a55dc, 0x94 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020a55dc {
    unsigned char pad_00[0x64];
    int unk_64;
};

extern int func_020ee61c(int);
extern void func_020a5670(void);
extern void func_0208f8f0(void);
extern void func_020a7448(void);
extern void func_020a6d84(void);
extern int func_02073dd4(struct UnkStruct_020a55dc *, int);
extern int func_020a6ea0(void);
extern void func_020a6eb0(int);

extern unsigned char data_021f42f0;
extern int data_021f42f4;
extern unsigned char data_021f42e0;
extern unsigned char data_021f42dc;
extern unsigned char data_021f42e4;
extern struct UnkStruct_020a55dc *data_020ccf94;

int func_020a55dc(int arg)
{
    if (func_020ee61c(arg) == 0) {
        return 0;
    }

    if (data_021f42f0 != 0) {
        return 1;
    }

    func_020a5670();
    func_0208f8f0();
    data_021f42f4 = arg;
    data_021f42e0 = 4;
    func_020a7448();
    func_020a6d84();
    data_021f42f0++;

    if (func_02073dd4(data_020ccf94, data_020ccf94->unk_64) != 0) {
        int v = func_020a6ea0();
        switch (v) {
            case 6:
                func_020a6eb0(7);
                break;
            case 0xd:
                func_020a6eb0(0xe);
                break;
        }
    }

    data_021f42dc = 0;
    data_021f42e4 = 0;

    return 1;
}
