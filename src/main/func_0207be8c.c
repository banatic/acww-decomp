/* func_0207be8c @ 0x0207be8c, 0x54 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x64];
    int unk_64;
} UnkStruct_0207be8c;
typedef struct {
    char data[0x7ec];
} UnkStruct_0207be8c_2;

extern UnkStruct_0207be8c *data_020ccf94;
extern int func_02073dd4(UnkStruct_0207be8c *p, int field);
extern void func_0209e474(void *buffer);
extern void func_0208150c(UnkStruct_0207be8c_2 *p);
extern int func_02003704(void);
extern void func_0207d840(UnkStruct_0207be8c_2 *p, void *buffer);

void func_0207be8c(UnkStruct_0207be8c_2 *ptr)
{
    int i;
    int buffer[3];

    if (func_02073dd4(data_020ccf94, data_020ccf94->unk_64) != 0) {
        return;
    }

    buffer[0] = 0;
    buffer[1] = 0;
    func_0209e474(buffer);

    for (i = 0; i < 8; i++) {
        func_0208150c(ptr);
        if (func_02003704()) {
            func_0207d840(ptr, buffer);
        }
        ptr++;
    }
}
