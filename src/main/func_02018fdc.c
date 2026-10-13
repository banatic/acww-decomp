/* func_02018fdc @ 0x02018fdc, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char data[28];
} UnkStruct_02018fdc;
extern UnkStruct_02018fdc data_020c8290[];
UnkStruct_02018fdc *func_02018fdc(unsigned int idx)
{
    if (idx < 60) {
        return &data_020c8290[idx];
    }
    return 0;
}
