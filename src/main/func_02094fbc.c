/* func_02094fbc @ 0x02094fbc, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02094fbc {
    void *unk_00;
};

extern char data_020e2f6c[];
void *func_020a8c38(struct UnkStruct_02094fbc *arg);

struct UnkStruct_02094fbc *func_02094fbc(struct UnkStruct_02094fbc *arg)
{
    arg->unk_00 = &data_020e2f6c;
    func_020a8c38(arg);
    return arg;
}
