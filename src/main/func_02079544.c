/* func_02079544 @ 0x02079544, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02073dd4(void *, int);
struct GType {
    char pad_00[0x64];
    int val;
};
extern struct GType *data_020ccf94;

int func_02079544(unsigned char *param)
{
    if (func_02073dd4(data_020ccf94, data_020ccf94->val) != 0 && *param != 7) {
        return 0;
    } else {
        return *param;
    }
}
