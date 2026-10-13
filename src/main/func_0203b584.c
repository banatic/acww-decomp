/* func_0203b584 @ 0x0203b584, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0203caa4(void *a, int b, int c);
extern void func_0203c99c(void *a, int b);
extern void func_0203ad58(void);

typedef struct {
    unsigned char pad_00[4];
    unsigned char unk_04;
} UnkStruct_0203b584;

extern UnkStruct_0203b584 *data_021f6948;

int func_0203b584(void *a)
{
    if (data_021f6948->unk_04 == 0) {
        func_0203caa4(a, 0x1c, 0);
    } else {
        func_0203caa4(a, 0x1b, 0);
    }
    func_0203c99c(a, 3);
    func_0203ad58();
    return 1;
}
