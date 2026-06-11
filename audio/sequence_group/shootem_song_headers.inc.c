extern const u8 s_f_shootem_shot_mid[];
struct SongHeader s_f_shootem_shot_seqData = {
	/* MIDI Sequence */ s_f_shootem_shot_mid,
	/* Sound Player  */ SFX_PLAYER_0,
	/* Bank Number   */ INST_BANK_SHOOTEM,
	/* Volume        */ 115,
	/* Priority      */ 80,
	/* unk8          */ 0x40,
	/* Song Title    */ s_f_shootem_shot_seqName,
	/* Song Number   */ 91
};

extern const u8 s_f_shootem_spawn_mid[];
struct SongHeader s_f_shootem_spawn_seqData = {
	/* MIDI Sequence */ s_f_shootem_spawn_mid,
	/* Sound Player  */ SFX_PLAYER_1,
	/* Bank Number   */ INST_BANK_SHOOTEM,
	/* Volume        */ 115,
	/* Priority      */ 80,
	/* unk8          */ 0x40,
	/* Song Title    */ s_f_shootem_spawn_seqName,
	/* Song Number   */ 92
};

extern const u8 s_f_shootem_hit_mid[];
struct SongHeader s_f_shootem_hit_seqData = {
	/* MIDI Sequence */ s_f_shootem_hit_mid,
	/* Sound Player  */ SFX_PLAYER_2,
	/* Bank Number   */ INST_BANK_SHOOTEM,
	/* Volume        */ 127,
	/* Priority      */ 80,
	/* unk8          */ 0x40,
	/* Song Title    */ s_f_shootem_hit_seqName,
	/* Song Number   */ 93
};

extern const u8 s_f_shootem_miss_mid[];
struct SongHeader s_f_shootem_miss_seqData = {
	/* MIDI Sequence */ s_f_shootem_miss_mid,
	/* Sound Player  */ SFX_PLAYER_3,
	/* Bank Number   */ INST_BANK_SHOOTEM,
	/* Volume        */ 127,
	/* Priority      */ 80,
	/* unk8          */ 0x40,
	/* Song Title    */ s_f_shootem_miss_seqName,
	/* Song Number   */ 94
};
