/* func_0203ac5c @ 0x0203ac5c, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x1f4];
    unsigned char enabled;
} CARDiWork;
extern CARDiWork *data_021c67a4; // 0x021c67a4

int func_0203ac5c(void)
{
    return data_021c67a4->enabled != 0;
}
