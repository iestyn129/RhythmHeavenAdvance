extern const u8 s_lockstep_bgm_mid[];
struct SongHeader s_lockstep_bgm_seqData = {
	/* MIDI Sequence */ s_lockstep_bgm_mid,
	/* Sound Player  */ MUSIC_PLAYER_0,
	/* Bank Number   */ INST_BANK_LOCKSTEP,
	/* Volume        */ 90,
	/* Priority      */ 50,
	/* unk8          */ 0xFF,
	/* Song Title    */ s_lockstep_bgm_seqName,
	/* Song Number   */ 80
};

extern const u8 s_f_lockstep_step_mid[];
struct SongHeader s_f_lockstep_step_seqData = {
	/* MIDI Sequence */ s_f_lockstep_step_mid,
	/* Sound Player  */ MUSIC_PLAYER_1,
	/* Bank Number   */ INST_BANK_LOCKSTEP,
	/* Volume        */ 115,
	/* Priority      */ 80,
	/* unk8          */ 0x40,
	/* Song Title    */ s_f_lockstep_step_seqName,
	/* Song Number   */ 81
};

extern const u8 s_f_lockstep_shot_r_mid[];
struct SongHeader s_f_lockstep_shot_r_seqData = {
	/* MIDI Sequence */ s_f_lockstep_shot_r_mid,
	/* Sound Player  */ MUSIC_PLAYER_2,
	/* Bank Number   */ INST_BANK_LOCKSTEP,
	/* Volume        */ 115,
	/* Priority      */ 80,
	/* unk8          */ 0x40,
	/* Song Title    */ s_f_lockstep_shot_r_seqName,
	/* Song Number   */ 82
};

extern const u8 s_f_lockstep_shot_l_mid[];
struct SongHeader s_f_lockstep_shot_l_seqData = {
	/* MIDI Sequence */ s_f_lockstep_shot_l_mid,
	/* Sound Player  */ MUSIC_PLAYER_2,
	/* Bank Number   */ INST_BANK_LOCKSTEP,
	/* Volume        */ 115,
	/* Priority      */ 80,
	/* unk8          */ 0x40,
	/* Song Title    */ s_f_lockstep_shot_l_seqName,
	/* Song Number   */ 83
};
