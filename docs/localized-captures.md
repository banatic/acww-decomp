# Audited fish capture messages

Add `--localized-captures` to the resource generator or player builder. It creates a separate
`-captures` resource directory and executable suffix. It can be combined with the existing
keyboard, Spanish grammar and fixed-record name options. It needs no new runtime behavior;
the generated message file retains the original Korean layout.

The supported `message/obj/etc/getfish_.bmg` has 67 Korean rows and 65 European rows, with
12-byte INF1 entries. Its common indices have the same roles: 0-55 fish species, 56-58 trash,
59 empty, 60-62 full-pocket cases, 63 the completion lead and 64 completion. The two extra
Korean messages at 65 and 66 are empty. This was checked against the two supported dumps,
including the individual capture/species messages and the common handling tail.

For this explicitly audited path and exact shape, the converter imports rows 0-64 without
renumbering. It keeps all 67 original indices and all original per-row attributes, including
those of the two additional empty rows. Those rows point to a terminated empty UTF-16
payload. Nonempty extra rows, different counts, encodings or entry sizes are rejected; invalid
offsets raise an error. This exception is not applied to other mismatched archives. Without
the option, the previous strict fallback behavior and generated paths remain available.

Four synthetic tests check preservation of every index and original attribute, default
rejection, incompatible/nonempty tails and corrupt offsets. The supported private dumps
produce one more imported script, leaving 131 fallbacks with this option. This does not
resolve the other 40 message-count mismatches identified by the static audit.

Live Clean validation replayed the prepared fishing case through frame 37764 with Spanish
grammar and capture conversion: the captured fish was announced in Spanish. After accepting
the dialogue, item 0x12e9 entered pocket 1 at frame 38124. The private dump check also converts
the archive in all five languages, retaining 67 indices and every original attribute. The fixed-record name
option is tested separately because it changes the preceding dialogue's metadata and timing.
No private text, ROM, screenshots or saves are committed.
