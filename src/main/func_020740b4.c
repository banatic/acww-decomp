/* func_020740b4 @ 0x020740b4, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct GameState {
    char pad_00[0x64];
    int flag;
};

extern struct GameState *data_020ccf94;
extern unsigned int func_020740dc(void);

unsigned int func_020740b4(void)
{
    unsigned int result;
    int field;

    result = func_020740dc();
    field = data_020ccf94->flag;
    if (field < 4) {
        result |= (unsigned short) (1 << field);
    }
    return result;
}
