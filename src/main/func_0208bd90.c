/* func_0208bd90 @ 0x0208bd90, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0208bd90 {
    char pad_00[12];
    char sub[20];
    int unk_20;
    char pad_24;
    char unk_25;
} UnkStruct_0208bd90;

extern int data_020d5c44;
void func_0208a1f0(char *, int);
void func_0208a1ec(char *, int);
void *func_0208a144(char *);
void func_0208a158(char *);

void func_0208bd90(UnkStruct_0208bd90 *obj)
{
    obj->unk_20 = 2;
    obj->unk_25 = 0;
    func_0208a1f0(obj->sub, (int) &data_020d5c44);
    func_0208a1ec(obj->sub, 1);
    func_0208a144(obj->sub);
    func_0208a158(obj->sub);
}
