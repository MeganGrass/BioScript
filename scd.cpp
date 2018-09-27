
#include "stdafx.h"
#include FRAMEWORK_H

#include BIO2_H
#include "bytecode.h"
#include "op15.h"
#include "opcode.h"

// Boot
Bio_Hazard_2_Script::Bio_Hazard_2_Script(VOID) {
}
Bio_Hazard_2_Script::~Bio_Hazard_2_Script(VOID) {
}
// I/O
ULONG Bio_Hazard_2_Script::InitScan(_iobuf * BINARY, ULONG _Offset) {

	// Error
	if (!IsOpen(BINARY)) { return NULL; }

	// Variable
	ULONG Pointer = _Offset;
	UCHAR Opcode = NULL;
	UCHAR OpPeek = NULL;
	ULONG _Filesize = Size(BINARY);
	Scan = new tagBioScriptScan;
	std::vector <tagBio2Bytecode::tagIfel_ck> Ifel_ck;
	std::vector <tagBio2Bytecode::tagElse_ck> Else_ck;
	std::vector <tagBio2Bytecode::tagEndif> Endif;

	// Work
	Pointer = _Offset;
	Opcode = NULL;
	for (ULONG n = 0; n < _Filesize; n++) {

		// Complete
		if (feof(BINARY)) { break; }
		if (Pointer >= _Filesize) { break; }

		// Opcodes & Pointers
		Read(BINARY, Pointer, &Opcode, sizeof(unsigned char));
		Scan->Pointer.push_back(Pointer);
		Scan->Opcode.push_back(Opcode);
		Read(BINARY, (Pointer + Bio_Hazard_2_Script_Bytecode_Size[Opcode]), &OpPeek, sizeof(unsigned char));

		// Bytecode Size
		switch (Opcode)
		{
		case 0x00: {
			if (!OpPeek) {
				if (Else_ck.size()) { Else_ck.pop_back(); }
				if (Ifel_ck.size()) { Ifel_ck.pop_back(); }
				Pointer++;
				Scan->Pointer.push_back(Pointer);
				Scan->Opcode.push_back(Opcode);
			}
		} break;
		case 0x01: {
			if (!Ifel_ck.size() && !Else_ck.size()) {
				Pointer += Bio_Hazard_2_Script_Bytecode_Size[Opcode];
				Scan->Size = (Pointer - _Offset);
				return Scan->Size;
			}
		} break;
		case 0x06: {
			tagBio2Bytecode::tagIfel_ck Data = { NULL };
			Read(BINARY, Pointer, &Data, sizeof(tagBio2Bytecode::tagIfel_ck));
			Ifel_ck.push_back(Data);
		} break;
		case 0x07: {
			tagBio2Bytecode::tagElse_ck Data = { NULL };
			Read(BINARY, Pointer, &Data, sizeof(tagBio2Bytecode::tagElse_ck));
			Else_ck.push_back(Data);
		} break;
		case 0x08: {
			if (Ifel_ck.size()) { Ifel_ck.pop_back(); }
		} break;
		}

		// Complete
		Pointer += Bio_Hazard_2_Script_Bytecode_Size[Opcode];
	}

	// Terminate
	return NULL;
}
ULONG Bio_Hazard_2_Script::InitScan(CONST CHAR * _FileName, ...) {

	// _FileName
	va_list _ArgList = { NULL };
	__crt_va_start(_ArgList, _FileName);
	_StrLen = (_vscprintf(_FileName, _ArgList) + 2);
	CHAR * FileName = new CHAR[(_StrLen * 2)];
	RtlSecureZeroMemory(FileName, (_StrLen * 2));
	vsprintf_s(FileName, _StrLen, _FileName, _ArgList);
	__crt_va_end(_ArgList);

	// Error
	if (!Exists(FileName)) { delete[] FileName; return NULL; }

	// Open
	CHAR * Directory = GetDirectory(FileName);
	CHAR * NameBase = GetNamebase(FileName);
	_iobuf * _File = Open(READ_FILE, FileName);
	_iobuf * Log = Open(CREATE_FILE, "%s\\%s.log", Directory, NameBase);

	// Work
	ULONG Size = InitScan(_File, 0x00);
	Print(Log, (CHAR*)"// %s\r\n// %d opcodes\r\n", FileName, Scan->Opcode.size());
	if (Size) {
		for (ULONG n = 0; n < Scan->Opcode.size(); n++) {
			Print(Log, (CHAR*)"// [%02X] [%08X]\r\n", Scan->Opcode[n], Scan->Pointer[n]);
		}
	}

	// Cleanup
	delete[] NameBase;
	delete[] Directory;
	delete[] FileName;
	fclose(Log);
	fclose(_File);

	// Terminate
	return Size;
}
UCHAR Bio_Hazard_2_Script::ScdRead(_iobuf * BINARY, ULONG _Offset) {

	// Error
	if (!IsOpen(BINARY)) { return NULL; }
	if (feof(BINARY)) { return NULL; }

	// Opcode
	Read(BINARY, _Offset, &Scd->Opcode, 1);

	// Bytecode
	switch(Scd->Opcode)
	{
	case 0x00:
	{
		if (ElseCk) {
			USHORT EndIfElse = NULL;
			Read(BINARY, _Offset, &EndIfElse, 0x02);
			if (!EndIfElse) {
				Scd->Opcode = Scd->Endif.Opcode = 0x08;
				Scd->Endif.zAlign = 0x00;
				ElseCnt--;
				if (!ElseCnt) { ElseCk = FALSE; }
			} else {
				Read(BINARY, _Offset, &Scd->Nop, sizeof(tagBio2Bytecode::tagNop));
			}
		} else {
			Read(BINARY, _Offset, &Scd->Nop, sizeof(tagBio2Bytecode::tagNop));
		}
	}
	break;
	case 0x01:
		Read(BINARY, _Offset, &Scd->Evt_end, sizeof(tagBio2Bytecode::tagEvt_end));
	break;
	case 0x02:
		Read(BINARY, _Offset, &Scd->Evt_next, sizeof(tagBio2Bytecode::tagEvt_next));
	break;
	case 0x03:
		Read(BINARY, _Offset, &Scd->Evt_chain, sizeof(tagBio2Bytecode::tagEvt_chain));
	break;
	case 0x04:
		Read(BINARY, _Offset, &Scd->Evt_exec, sizeof(tagBio2Bytecode::tagEvt_exec));
	break;
	case 0x05:
		Read(BINARY, _Offset, &Scd->Evt_kill, sizeof(tagBio2Bytecode::tagEvt_kill));
	break;
	case 0x06:
		Read(BINARY, _Offset, &Scd->Ifel_ck, sizeof(tagBio2Bytecode::tagIfel_ck));
	break;
	case 0x07:
		Read(BINARY, _Offset, &Scd->Else_ck, sizeof(tagBio2Bytecode::tagElse_ck));
		ElseCk = TRUE;
		ElseCnt++;
	break;
	case 0x08:
		Read(BINARY, _Offset, &Scd->Endif, sizeof(tagBio2Bytecode::tagEndif));
	break;
	case 0x09:
		Read(BINARY, _Offset, &Scd->Sleep, sizeof(tagBio2Bytecode::tagSleep));
	break;
	case 0x0A:
		Read(BINARY, _Offset, &Scd->Sleeping, sizeof(tagBio2Bytecode::tagSleeping));
	break;
	case 0x0B:
		Read(BINARY, _Offset, &Scd->Wsleep, sizeof(tagBio2Bytecode::tagWsleep));
	break;
	case 0x0C:
		Read(BINARY, _Offset, &Scd->Wsleeping, sizeof(tagBio2Bytecode::tagWsleeping));
	break;
	case 0x0D:
		Read(BINARY, _Offset, &Scd->For, sizeof(tagBio2Bytecode::tagFor));
	break;
	case 0x0E:
		Read(BINARY, _Offset, &Scd->Next, sizeof(tagBio2Bytecode::tagNext));
	break;
	case 0x0F:
		Read(BINARY, _Offset, &Scd->While, sizeof(tagBio2Bytecode::tagWhile));
	break;
	case 0x10:
		Read(BINARY, _Offset, &Scd->Ewhile, sizeof(tagBio2Bytecode::tagEwhile));
	break;
	case 0x11:
		Read(BINARY, _Offset, &Scd->Do, sizeof(tagBio2Bytecode::tagDo));
	break;
	case 0x12:
		Read(BINARY, _Offset, &Scd->Edwhile, sizeof(tagBio2Bytecode::tagEdwhile));
	break;
	case 0x13:
		Read(BINARY, _Offset, &Scd->Switch, sizeof(tagBio2Bytecode::tagSwitch));
	break;
	case 0x14:
		Read(BINARY, _Offset, &Scd->Case, sizeof(tagBio2Bytecode::tagCase));
	break;
	case 0x15:
		Read(BINARY, _Offset, &Scd->Default, sizeof(tagBio2Bytecode::tagDefault));
	break;
	case 0x16:
		Read(BINARY, _Offset, &Scd->Eswitch, sizeof(tagBio2Bytecode::tagEswitch));
	break;
	case 0x17:
		Read(BINARY, _Offset, &Scd->Goto, sizeof(tagBio2Bytecode::tagGoto));
	break;
	case 0x18:
		Read(BINARY, _Offset, &Scd->Gosub, sizeof(tagBio2Bytecode::tagGosub));
	break;
	case 0x19:
		Read(BINARY, _Offset, &Scd->Return, sizeof(tagBio2Bytecode::tagReturn));
	break;
	case 0x1A:
		Read(BINARY, _Offset, &Scd->Break, sizeof(tagBio2Bytecode::tagBreak));
	break;
	case 0x1B:
		Read(BINARY, _Offset, &Scd->For2, sizeof(tagBio2Bytecode::tagFor2));
	break;
	case 0x1C:
		Read(BINARY, _Offset, &Scd->Break_point, sizeof(tagBio2Bytecode::tagBreak_point));
	break;
	case 0x1D:
		Read(BINARY, _Offset, &Scd->Work_copy, sizeof(tagBio2Bytecode::tagWork_copy));
	break;
	case 0x1E:
		Read(BINARY, _Offset, &Scd->Opcode1E, sizeof(tagBio2Bytecode::tagOpcode1E));
	break;
	case 0x1F:
		Read(BINARY, _Offset, &Scd->Opcode1F, sizeof(tagBio2Bytecode::tagOpcode1F));
	break;
	case 0x20:
		Read(BINARY, _Offset, &Scd->Opcode20, sizeof(tagBio2Bytecode::tagOpcode20));
	break;
	case 0x21:
		Read(BINARY, _Offset, &Scd->Ck, sizeof(tagBio2Bytecode::tagCk));
	break;
	case 0x22:
		Read(BINARY, _Offset, &Scd->Set, sizeof(tagBio2Bytecode::tagSet));
	break;
	case 0x23:
		Read(BINARY, _Offset, &Scd->Cmp, sizeof(tagBio2Bytecode::tagCmp));
	break;
	case 0x24:
		Read(BINARY, _Offset, &Scd->Save, sizeof(tagBio2Bytecode::tagSave));
	break;
	case 0x25:
		Read(BINARY, _Offset, &Scd->Copy, sizeof(tagBio2Bytecode::tagCopy));
	break;
	case 0x26:
		Read(BINARY, _Offset, &Scd->Calc, sizeof(tagBio2Bytecode::tagCalc));
	break;
	case 0x27:
		Read(BINARY, _Offset, &Scd->Calc2, sizeof(tagBio2Bytecode::tagCalc2));
	break;
	case 0x28:
		Read(BINARY, _Offset, &Scd->Sce_rnd, sizeof(tagBio2Bytecode::tagSce_rnd));
	break;
	case 0x29:
		Read(BINARY, _Offset, &Scd->Cut_chg, sizeof(tagBio2Bytecode::tagCut_chg));
	break;
	case 0x2A:
		Read(BINARY, _Offset, &Scd->Cut_old, sizeof(tagBio2Bytecode::tagCut_old));
	break;
	case 0x2B:
		Read(BINARY, _Offset, &Scd->Message_on, sizeof(tagBio2Bytecode::tagMessage_on));
	break;
	case 0x2C:
		Read(BINARY, _Offset, &Scd->Aot_set, sizeof(tagBio2Bytecode::tagAot_set));
	break;
	case 0x2D:
		Read(BINARY, _Offset, &Scd->Obj_model_set, sizeof(tagBio2Bytecode::tagObj_model_set));
	break;
	case 0x2E:
		Read(BINARY, _Offset, &Scd->Work_set, sizeof(tagBio2Bytecode::tagWork_set));
	break;
	case 0x2F:
		Read(BINARY, _Offset, &Scd->Speed_set, sizeof(tagBio2Bytecode::tagSpeed_set));
	break;
	case 0x30:
		Read(BINARY, _Offset, &Scd->Add_speed, sizeof(tagBio2Bytecode::tagAdd_speed));
	break;
	case 0x31:
		Read(BINARY, _Offset, &Scd->Add_aspeed, sizeof(tagBio2Bytecode::tagAdd_aspeed));
	break;
	case 0x32:
		Read(BINARY, _Offset, &Scd->Pos_set, sizeof(tagBio2Bytecode::tagPos_set));
	break;
	case 0x33:
		Read(BINARY, _Offset, &Scd->Dir_set, sizeof(tagBio2Bytecode::tagDir_set));
	break;
	case 0x34:
		Read(BINARY, _Offset, &Scd->Member_set, sizeof(tagBio2Bytecode::tagMember_set));
	break;
	case 0x35:
		Read(BINARY, _Offset, &Scd->Member_set2, sizeof(tagBio2Bytecode::tagMember_set2));
	break;
	case 0x36:
		Read(BINARY, _Offset, &Scd->Se_on, sizeof(tagBio2Bytecode::tagSe_on));
	break;
	case 0x37:
		Read(BINARY, _Offset, &Scd->Sca_id_set, sizeof(tagBio2Bytecode::tagSca_id_set));
	break;
	case 0x38:
		Read(BINARY, _Offset, &Scd->Flr_set, sizeof(tagBio2Bytecode::tagFlr_set));
	break;
	case 0x39:
		Read(BINARY, _Offset, &Scd->Dir_ck, sizeof(tagBio2Bytecode::tagDir_ck));
	break;
	case 0x3A:
		Read(BINARY, _Offset, &Scd->Sce_espr_on, sizeof(tagBio2Bytecode::tagSce_espr_on));
	break;
	case 0x3B:
		Read(BINARY, _Offset, &Scd->Door_aot_set, sizeof(tagBio2Bytecode::tagDoor_aot_set));
	break;
	case 0x3C:
		Read(BINARY, _Offset, &Scd->Cut_auto, sizeof(tagBio2Bytecode::tagCut_auto));
	break;
	case 0x3D:
		Read(BINARY, _Offset, &Scd->Member_copy, sizeof(tagBio2Bytecode::tagMember_copy));
	break;
	case 0x3E:
		Read(BINARY, _Offset, &Scd->Member_cmp, sizeof(tagBio2Bytecode::tagMember_cmp));
	break;
	case 0x3F:
		Read(BINARY, _Offset, &Scd->Plc_motion, sizeof(tagBio2Bytecode::tagPlc_motion));
	break;
	case 0x40:
		Read(BINARY, _Offset, &Scd->Plc_dest, sizeof(tagBio2Bytecode::tagPlc_dest));
	break;
	case 0x41:
		Read(BINARY, _Offset, &Scd->Plc_neck, sizeof(tagBio2Bytecode::tagPlc_neck));
	break;
	case 0x42:
		Read(BINARY, _Offset, &Scd->Plc_ret, sizeof(tagBio2Bytecode::tagPlc_ret));
	break;
	case 0x43:
		Read(BINARY, _Offset, &Scd->Plc_flg, sizeof(tagBio2Bytecode::tagPlc_flg));
	break;
	case 0x44:
		Read(BINARY, _Offset, &Scd->Sce_em_set, sizeof(tagBio2Bytecode::tagSce_em_set));
	break;
	case 0x45:
		if (TrialEdition) {
			Read(BINARY, _Offset, &Trial->Col_chg_set, sizeof(tagBio2BytecodeT::tagCol_chg_set));
		} else {
			Read(BINARY, _Offset, &Scd->Col_chg_set, sizeof(tagBio2Bytecode::tagCol_chg_set));
		}
	break;
	case 0x46:
		Read(BINARY, _Offset, &Scd->Aot_reset, sizeof(tagBio2Bytecode::tagAot_reset));
	break;
	case 0x47:
		Read(BINARY, _Offset, &Scd->Aot_on, sizeof(tagBio2Bytecode::tagAot_on));
	break;
	case 0x48:
		Read(BINARY, _Offset, &Scd->Super_set, sizeof(tagBio2Bytecode::tagSuper_set));
	break;
	case 0x49:
		Read(BINARY, _Offset, &Scd->Super_reset, sizeof(tagBio2Bytecode::tagSuper_reset));
	break;
	case 0x4A:
		Read(BINARY, _Offset, &Scd->Plc_gun, sizeof(tagBio2Bytecode::tagPlc_gun));
	break;
	case 0x4B:
		Read(BINARY, _Offset, &Scd->Cut_replace, sizeof(tagBio2Bytecode::tagCut_replace));
	break;
	case 0x4C:
		Read(BINARY, _Offset, &Scd->Sce_espr_kill, sizeof(tagBio2Bytecode::tagSce_espr_kill));
	break;
	case 0x4D:
		Read(BINARY, _Offset, &Scd->Door_model_set, sizeof(tagBio2Bytecode::tagDoor_model_set));
	break;
	case 0x4E:
		Read(BINARY, _Offset, &Scd->Item_aot_set, sizeof(tagBio2Bytecode::tagItem_aot_set));
	break;
	case 0x4F:
		Read(BINARY, _Offset, &Scd->Sce_key_ck, sizeof(tagBio2Bytecode::tagSce_key_ck));
	break;
	case 0x50:
		Read(BINARY, _Offset, &Scd->Sce_trg_ck, sizeof(tagBio2Bytecode::tagSce_trg_ck));
	break;
	case 0x51:
		Read(BINARY, _Offset, &Scd->Sce_bgm_control, sizeof(tagBio2Bytecode::tagSce_bgm_control));
	break;
	case 0x52:
		Read(BINARY, _Offset, &Scd->Sce_espr_control, sizeof(tagBio2Bytecode::tagSce_espr_control));
	break;
	case 0x53:
		Read(BINARY, _Offset, &Scd->Sce_fade_set, sizeof(tagBio2Bytecode::tagSce_fade_set));
	break;
	case 0x54:
		Read(BINARY, _Offset, &Scd->Sce_espr3d_on, sizeof(tagBio2Bytecode::tagSce_espr3d_on));
	break;
	case 0x55:
		Read(BINARY, _Offset, &Scd->Member_calc, sizeof(tagBio2Bytecode::tagMember_calc));
	break;
	case 0x56:
		Read(BINARY, _Offset, &Scd->Member_calc2, sizeof(tagBio2Bytecode::tagMember_calc2));
	break;
	case 0x57:
		Read(BINARY, _Offset, &Scd->Sce_bgmtbl_set, sizeof(tagBio2Bytecode::tagSce_bgmtbl_set));
	break;
	case 0x58:
		Read(BINARY, _Offset, &Scd->Plc_rot, sizeof(tagBio2Bytecode::tagPlc_rot));
	break;
	case 0x59:
		Read(BINARY, _Offset, &Scd->Xa_on, sizeof(tagBio2Bytecode::tagXa_on));
	break;
	case 0x5A:
		Read(BINARY, _Offset, &Scd->Weapon_chg, sizeof(tagBio2Bytecode::tagWeapon_chg));
	break;
	case 0x5B:
		Read(BINARY, _Offset, &Scd->Plc_cnt, sizeof(tagBio2Bytecode::tagPlc_cnt));
	break;
	case 0x5C:
		Read(BINARY, _Offset, &Scd->Sce_shake_on, sizeof(tagBio2Bytecode::tagSce_shake_on));
	break;
	case 0x5D:
		Read(BINARY, _Offset, &Scd->Mizu_div_set, sizeof(tagBio2Bytecode::tagMizu_div_set));
	break;
	case 0x5E:
		Read(BINARY, _Offset, &Scd->Keep_Item_ck, sizeof(tagBio2Bytecode::tagKeep_Item_ck));
	break;
	case 0x5F:
		Read(BINARY, _Offset, &Scd->Xa_vol, sizeof(tagBio2Bytecode::tagXa_vol));
	break;
	case 0x60:
		if(TrialEdition) {
			Read(BINARY, _Offset, &Trial->Kage_set, sizeof(tagBio2BytecodeT::tagKage_set));
		} else {
			Read(BINARY, _Offset, &Scd->Kage_set, sizeof(tagBio2Bytecode::tagKage_set));
		}
	break;
	case 0x61:
		Read(BINARY, _Offset, &Scd->Cut_be_set, sizeof(tagBio2Bytecode::tagCut_be_set));
	break;
	case 0x62:
		Read(BINARY, _Offset, &Scd->Sce_Item_lost, sizeof(tagBio2Bytecode::tagSce_Item_lost));
	break;
	case 0x63:
		Read(BINARY, _Offset, &Scd->Plc_gun_eff, sizeof(tagBio2Bytecode::tagPlc_gun_eff));
	break;
	case 0x64:
		Read(BINARY, _Offset, &Scd->Sce_espr_on2, sizeof(tagBio2Bytecode::tagSce_espr_on2));
	break;
	case 0x65:
		Read(BINARY, _Offset, &Scd->Sce_espr_kill2, sizeof(tagBio2Bytecode::tagSce_espr_kill2));
	break;
	case 0x66:
		Read(BINARY, _Offset, &Scd->Plc_stop, sizeof(tagBio2Bytecode::tagPlc_stop));
	break;
	case 0x67:
		Read(BINARY, _Offset, &Scd->Aot_set_4p, sizeof(tagBio2Bytecode::tagAot_set_4p));
	break;
	case 0x68:
		Read(BINARY, _Offset, &Scd->Door_aot_set_4p, sizeof(tagBio2Bytecode::tagDoor_aot_set_4p));
	break;
	case 0x69:
		Read(BINARY, _Offset, &Scd->Item_aot_set_4p, sizeof(tagBio2Bytecode::tagItem_aot_set_4p));
	break;
	case 0x6A:
		Read(BINARY, _Offset, &Scd->Light_pos_set, sizeof(tagBio2Bytecode::tagLight_pos_set));
	break;
	case 0x6B:
		Read(BINARY, _Offset, &Scd->Light_kido_set, sizeof(tagBio2Bytecode::tagLight_kido_set));
	break;
	case 0x6C:
		Read(BINARY, _Offset, &Scd->Rbj_reset, sizeof(tagBio2Bytecode::tagRbj_reset));
	break;
	case 0x6D:
		Read(BINARY, _Offset, &Scd->Sce_scr_move, sizeof(tagBio2Bytecode::tagSce_scr_move));
	break;
	case 0x6E:
		Read(BINARY, _Offset, &Scd->Parts_set, sizeof(tagBio2Bytecode::tagParts_set));
	break;
	case 0x6F:
		Read(BINARY, _Offset, &Scd->Movie_on, sizeof(tagBio2Bytecode::tagMovie_on));
	break;
	case 0x70:
		Read(BINARY, _Offset, &Scd->Splc_ret, sizeof(tagBio2Bytecode::tagSplc_ret));
	break;
	case 0x71:
		Read(BINARY, _Offset, &Scd->Splc_sce, sizeof(tagBio2Bytecode::tagSplc_sce));
	break;
	case 0x72:
		Read(BINARY, _Offset, &Scd->Super_on, sizeof(tagBio2Bytecode::tagSuper_on));
	break;
	case 0x73:
		Read(BINARY, _Offset, &Scd->Mirror_set, sizeof(tagBio2Bytecode::tagMirror_set));
	break;
	case 0x74:
		Read(BINARY, _Offset, &Scd->Sce_fade_adjust, sizeof(tagBio2Bytecode::tagSce_fade_adjust));
	break;
	case 0x75:
		Read(BINARY, _Offset, &Scd->Sce_espr3d_on2, sizeof(tagBio2Bytecode::tagSce_espr3d_on2));
	break;
	case 0x76:
		Read(BINARY, _Offset, &Scd->Sce_Item_get, sizeof(tagBio2Bytecode::tagSce_Item_get));
	break;
	case 0x77:
		Read(BINARY, _Offset, &Scd->Sce_line_start, sizeof(tagBio2Bytecode::tagSce_line_start));
	break;
	case 0x78:
		Read(BINARY, _Offset, &Scd->Sce_line_main, sizeof(tagBio2Bytecode::tagSce_line_main));
	break;
	case 0x79:
		Read(BINARY, _Offset, &Scd->Sce_line_end, sizeof(tagBio2Bytecode::tagSce_line_end));
	break;
	case 0x7A:
		Read(BINARY, _Offset, &Scd->Sce_parts_bomb, sizeof(tagBio2Bytecode::tagSce_parts_bomb));
	break;
	case 0x7B:
		Read(BINARY, _Offset, &Scd->Sce_parts_down, sizeof(tagBio2Bytecode::tagSce_parts_down));
	break;
	case 0x7C:
		Read(BINARY, _Offset, &Scd->Light_color_set, sizeof(tagBio2Bytecode::tagLight_color_set));
	break;
	case 0x7D:
		Read(BINARY, _Offset, &Scd->Light_pos_set2, sizeof(tagBio2Bytecode::tagLight_pos_set2));
	break;
	case 0x7E:
		Read(BINARY, _Offset, &Scd->Light_kido_set2, sizeof(tagBio2Bytecode::tagLight_kido_set2));
	break;
	case 0x7F:
		Read(BINARY, _Offset, &Scd->Light_color_set2, sizeof(tagBio2Bytecode::tagLight_color_set2));
	break;
	case 0x80:
		Read(BINARY, _Offset, &Scd->Se_vol, sizeof(tagBio2Bytecode::tagSe_vol));
	break;
	case 0x81:
		Read(BINARY, _Offset, &Scd->Sce_Item_cmp, sizeof(tagBio2Bytecode::tagSce_Item_cmp));
	break;
	case 0x82:
		Read(BINARY, _Offset, &Scd->Sce_espr_task, sizeof(tagBio2Bytecode::tagSce_espr_task));
	break;
	case 0x83:
		Read(BINARY, _Offset, &Scd->Plc_heal, sizeof(tagBio2Bytecode::tagPlc_heal));
	break;
	case 0x84:
		Read(BINARY, _Offset, &Scd->St_map_hint, sizeof(tagBio2Bytecode::tagSt_map_hint));
	break;
	case 0x85:
		Read(BINARY, _Offset, &Scd->Sce_em_pos_ck, sizeof(tagBio2Bytecode::tagSce_em_pos_ck));
	break;
	case 0x86:
		Read(BINARY, _Offset, &Scd->Poison_ck, sizeof(tagBio2Bytecode::tagPoison_ck));
	break;
	case 0x87:
		Read(BINARY, _Offset, &Scd->Poison_clr, sizeof(tagBio2Bytecode::tagPoison_clr));
	break;
	case 0x88:
		Read(BINARY, _Offset, &Scd->Sce_Item_lost2, sizeof(tagBio2Bytecode::tagSce_Item_lost2));
	break;
	case 0x89:
		Read(BINARY, _Offset, &Scd->Evt_next2, sizeof(tagBio2Bytecode::tagEvt_next2));
	break;
	case 0x8A:
		Read(BINARY, _Offset, &Scd->Vib_set0, sizeof(tagBio2Bytecode::tagVib_set0));
	break;
	case 0x8B:
		Read(BINARY, _Offset, &Scd->Vib_set1, sizeof(tagBio2Bytecode::tagVib_set1));
	break;
	case 0x8C:
		Read(BINARY, _Offset, &Scd->Vib_fade_set, sizeof(tagBio2Bytecode::tagVib_fade_set));
	break;
	case 0x8D:
		Read(BINARY, _Offset, &Scd->Item_aot_set2, sizeof(tagBio2Bytecode::tagItem_aot_set2));
	break;
	case 0x8E:
		Read(BINARY, _Offset, &Scd->Sce_em_set2, sizeof(tagBio2Bytecode::tagSce_em_set2));
	break;
	}

	// Terminate
	return Scd->Opcode;
}
UCHAR Bio_Hazard_2_Script::ScdPeek(_iobuf * BINARY, ULONG _Offset) {
	if (!IsOpen(BINARY)) { return NULL; }
	UCHAR Opcode = NULL;
	Read(BINARY, _Offset, &Opcode, 1);
	return Opcode;
}
// Ifel_ck
ULONG Bio_Hazard_2_Script::ClausePrint(_iobuf * BINARY, _iobuf * SOURCE, ULONG _Offset, UCHAR OpClause) {

	// Error
	if (!IsOpen(BINARY)) { return _Offset; }
	if (!IsOpen(SOURCE)) { return _Offset; }

	// Variable
	ULONG Pointer = (_Offset + Bio_Hazard_2_Script_Bytecode_Size[OpClause]);
	ULONG _Filesize = Size(BINARY);
	UCHAR Opcode = NULL;
	UCHAR OpNext = NULL;

	// Parse
	for (ULONG n = 0; n < _Filesize; n++)
	{
		// Complete
		if (feof(BINARY)) { break; }
		if (Pointer >= _Filesize) { break; }

		// Read
		Read(BINARY, Pointer, &Opcode, 1);
		if (Opcode != 0x1D &&
			Opcode != 0x21 &&
			Opcode != 0x23 &&
			Opcode != 0x3E &&
			Opcode != 0x4F &&
			Opcode != 0x50 &&
			Opcode != 0x5E &&
			Opcode != 0x81 &&
			Opcode != 0x86) {
			break;
		} else {
			ScdRead(BINARY, Pointer);
		}

		// Print
		switch (Opcode)
		{
		case 0x1D:	// Work_copy
			Print(SOURCE, "Work_copy(0x%02hhX, 0x%02hhX, 0x%02hhX)",
				Scd->Work_copy.Source, Scd->Work_copy.Destination, Scd->Work_copy.Typecast);
		break;
		case 0x21:	// Ck
			Print(SOURCE, "Ck(%s, 0x%02hhX, %s)",
				GetCkFlag(Scd->Ck.Flag), Scd->Ck.Id, GetOnOff(Scd->Ck.OnOff));
		break;
		case 0x23:	// Cmp
			Print(SOURCE, "Cmp(%s %s %d)",
				GetMemberFlag(Scd->Cmp.Flag), GetCmpOperator(Scd->Cmp.Operator), Scd->Cmp.Value);
		break;
		case 0x3E:	// Member_cmp
			Print(SOURCE, "Member_cmp(%s %s %d)",
				GetMemberFlag(Scd->Member_cmp.Flag), GetCmpOperator(Scd->Member_cmp.Operator), Scd->Member_cmp.Value);
		break;
		case 0x4F:	// Sce_key_ck
			Print(SOURCE, "Sce_key_ck(0x%02hhX, 0x%04hX)", Scd->Sce_key_ck.Flag, Scd->Sce_key_ck.Value);
		break;
		case 0x50:	// Sce_trg_ck
			Print(SOURCE, "Sce_trg_ck(0x%02hhX, 0x%04hX)", Scd->Sce_trg_ck.Flag, Scd->Sce_trg_ck.Value);
		break;
		case 0x5E:	// Keep_Item_ck
			Print(SOURCE, "Keep_Item_ck(0x%02hhX)", Scd->Keep_Item_ck.Id);
		break;
		case 0x81:	// Sce_Item_cmp
			Print(SOURCE, "Sce_Item_cmp(0x%02hhX, 0x%02hhX)", Scd->Sce_Item_cmp.data0, Scd->Sce_Item_cmp.data1);
		break;
		case 0x86:	// Poison_ck
			Print(SOURCE, "Poison_ck()");
		break;
		default:
			Message((CHAR *)"Unable to find suitable match for if clause!\r\nThe opcode given was: 0x%02hhX", Opcode);
		break;
		}

		// Complete
		OpNext = ScdPeek(BINARY, (Pointer + Bio_Hazard_2_Script_Bytecode_Size[Opcode]));
		if (OpNext != 0x1D &&
			OpNext != 0x21 &&
			OpNext != 0x23 &&
			OpNext != 0x3E &&
			OpNext != 0x4F &&
			OpNext != 0x50 &&
			OpNext != 0x5E &&
			OpNext != 0x81 &&
			OpNext != 0x86) {
			break;
		} else {
			Pointer += Bio_Hazard_2_Script_Bytecode_Size[Opcode];
			Print(SOURCE, " && ");
		}
	}

	// Terminate
	return Pointer;
}
// Goto
VOID Bio_Hazard_2_Script::FindJumpLabels(_iobuf * BINARY, ULONG _Offset) {

	// Error
	if (!IsOpen(BINARY)) { return; }

	// Variable
	ULONG Pointer = _Offset;
	ULONG _Filesize = Size(BINARY);
	UCHAR Opcode = NULL;

	// Locate and index all jump labels for future use
	for (ULONG n = 0; n < _Filesize; n++)
	{
		// Complete
		if (feof(BINARY)) { break; }
		if (Pointer >= _Filesize) { break; }

		// Read
		Read(BINARY, Pointer, &Opcode, 1);
		switch (Opcode)
		{
		case 0x17:
			Read(BINARY, Pointer, &Jump[nJumpLabels].Goto, sizeof(tagBio2JumpLabel::tagGoto));
			Jump[nJumpLabels].pGoto = Pointer;
			Jump[nJumpLabels].pJump = (Pointer + Jump[nJumpLabels].Goto.Offset);
			nJumpLabels++;
		break;
		}

		// 
		if (TrialEdition) {
			switch (Opcode)
			{
			case 0x45:
				Pointer += sizeof(tagBio2BytecodeT::Col_chg_set);
			break;
			case 0x60:
				Pointer += sizeof(tagBio2BytecodeT::Kage_set);
			break;
			default:
				Pointer += Bio_Hazard_2_Script_Bytecode_Size[Opcode];
			break;
			}
		} else {
			Pointer += Bio_Hazard_2_Script_Bytecode_Size[Opcode];
		}
	}

}
VOID Bio_Hazard_2_Script::JumpLabelCk(_iobuf * SOURCE, ULONG _Offset) {

	// check offset to see if a jump label is required

	for (ULONG n = 0; n < nJumpLabels; n++)
	{
		if (Jump[n].pJump != _Offset) {
		} else {
			if (DebugMode) { Print(SOURCE, "/* 0x%08X */ ", _Offset); }
			Print(SOURCE, "JUMP%02hd:\r\n", n);
		}
	}

}
CHAR * Bio_Hazard_2_Script::GetJumpLabel(ULONG _Offset) {

	// return string for goto statement

	for (ULONG n = 0; n < nJumpLabels; n++)
	{
		if (Jump[n].pJump != _Offset) {
		} else {
			return Get("JUMP%02hd", n);
		}
	}

	return (CHAR *)"\0\0\0\0";
}
// Print
CHAR * Bio_Hazard_2_Script::GetOnOff(USHORT Flag) {

	switch(Flag)
	{
	case 0x00:
		return (CHAR *)"OFF\0\0";
	break;
	case 0x01:
		return (CHAR *)"ON\0\0";
	break;

	default:
		return (CHAR *)"NULL\0\0";
	break;
	}

}
CHAR * Bio_Hazard_2_Script::GetAotSet(USHORT SAT) {

	switch(SAT)
	{
	case 0x00:
		return (CHAR *)"AUTO\0\0";
	break;
	case 0x01:
		return (CHAR *)"DOOR\0\0";
	break;
	case 0x02:
		return (CHAR *)"ITEM\0\0";
	break;
	case 0x03:
		return (CHAR *)"NORMAL\0\0";
	break;
	case 0x04:
		return (CHAR *)"MESSAGE\0\0";
	break;
	case 0x05:
		return (CHAR *)"EVENT\0\0";
	break;
	case 0x06:
		return (CHAR *)"FLAG_CHG\0\0";
	break;
	case 0x07:
		return (CHAR *)"WATER\0\0";
	break;
	case 0x08:
		return (CHAR *)"MOVE\0\0";
	break;
	case 0x09:
		return (CHAR *)"SAVE\0\0";
	break;
	case 0x0A:
		return (CHAR *)"ITEMBOX\0\0";
	break;
	case 0x0B:
		return (CHAR *)"DAMAGE\0\0";
	break;
	case 0x0C:
		return (CHAR *)"STATUS\0\0";
	break;
	case 0x0D:
		return (CHAR *)"HIKIDASHI\0\0";
	break;
	case 0x0E:
		return (CHAR *)"WINDOWS\0\0";
	break;

	default:
		return (CHAR *)"NULL\0\0";
	break;
	}

}
CHAR * Bio_Hazard_2_Script::GetAotSat(USHORT SAT) {

	// Disabled
	if (!SAT) { return (CHAR *)"AUTO\0\0"; }

	// String
	CHAR * pszDest = new CHAR[_MAX_FNAME];
	RtlSecureZeroMemory(pszDest, _MAX_FNAME);

	// Byte 0
	UCHAR Byte0 = GetByte(0, SAT);
	if (Byte0) {
		UCHAR * Bits = GetBits(Byte0);
		if (Bits[0]) { StringCchCatA(pszDest, _MAX_FNAME, "PL+\0\0"); }
		if (Bits[1]) { StringCchCatA(pszDest, _MAX_FNAME, "EM+\0\0"); }
		if (Bits[2]) { StringCchCatA(pszDest, _MAX_FNAME, "SPL+\0\0"); }
		if (Bits[3]) { StringCchCatA(pszDest, _MAX_FNAME, "OB+\0\0"); }
		if (Bits[4]) { StringCchCatA(pszDest, _MAX_FNAME, "MANUAL+\0\0"); }
		if (Bits[5]) { StringCchCatA(pszDest, _MAX_FNAME, "FRONT+\0\0"); }
		if (Bits[6]) { StringCchCatA(pszDest, _MAX_FNAME, "UNDER+\0\0"); }
		if (Bits[7]) { StringCchCatA(pszDest, _MAX_FNAME, "0x80+\0\0"); }	// 4p
		delete[] Bits;
	}

	// Cleanup
	if (pszDest[strlen(pszDest) - 1] != 0x2B) {}
	else { pszDest[strlen(pszDest) - 1] = 0x00; }

	// Terminate
	return pszDest;
}
CHAR * Bio_Hazard_2_Script::GetBgmCtlId(USHORT Id) {

	switch(Id)
	{
	case 0x00:
		return (CHAR *)"MAIN\0\0";
	break;
	case 0x01:
		return (CHAR *)"SUB0\0\0";
	break;
	case 0x02:
		return (CHAR *)"SUB1\0\0";
	break;

	default:
		return (CHAR *)"NULL\0\0";
	break;
	}

}
CHAR * Bio_Hazard_2_Script::GetBgmCtlOp(USHORT Op) {

	switch(Op)
	{
	case 0x00:
		return (CHAR *)"NOP\0\0";
	break;
	case 0x01:
		return (CHAR *)"START\0\0";
	break;
	case 0x02:
		return (CHAR *)"STOP\0\0";
	break;
	case 0x03:
		return (CHAR *)"RESTART\0\0";
	break;
	case 0x04:
		return (CHAR *)"PAUSE\0\0";
	break;
	case 0x05:
		return (CHAR *)"FADEOUT\0\0";
	break;

	default:
		return (CHAR *)"NULL\0\0";
	break;
	}

}
CHAR * Bio_Hazard_2_Script::GetBgmCtlType(USHORT Type) {

	switch(Type)
	{
	case 0x00:
		return (CHAR *)"MAIN_VOL\0\0";
	break;
	case 0x01:
		return (CHAR *)"PROG0_VOL\0\0";
	break;
	case 0x02:
		return (CHAR *)"PROG1_VOL\0\0";
	break;
	case 0x03:
		return (CHAR *)"PROG2_VOL\0\0";
	break;

	default:
		return (CHAR *)"NULL\0\0";
	break;
	}

}
CHAR * Bio_Hazard_2_Script::GetCalcOperator(USHORT Operator) {

	switch(Operator)
	{
	case 0x00:
		return (CHAR *)"+\0\0";
	break;
	case 0x01:
		return (CHAR *)"-\0\0";
	break;
	case 0x02:
		return (CHAR *)"*\0\0";
	break;
	case 0x03:
		return (CHAR *)"/\0\0";
	break;
	case 0x04:
		return (CHAR *)"%\0\0";
	break;
	case 0x05:
		return (CHAR *)"|\0\0";
	break;
	case 0x06:
		return (CHAR *)"&\0\0";
	break;
	case 0x07:
		return (CHAR *)"^\0\0";
	break;
	case 0x08:
		return (CHAR *)"~\0\0";
	break;
	case 0x09:
		return (CHAR *)"<<\0\0";
	break;
	case 0x0A:
		return (CHAR *)">>\0\0";
	break;
	case 0x0B:
		return (CHAR *)">>=\0\0";
	break;

	default:
		return (CHAR *)"NULL\0\0";
	break;
	}

}
CHAR * Bio_Hazard_2_Script::GetCkFlag(USHORT Flag) {

	switch(Flag)
	{
	case 0x00:
		return (CHAR *)"SYSTEM\0\0";
	break;
	case 0x01:
		return (CHAR *)"STATUS\0\0";
	break;
	case 0x02:
		return (CHAR *)"STOP\0\0";
	break;
	case 0x03:
		return (CHAR *)"SCENARIO\0\0";
	break;
	case 0x04:
		return (CHAR *)"COMMON\0\0";
	break;
	case 0x05:
		return (CHAR *)"ROOM\0\0";
	break;
	case 0x06:
		return (CHAR *)"ENEMY\0\0";
	break;
	case 0x07:
		return (CHAR *)"ENEMY_2\0\0";
	break;
	case 0x08:
		return (CHAR *)"ITEM\0\0";
	break;
	case 0x09:
		return (CHAR *)"MAP\0\0";
	break;
	case 0x0A:
		return (CHAR *)"USE\0\0";
	break;
	case 0x0B:
		return (CHAR *)"MESSAGE\0\0";
	break;
	case 0x0C:
		return (CHAR *)"ROOM_ENEMY\0\0";
	break;
	case 0x0D:
		return (CHAR *)"PBF00\0\0";
	break;
	case 0x0E:
		return (CHAR *)"PBF01\0\0";
	break;
	case 0x0F:
		return (CHAR *)"PBF02\0\0";
	break;
	case 0x10:
		return (CHAR *)"PBF03\0\0";
	break;
	case 0x11:
		return (CHAR *)"PBF04\0\0";
	break;
	case 0x12:
		return (CHAR *)"PBF05\0\0";
	break;
	case 0x13:
		return (CHAR *)"PBF06\0\0";
	break;
	case 0x14:
		return (CHAR *)"PBF07\0\0";
	break;
	case 0x15:
		return (CHAR *)"PBF08\0\0";
	break;
	case 0x16:
		return (CHAR *)"PBF09\0\0";
	break;
	case 0x17:
		return (CHAR *)"PBF0A\0\0";
	break;
	case 0x18:
		return (CHAR *)"PBF0B\0\0";
	break;
	case 0x19:
		return (CHAR *)"PBF0C\0\0";
	break;
	case 0x1A:
		return (CHAR *)"PBF0D\0\0";
	break;
	case 0x1B:
		return (CHAR *)"PBF0E\0\0";
	break;
	case 0x1C:
		return (CHAR *)"PBF0F\0\0";
	break;
	case 0x1D:
		return (CHAR *)"ZAPPING\0\0";
	break;
	case 0x1E:
		return (CHAR *)"RBJ_SET\0\0";
	break;
	case 0x1F:
		return (CHAR *)"KEY\0\0";
	break;
	case 0x20:
		return (CHAR *)"MAP_C\0\0";
	break;
	case 0x21:
		return (CHAR *)"MAP_I\0\0";
	break;
	case 0x22:
		return (CHAR *)"ITEM_2\0\0";
	break;

	default:
		return (CHAR *)"NULL\0\0";
	break;
	}

}
CHAR * Bio_Hazard_2_Script::GetCmpOperator(USHORT Operator) {

	switch(Operator)
	{
	case 0x00:
		return (CHAR *)"=\0\0";
	break;
	case 0x01:
		return (CHAR *)">\0\0";
	break;
	case 0x02:
		return (CHAR *)">=\0\0";
	break;
	case 0x03:
		return (CHAR *)"<\0\0";
	break;
	case 0x04:
		return (CHAR *)"<=\0\0";
	break;
	case 0x05:
		return (CHAR *)"!=\0\0";
	break;
	case 0x06:
		return (CHAR *)"&\0\0";
	break;

	default:
		return (CHAR *)"NULL\0\0";
	break;
	}

}
CHAR * Bio_Hazard_2_Script::GetEmdName(USHORT Id) {
	return Get("EMD%02X\0\0", Id);
}
CHAR * Bio_Hazard_2_Script::GetItemName(USHORT iItem) {

	UCHAR Byte0 = GetByte(0, iItem);
	switch(Byte0)
	{
	case 0x00:
		return (CHAR *)"NOTHING\0\0";
	break;
	case 0x01:
		return (CHAR *)"KNIFE\0\0";
	break;
	case 0x02:
		return (CHAR *)"H&K_VP70\0\0";
	break;
	case 0x03:
		return (CHAR *)"BROWNING_HP\0\0";
	break;
	case 0x04:
		return (CHAR *)"C_HAND_GUN\0\0";
	break;
	case 0x05:
		return (CHAR *)"MAGNUM\0\0";
	break;
	case 0x06:
		return (CHAR *)"CUSTOM_MAGNUM\0\0";
	break;
	case 0x07:
		return (CHAR *)"SHOTGUN\0\0";
	break;
	case 0x08:
		return (CHAR *)"CUSTOM_SHOTGUN\0\0";
	break;
	case 0x09:
		return (CHAR *)"G_LAUNCHER_EXPLOSIVE\0\0";
	break;
	case 0x0A:
		return (CHAR *)"G_LAUNCHER_FLAME\0\0";
	break;
	case 0x0B:
		return (CHAR *)"G_LAUNCHER_ACID\0\0";
	break;
	case 0x0C:
		return (CHAR *)"BOW_GUN\0\0";
	break;
	case 0x0D:
		return (CHAR *)"COLT_SAA\0\0";
	break;
	case 0x0E:
		return (CHAR *)"SPARK_SHOT\0\0";
	break;
	case 0x0F:
		return (CHAR *)"S_MACHINE_GUN\0\0";
	break;
	case 0x10:
		return (CHAR *)"FLAMETHROWER\0\0";
	break;
	case 0x11:
		return (CHAR *)"R_LAUNCHER\0\0";
	break;
	case 0x12:
		return (CHAR *)"GATLING_GUN\0\0";
	break;
	case 0x13:
		return (CHAR *)"BARETTA_M92FS\0\0";
	break;
	case 0x14:
		return (CHAR *)"H_GUN_BULLETS\0\0";
	break;
	case 0x15:
		return (CHAR *)"SHOT_GUN_SHELLS\0\0";
	break;
	case 0x16:
		return (CHAR *)"M_BULLETS\0\0";
	break;
	case 0x17:
		return (CHAR *)"FUEL\0\0";
	break;
	case 0x18:
		return (CHAR *)"G_ROUNDS\0\0";
	break;
	case 0x19:
		return (CHAR *)"FLAME_ROUNDS\0\0";
	break;
	case 0x1A:
		return (CHAR *)"ACID_ROUNDS\0\0";
	break;
	case 0x1B:
		return (CHAR *)"MG_BULLETS\0\0";
	break;
	case 0x1C:
		return (CHAR *)"S_SHOT_BULLETS\0\0";
	break;
	case 0x1D:
		return (CHAR *)"BOWGUN_BOLTS\0\0";
	break;
	case 0x1E:
		return (CHAR *)"INK_RIBBON\0\0";
	break;
	case 0x1F:
		return (CHAR *)"SMALL_KEY\0\0";
	break;
	case 0x20:
		return (CHAR *)"C_HANDGUN_PARTS\0\0";
	break;
	case 0x21:
		return (CHAR *)"C_MAGNUM_PARTS\0\0";
	break;
	case 0x22:
		return (CHAR *)"C_SHOTGUN_PARTS\0\0";
	break;
	case 0x23:
		return (CHAR *)"F_AID_SPRAY\0\0";
	break;
	case 0x24:
		return (CHAR *)"CHEMICAL_FR_W09\0\0";
	break;
	case 0x25:
		return (CHAR *)"CHEMICAL_AC_W24\0\0";
	break;
	case 0x26:
		return (CHAR *)"GREEN_HERB\0\0";
	break;
	case 0x27:
		return (CHAR *)"RED_HERB\0\0";
	break;
	case 0x28:
		return (CHAR *)"BLUE_HERB\0\0";
	break;
	case 0x29:
		return (CHAR *)"MIXED_HERB_GG\0\0";
	break;
	case 0x2A:
		return (CHAR *)"MIXED_HERB_GR\0\0";
	break;
	case 0x2B:
		return (CHAR *)"MIXED_HERB_GB\0\0";
	break;
	case 0x2C:
		return (CHAR *)"MIXED_HERB_GGG\0\0";
	break;
	case 0x2D:
		return (CHAR *)"MIXED_HERB_GGB\0\0";
	break;
	case 0x2E:
		return (CHAR *)"MIXED_HERB_GRB\0\0";
	break;
	case 0x2F:
		return (CHAR *)"LIGHTER\0\0";
	break;
	case 0x30:
		return (CHAR *)"LOCKPICK\0\0";
	break;
	case 0x31:
		return (CHAR *)"PICTURE_FAMILY\0\0";
	break;
	case 0x32:
		return (CHAR *)"VALVE_HANDLE\0\0";
	break;
	case 0x33:
		return (CHAR *)"RED_JEWEL\0\0";
	break;
	case 0x34:
		return (CHAR *)"RED_CARD_KEY\0\0";
	break;
	case 0x35:
		return (CHAR *)"BLUE_CARD_KEY\0\0";
	break;
	case 0x36:
		return (CHAR *)"SERPENT_STONE\0\0";
	break;
	case 0x37:
		return (CHAR *)"JAGUAR_STONE\0\0";
	break;
	case 0x38:
		return (CHAR *)"BLUE_STONE_1\0\0";
	break;
	case 0x39:
		return (CHAR *)"BLUE_STONE_2\0\0";
	break;
	case 0x3A:
		return (CHAR *)"EAGLE_STONE\0\0";
	break;
	case 0x3B:
		return (CHAR *)"BISHOP_PLUG\0\0";
	break;
	case 0x3C:
		return (CHAR *)"ROOK_PLUG\0\0";
	break;
	case 0x3D:
		return (CHAR *)"KNIGHT_PLUG\0\0";
	break;
	case 0x3E:
		return (CHAR *)"KING_PLUG\0\0";
	break;
	case 0x3F:
		return (CHAR *)"W_BOX_KEY\0\0";
	break;
	case 0x40:
		return (CHAR *)"DETONATOR\0\0";
	break;
	case 0x41:
		return (CHAR *)"PLASTIC_BOMB\0\0";
	break;
	case 0x42:
		return (CHAR *)"BOMB_AND_DET\0\0";
	break;
	case 0x43:
		return (CHAR *)"CRANK\0\0";
	break;
	case 0x44:
		return (CHAR *)"FILM_1\0\0";
	break;
	case 0x45:
		return (CHAR *)"FILM_2\0\0";
	break;
	case 0x46:
		return (CHAR *)"FILM_3\0\0";
	break;
	case 0x47:
		return (CHAR *)"UNICORN_MEDAL\0\0";
	break;
	case 0x48:
		return (CHAR *)"EAGLE_MEDAL\0\0";
	break;
	case 0x49:
		return (CHAR *)"WOLF_MEDAL\0\0";
	break;
	case 0x4A:
		return (CHAR *)"G_COGWHEEL\0\0";
	break;
	case 0x4B:
		return (CHAR *)"MANHOLE_OPENER\0\0";
	break;
	case 0x4C:
		return (CHAR *)"MAIN_FUSE\0\0";
	break;
	case 0x4D:
		return (CHAR *)"FUSE_CASE\0\0";
	break;
	case 0x4E:
		return (CHAR *)"VACCINE\0\0";
	break;
	case 0x4F:
		return (CHAR *)"VACCINECART\0\0";
	break;
	case 0x50:
		return (CHAR *)"FILM_4\0\0";
	break;
	case 0x51:
		return (CHAR *)"BASE_VACCINE\0\0";
	break;
	case 0x52:
		return (CHAR *)"G_VIRUS\0\0";
	break;
	case 0x53:
		return (CHAR *)"SPECIAL_KEY\0\0";
	break;
	case 0x54:
		return (CHAR *)"JOINT_S_PLUG\0\0";
	break;
	case 0x55:
		return (CHAR *)"JOINT_N_PLUG\0\0";
	break;
	case 0x56:
		return (CHAR *)"CORD\0\0";
	break;
	case 0x57:
		return (CHAR *)"PICTURE_ADA\0\0";
	break;
	case 0x58:
		return (CHAR *)"CABIN_KEY\0\0";
	break;
	case 0x59:
		return (CHAR *)"KEY_SPADE\0\0";
	break;
	case 0x5A:
		return (CHAR *)"KEY_DIAMOND\0\0";
	break;
	case 0x5B:
		return (CHAR *)"KEY_HEART\0\0";
	break;
	case 0x5C:
		return (CHAR *)"KEY_CLUB\0\0";
	break;
	case 0x5D:
		return (CHAR *)"C_PANEL_KEY_DOWN\0\0";
	break;
	case 0x5E:
		return (CHAR *)"C_PANEL_KEY_UP\0\0";
	break;
	case 0x5F:
		return (CHAR *)"P_ROOM_KEY\0\0";
	break;
	case 0x60:
		return (CHAR *)"MO_DISK\0\0";
	break;
	case 0x61:
		return (CHAR *)"LAB_CARD_KEY\0\0";
	break;
	case 0x62:
		return (CHAR *)"MASTER_KEY\0\0";
	break;
	case 0x63:
		return (CHAR *)"PLATFORM_KEY\0\0";
	break;


	default:
		return (CHAR *)"NOTHING\0\0";
	break;
	}

}
CHAR * Bio_Hazard_2_Script::GetMemberFlag(USHORT Flag) {

	switch(Flag)
	{
	case 0x00:
		return (CHAR *)"POINTER\0\0";
	break;
	case 0x01:
		return (CHAR *)"BE_FLAG\0\0";
	break;
	case 0x02:
		return (CHAR *)"ROUTINE0\0\0";
	break;
	case 0x03:
		return (CHAR *)"ROUTINE1\0\0";
	break;
	case 0x04:
		return (CHAR *)"ROUTINE2\0\0";
	break;
	case 0x05:
		return (CHAR *)"ROUTINE3\0\0";
	break;
	case 0x06:
		return (CHAR *)"ID\0\0";
	break;
	case 0x07:
		return (CHAR *)"TYPE\0\0";
	break;
	case 0x08:
		return (CHAR *)"OBJ_NO\0\0";
	break;
	case 0x09:
		return (CHAR *)"SCE_NO\0\0";
	break;
	case 0x0A:
		return (CHAR *)"ATTRIBUTE\0\0";
	break;
	case 0x0B:
		return (CHAR *)"X_POS\0\0";
	break;
	case 0x0C:
		return (CHAR *)"Y_POS\0\0";
	break;
	case 0x0D:
		return (CHAR *)"Z_POS\0\0";
	break;
	case 0x0E:
		return (CHAR *)"X_DIR\0\0";
	break;
	case 0x0F:
		return (CHAR *)"Y_DIR\0\0";
	break;
	case 0x10:
		return (CHAR *)"Z_DIR\0\0";
	break;
	case 0x11:
		return (CHAR *)"nFLOOR\0\0";
	break;
	case 0x12:
		return (CHAR *)"STATUS_FLAG\0\0";
	break;
	case 0x13:
		return (CHAR *)"GROUND\0\0";
	break;
	case 0x14:
		return (CHAR *)"X_DEST\0\0";
	break;
	case 0x15:
		return (CHAR *)"Z_DEST\0\0";
	break;
	case 0x16:
		return (CHAR *)"SCE_FLAG\0\0";
	break;
	case 0x17:
		return (CHAR *)"SCE_FREE0\0\0";
	break;
	case 0x18:
		return (CHAR *)"SCE_FREE1\0\0";
	break;
	case 0x19:
		return (CHAR *)"SCE_FREE2\0\0";
	break;
	case 0x1A:
		return (CHAR *)"SCE_FREE3\0\0";
	break;
	case 0x1B:
		return (CHAR *)"X_SPEED0\0\0";
	break;
	case 0x1C:
		return (CHAR *)"X_SPEED1\0\0";
	break;
	case 0x1D:
		return (CHAR *)"Y_SPEED\0\0";
	break;
	case 0x1E:
		return (CHAR *)"Z_SPEED\0\0";
	break;
	case 0x1F:
		return (CHAR *)"HOKAN_FLAG\0\0";
	break;
	case 0x20:
		return (CHAR *)"OBJ_OFS_X\0\0";
	break;
	case 0x21:
		return (CHAR *)"OBJ_OFS_Y\0\0";
	break;
	case 0x22:
		return (CHAR *)"OBJ_OFS_Z\0\0";
	break;
	case 0x23:
		return (CHAR *)"OBJ_W\0\0";
	break;
	case 0x24:
		return (CHAR *)"OBJ_H\0\0";
	break;
	case 0x25:
		return (CHAR *)"OBJ_D\0\0";
	break;
	case 0x26:
		return (CHAR *)"PARTS_POS_Y\0\0";
	break;
	case 0x27:
		return (CHAR *)"SCA_OLD_X\0\0";
	break;
	case 0x28:
		return (CHAR *)"SCA_OLD_Z\0\0";
	break;
	case 0x29:
		return (CHAR *)"FREE0\0\0";
	break;
	case 0x2A:
		return (CHAR *)"FREE1\0\0";
	break;
	case 0x2B:
		return (CHAR *)"DAMAGE_CNT\0\0";
	break;

	default:
		return (CHAR *)"NULL\0\0";
	break;
	}

}
CHAR * Bio_Hazard_2_Script::GetObjSetId(USHORT Id) {

	// Disabled
	if (!Id) { return (CHAR *)"NORMAL\0\0"; }

	// String
	CHAR * pszDest = new CHAR[_MAX_FNAME];
	RtlSecureZeroMemory(pszDest, _MAX_FNAME);

	// Byte 0
	UCHAR Byte0 = GetByte(0, Id);
	if (Byte0) {
		UCHAR * Bits = GetBits(Byte0);
		if (Bits[0]) { StringCchCatA(pszDest, _MAX_FNAME, "WATER+\0\0"); }
		if (Bits[1]) { StringCchCatA(pszDest, _MAX_FNAME, "HIT+\0\0"); }
		if (Bits[2]) { StringCchCatA(pszDest, _MAX_FNAME, "BOX+\0\0"); }
		if (Bits[3]) { StringCchCatA(pszDest, _MAX_FNAME, "0x08+\0\0"); }
		if (Bits[4]) { StringCchCatA(pszDest, _MAX_FNAME, "0x10+\0\0"); }
		if (Bits[5]) { StringCchCatA(pszDest, _MAX_FNAME, "0x20+\0\0"); }
		if (Bits[6]) { StringCchCatA(pszDest, _MAX_FNAME, "0x40+\0\0"); }
		if (Bits[7]) { StringCchCatA(pszDest, _MAX_FNAME, "0x80+\0\0"); }
		delete[] Bits;
	}

	// Cleanup
	if (pszDest[strlen(pszDest) - 1] != 0x2B) {}
	else { pszDest[strlen(pszDest) - 1] = 0x00; }

	// Terminate
	return pszDest;

}
CHAR * Bio_Hazard_2_Script::GetObjSetBeFlg(USHORT BeFlg) {

	// Disabled
	if (!BeFlg) { return (CHAR *)"DISABLED\0\0"; }

	// String
	CHAR * pszDest = new CHAR[_MAX_FNAME];
	RtlSecureZeroMemory(pszDest, _MAX_FNAME);

	// Byte 0
	UCHAR Byte0 = GetByte(0, BeFlg);
	if (Byte0) {
		UCHAR * Bits = GetBits(Byte0);
		if (Bits[0]) { StringCchCatA(pszDest, _MAX_FNAME, "ENABLED+\0\0"); }
		if (Bits[1]) { StringCchCatA(pszDest, _MAX_FNAME, "NO_SCA+\0\0"); }
		if (Bits[2]) { StringCchCatA(pszDest, _MAX_FNAME, "0x0004+\0\0"); }
		if (Bits[3]) { StringCchCatA(pszDest, _MAX_FNAME, "0x0008+\0\0"); }
		if (Bits[4]) { StringCchCatA(pszDest, _MAX_FNAME, "0x0010+\0\0"); }
		if (Bits[5]) { StringCchCatA(pszDest, _MAX_FNAME, "0x0020+\0\0"); }
		if (Bits[6]) { StringCchCatA(pszDest, _MAX_FNAME, "ENEM_SE_INS_MASK+\0\0"); }
		if (Bits[7]) { StringCchCatA(pszDest, _MAX_FNAME, "PL_PUSH_OB+\0\0"); }
		delete[] Bits;
	}

	// Byte 1
	UCHAR Byte1 = GetByte(1, BeFlg);
	if (Byte1) {
		UCHAR * Bits = GetBits(Byte1);
		if (Bits[0]) { StringCchCatA(pszDest, _MAX_FNAME, "MV+\0\0"); }
		if (Bits[1]) { StringCchCatA(pszDest, _MAX_FNAME, "MO+\0\0"); }
		if (Bits[2]) { StringCchCatA(pszDest, _MAX_FNAME, "0x0400+\0\0"); }
		if (Bits[3]) { StringCchCatA(pszDest, _MAX_FNAME, "0x0800+\0\0"); }
		if (Bits[4]) { StringCchCatA(pszDest, _MAX_FNAME, "0x1000+\0\0"); }
		if (Bits[5]) { StringCchCatA(pszDest, _MAX_FNAME, "SC_AT+\0\0"); }
		if (Bits[6]) { StringCchCatA(pszDest, _MAX_FNAME, "OB_AT+\0\0"); }
		if (Bits[7]) { StringCchCatA(pszDest, _MAX_FNAME, "NO_HOSEI+\0\0"); }
		delete[] Bits;
	}

	// Cleanup
	if (pszDest[strlen(pszDest)-1] != 0x2B) {}
	else { pszDest[strlen(pszDest)-1] = 0x00; }

	// Terminate
	return pszDest;
}
CHAR * Bio_Hazard_2_Script::GetObjSetAttr(USHORT Attribute) {

	// Disabled
	if (!Attribute) { return (CHAR *)"LIGHT_ON\0\0"; }

	// String
	CHAR * pszDest = new CHAR[_MAX_FNAME];
	RtlSecureZeroMemory(pszDest, _MAX_FNAME);

	// Byte 0
	UCHAR Byte0 = GetByte(0, Attribute);
	if (Byte0) {
		UCHAR * Bits = GetBits(Byte0);
		if (Bits[0]) { StringCchCatA(pszDest, _MAX_FNAME, "0x01+\0\0"); }
		if (Bits[1]) { StringCchCatA(pszDest, _MAX_FNAME, "0x02+\0\0"); }
		if (Bits[2]) { StringCchCatA(pszDest, _MAX_FNAME, "0x04+\0\0"); }
		if (Bits[3]) { StringCchCatA(pszDest, _MAX_FNAME, "0x08+\0\0"); }
		if (Bits[4]) { StringCchCatA(pszDest, _MAX_FNAME, "LIGHT_OFF+\0\0"); }
		if (Bits[5]) { StringCchCatA(pszDest, _MAX_FNAME, "DISABLED_2+\0\0"); }
		if (Bits[6]) { StringCchCatA(pszDest, _MAX_FNAME, "0x40+\0\0"); }
		if (Bits[7]) { StringCchCatA(pszDest, _MAX_FNAME, "0x80+\0\0"); }
		delete[] Bits;
	}

	// Cleanup
	if (pszDest[strlen(pszDest) - 1] != 0x2B) {}
	else { pszDest[strlen(pszDest) - 1] = 0x00; }

	// Terminate
	return pszDest;

}
CHAR * Bio_Hazard_2_Script::GetPlcNeck(USHORT Op) {

	switch(Op)
	{
	case 0x00:
		return (CHAR *)"FRONT\0\0";
	break;
	case 0x01:
		return (CHAR *)"COORD\0\0";
	break;
	case 0x02:
		return (CHAR *)"ANGLE\0\0";
	break;
	case 0x03:
		return (CHAR *)"YES\0\0";
	break;
	case 0x04:
		return (CHAR *)"NO\0\0";
	break;
	case 0x05:
		return (CHAR *)"TRACE\0\0";
	break;
	case 0x06:
		return (CHAR *)"AUTO\0\0";
	break;
	case 0x07:
		return (CHAR *)"FREE\0\0";
	break;
	case 0x08:
		return (CHAR *)"INIT\0\0";
	break;

	default:
		return (CHAR *)"NULL\0\0";
	break;
	}

}
CHAR * Bio_Hazard_2_Script::GetSpeedId(USHORT Id) {

	switch(Id)
	{
	case 0x00:
		return (CHAR *)"X_POS\0\0";
	break;
	case 0x01:
		return (CHAR *)"Y_POS\0\0";
	break;
	case 0x02:
		return (CHAR *)"Z_POS\0\0";
	break;
	case 0x03:
		return (CHAR *)"X_DIR\0\0";
	break;
	case 0x04:
		return (CHAR *)"Y_DIR\0\0";
	break;
	case 0x05:
		return (CHAR *)"Z_DIR\0\0";
	break;
	case 0x06:
		return (CHAR *)"X_POS2\0\0";
	break;
	case 0x07:
		return (CHAR *)"Y_POS2\0\0";
	break;
	case 0x08:
		return (CHAR *)"Z_POS2\0\0";
	break;
	case 0x09:
		return (CHAR *)"X_DIR2\0\0";
	break;
	case 0x0A:
		return (CHAR *)"Y_DIR2\0\0";
	break;
	case 0x0B:
		return (CHAR *)"Z_DIR2\0\0";
	break;

	default:
		return (CHAR *)"NULL\0\0";
	break;
	}

}
CHAR * Bio_Hazard_2_Script::GetWorkSet(USHORT Type) {

	switch(Type)
	{
	case 0x00:
		return (CHAR *)"NONE\0\0";
	break;
	case 0x01:
		return (CHAR *)"PLAYER\0\0";
	break;
	case 0x02:
		return (CHAR *)"SPLAYER\0\0";
	break;
	case 0x03:
		return (CHAR *)"ENEMY\0\0";
	break;
	case 0x04:
		return (CHAR *)"OBJECT\0\0";
	break;
	case 0x05:
		return (CHAR *)"DOOR\0\0";
	break;
	case 0x06:
		return (CHAR *)"ALL\0\0";
	break;
	case 0x80:
		return (CHAR *)"PL_PARTS\0\0";
	break;
	case 0xA0:
		return (CHAR *)"SPL_PARTS\0\0";
	break;
	case 0xC0:
		return (CHAR *)"EM_PARTS\0\0";
	break;
	case 0xE0:
		return (CHAR *)"OM_PARTS\0\0";
	break;

	default:
		return (CHAR *)"NULL\0\0";
	break;
	}

}
VOID Bio_Hazard_2_Script::ScdPrint(_iobuf * BINARY, _iobuf * SOURCE, ULONG &_Offset) {

	// Error
	if (!IsOpen(BINARY)) { return; }
	if (!IsOpen(SOURCE)) { return; }

	// Jump
	JumpLabelCk(SOURCE, _Offset);

	// Flag
	NoTab = TRUE;
	NoSemi = FALSE;
	NoRet = FALSE;
	if (DebugMode) { Print(SOURCE, "/* 0x%08X */ ", _Offset); }

	// Source
	switch(Scd->Opcode)
	{
	case 0x00:
		if (PrintNop) { Print(SOURCE, "Nop()"); }
	break;
	case 0x01:
		Print(SOURCE, "Evt_end()");
	break;
	case 0x02:
		Print(SOURCE, "Evt_next()");
	break;
	case 0x03:
		Print(SOURCE, "Evt_chain(%d)", Scd->Evt_chain.Id);
	break;
	case 0x04:
		Print(SOURCE, "Evt_exec(0x%02hhX, 0x%02hhX)", Scd->Evt_exec.data1, Scd->Evt_exec.ScdId);
	break;
	case 0x05:
		Print(SOURCE, "Evt_kill(0x%02hhX)", Scd->Evt_kill.Id);
	break;
	case 0x06:
	{
		Print(SOURCE, "if (");
		_Offset = ClausePrint(BINARY, SOURCE, _Offset, 0x06);
		Print(SOURCE, ") {");
		NoSemi = TRUE;
	}
	break;
	case 0x07:
		Print(SOURCE, "} else {");
		NoSemi = TRUE;
	break;
	case 0x08:
		Print(SOURCE, "}");
		NoSemi = TRUE;
	break;
	case 0x09:
		Print(SOURCE, "Sleep(%d)", Scd->Sleep.Count);
	break;
	case 0x0A:
		Print(SOURCE, "Sleeping(%d)", Scd->Sleeping.Count);
	break;
	case 0x0B:
		Print(SOURCE, "Wsleep()");
	break;
	case 0x0C:
		Print(SOURCE, "Wsleeping()");
	break;
	case 0x0D:
		Print(SOURCE, "for(%d) {", Scd->For.Count);
		NoSemi = TRUE;
	break;
	case 0x0E:
		Print(SOURCE, "}");
		NoSemi = TRUE;
	break;
	case 0x0F:
		Print(SOURCE, "while (");
		_Offset = ClausePrint(BINARY, SOURCE, _Offset, 0x0F);
		Print(SOURCE, ") {");
		NoSemi = TRUE;
	break;
	case 0x10:
		Print(SOURCE, "}");
		NoSemi = TRUE;
	break;
	case 0x11:
		Print(SOURCE, "do {");
		NoSemi = TRUE;
	break;
	case 0x12:
		Print(SOURCE, "} while (");
		_Offset = ClausePrint(BINARY, SOURCE, _Offset, 0x12);
		Print(SOURCE, ")");
	break;
	case 0x13:
		Print(SOURCE, "switch(%s)", GetMemberFlag(Scd->Switch.Value));
		if (DebugMode) { Print(SOURCE, "\t// 0x%04hX bytes", (Scd->Switch.Size + sizeof(tagBio2Bytecode::tagSwitch))); }
		Print(SOURCE, "\r\n{");
		NoSemi = TRUE;
	break;
	case 0x14:
		Print(SOURCE, "case %d:", Scd->Case.Value);
		if (DebugMode) { Print(SOURCE, "\t// 0x%04hX bytes", (Scd->Case.Size + sizeof(tagBio2Bytecode::tagCase))); }
		NoSemi = TRUE;
	break;
	case 0x15:
		Print(SOURCE, "default:");
		NoSemi = TRUE;
	break;
	case 0x16:
		Print(SOURCE, "}");
		NoSemi = TRUE;
	break;
	case 0x17:
		Print(SOURCE, "goto %s", GetJumpLabel(_Offset + Scd->Goto.Offset));
		if (DebugMode) { Print(SOURCE, "\t// 0x%08X", (_Offset + Scd->Goto.Offset)); }
	break;
	case 0x18:
		Print(SOURCE, "Gosub(0x%02hhX)", Scd->Gosub.SCD);
	break;
	case 0x19:
		Print(SOURCE, "return");
	break;
	case 0x1A:
		Print(SOURCE, "break");
	break;
	case 0x1B:
		Print(SOURCE, "For2");
	break;
	case 0x1C:
		Print(SOURCE, "Break_point()");
	break;
	case 0x1D:
		Print(SOURCE, "Work_copy(0x%02hhX, 0x%02hhX, 0x%02hhX)",
			Scd->Work_copy.Source, Scd->Work_copy.Destination, Scd->Work_copy.Typecast);
	break;
	case 0x1E:
		Print(SOURCE, "// Opcode[0x%02hhX] is unsupported in every version of Bio Hazard 2.", 0x1E);
	break;
	case 0x1F:
		Print(SOURCE, "// Opcode[0x%02hhX] is unsupported in every version of Bio Hazard 2.", 0x1F);
	break;
	case 0x20:
		Print(SOURCE, "// Opcode[0x%02hhX] is unsupported in every version of Bio Hazard 2.", 0x20);
	break;
	case 0x21:
		Print(SOURCE, "Ck(%s, 0x%02hhX, %s)",
			GetCkFlag(Scd->Ck.Flag), Scd->Ck.Id, GetOnOff(Scd->Ck.OnOff));
	break;
	case 0x22:
		Print(SOURCE, "Set(%s, 0x%02hhX, %s)",
			GetCkFlag(Scd->Set.Flag), Scd->Set.Id, GetOnOff(Scd->Set.OnOff));
	break;
	case 0x23:
		Print(SOURCE, "Cmp(%s %s %d)",
			GetMemberFlag(Scd->Cmp.Flag), GetCmpOperator(Scd->Cmp.Operator), Scd->Cmp.Value);
	break;
	case 0x24:
		Print(SOURCE, "Save(%s, %d)",
			GetMemberFlag(Scd->Save.Destination), Scd->Save.Source);
	break;
	case 0x25:
		Print(SOURCE, "Copy(%s, %d)",
			GetMemberFlag(Scd->Copy.Destination), Scd->Copy.Source);
	break;
	case 0x26:
		Print(SOURCE, "Calc(%s %s %d)",
			GetMemberFlag(Scd->Calc.Flag), GetCalcOperator(Scd->Calc.Operator), Scd->Calc.Value);
	break;
	case 0x27:
		Print(SOURCE, "Calc2(%s %s %d)",
			GetMemberFlag(Scd->Calc2.Flag), GetCalcOperator(Scd->Calc2.Operator), Scd->Calc2.Value);
	break;
	case 0x28:
		Print(SOURCE, "Sce_rnd()");
	break;
	case 0x29:
		Print(SOURCE, "Cut_chg(0x%02hhX)",
			Scd->Cut_chg.nCut);
	break;
	case 0x2A:
		Print(SOURCE, "Cut_old()");
	break;
	case 0x2B:
		Print(SOURCE, "Message_on(0x%02hhX, 0x%02hhX, 0x%04hX)",
			Scd->Message_on.data0, Scd->Message_on.data1, Scd->Message_on.data2);
	break;
	case 0x2C:
		Print(SOURCE, "Aot_set(%d, %s, %s, %d, %d, %d, %d, %d, %d, 0x%04hX, 0x%04hX, 0x%04hX)",
			Scd->Aot_set.Aot, GetAotSet(Scd->Aot_set.SCE), GetAotSat(Scd->Aot_set.SAT), Scd->Aot_set.nFloor, Scd->Aot_set.Super,
			Scd->Aot_set.X, Scd->Aot_set.Z, Scd->Aot_set.W, Scd->Aot_set.D,
			Scd->Aot_set.Data0, Scd->Aot_set.Data1, Scd->Aot_set.Data2);
	break;
	case 0x2D:
		Print(SOURCE, "Obj_model_set(0x%02hhX, %s, 0x%02hhX, 0x%02hhX, 0x%02hhX, %d, %d, 0x%04hX, %s, %s, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d)",
			Scd->Obj_model_set.MD1, GetObjSetId(Scd->Obj_model_set.Id),
			Scd->Obj_model_set.Ccol_old, Scd->Obj_model_set.Ccol_no, Scd->Obj_model_set.Ctex_old,
			Scd->Obj_model_set.nFloor, Scd->Obj_model_set.Super,
			Scd->Obj_model_set.Type, GetObjSetBeFlg(Scd->Obj_model_set.BeFlag), GetObjSetAttr(Scd->Obj_model_set.Attribute),
			Scd->Obj_model_set.X, Scd->Obj_model_set.Y, Scd->Obj_model_set.Z,
			Scd->Obj_model_set.DirX, Scd->Obj_model_set.DirY, Scd->Obj_model_set.DirY,
			Scd->Obj_model_set.AtariOffsetX, Scd->Obj_model_set.AtariOffsetY, Scd->Obj_model_set.AtariOffsetZ,
			Scd->Obj_model_set.AtariSizeX, Scd->Obj_model_set.AtariSizeY, Scd->Obj_model_set.AtariSizeZ);
	break;
	case 0x2E:
		Print(SOURCE, "Work_set(%s, %d)",
			GetWorkSet(Scd->Work_set.Type), Scd->Work_set.Aot);
	break;
	case 0x2F:
		Print(SOURCE, "Speed_set(%s, %d)",
			GetSpeedId(Scd->Speed_set.Id), Scd->Speed_set.Value);
	break;
	case 0x30:
		Print(SOURCE, "Add_speed()");
	break;
	case 0x31:
		Print(SOURCE, "Add_aspeed()");
	break;
	case 0x32:
		Print(SOURCE, "Pos_set(%d, %d, %d)",
			Scd->Pos_set.X, Scd->Pos_set.Y, Scd->Pos_set.Z);
	break;
	case 0x33:
		Print(SOURCE, "Dir_set(%d, %d, %d)",
			Scd->Dir_set.X, Scd->Dir_set.Y, Scd->Dir_set.Z);
	break;
	case 0x34:
		Print(SOURCE, "Member_set(%s, %d)",
			GetMemberFlag(Scd->Member_set.Destination), Scd->Member_set.Source);
	break;
	case 0x35:
		Print(SOURCE, "Member_set2(%s, 0x%02hhX)",
			GetMemberFlag(Scd->Member_set2.Destination), Scd->Member_set2.Source);
	break;
	case 0x36:
		Print(SOURCE, "Se_on(0x%02hhX, 0x%04hX, %d, %d, %d, %d)",
			Scd->Se_on.VAB, Scd->Se_on.EDT, Scd->Se_on.data0,
			Scd->Se_on.X, Scd->Se_on.Y, Scd->Se_on.Z);
	break;
	case 0x37:
		Print(SOURCE, "Sca_id_set(%d, 0x%04hX)",
			Scd->Sca_id_set.iEntry, Scd->Sca_id_set.Id);
	break;
	case 0x38:
		Print(SOURCE, "Flr_set(%d, 0x%02hhX)",
			Scd->Flr_set.Id, Scd->Flr_set.Flag);
	break;
	case 0x39:
		Print(SOURCE, "Dir_ck(%d, %d, %d);",
			Scd->Dir_ck.X, Scd->Dir_ck.Z, Scd->Dir_ck.Add);
	break;
	case 0x3A:
		Print(SOURCE, "Sce_espr_on(0x%04hX, 0x%04hX, 0x%04hX, %d, %d, %d, %d)",
			Scd->Sce_espr_on.data0, Scd->Sce_espr_on.data1, Scd->Sce_espr_on.data2,
			Scd->Sce_espr_on.X, Scd->Sce_espr_on.Y, Scd->Sce_espr_on.Z, Scd->Sce_espr_on.DirY);
	break;
	case 0x3B:
		Print(SOURCE, "Door_aot_set(%d, %s, %s, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, 0x%02hhX, 0x%02hhX, 0x%02hhX, 0x%02hhX, 0x%02hhX, 0x%02hhX, 0x%02hhX, 0x%02hhX, 0x%02hhX, 0x%02hhX)",
			Scd->Door_aot_set.Aot, GetAotSet(Scd->Door_aot_set.SCE), GetAotSat(Scd->Door_aot_set.SAT),
			Scd->Door_aot_set.nFloor, Scd->Door_aot_set.Super,
			Scd->Door_aot_set.X, Scd->Door_aot_set.Z, Scd->Door_aot_set.W, Scd->Door_aot_set.D,
			Scd->Door_aot_set.Next_pos_x, Scd->Door_aot_set.Next_pos_y, Scd->Door_aot_set.Next_pos_z, Scd->Door_aot_set.Next_cdir_y,
			Scd->Door_aot_set.Next_stage, Scd->Door_aot_set.Next_room, Scd->Door_aot_set.Next_cut, Scd->Door_aot_set.Next_nfloor,
			Scd->Door_aot_set.Dtex_type, Scd->Door_aot_set.Door_type, Scd->Door_aot_set.Knock_type,
			Scd->Door_aot_set.Key_id, Scd->Door_aot_set.Key_type, Scd->Door_aot_set.Free);
	break;
	case 0x3C:
		Print(SOURCE, "Cut_auto(%s)",
			GetOnOff(Scd->Cut_auto.OnOff));
	break;
	case 0x3D:
		Print(SOURCE, "Member_copy(%s, %d)",
			GetMemberFlag(Scd->Member_copy.Destination), Scd->Member_copy.Source);
	break;
	case 0x3E:
		Print(SOURCE, "Member_cmp(%s %s %d)",
			GetMemberFlag(Scd->Member_cmp.Flag), GetCmpOperator(Scd->Member_cmp.Operator), Scd->Member_cmp.Value);
	break;
	case 0x3F:
		Print(SOURCE, "Plc_motion(0x%02hhX, 0x%02hhX, 0x%02hhX)",
			Scd->Plc_motion.Animation, Scd->Plc_motion.data0, Scd->Plc_motion.data1);
	break;
	case 0x40:
		Print(SOURCE, "Plc_dest(0x%02hhX, 0x%02hhX, %d, %d)",
			Scd->Plc_dest.Animation, Scd->Plc_dest.Bit,
			Scd->Plc_dest.X, Scd->Plc_dest.Z);
	break;
	case 0x41:
		Print(SOURCE, "Plc_neck(%s, %d, %d, %d, %d, %d)",
			GetPlcNeck(Scd->Plc_neck.Op),
			Scd->Plc_neck.X, Scd->Plc_neck.Y, Scd->Plc_neck.Z,
			Scd->Plc_neck.SpeedX, Scd->Plc_neck.SpeedZ);
	break;
	case 0x42:
		Print(SOURCE, "Plc_ret()");
	break;
	case 0x43:
		Print(SOURCE, "Plc_flg");
	break;
	case 0x44:
		Print(SOURCE, "Sce_em_set(%d, %s, 0x%04hX, %d, 0x%02hhX, 0x%02hhX, 0x%02hhX, %d, %d, %d, %d, %d, %d)",
			Scd->Sce_em_set.Em_no, GetEmdName(Scd->Sce_em_set.Id), Scd->Sce_em_set.Type,
			Scd->Sce_em_set.nFloor, Scd->Sce_em_set.Sound_flg, Scd->Sce_em_set.Model_type, Scd->Sce_em_set.Em_set_flg,
			Scd->Sce_em_set.Pos_x, Scd->Sce_em_set.Pos_y, Scd->Sce_em_set.Pos_z, Scd->Sce_em_set.Cdir_y,
			Scd->Sce_em_set.Motion, Scd->Sce_em_set.Ctr_flg);
	break;
	case 0x45:
		if (TrialEdition) {
			Print(SOURCE, "// Col_chg_set() is unimplemented in the Trial Edition");
		} else {
			Print(SOURCE, "Col_chg_set(%d, %d, %d, %d)",
				Scd->Col_chg_set.Data0, Scd->Col_chg_set.Data1, Scd->Col_chg_set.Data2, Scd->Col_chg_set.Data3);
		}
	break;
	case 0x46:
		Print(SOURCE, "Aot_reset(%d, %s, %s, 0x%04hX, 0x%04hX, 0x%04hX)",
			Scd->Aot_reset.Aot, GetAotSet(Scd->Aot_reset.SCE), GetAotSat(Scd->Aot_reset.SAT),
			Scd->Aot_reset.Data0, Scd->Aot_reset.Data1, Scd->Aot_reset.Data2);
	break;
	case 0x47:
		Print(SOURCE, "Aot_on(%d)",
			Scd->Aot_on.Aot);
	break;
	case 0x48:
		Print(SOURCE, "Super_set(%s, %d, %d, %d, %d, %d, %d, %d);",
			GetWorkSet(Scd->Super_set.Work), Scd->Super_set.Id,
			Scd->Super_set.pX, Scd->Super_set.pY, Scd->Super_set.pZ,
			Scd->Super_set.dX, Scd->Super_set.dY, Scd->Super_set.dZ);
	break;
	case 0x49:
		Print(SOURCE, "Super_reset(%d, %d, %d)",
			Scd->Super_reset.dX, Scd->Super_reset.dY, Scd->Super_reset.dZ);
	break;
	case 0x4A:
		Print(SOURCE, "Plc_gun(0x%02hhX)",
			Scd->Plc_gun.Animation);
	break;
	case 0x4B:
		Print(SOURCE, "Cut_replace(0x%02hhX, 0x%02hhX)",
			Scd->Cut_replace.Id, Scd->Cut_replace.Value);
	break;
	case 0x4C:
		Print(SOURCE, "Sce_espr_kill(0x%02hhX, 0x%02hhX, %d, %d)",
			Scd->Sce_espr_kill.id, Scd->Sce_espr_kill.tp,
			Scd->Sce_espr_kill.WorkKind, Scd->Sce_espr_kill.WorkNo);
	break;
	case 0x4D:
		Print(SOURCE, "Door_model_set(%d, %d, %d, 0x%02hhX, 0x%02hhX, 0x%04hX, %d, %d, %d, %d, 0x%04hX, 0x%04hX, 0x%04hX);",
			Scd->Door_model_set.data0, Scd->Door_model_set.Id, Scd->Door_model_set.OfsY, Scd->Door_model_set.BeFlg,
			Scd->Door_model_set.data5, Scd->Door_model_set.data6,
			Scd->Door_model_set.X, Scd->Door_model_set.Y, Scd->Door_model_set.Z, Scd->Door_model_set.DirY,
			Scd->Door_model_set.data10, Scd->Door_model_set.data11, Scd->Door_model_set.data12);
	break;
	case 0x4E:
		Print(SOURCE, "Item_aot_set(%d, %s, %s, %d, %d, %d, %d, %d, %d, %s, %d, 0x%04hX, 0x%02hhX, 0x%02hhX)",
			Scd->Item_aot_set.Aot, GetAotSet(Scd->Item_aot_set.SCE), GetAotSat(Scd->Item_aot_set.SAT),
			Scd->Item_aot_set.nFloor, Scd->Item_aot_set.Super,
			Scd->Item_aot_set.X, Scd->Item_aot_set.Z, Scd->Item_aot_set.W, Scd->Item_aot_set.D,
			GetItemName(Scd->Item_aot_set.iItem), Scd->Item_aot_set.nItem, Scd->Item_aot_set.Flag,
			Scd->Item_aot_set.MD1, Scd->Item_aot_set.Action);
	break;
	case 0x4F:
		Print(SOURCE, "Sce_key_ck(0x%02hhX, 0x%04hX)",
			Scd->Sce_key_ck.Flag, Scd->Sce_key_ck.Value);
	break;
	case 0x50:
		Print(SOURCE, "Sce_trg_ck(0x%02hhX, 0x%04hX)",
			Scd->Sce_trg_ck.Flag, Scd->Sce_trg_ck.Value);
	break;
	case 0x51:
		Print(SOURCE, "Sce_bgm_control(%s, %s, %s, %d, %d)",
			GetBgmCtlId(Scd->Sce_bgm_control.Id),
			GetBgmCtlOp(Scd->Sce_bgm_control.Op),
			GetBgmCtlType(Scd->Sce_bgm_control.Type),
			Scd->Sce_bgm_control.VolL, Scd->Sce_bgm_control.VolR);
	break;
	case 0x52:
		Print(SOURCE, "Sce_espr_control(0x%02hhX, 0x%02hhX, 0x%02hhX, %d, %d)",
			Scd->Sce_espr_control.Id, Scd->Sce_espr_control.Type, Scd->Sce_espr_control.Return,
			Scd->Sce_espr_control.WorkKind, Scd->Sce_espr_control.WorkNo);
	break;
	case 0x53:
		Print(SOURCE, "Sce_fade_set(0x%02hhX, 0x%02hhX, 0x%02hhX, 0x%04hX)",
			Scd->Sce_fade_set.data0, Scd->Sce_fade_set.data1, Scd->Sce_fade_set.data2, Scd->Sce_fade_set.data3);
	break;
	case 0x54:
		Print(SOURCE, "Sce_espr3d_on(0x%04hX, 0x%04hX, 0x%04hX, %d, %d, %d, %d, %d, %d, 0x%04hX",
			Scd->Sce_espr3d_on.data0, Scd->Sce_espr3d_on.data1, Scd->Sce_espr3d_on.data2,
			Scd->Sce_espr3d_on.X, Scd->Sce_espr3d_on.Y, Scd->Sce_espr3d_on.Z,
			Scd->Sce_espr3d_on.DirX, Scd->Sce_espr3d_on.DirY, Scd->Sce_espr3d_on.DirZ,
			Scd->Sce_espr3d_on.data3);
	break;
	case 0x55:
		Print(SOURCE, "Member_calc(%s %s %d)",
			GetMemberFlag(Scd->Member_calc.Flag), GetCalcOperator(Scd->Member_calc.Operator), Scd->Member_calc.Value);
	break;
	case 0x56:
		Print(SOURCE, "Member_calc2(%s %s %d)",
			GetMemberFlag(Scd->Member_calc2.Flag), GetCalcOperator(Scd->Member_calc2.Operator), Scd->Member_calc2.Value);;
	break;
	case 0x57:
		Print(SOURCE, "Sce_bgmtbl_set(ROOM%X%02X, 0x%04hX, 0x%04hX)",
			Scd->Sce_bgmtbl_set.Stage, Scd->Sce_bgmtbl_set.Room,
			Scd->Sce_bgmtbl_set.data1, Scd->Sce_bgmtbl_set.data2);
	break;
	case 0x58:
		Print(SOURCE, "Plc_rot(%d, %d)",
			Scd->Plc_rot.Id, Scd->Plc_rot.Sce_free0);
	break;
	case 0x59:
		Print(SOURCE, "Xa_on(0x%02hhX, 0x%04hX)",
			Scd->Xa_on.Mode, Scd->Xa_on.Number);
	break;
	case 0x5A:
		Print(SOURCE, "Weapon_chg(0x%02hhX)",
			Scd->Weapon_chg.Id);
	break;
	case 0x5B:
		Print(SOURCE, "Plc_cnt(0x%02hhX)",
			Scd->Plc_cnt.Id);
	break;
	case 0x5C:
		Print(SOURCE, "Sce_shake_on(%d, %d)",
			Scd->Sce_shake_on.Slide_ofs, Scd->Sce_shake_on.Copy_ofs);
	break;
	case 0x5D:
		Print(SOURCE, "Water_div_set(%d)",
			Scd->Mizu_div_set.Id);
	break;
	case 0x5E:
		Print(SOURCE, "Keep_Item_ck(0x%02hhX)",
			Scd->Keep_Item_ck.Id);
	break;
	case 0x5F:
		Print(SOURCE, "Xa_vol(%d)",
			Scd->Xa_vol.Value);
	break;
	case 0x60:
		if (TrialEdition) {
			Print(SOURCE, "// Kage_set() is unimplemented in the Trial Edition");
		} else {
			Print(SOURCE, "Kage_set(%s, %d, 0x%02hhX, 0x%02hhX, 0x%02hhX, %d, %d, %d, %d)",
				GetWorkSet(Scd->Kage_set.Work), Scd->Kage_set.Id,
				Scd->Kage_set.Data0, Scd->Kage_set.Data1, Scd->Kage_set.Data2,
				Scd->Kage_set.Data3, Scd->Kage_set.Data4, Scd->Kage_set.Data5, Scd->Kage_set.Data6);
		}
	break;
	case 0x61:
		Print(SOURCE, "Cut_be_set(0x%02hhX, 0x%02hhX, %s)",
			Scd->Cut_be_set.Id, Scd->Cut_be_set.Value, GetOnOff(Scd->Cut_be_set.OnOff));
	break;
	case 0x62:
		Print(SOURCE, "Sce_Item_lost(%s)",
			GetItemName(Scd->Sce_Item_lost.Id));
	break;
	case 0x63:
		Print(SOURCE, "Plc_gun_eff()");
	break;
	case 0x64:
		Print(SOURCE, "Sce_espr_on2(0x%02hhX, 0x%04hX, 0x%02hhX, 0x%02hhX, 0x%04hX, %d, %d, %d, %d)",
			Scd->Sce_espr_on2.dir_y_id2, Scd->Sce_espr_on2.data1, Scd->Sce_espr_on2.WorkKind, Scd->Sce_espr_on2.WorkNo,
			Scd->Sce_espr_on2.data3,
			Scd->Sce_espr_on2.X, Scd->Sce_espr_on2.Y, Scd->Sce_espr_on2.Z, Scd->Sce_espr_on2.DirY);
	break;
	case 0x65:
		Print(SOURCE, "Sce_espr_kill2(0x%02hhX)",
			Scd->Sce_espr_kill2.Id);
	break;
	case 0x66:
		Print(SOURCE, "Plc_stop()");
	break;
	case 0x67:
		Print(SOURCE, "Aot_set_4p(%d, %s, %s, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, 0x%04hX, 0x%04hX, 0x%04hX)",
			Scd->Aot_set_4p.Aot, GetAotSet(Scd->Aot_set_4p.SCE), GetAotSat(Scd->Aot_set_4p.SAT),
			Scd->Aot_set_4p.nFloor, Scd->Aot_set_4p.Super,
			Scd->Aot_set_4p.X0, Scd->Aot_set_4p.Z0, Scd->Aot_set_4p.X1, Scd->Aot_set_4p.Z1,
			Scd->Aot_set_4p.X2, Scd->Aot_set_4p.Z2, Scd->Aot_set_4p.X3, Scd->Aot_set_4p.Z3,
			Scd->Aot_set_4p.Data0, Scd->Aot_set_4p.Data1, Scd->Aot_set_4p.Data2);
	break;
	case 0x68:
		Print(SOURCE, "Door_aot_set_4p(%d, %s, %s, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, 0x%02hhX, 0x%02hhX, 0x%02hhX, 0x%02hhX, 0x%02hhX, 0x%02hhX, 0x%02hhX, 0x%02hhX, 0x%02hhX, 0x%02hhX)",
			Scd->Door_aot_set_4p.Aot, GetAotSet(Scd->Door_aot_set_4p.SCE), GetAotSat(Scd->Door_aot_set_4p.SAT),
			Scd->Door_aot_set_4p.nFloor, Scd->Door_aot_set_4p.Super,
			Scd->Door_aot_set_4p.X0, Scd->Door_aot_set_4p.Z0, Scd->Door_aot_set_4p.X1, Scd->Door_aot_set_4p.Z1,
			Scd->Door_aot_set_4p.X2, Scd->Door_aot_set_4p.Z2, Scd->Door_aot_set_4p.X3, Scd->Door_aot_set_4p.Z3,
			Scd->Door_aot_set_4p.Next_pos_x, Scd->Door_aot_set_4p.Next_pos_y, Scd->Door_aot_set_4p.Next_pos_z, Scd->Door_aot_set_4p.Next_cdir_y,
			Scd->Door_aot_set_4p.Next_stage, Scd->Door_aot_set_4p.Next_room, Scd->Door_aot_set_4p.Next_cut, Scd->Door_aot_set_4p.Next_nfloor,
			Scd->Door_aot_set_4p.Dtex_type, Scd->Door_aot_set_4p.Door_type, Scd->Door_aot_set_4p.Knock_type,
			Scd->Door_aot_set_4p.Key_id, Scd->Door_aot_set_4p.Key_type, Scd->Door_aot_set_4p.Free);
	break;
	case 0x69:
		Print(SOURCE, "Item_aot_set_4p(%d, %s, %s, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %s, %d, 0x%04hX, 0x%02hhX, 0x%02hhX)",
			Scd->Item_aot_set_4p.Aot, GetAotSet(Scd->Item_aot_set_4p.SCE), GetAotSat(Scd->Item_aot_set_4p.SAT),
			Scd->Item_aot_set_4p.nFloor, Scd->Item_aot_set_4p.Super,
			Scd->Item_aot_set_4p.X0, Scd->Item_aot_set_4p.Z0, Scd->Item_aot_set_4p.X1, Scd->Item_aot_set_4p.Z1,
			Scd->Item_aot_set_4p.X2, Scd->Item_aot_set_4p.Z2, Scd->Item_aot_set_4p.X3, Scd->Item_aot_set_4p.Z3,
			GetItemName(Scd->Item_aot_set_4p.iItem), Scd->Item_aot_set_4p.nItem, Scd->Item_aot_set_4p.Flag,
			Scd->Item_aot_set_4p.MD1, Scd->Item_aot_set_4p.Action);
	break;
	case 0x6A:
		Print(SOURCE, "Light_pos_set(%d, 0x%02hhX, %d)",
			Scd->Light_pos_set.Index, Scd->Light_pos_set.XYZ, Scd->Light_pos_set.Position);
	break;
	case 0x6B:
		Print(SOURCE, "Light_kido_set(%d, %d)",
			Scd->Light_kido_set.Index, Scd->Light_kido_set.Luminosity);
	break;
	case 0x6C:
		Print(SOURCE, "Rbj_reset()");
	break;
	case 0x6D:
		Print(SOURCE, "Sce_scr_move(%d)", Scd->Sce_scr_move.Scrl_y);
	break;
	case 0x6E:
		Print(SOURCE, "Parts_set(%s %s %d)",
			GetMemberFlag(Scd->Parts_set.Id), GetCmpOperator(Scd->Parts_set.Type), Scd->Parts_set.Value);
	break;
	case 0x6F:
		Print(SOURCE, "Movie_on(0x%02hhX)",
			Scd->Movie_on.Id);
	break;
	case 0x70:
		Print(SOURCE, "Splc_ret()");
	break;
	case 0x71:
		Print(SOURCE, "Splc_sce()");
	break;
	case 0x72:
		Print(SOURCE, "Super_on(%d, %d, %d, %d, %d, %d, %d, %d)",
			Scd->Super_on.data0, Scd->Super_on.data1,
			Scd->Super_on.data2, Scd->Super_on.data3, Scd->Super_on.data4,
			Scd->Super_on.data5, Scd->Super_on.data6, Scd->Super_on.data7);
	break;
	case 0x73:
		Print(SOURCE, "Mirror_set(%d, %d, %d, %d)",
			Scd->Mirror_set.Flag, Scd->Mirror_set.Position,
			Scd->Mirror_set.Min, Scd->Mirror_set.Max);
	break;
	case 0x74:
		Print(SOURCE, "Sce_fade_adjust(0x%02hhX, %d)",
			Scd->Sce_fade_adjust.data0, Scd->Sce_fade_adjust.data1);
	break;
	case 0x75:
		Print(SOURCE, "Sce_espr3d_on2(%d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d)",
			Scd->Sce_espr3d_on2.dir_y_id2, Scd->Sce_espr3d_on2.bit, Scd->Sce_espr3d_on2.data4,
			Scd->Sce_espr3d_on2.data6, Scd->Sce_espr3d_on2.data8, Scd->Sce_espr3d_on2.dataA, Scd->Sce_espr3d_on2.dataC,
			Scd->Sce_espr3d_on2.dataE, Scd->Sce_espr3d_on2.data10, Scd->Sce_espr3d_on2.data12, Scd->Sce_espr3d_on2.data14);
	break;
	case 0x76:
		Print(SOURCE, "Sce_Item_get(%s, %d)",
			GetItemName(Scd->Sce_Item_get.Id), Scd->Sce_Item_get.Num);
	break;
	case 0x77:
		Print(SOURCE, "Sce_line_start(%d, %d)",
			Scd->Sce_line_start.Id, Scd->Sce_line_start.Value);
	break;
	case 0x78:
		Print(SOURCE, "Sce_line_main(%d, %d, %d)",
			Scd->Sce_line_main.Id, Scd->Sce_line_main.Data0, Scd->Sce_line_main.Data1);
	break;
	case 0x79:
		Print(SOURCE, "Sce_line_end()");
	break;
	case 0x7A:
		Print(SOURCE, "Sce_parts_bomb(%d, %d, %d, %d, %d, %d, %d, %d, %d)",
			Scd->Sce_parts_bomb.data2, Scd->Sce_parts_bomb.data3, Scd->Sce_parts_bomb.data4, Scd->Sce_parts_bomb.data5,
			Scd->Sce_parts_bomb.data6, Scd->Sce_parts_bomb.data8,
			Scd->Sce_parts_bomb.dataA, Scd->Sce_parts_bomb.dataC,
			Scd->Sce_parts_bomb.dataE);
	break;
	case 0x7B:
		Print(SOURCE, "Sce_parts_down(%d, %d, %d, %d, %d, %d, %d);",
			Scd->Sce_parts_down.X, Scd->Sce_parts_down.Y, Scd->Sce_parts_down.Z,
			Scd->Sce_parts_down.cDirZ,
			Scd->Sce_parts_down.DirX, Scd->Sce_parts_down.DirY, Scd->Sce_parts_down.DirZ);
	break;
	case 0x7C:
		Print(SOURCE, "Light_color_set(%d, %d, %d, %d)",
			Scd->Light_color_set.Index,
			Scd->Light_color_set.R, Scd->Light_color_set.G, Scd->Light_color_set.B);
	break;
	case 0x7D:
		Print(SOURCE, "Light_pos_set2(0x%02hhX, %d, 0x%02hhX, %d)",
			Scd->Light_pos_set2.nCut, Scd->Light_pos_set2.Index,
			Scd->Light_pos_set2.XYZ, Scd->Light_pos_set2.Position);
	break;
	case 0x7E:
		Print(SOURCE, "Light_kido_set2(0x%02hhX, %d, %d)",
			Scd->Light_kido_set2.nCut, Scd->Light_kido_set2.Index,
			Scd->Light_kido_set2.Luminosity);
	break;
	case 0x7F:
		Print(SOURCE, "Light_color_set2(0x%02hhX, %d, %d, %d, %d)",
			Scd->Light_color_set2.nCut, Scd->Light_color_set2.Index,
			Scd->Light_color_set2.R, Scd->Light_color_set2.G, Scd->Light_color_set2.B);
	break;
	case 0x80:
		Print(SOURCE, "Se_vol(%d)",
			Scd->Se_vol.Value);
	break;
	case 0x81:
		Print(SOURCE, "Sce_Item_cmp(0x%02hhX, 0x%02hhX)",
			Scd->Sce_Item_cmp.data0, Scd->Sce_Item_cmp.data1);
	break;
	case 0x82:
		Print(SOURCE, "Sce_espr_task(%d, %d)",
			Scd->Sce_espr_task.WorkKind, Scd->Sce_espr_task.WorkNo);
	break;
	case 0x83:
		Print(SOURCE, "Plc_heal()");
	break;
	case 0x84:
		Print(SOURCE, "St_map_hint(%d)",
			Scd->St_map_hint.DrModeTag);
	break;
	case 0x85:
		Print(SOURCE, "Sce_em_pos_ck(%d, %d, %d, %d)",
			Scd->Sce_em_pos_ck.Id, Scd->Sce_em_pos_ck.data1,
			Scd->Sce_em_pos_ck.Att, Scd->Sce_em_pos_ck.Flg);
	break;
	case 0x86:
		Print(SOURCE, "Poison_ck()");
	break;
	case 0x87:
		Print(SOURCE, "Poison_clr()");
	break;
	case 0x88:
		Print(SOURCE, "Sce_Item_lost2(%s, %d)",
			GetItemName(Scd->Sce_Item_lost2.Id), Scd->Sce_Item_lost2.Num);
	break;
	case 0x89:
		Print(SOURCE, "Evt_next2()");
	break;
	case 0x8A:
		Print(SOURCE, "Vib_set0(%d, %d)",
			Scd->Vib_set0.data0, Scd->Vib_set0.data1);
	break;
	case 0x8B:
		Print(SOURCE, "Vib_set1(%d, %d, %d)",
			Scd->Vib_set1.Id, Scd->Vib_set1.data0, Scd->Vib_set1.data1);
	break;
	case 0x8C:
		Print(SOURCE, "Vib_fade_set(%d, %d, %d, %d)",
			Scd->Vib_fade_set.data0, Scd->Vib_fade_set.data1, Scd->Vib_fade_set.data2, Scd->Vib_fade_set.data3);
	break;
	case 0x8D:
		Print(SOURCE, "Item_aot_set2(%d, %s, %s, %d, %d, %d, %d, %d, %d, %s, %d, 0x%04hX, 0x%02hhX, 0x%02hhX, 0x%02hhX, 0x%02hhX)",
			Scd->Item_aot_set2.Aot, GetAotSet(Scd->Item_aot_set2.SCE), GetAotSat(Scd->Item_aot_set2.SAT),
			Scd->Item_aot_set2.nFloor, Scd->Item_aot_set2.Super,
			Scd->Item_aot_set2.X, Scd->Item_aot_set2.Z, Scd->Item_aot_set2.W, Scd->Item_aot_set2.D,
			GetItemName(Scd->Item_aot_set2.iItem), Scd->Item_aot_set2.nItem, Scd->Item_aot_set2.Flag,
			Scd->Item_aot_set2.MD1, Scd->Item_aot_set2.Action,
			Scd->Item_aot_set2.data16, Scd->Item_aot_set2.data17);
	break;
	case 0x8E:
		Print(SOURCE, "Sce_em_set2(%d, %s, 0x%04hX, %d, 0x%02hhX, 0x%02hhX, 0x%02hhX, %d, %d, %d, %d, 0x%04hX, 0x%04hX, 0x%04hX)",
			Scd->Sce_em_set2.Aot, GetEmdName(Scd->Sce_em_set2.EMD), Scd->Sce_em_set2.Type,
			Scd->Sce_em_set2.nFloor, Scd->Sce_em_set2.SeType, Scd->Sce_em_set2.ModelType, Scd->Sce_em_set2.EmSetFlg,
			Scd->Sce_em_set2.X, Scd->Sce_em_set2.Y, Scd->Sce_em_set2.Z, Scd->Sce_em_set2.DirY,
			Scd->Sce_em_set2.Timer0, Scd->Sce_em_set2.Timer1, Scd->Sce_em_set2.data16);
	break;
	}

	// Semi-Colon
	if (NoSemi) { NoSemi = FALSE; }
	else { Print(SOURCE, ";"); }

	// End Line
	if (NoRet) { NoRet = FALSE; }
	else { Print(SOURCE, "\r\n"); }

	// Indention
	if (TabCount <= 0) { TabCount = 1; }

	// Complete
	if (TrialEdition) {
		switch (Scd->Opcode)
		{
		case 0x45:
			_Offset += sizeof(tagBio2BytecodeT::Col_chg_set);
		break;
		case 0x60:
			_Offset += sizeof(tagBio2BytecodeT::Kage_set);
		break;
		default:
			_Offset += Bio_Hazard_2_Script_Bytecode_Size[Scd->Opcode];
		break;
		}
	} else {
		_Offset += Bio_Hazard_2_Script_Bytecode_Size[Scd->Opcode];
	}
}
// Disassemble
ULONG Bio_Hazard_2_Script::Disassemble(_iobuf * BINARY, _iobuf * SOURCE, ULONG _Offset) {

	// Error
	if (!IsOpen(BINARY)) { return _Offset; }

	// Print
	TabCount = 1;
	NoTab = FALSE;
	NoSemi = FALSE;
	NoRet = FALSE;

	// Else
	ElseCk = FALSE;
	ElseCnt = NULL;

	// Meta
	Scd = new tagBio2Bytecode;
	ULONG _ElementSize = InitScan(BINARY, _Offset);

	// Jump
	nJumpLabels = NULL;
	RtlSecureZeroMemory(Jump, (sizeof(tagBio2JumpLabel) * 32));
	FindJumpLabels(BINARY, _Offset);
	if (DebugMode) { Print(SOURCE, "// Contains %d jump label(s)\r\n\r\n", nJumpLabels); }

	// Parse
	Print(SOURCE, "VOID %s(VOID) {\r\n", NameBase);
	for (ULONG n = 0; n < _ElementSize; n++)
	{
		// Complete
		if (feof(BINARY)) { break; }
		if (_Offset >= _ElementSize) { break; }

		// Read
		ScdRead(BINARY, _Offset);
		ScdPrint(BINARY, SOURCE, _Offset);
	}
	Print(SOURCE, "}");

	// Terminate
	delete[] Scd;
	return _Offset;
}
ULONG Bio_Hazard_2_Script::Disassemble(CONST CHAR * _FileName, ...) {

	// _FileName
	va_list _ArgList = { NULL };
	__crt_va_start(_ArgList, _FileName);
	_StrLen = (_vscprintf(_FileName, _ArgList) + 2);
	CHAR * FileName = new CHAR[(_StrLen * 2)];
	RtlSecureZeroMemory(FileName, (_StrLen * 2));
	vsprintf_s(FileName, _StrLen, _FileName, _ArgList);
	__crt_va_end(_ArgList);

	// Error
	if (!Exists(FileName)) { delete[] FileName; return NULL; }

	// Binary
	_iobuf * Binary = Open(READ_FILE, FileName);
	if (!Binary) {
		delete[] FileName;
		return NULL;
	}
	Directory = GetDirectory(FileName);
	NameBase = GetNamebase(FileName);

	// Source
	CHAR * SourceName = Get("%s%s.cpp", Directory, NameBase);
	_iobuf * Source = Open(CREATE_FILE, SourceName);
	if (!Source) {
		fclose(Binary);
		delete[] NameBase;
		delete[] Directory;
		delete[] FileName;
		delete[] SourceName;
		return NULL;
	}

	// Disassembly
	ULONG ScriptSize = Disassemble(Binary, Source, 0x00);

	// Cleanup
	delete[] NameBase;
	delete[] Directory;
	delete[] FileName;
	delete[] SourceName;
	fclose(Source);
	fclose(Binary);

	// Terminate
	return ScriptSize;
}
// RDT
ULONG Bio_Hazard_2_Script::Room(CONST CHAR * _FileName, ...) {

	// _FileName
	va_list _ArgList = { NULL };
	__crt_va_start(_ArgList, _FileName);
	_StrLen = (_vscprintf(_FileName, _ArgList) + 2);
	CHAR * FileName = new CHAR[(_StrLen * 2)];
	RtlSecureZeroMemory(FileName, (_StrLen * 2));
	vsprintf_s(FileName, _StrLen, _FileName, _ArgList);
	__crt_va_end(_ArgList);

	// Error
	if (!Exists(FileName)) { delete[] FileName; return NULL; }

	// Open
	_iobuf * _File = Open(READ_FILE, FileName);
	if (!_File) {
		delete[] FileName;
		return NULL;
	}
	CHAR * Directory = GetDirectory(FileName);
	CHAR * NameBase = GetNamebase(FileName);

	// Header
	Bio2Room * Rdt = new tagBio2Room;
	RtlSecureZeroMemory(Rdt, sizeof(tagBio2Room));
	Read(_File, 0x00, Rdt, sizeof(tagBio2Room));

	// Main
	if (Rdt->pScdx) {
		USHORT nScd = NULL;
		Read(_File, Rdt->pScdx, &nScd, 0x02);
		nScd /= 2;
		ULONG Pointer = Rdt->pScdx;
		ULONG _Offset = NULL;
		for (USHORT n = 0; n < nScd; n++, Pointer += 0x02)
		{
			Read(_File, Pointer, &_Offset, 0x02);
			if (_Offset) {
				_Offset += Rdt->pScdx;
				ULONG _ElementSize = InitScan(_File, _Offset);
				CreateFromSource(_File, _Offset, _ElementSize, "%s%s\\main%02d.scd", Directory, NameBase, n);
				Disassemble("%s%s\\main%02d.scd", Directory, NameBase, n);
			}
		}
	}

	// Sub
	if (Rdt->pScd) {
		USHORT nScd = NULL;
		Read(_File, Rdt->pScd, &nScd, 0x02);
		nScd /= 2;
		ULONG Pointer = Rdt->pScd;
		ULONG _Offset = NULL;
		for (USHORT n = 0; n < nScd; n++, Pointer += 0x02)
		{
			Read(_File, Pointer, &_Offset, 0x02);
			if (_Offset) {
				_Offset += Rdt->pScd;
				ULONG _ElementSize = InitScan(_File, _Offset);
				CreateFromSource(_File, _Offset, _ElementSize, "%s%s\\sub%02d.scd", Directory, NameBase, n);
				Disassemble("%s%s\\sub%02d.scd", Directory, NameBase, n);
			}
		}
	}

	// Cleanup
	delete[] NameBase;
	delete[] Directory;
	delete[] FileName;
	delete Rdt;
	fclose(_File);

	// Terminate
	return NULL;
}
// Prototype
BOOL Bio_Hazard_2_Script::ExScdContainer(CONST CHAR * _FileName, ...) {

	// _FileName
	va_list _ArgList = { NULL };
	__crt_va_start(_ArgList, _FileName);
	_StrLen = (_vscprintf(_FileName, _ArgList) + 2);
	CHAR * FileName = new CHAR[(_StrLen * 2)];
	RtlSecureZeroMemory(FileName, (_StrLen * 2));
	vsprintf_s(FileName, _StrLen, _FileName, _ArgList);
	__crt_va_end(_ArgList);

	// Error
	if (!Exists(FileName)) { delete[] FileName; return NULL; }

	// Open
	_iobuf * _File = Open(READ_FILE, FileName);
	if (!_File) {
		delete[] FileName;
		return NULL;
	}
	CHAR * Directory = GetDirectory(FileName);
	CHAR * NameBase = GetNamebase(FileName);
	ULONG _ElementSize = Size(_File);

	// Setup
	USHORT nScd = NULL;
	Read(_File, 0x00, &nScd, sizeof(unsigned short int));
	nScd /= sizeof(unsigned short int);
	USHORT _Offset = NULL;
	USHORT Offset = NULL;
	std::vector <ULONG> Pointer;
	std::vector <ULONG> Size;
	ULONG _Size = NULL;

	// Pointer
	for (USHORT iScd = NULL; iScd < nScd; iScd++) {
		Read(_File, _Offset, &Offset, sizeof(unsigned short int));
		Pointer.push_back(Offset);
		_Offset += 0x02;
	}

	// Size
	for (USHORT iScd = NULL; iScd < nScd; iScd++) {
		if ((iScd + 1) >= nScd) { _Size = (_ElementSize - Pointer[iScd]); }
		else { _Size = (Pointer[iScd + 1] - Pointer[iScd]); }
		Size.push_back(_Size);
	}

	// Extract
	for (USHORT iScd = NULL; iScd < nScd; iScd++) {
		CreateFromSource(_File, Pointer[iScd], Size[iScd], "%s\\%s\\%s%02X.scd", Directory, NameBase, NameBase, iScd);
		UpdatePrototype((CHAR*)"%s\\%s\\%s%02X.scd", Directory, NameBase, NameBase, iScd);
	}

	// Cleanup
	fclose(_File);

	// Terminate
	return TRUE;
}
ULONG Bio_Hazard_2_Script::InitScanProto(_iobuf * BINARY, ULONG _Offset) {

	// Error
	if (!IsOpen(BINARY)) { return NULL; }

	// Variable
	ULONG Pointer = _Offset;
	UCHAR Opcode = NULL;
	UCHAR OpPeek = NULL;
	ULONG _Filesize = Size(BINARY);
	Scan = new tagBioScriptScan;
	std::vector <tagBio2BytecodeP::tagIfel_ck> Ifel_ck;
	std::vector <tagBio2BytecodeP::tagElse_ck> Else_ck;
	std::vector <tagBio2BytecodeP::tagEndif> Endif;
	Scd = new tagBio2Bytecode;
	Scd15 = new tagBio2BytecodeP;

	// Work
	Pointer = _Offset;
	Opcode = NULL;
	for (ULONG n = 0; n < _Filesize; n++) {

		// Complete
		if (feof(BINARY)) { break; }
		if (Pointer >= _Filesize) { break; }

		// Opcodes & Pointers
		Read(BINARY, Pointer, &Opcode, sizeof(unsigned char));
		Scan->Pointer.push_back(Pointer);
		Scan->Opcode.push_back(Opcode);
		Read(BINARY, (Pointer + Bio_Hazard_2_Proto_Script_Bytecode_Size[Opcode]), &OpPeek, sizeof(unsigned char));

		// Bytecode Size
		switch (Opcode)
		{
		case 0x00: {
			if (!OpPeek) {
				if (Else_ck.size()) { Else_ck.pop_back(); }
				if (Ifel_ck.size()) { Ifel_ck.pop_back(); }
				Pointer++;
				Scan->Pointer.push_back(Pointer);
				Scan->Opcode.push_back(Opcode);
			}
		} break;
		case 0x01: {
			if (!Ifel_ck.size() && !Else_ck.size()) {
				Pointer += Bio_Hazard_2_Proto_Script_Bytecode_Size[Opcode];
				Scan->Size = (Pointer - _Offset);
				return Scan->Size;
			}
		} break;
		case 0x06: {
			tagBio2BytecodeP::tagIfel_ck Data = { NULL };
			Read(BINARY, Pointer, &Data, sizeof(tagBio2BytecodeP::tagIfel_ck));
			Ifel_ck.push_back(Data);
		} break;
		case 0x07: {
			tagBio2BytecodeP::tagElse_ck Data = { NULL };
			Read(BINARY, Pointer, &Data, sizeof(tagBio2BytecodeP::tagElse_ck));
			Else_ck.push_back(Data);
		} break;
		case 0x08: {
			if (Ifel_ck.size()) { Ifel_ck.pop_back(); }
		} break;
		case 0x2C: {
			Read(BINARY, Pointer, &Scd15->Aot_set, sizeof(tagBio2BytecodeP::tagAot_set));
			if (Scd15->Aot_set.SAT & 0x80) {
				Scan->Opcode.pop_back();
				Opcode = 0x67;
				Scan->Opcode.push_back(Opcode);
			}
		} break;
		/*case 0x3B: {
			Read(BINARY, Pointer, &Scd15->Door_aot_set, sizeof(tagBio2BytecodeP::tagDoor_aot_set));
			if (Scd15->Door_aot_set.SAT & 0x80) {
				Scan->Opcode.pop_back();
				Opcode = 0x68;
				Scan->Opcode.push_back(Opcode);
			}
		} break;*/
		case 0x50: {
			Read(BINARY, Pointer, &Scd15->Item_aot_set, sizeof(tagBio2BytecodeP::tagItem_aot_set));
			if (Scd15->Item_aot_set.SAT & 0x80) {
				Scan->Opcode.pop_back();
				Opcode = 0x69;
				Scan->Opcode.push_back(Opcode);
			}
		} break;
		}

		// Complete
		Pointer += Bio_Hazard_2_Proto_Script_Bytecode_Size[Opcode];
	}

	// 
	delete[] Scd15;
	delete[] Scd;

	// Terminate
	return NULL;
}
ULONG Bio_Hazard_2_Script::InitScanProto(CONST CHAR * _FileName, ...) {

	// _FileName
	va_list _ArgList = { NULL };
	__crt_va_start(_ArgList, _FileName);
	_StrLen = (_vscprintf(_FileName, _ArgList) + 2);
	CHAR * FileName = new CHAR[(_StrLen * 2)];
	RtlSecureZeroMemory(FileName, (_StrLen * 2));
	vsprintf_s(FileName, _StrLen, _FileName, _ArgList);
	__crt_va_end(_ArgList);

	// Error
	if (!Exists(FileName)) { delete[] FileName; return NULL; }

	// Open
	CHAR * Directory = GetDirectory(FileName);
	CHAR * NameBase = GetNamebase(FileName);
	_iobuf * _File = Open(READ_FILE, FileName);
	_iobuf * Log = Open(CREATE_FILE, "%s\\%s.log", Directory, NameBase);

	// Work
	ULONG Size = InitScanProto(_File, 0x00);
	Print(Log, (CHAR*)"// %s\r\n// %d opcodes\r\n", FileName, Scan->Opcode.size());
	if (Size) {
		for (ULONG n = 0; n < Scan->Opcode.size(); n++) {
			Print(Log, (CHAR*)"// [%02X] [%08X]\r\n", Scan->Opcode[n], Scan->Pointer[n]);
		}
	}

	// Cleanup
	delete[] NameBase;
	delete[] Directory;
	delete[] FileName;
	fclose(Log);
	fclose(_File);

	// Terminate
	return Size;
}
UCHAR Bio_Hazard_2_Script::GetSceTypeProto(ULONG Value) {
	switch (Value)
	{
	case SCE_NOTHING_P:
		return SCE_NOTHING;
	case SCE_MESSAGE_P:
		return SCE_MESSAGE;
	case SCE_DOOR_P:
		return SCE_DOOR;
	case SCE_EVENT_P:
		return SCE_EVENT;
	case SCE_FLAG_CHG_P:
		return SCE_FLAG_CHG;
	case SCE_NORMAL_P:
		return SCE_NORMAL;
	case SCE_STATUS_P:
		return SCE_STATUS;
	case SCE_WATER_P:
		return SCE_WATER;
	case SCE_ITEM_P:
		return SCE_ITEM;
	case SCE_DAMAGE_P:
		return SCE_DAMAGE;
	case SCE_MOVE_P:
		return SCE_MOVE;
	}
	return SCE_NOTHING;
}
ULONG Bio_Hazard_2_Script::RoomProto(CONST CHAR * _FileName, ...) {

	// _FileName
	va_list _ArgList = { NULL };
	__crt_va_start(_ArgList, _FileName);
	_StrLen = (_vscprintf(_FileName, _ArgList) + 2);
	CHAR * FileName = new CHAR[(_StrLen * 2)];
	RtlSecureZeroMemory(FileName, (_StrLen * 2));
	vsprintf_s(FileName, _StrLen, _FileName, _ArgList);
	__crt_va_end(_ArgList);

	// Error
	if (!Exists(FileName)) { delete[] FileName; return NULL; }

	// Open
	_iobuf * _File = Open(READ_FILE, FileName);
	if (!_File) {
		delete[] FileName;
		return NULL;
	}
	CHAR * Directory = GetDirectory(FileName);
	CHAR * NameBase = GetNamebase(FileName);

	// Log
	_iobuf * Log = Open(CREATE_FILE, "%s\\%s\\%s.log", Directory, NameBase, NameBase);
	Print(Log, (CHAR*)"// %s\r\n", FileName);

	// Header
	Bio2RoomProto * Rdt = new tagBio2RoomProto;
	RtlSecureZeroMemory(Rdt, sizeof(tagBio2RoomProto));
	Read(_File, 0x00, Rdt, sizeof(tagBio2RoomProto));

	// Main
	USHORT nScd = NULL;
	ULONG _Offset = NULL;
	ULONG Pointer = NULL;
	ULONG _ElementSize = NULL;
	if (Rdt->pScdx) {
		Read(_File, Rdt->pScdx, &nScd, sizeof(unsigned short int));
		nScd /= sizeof(unsigned short int);
		Pointer = Rdt->pScdx;
		Print(Log, (CHAR*)"// %d scripts\r\n", nScd);
		for (USHORT n = 0; n < nScd; n++, Pointer += sizeof(unsigned short int))
		{
			_Offset = NULL;
			Read(_File, Pointer, &_Offset, sizeof(unsigned short int));
			if (_Offset) {
				_Offset += Rdt->pScdx;
				_ElementSize = InitScanProto(_File, _Offset);
				Print(Log, (CHAR*)"[%08X] %d opcodes, Size: 0x%X bytes\r\n", _Offset, Scan->Opcode.size(), _ElementSize);
				CreateFromSource(_File, _Offset, _ElementSize, "%s\\%s\\main%02d.scd", Directory, NameBase, n);
				UpdatePrototype("%s\\%s\\main%02d.scd", Directory, NameBase, n);
			}
		}
	}

	// Sub
	nScd = NULL;
	_Offset = NULL;
	Pointer = NULL;
	_ElementSize = NULL;
	if (Rdt->pScd) {
		Read(_File, Rdt->pScd, &nScd, sizeof(unsigned short int));
		nScd /= sizeof(unsigned short int);
		Pointer = Rdt->pScd;
		Print(Log, (CHAR*)"// %d scripts\r\n", nScd);
		for (USHORT n = 0; n < nScd; n++, Pointer += sizeof(unsigned short int))
		{
			_Offset = NULL;
			Read(_File, Pointer, &_Offset, sizeof(unsigned short int));
			if (_Offset) {
				_Offset += Rdt->pScd;
				_ElementSize = InitScanProto(_File, _Offset);
				Print(Log, (CHAR*)"[%08X] %d opcodes, Size: 0x%X bytes\r\n", _Offset, Scan->Opcode.size(), _ElementSize);
				CreateFromSource(_File, _Offset, _ElementSize, "%s\\%s\\sub%02d.scd", Directory, NameBase, n);
				UpdatePrototype("%s\\%s\\sub%02d.scd", Directory, NameBase, n);
			}
		}
	}

	// Ex
	nScd = NULL;
	_Offset = NULL;
	Pointer = NULL;
	_ElementSize = NULL;
	if (Rdt->pScdOld) {
		Read(_File, Rdt->pScdOld, &nScd, sizeof(unsigned short int));
		nScd /= sizeof(unsigned short int);
		Pointer = Rdt->pScdOld;
		Print(Log, (CHAR*)"// %d scripts\r\n", nScd);
		for (USHORT n = 0; n < nScd; n++, Pointer += sizeof(unsigned short int))
		{
			_Offset = NULL;
			Read(_File, Pointer, &_Offset, sizeof(unsigned short int));
			if (_Offset) {
				_Offset += Rdt->pScdOld;
				_ElementSize = InitScanProto(_File, _Offset);
				Print(Log, (CHAR*)"[%08X] %d opcodes, Size: 0x%X bytes\r\n", _Offset, Scan->Opcode.size(), _ElementSize);
				CreateFromSource(_File, _Offset, _ElementSize, "%s\\%s\\ex%02d.scd", Directory, NameBase, n);
				UpdatePrototype("%s\\%s\\ex%02d.scd", Directory, NameBase, n);
			}
		}
	}

	// Cleanup
	delete[] NameBase;
	delete[] Directory;
	delete[] FileName;
	delete Rdt;
	fclose(Log);
	fclose(_File);

	// Terminate
	return NULL;
}
BOOL Bio_Hazard_2_Script::UpdatePrototype(CONST CHAR * _FileName, ...) {

	// _FileName
	va_list _ArgList = { NULL };
	__crt_va_start(_ArgList, _FileName);
	_StrLen = (_vscprintf(_FileName, _ArgList) + 2);
	CHAR * FileName = new CHAR[(_StrLen * 2)];
	RtlSecureZeroMemory(FileName, (_StrLen * 2));
	vsprintf_s(FileName, _StrLen, _FileName, _ArgList);
	__crt_va_end(_ArgList);

	// Error
	if (!Exists(FileName)) { delete[] FileName; return NULL; }

	// Open
	_iobuf * _File = Open(READ_FILE, FileName);
	if (!_File) {
		delete[] FileName;
		return NULL;
	}
	CHAR * Directory = GetDirectory(FileName);
	CHAR * NameBase = GetNamebase(FileName);
	ULONG _ElementSize = Size(_File);

	// Output
	_iobuf * Output = Open(CREATE_FILE, (CHAR*)"%s\\_%s.scd", Directory, NameBase);
	if (!Output) {
		delete[] NameBase;
		delete[] Directory;
		delete[] FileName;
		fclose(_File);
		return NULL;
	}

	// Bio15 -> Bio2
	Scd = new tagBio2Bytecode;
	Scd15 = new tagBio2BytecodeP;
	InitScanProto(FileName);
	ULONG _Offset = NULL;	// Bio1.5
	ULONG Pointer = NULL;	// Bio2
	BOOL ValidOpcode = NO;
	BOOL UpdateOffset = YES;
	for (ULONG n = 0; n < _ElementSize; n++)
	{
		// Complete
		if (feof(_File)) { break; }
		if (_Offset >= _ElementSize) { break; }

		// Flag
		ValidOpcode = NO;
		UpdateOffset = YES;

		// Opcode
		Read(_File, _Offset, &Scd15->Opcode, 1);
		switch (Scd15->Opcode)
		{
		case 0x00:	// Nop
			ValidOpcode = YES;
			Read(_File, _Offset, &Scd15->Nop, sizeof(tagBio2BytecodeP::tagNop));
			Scd->Nop.Opcode = Scd->Opcode = 0x00;
			Write(Output, Pointer, &Scd->Nop, sizeof(tagBio2Bytecode::tagNop));
		break;
		case 0x01:	// Evt_end
			ValidOpcode = YES;
			Read(_File, _Offset, &Scd15->Evt_end, sizeof(tagBio2BytecodeP::tagEvt_end));
			Scd->Evt_end.Opcode = Scd->Opcode = 0x01;
			Scd->Evt_end.zAlign = NULL;
			Write(Output, Pointer, &Scd->Evt_end, sizeof(tagBio2Bytecode::tagEvt_end));
		break;
		case 0x02:	// Evt_next
			ValidOpcode = YES;
			Read(_File, _Offset, &Scd15->Evt_next, sizeof(tagBio2BytecodeP::tagEvt_next));
			Scd->Evt_next.Opcode = Scd->Opcode = 0x02;
			Write(Output, Pointer, &Scd->Evt_next, sizeof(tagBio2Bytecode::tagEvt_next));
		break;
		case 0x03:	// Evt_chain
			ValidOpcode = YES;
			Read(_File, _Offset, &Scd15->Evt_chain, sizeof(tagBio2BytecodeP::tagEvt_chain));
			Scd->Evt_chain.Opcode = Scd->Opcode = 0x03;
			Scd->Evt_chain.Id = Scd15->Evt_chain.Id;
			Write(Output, Pointer, &Scd->Evt_chain, sizeof(tagBio2Bytecode::tagEvt_chain));
		break;
		case 0x04:	// Evt_exec
			ValidOpcode = YES;
			Read(_File, _Offset, &Scd15->Evt_exec, sizeof(tagBio2BytecodeP::tagEvt_exec));
			Scd->Evt_exec.Opcode = Scd->Opcode = 0x04;
			Scd->Evt_exec.data1 = Scd15->Evt_exec.data1;
			Scd->Evt_exec.Gosub = Scd15->Evt_exec.Gosub;
			Scd->Evt_exec.ScdId = Scd15->Evt_exec.ScdId;
			Write(Output, Pointer, &Scd->Evt_exec, sizeof(tagBio2Bytecode::tagEvt_exec));
		break;
		case 0x05:	// Evt_kill
			ValidOpcode = YES;
			Read(_File, _Offset, &Scd15->Evt_kill, sizeof(tagBio2BytecodeP::tagEvt_kill));
			Scd->Evt_kill.Opcode = Scd->Opcode = 0x05;
			Scd->Evt_kill.Id = Scd15->Evt_kill.Id;
			Write(Output, Pointer, &Scd->Evt_kill, sizeof(tagBio2Bytecode::tagEvt_kill));
		break;
		case 0x06:	// Ifel_ck
			ValidOpcode = YES;
			Read(_File, _Offset, &Scd15->Ifel_ck, sizeof(tagBio2BytecodeP::tagIfel_ck));
			Scd->Ifel_ck.Opcode = Scd->Opcode = 0x06;
			Scd->Ifel_ck.zAlign = NULL;
			Scd->Ifel_ck.Size = Scd15->Ifel_ck.Size;
			Write(Output, Pointer, &Scd->Ifel_ck, sizeof(tagBio2Bytecode::tagIfel_ck));
		break;
		case 0x07:	// Else_ck
			ValidOpcode = YES;
			Read(_File, _Offset, &Scd15->Else_ck, sizeof(tagBio2BytecodeP::tagElse_ck));
			Scd->Else_ck.Opcode = Scd->Opcode = 0x07;
			Scd->Else_ck.zAlign = NULL;
			Scd->Else_ck.Size = Scd15->Else_ck.Size;
			Write(Output, Pointer, &Scd->Else_ck, sizeof(tagBio2Bytecode::tagElse_ck));
		break;
		case 0x08:	// Endif
			ValidOpcode = YES;
			Read(_File, _Offset, &Scd15->Endif, sizeof(tagBio2BytecodeP::tagEndif));
			Scd->Endif.Opcode = Scd->Opcode = 0x08;
			Scd->Endif.zAlign = NULL;
			Write(Output, Pointer, &Scd->Endif, sizeof(tagBio2Bytecode::tagEndif));
		break;
		case 0x09:	// Sleep
			ValidOpcode = YES;
			Read(_File, _Offset, &Scd15->Sleep, sizeof(tagBio2BytecodeP::tagSleep));
			Scd->Sleep.Opcode = Scd->Opcode = 0x09;
			Scd->Sleep.Sleeping = 0x0A;
			Scd->Sleep.Count = Scd15->Sleep.Count;
			Write(Output, Pointer, &Scd->Sleep, sizeof(tagBio2Bytecode::tagSleep));
		break;
		case 0x0A:	// Sleeping
			ValidOpcode = YES;
			Read(_File, _Offset, &Scd15->Sleeping, sizeof(tagBio2BytecodeP::tagSleeping));
			Scd->Sleeping.Opcode = Scd->Opcode = 0x0A;
			Scd->Sleeping.Count = Scd15->Sleeping.Count;
			Write(Output, Pointer, &Scd->Sleeping, sizeof(tagBio2Bytecode::tagSleeping));
		break;
		case 0x0B:	// Wsleep
			ValidOpcode = YES;
			Read(_File, _Offset, &Scd15->Wsleep, sizeof(tagBio2BytecodeP::tagWsleep));
			Scd->Wsleep.Opcode = Scd->Opcode = 0x0B;
			Write(Output, Pointer, &Scd->Wsleep, sizeof(tagBio2Bytecode::tagWsleep));
		break;
		case 0x0C:	// Wsleeping
			ValidOpcode = YES;
			Read(_File, _Offset, &Scd15->Wsleeping, sizeof(tagBio2BytecodeP::tagWsleeping));
			Scd->Wsleeping.Opcode = Scd->Opcode = 0x0C;
			Write(Output, Pointer, &Scd->Wsleeping, sizeof(tagBio2Bytecode::tagWsleeping));
		break;
		case 0x0D:	// For
			ValidOpcode = YES;
			Read(_File, _Offset, &Scd15->For, sizeof(tagBio2BytecodeP::tagFor));
			Scd->For.Opcode = Scd->Opcode = 0x0D;
			Scd->For.zAlign = NULL;
			Scd->For.Size = Scd15->For.Size;
			Scd->For.Count = Scd15->For.Count;
			Write(Output, Pointer, &Scd->For, sizeof(tagBio2Bytecode::tagFor));
		break;
		case 0x0E:	// Next
			ValidOpcode = YES;
			Read(_File, _Offset, &Scd15->Next, sizeof(tagBio2BytecodeP::tagNext));
			Scd->Next.Opcode = Scd->Opcode = 0x0E;
			Scd->Next.zAlign = NULL;
			Write(Output, Pointer, &Scd->Next, sizeof(tagBio2Bytecode::tagNext));
		break;
		case 0x0F:	// While
			ValidOpcode = YES;
			Read(_File, _Offset, &Scd15->While, sizeof(tagBio2BytecodeP::tagWhile));
			Scd->While.Opcode = Scd->Opcode = 0x0F;
			Scd->While.Num = Scd15->While.Num;
			Scd->While.Size = Scd15->While.Size;
			Write(Output, Pointer, &Scd->While, sizeof(tagBio2Bytecode::tagWhile));
		break;
		case 0x10:	// Ewhile
			ValidOpcode = YES;
			Read(_File, _Offset, &Scd15->Ewhile, sizeof(tagBio2BytecodeP::tagEwhile));
			Scd->Ewhile.Opcode = Scd->Opcode = 0x10;
			Scd->Ewhile.zAlign = NULL;
			Write(Output, Pointer, &Scd->Ewhile, sizeof(tagBio2Bytecode::tagEwhile));
		break;
		case 0x11:	// Do
			ValidOpcode = YES;
			Read(_File, _Offset, &Scd15->Do, sizeof(tagBio2BytecodeP::tagDo));
			Scd->Do.Opcode = Scd->Opcode = 0x11;
			Scd->Do.Num = Scd15->Do.Num;
			Scd->Do.Size = Scd15->Do.Size;
			Write(Output, Pointer, &Scd->Do, sizeof(tagBio2Bytecode::tagDo));
		break;
		case 0x12:	// Edwhile
			ValidOpcode = YES;
			Read(_File, _Offset, &Scd15->Edwhile, sizeof(tagBio2BytecodeP::tagEdwhile));
			Scd->Edwhile.Opcode = Scd->Opcode = 0x12;
			Scd->Edwhile.Size = Scd15->Edwhile.Size;
			Write(Output, Pointer, &Scd->Edwhile, sizeof(tagBio2Bytecode::tagEdwhile));
		break;
		case 0x13:	// Switch
			ValidOpcode = YES;
			Read(_File, _Offset, &Scd15->Switch, sizeof(tagBio2BytecodeP::tagSwitch));
			Scd->Switch.Opcode = Scd->Opcode = 0x13;
			Scd->Switch.Value = Scd15->Switch.Value;
			Scd->Switch.Size = Scd15->Switch.Size;
			Write(Output, Pointer, &Scd->Switch, sizeof(tagBio2Bytecode::tagSwitch));
		break;
		case 0x14:	// Case
			ValidOpcode = YES;
			Read(_File, _Offset, &Scd15->Case, sizeof(tagBio2BytecodeP::tagCase));
			Scd->Case.Opcode = Scd->Opcode = 0x14;
			Scd->Case.zAlign = NULL;
			Scd->Case.Size = Scd15->Case.Size;
			Scd->Case.Value = Scd15->Case.Value;
			Write(Output, Pointer, &Scd->Case, sizeof(tagBio2Bytecode::tagCase));
		break;
		case 0x15:	// Default
			ValidOpcode = YES;
			Read(_File, _Offset, &Scd15->Default, sizeof(tagBio2BytecodeP::tagDefault));
			Scd->Default.Opcode = Scd->Opcode = 0x15;
			Scd->Default.zAlign = NULL;
			Write(Output, Pointer, &Scd->Default, sizeof(tagBio2Bytecode::tagDefault));
		break;
		case 0x16:	// Eswitch
			ValidOpcode = YES;
			Read(_File, _Offset, &Scd15->Eswitch, sizeof(tagBio2BytecodeP::tagEswitch));
			Scd->Eswitch.Opcode = Scd->Opcode = 0x16;
			Scd->Eswitch.zAlign = NULL;
			Write(Output, Pointer, &Scd->Eswitch, sizeof(tagBio2Bytecode::tagEswitch));
		break;
		case 0x17:	// Goto
			ValidOpcode = YES;
			Read(_File, _Offset, &Scd15->Goto, sizeof(tagBio2BytecodeP::tagGoto));
			Scd->Goto.Opcode = Scd->Opcode = 0x17;
			Scd->Goto.Ifel_ctr = Scd15->Goto.Ifel_ctr;
			Scd->Goto.Loop_ctr = Scd15->Goto.Loop_ctr;
			Scd->Goto.zAlign = NULL;
			Scd->Goto.Offset = Scd15->Goto.Offset;
			Write(Output, Pointer, &Scd->Goto, sizeof(tagBio2Bytecode::tagGoto));
		break;
		case 0x18:	// Gosub
			ValidOpcode = YES;
			Read(_File, _Offset, &Scd15->Gosub, sizeof(tagBio2BytecodeP::tagGosub));
			Scd->Gosub.Opcode = Scd->Opcode = 0x18;
			Scd->Gosub.SCD = Scd15->Gosub.SCD;
			Write(Output, Pointer, &Scd->Gosub, sizeof(tagBio2Bytecode::tagGosub));
		break;
		case 0x19:	// Return
			ValidOpcode = YES;
			Read(_File, _Offset, &Scd15->Return, sizeof(tagBio2BytecodeP::tagReturn));
			Scd->Return.Opcode = Scd->Opcode = 0x19;
			Scd->Return.zAlign = NULL;
			Write(Output, Pointer, &Scd->Return, sizeof(tagBio2Bytecode::tagReturn));
		break;
		case 0x1A:	// Break
			ValidOpcode = YES;
			Read(_File, _Offset, &Scd15->Break, sizeof(tagBio2BytecodeP::tagBreak));
			Scd->Break.Opcode = Scd->Opcode = 0x1A;
			Scd->Break.zAlign = NULL;
			Write(Output, Pointer, &Scd->Break, sizeof(tagBio2Bytecode::tagBreak));
		break;
		case 0x1B:	// For2
			ValidOpcode = YES;
			Read(_File, _Offset, &Scd15->For2, sizeof(tagBio2BytecodeP::tagFor2));
			Scd->For2.Opcode = Scd->Opcode = 0x1B;
			Scd->For2.zAlign = NULL;
			Scd->For2.data0 = Scd15->For2.data0;
			Scd->For2.data1 = Scd15->For2.data1;
			Scd->For2.data2 = Scd15->For2.data2;
			Write(Output, Pointer, &Scd->For2, sizeof(tagBio2Bytecode::tagFor2));
		break;
		case 0x1C:	// Break_point
			ValidOpcode = YES;
			Read(_File, _Offset, &Scd15->Break_point, sizeof(tagBio2BytecodeP::tagBreak_point));
			Scd->Break_point.Opcode = Scd->Opcode = 0x1C;
			Write(Output, Pointer, &Scd->Break_point, sizeof(tagBio2Bytecode::tagBreak_point));
		break;
		case 0x1D:	// Nop
			ValidOpcode = YES;
			Read(_File, _Offset, &Scd15->Nop, sizeof(tagBio2BytecodeP::tagNop));
			Scd->Nop.Opcode = Scd->Opcode = 0x1E;	// DO NOT MODIFY
			Write(Output, Pointer, &Scd->Nop, sizeof(tagBio2Bytecode::tagNop));
		break;
		case 0x1E:	// Nop
			ValidOpcode = YES;
			Read(_File, _Offset, &Scd15->Nop, sizeof(tagBio2BytecodeP::tagNop));
			Scd->Nop.Opcode = Scd->Opcode = 0x1E;
			Write(Output, Pointer, &Scd->Nop, sizeof(tagBio2Bytecode::tagNop));
		break;
		case 0x1F:	// Nop
			ValidOpcode = YES;
			Read(_File, _Offset, &Scd15->Nop, sizeof(tagBio2BytecodeP::tagNop));
			Scd->Nop.Opcode = Scd->Opcode = 0x1F;
			Write(Output, Pointer, &Scd->Nop, sizeof(tagBio2Bytecode::tagNop));
		break;
		case 0x20:	// Nop
			ValidOpcode = YES;
			Read(_File, _Offset, &Scd15->Nop, sizeof(tagBio2BytecodeP::tagNop));
			Scd->Nop.Opcode = Scd->Opcode = 0x20;
			Write(Output, Pointer, &Scd->Nop, sizeof(tagBio2Bytecode::tagNop));
		break;
		case 0x21:	// Ck
			ValidOpcode = YES;
			Read(_File, _Offset, &Scd15->Ck, sizeof(tagBio2BytecodeP::tagCk));
			Scd->Ck.Opcode = Scd->Opcode = 0x21;
			Scd->Ck.Flag = Scd15->Ck.Flag;
			Scd->Ck.Id = Scd15->Ck.Id;
			Scd->Ck.OnOff = Scd15->Ck.OnOff;
			Write(Output, Pointer, &Scd->Ck, sizeof(tagBio2Bytecode::tagCk));
		break;
		case 0x22:	// Set
			ValidOpcode = YES;
			Read(_File, _Offset, &Scd15->Set, sizeof(tagBio2BytecodeP::tagSet));
			Scd->Set.Opcode = Scd->Opcode = 0x22;
			Scd->Set.Flag = Scd15->Set.Flag;
			Scd->Set.Id = Scd15->Set.Id;
			Scd->Set.OnOff = Scd15->Set.OnOff;
			Write(Output, Pointer, &Scd->Set, sizeof(tagBio2Bytecode::tagSet));
		break;
		case 0x23:	// Cmp
			ValidOpcode = YES;
			Read(_File, _Offset, &Scd15->Cmp, sizeof(tagBio2BytecodeP::tagCmp));
			Scd->Cmp.Opcode = Scd->Opcode = 0x23;
			Scd->Cmp.zAlign = NULL;
			Scd->Cmp.Flag = Scd15->Cmp.Flag;
			Scd->Cmp.Operator = Scd15->Cmp.Operator;
			Scd->Cmp.Value = Scd15->Cmp.Value;
			Write(Output, Pointer, &Scd->Cmp, sizeof(tagBio2Bytecode::tagCmp));
		break;
		case 0x24:	// Save
			ValidOpcode = YES;
			Read(_File, _Offset, &Scd15->Save, sizeof(tagBio2BytecodeP::tagSave));
			Scd->Save.Opcode = Scd->Opcode = 0x24;
			Scd->Save.Destination = Scd15->Save.Destination;
			Scd->Save.Source = Scd15->Save.Source;
			Write(Output, Pointer, &Scd->Save, sizeof(tagBio2Bytecode::tagSave));
		break;
		case 0x25:	// Copy
			ValidOpcode = YES;
			Read(_File, _Offset, &Scd15->Copy, sizeof(tagBio2BytecodeP::tagCopy));
			Scd->Copy.Opcode = Scd->Opcode = 0x25;
			Scd->Copy.Destination = Scd15->Copy.Destination;
			Scd->Copy.Source = Scd15->Copy.Source;
			Write(Output, Pointer, &Scd->Copy, sizeof(tagBio2Bytecode::tagCopy));
		break;
		case 0x26:	// Calc
			ValidOpcode = YES;
			Read(_File, _Offset, &Scd15->Calc, sizeof(tagBio2BytecodeP::tagCalc));
			Scd->Calc.Opcode = Scd->Opcode = 0x26;
			Scd->Calc.zAlign = NULL;
			Scd->Calc.Operator = Scd15->Calc.Operator;
			Scd->Calc.Flag = Scd15->Calc.Flag;
			Scd->Calc.Value = Scd15->Calc.Value;
			Write(Output, Pointer, &Scd->Calc, sizeof(tagBio2Bytecode::tagCalc));
		break;
		case 0x27:	// Calc2
			ValidOpcode = YES;
			Read(_File, _Offset, &Scd15->Calc2, sizeof(tagBio2BytecodeP::tagCalc2));
			Scd->Calc2.Opcode = Scd->Opcode = 0x27;
			Scd->Calc2.Operator = Scd15->Calc2.Operator;
			Scd->Calc2.Flag = Scd15->Calc2.Flag;
			Scd->Calc2.Value = Scd15->Calc2.Value;
			Write(Output, Pointer, &Scd->Calc2, sizeof(tagBio2Bytecode::tagCalc2));
		break;
		case 0x28:	// Sce_rnd
			ValidOpcode = YES;
			Read(_File, _Offset, &Scd15->Sce_rnd, sizeof(tagBio2BytecodeP::tagSce_rnd));
			Scd->Sce_rnd.Opcode = Scd->Opcode = 0x28;
			Write(Output, Pointer, &Scd->Sce_rnd, sizeof(tagBio2Bytecode::tagSce_rnd));
		break;
		case 0x29:	// Cut_chg
			ValidOpcode = YES;
			Read(_File, _Offset, &Scd15->Cut_chg, sizeof(tagBio2BytecodeP::tagCut_chg));
			Scd->Cut_chg.Opcode = Scd->Opcode = 0x29;
			Scd->Cut_chg.nCut = Scd15->Cut_chg.nCut;
			Write(Output, Pointer, &Scd->Cut_chg, sizeof(tagBio2Bytecode::tagCut_chg));
		break;
		case 0x2A:	// Cut_old
			ValidOpcode = YES;
			Read(_File, _Offset, &Scd15->Cut_old, sizeof(tagBio2BytecodeP::tagCut_old));
			Scd->Cut_old.Opcode = Scd->Opcode = 0x2A;
			Write(Output, Pointer, &Scd->Cut_old, sizeof(tagBio2Bytecode::tagCut_old));
		break;
		case 0x2B:	// Message_on
			ValidOpcode = YES;
			Read(_File, _Offset, &Scd15->Message_on, sizeof(tagBio2BytecodeP::tagMessage_on));
			Scd->Message_on.Opcode = Scd->Opcode = 0x2B;
			Scd->Message_on.zAlign = NULL;
			Scd->Message_on.data0 = Scd15->Message_on.data1;
			Scd->Message_on.data1 = NULL;
			Scd->Message_on.data2 = Scd15->Message_on.data2;
			Write(Output, Pointer, &Scd->Message_on, sizeof(tagBio2Bytecode::tagMessage_on));
		break;
		case 0x2C:	// Aot_set
			ValidOpcode = YES;
			UpdateOffset = NO;
			Read(_File, _Offset, &Scd15->Aot_set, sizeof(tagBio2BytecodeP::tagAot_set));
			if (Scd15->Aot_set.SAT & 0x80) {	// 4P
				Read(_File, _Offset, &Scd15->Aot_set_4p, sizeof(tagBio2BytecodeP::tagAot_set_4p));
				Scd->Aot_set_4p.Opcode = Scd->Opcode = 0x67; // DO NOT CHANGE
				Scd->Aot_set_4p.Aot = Scd15->Aot_set_4p.Aot;
				Scd->Aot_set_4p.SCE = GetSceTypeProto(Scd15->Aot_set_4p.SCE);
				Scd->Aot_set_4p.SAT = Scd15->Aot_set_4p.SAT;
				Scd->Aot_set_4p.nFloor = Scd15->Aot_set_4p.nFloor;
				Scd->Aot_set_4p.Super = Scd15->Aot_set_4p.Super;
				Scd->Aot_set_4p.X0 = Scd15->Aot_set_4p.X0;
				Scd->Aot_set_4p.Z0 = Scd15->Aot_set_4p.Z0;
				Scd->Aot_set_4p.X1 = Scd15->Aot_set_4p.X1;
				Scd->Aot_set_4p.Z1 = Scd15->Aot_set_4p.Z1;
				Scd->Aot_set_4p.X2 = Scd15->Aot_set_4p.X2;
				Scd->Aot_set_4p.Z2 = Scd15->Aot_set_4p.Z2;
				Scd->Aot_set_4p.X3 = Scd15->Aot_set_4p.X3;
				Scd->Aot_set_4p.Z3 = Scd15->Aot_set_4p.Z3;
				Scd->Aot_set_4p.Data0 = Scd15->Aot_set_4p.data0;
				Scd->Aot_set_4p.Data1 = Scd15->Aot_set_4p.data1;
				Scd->Aot_set_4p.Data2 = Scd15->Aot_set_4p.data2;
				Write(Output, Pointer, &Scd->Aot_set_4p, sizeof(tagBio2Bytecode::tagAot_set_4p));
				_Offset += sizeof(tagBio2Bytecode::tagAot_set_4p);
			} else {	// STANDARD
				Scd->Aot_set.Opcode = Scd->Opcode = 0x2C;
				Scd->Aot_set.Aot = Scd15->Aot_set.Aot;
				Scd->Aot_set.SCE = GetSceTypeProto(Scd15->Aot_set.SCE);
				Scd->Aot_set.SAT = Scd15->Aot_set.SAT;
				Scd->Aot_set.nFloor = Scd15->Aot_set.nFloor;
				Scd->Aot_set.Super = Scd15->Aot_set.Super;
				Scd->Aot_set.X = Scd15->Aot_set.X;
				Scd->Aot_set.Z = Scd15->Aot_set.Z;
				Scd->Aot_set.W = Scd15->Aot_set.W;
				Scd->Aot_set.D = Scd15->Aot_set.D;
				Scd->Aot_set.Data0 = Scd15->Aot_set.Data0;
				Scd->Aot_set.Data1 = Scd15->Aot_set.Data1;
				Scd->Aot_set.Data2 = Scd15->Aot_set.Data2;
				Write(Output, Pointer, &Scd->Aot_set, sizeof(tagBio2Bytecode::tagAot_set));
				_Offset += sizeof(tagBio2Bytecode::tagAot_set);
			}
		break;
		case 0x2D:	// Obj_model_set	// WORK IN PROGRESS
			ValidOpcode = YES;
			Read(_File, _Offset, &Scd15->Obj_model_set, sizeof(tagBio2BytecodeP::tagObj_model_set));
			Scd->Obj_model_set.Opcode = Scd->Opcode = 0x2D;
			Scd->Obj_model_set.MD1 = Scd15->Obj_model_set.MD1;
			Scd->Obj_model_set.Id = Scd15->Obj_model_set.Id;
			Scd->Obj_model_set.Ccol_old = NULL;
			Scd->Obj_model_set.Ccol_no = NULL;
			Scd->Obj_model_set.Ctex_old = NULL;
			Scd->Obj_model_set.nFloor = Scd15->Obj_model_set.nFloor;
			Scd->Obj_model_set.Super = Scd15->Obj_model_set.Super;
			Scd->Obj_model_set.Type = Scd15->Obj_model_set.Type;
			Scd->Obj_model_set.BeFlag = Scd15->Obj_model_set.BeFlag;
			Scd->Obj_model_set.Attribute = Scd15->Obj_model_set.Attribute;
			Scd->Obj_model_set.X = Scd15->Obj_model_set.X;
			Scd->Obj_model_set.Y = Scd15->Obj_model_set.Y;
			Scd->Obj_model_set.Z = Scd15->Obj_model_set.Z;
			Scd->Obj_model_set.DirX = Scd15->Obj_model_set.DirX;
			Scd->Obj_model_set.DirY = Scd15->Obj_model_set.DirY;
			Scd->Obj_model_set.DirZ = Scd15->Obj_model_set.DirZ;
			Scd->Obj_model_set.AtariOffsetX = Scd15->Obj_model_set.AtariOffsetX;
			Scd->Obj_model_set.AtariOffsetY = Scd15->Obj_model_set.AtariOffsetY;
			Scd->Obj_model_set.AtariOffsetZ = Scd15->Obj_model_set.AtariOffsetZ;
			Scd->Obj_model_set.AtariSizeX = Scd15->Obj_model_set.AtariSizeX;
			Scd->Obj_model_set.AtariSizeY = Scd15->Obj_model_set.AtariSizeY;
			Scd->Obj_model_set.AtariSizeZ = Scd15->Obj_model_set.AtariSizeZ;
			Write(Output, Pointer, &Scd->Obj_model_set, sizeof(tagBio2Bytecode::tagObj_model_set));
		break;
		case 0x2E:	// Work_set
			ValidOpcode = YES;
			Read(_File, _Offset, &Scd15->Work_set, sizeof(tagBio2BytecodeP::tagWork_set));
			Scd->Work_set.Opcode = Scd->Opcode = 0x2E;
			Scd->Work_set.Type = Scd15->Work_set.Type;
			Scd->Work_set.Aot = Scd15->Work_set.Aot;
			Write(Output, Pointer, &Scd->Work_set, sizeof(tagBio2Bytecode::tagWork_set));
		break;
		case 0x2F:	// Speed_set
			ValidOpcode = YES;
			Read(_File, _Offset, &Scd15->Speed_set, sizeof(tagBio2BytecodeP::tagSpeed_set));
			Scd->Speed_set.Opcode = Scd->Opcode = 0x2F;
			Scd->Speed_set.Id = Scd15->Speed_set.Id;
			Scd->Speed_set.Value = Scd15->Speed_set.Value;
			Write(Output, Pointer, &Scd->Speed_set, sizeof(tagBio2Bytecode::tagSpeed_set));
		break;
		case 0x30:	// Add_speed
			ValidOpcode = YES;
			Read(_File, _Offset, &Scd15->Add_speed, sizeof(tagBio2BytecodeP::tagAdd_speed));
			Scd->Add_speed.Opcode = Scd->Opcode = 0x30;
			Write(Output, Pointer, &Scd->Add_speed, sizeof(tagBio2Bytecode::tagAdd_speed));
		break;
		case 0x31:	// Add_aspeed
			ValidOpcode = YES;
			Read(_File, _Offset, &Scd15->Add_aspeed, sizeof(tagBio2BytecodeP::tagAdd_aspeed));
			Scd->Add_aspeed.Opcode = Scd->Opcode = 0x31;
			Write(Output, Pointer, &Scd->Add_aspeed, sizeof(tagBio2Bytecode::tagAdd_aspeed));
		break;
		case 0x32:	// Pos_set
			ValidOpcode = YES;
			Read(_File, _Offset, &Scd15->Pos_set, sizeof(tagBio2BytecodeP::tagPos_set));
			Scd->Pos_set.Opcode = Scd->Opcode = 0x32;
			Scd->Pos_set.zAlign = NULL;
			Scd->Pos_set.X = Scd15->Pos_set.X;
			Scd->Pos_set.Y = Scd15->Pos_set.Y;
			Scd->Pos_set.Z = Scd15->Pos_set.Z;
			Write(Output, Pointer, &Scd->Pos_set, sizeof(tagBio2Bytecode::tagPos_set));
		break;
		case 0x33:	// Dir_set
			ValidOpcode = YES;
			Read(_File, _Offset, &Scd15->Dir_set, sizeof(tagBio2BytecodeP::tagDir_set));
			Scd->Dir_set.Opcode = Scd->Opcode = 0x33;
			Scd->Dir_set.zAlign = NULL;
			Scd->Dir_set.X = Scd15->Dir_set.X;
			Scd->Dir_set.Y = Scd15->Dir_set.Y;
			Scd->Dir_set.Z = Scd15->Dir_set.Z;
			Write(Output, Pointer, &Scd->Dir_set, sizeof(tagBio2Bytecode::tagDir_set));
		break;
		case 0x34:	// Member_set
			ValidOpcode = YES;
			Read(_File, _Offset, &Scd15->Member_set, sizeof(tagBio2BytecodeP::tagMember_set));
			Scd->Member_set.Opcode = Scd->Opcode = 0x34;
			Scd->Member_set.Destination = Scd15->Member_set.Destination;
			Scd->Member_set.Source = Scd15->Member_set.Source;
			Write(Output, Pointer, &Scd->Member_set, sizeof(tagBio2Bytecode::tagMember_set));
		break;
		case 0x35:	// Member_set2
			ValidOpcode = YES;
			Read(_File, _Offset, &Scd15->Member_set2, sizeof(tagBio2BytecodeP::tagMember_set2));
			Scd->Member_set2.Opcode = Scd->Opcode = 0x35;
			Scd->Member_set2.Destination = Scd15->Member_set2.Destination;
			Scd->Member_set2.Source = Scd15->Member_set2.Source;
			Write(Output, Pointer, &Scd->Member_set2, sizeof(tagBio2Bytecode::tagMember_set2));
		break;
		case 0x36:	// Se_on
			ValidOpcode = YES;
			Read(_File, _Offset, &Scd15->Se_on, sizeof(tagBio2BytecodeP::tagSe_on));
			Scd->Se_on.Opcode = Scd->Opcode = 0x36;
			Scd->Se_on.VAB = Scd15->Se_on.VAB;
			Scd->Se_on.EDT = Scd15->Se_on.EDT;
			Scd->Se_on.data0 = Scd15->Se_on.data0;
			Scd->Se_on.X = Scd15->Se_on.X;
			Scd->Se_on.Y = Scd15->Se_on.Y;
			Scd->Se_on.Z = Scd15->Se_on.Z;
			Write(Output, Pointer, &Scd->Se_on, sizeof(tagBio2Bytecode::tagSe_on));
		break;
		case 0x37:	// Sca_id_set
			ValidOpcode = YES;
			Scd->Sca_id_set.Opcode = Scd->Opcode = 0x37;	// STUB FUNCTION
			Scd->Sca_id_set.iEntry = NULL;
			Scd->Sca_id_set.Id = 0xFFFF;
			Write(Output, Pointer, &Scd->Sca_id_set, sizeof(tagBio2Bytecode::tagSca_id_set));
		break;
		case 0x38:	// Sca_xzwd_set	// INCOMPATIBLE BYTECODE
		break;
		case 0x39:	// Sca_type_set
			ValidOpcode = YES;
			Scd->Sca_id_set.Opcode = Scd->Opcode = 0x37;	// STUB FUNCTION
			Scd->Sca_id_set.iEntry = NULL;
			Scd->Sca_id_set.Id = 0xFFFF;
			Write(Output, Pointer, &Scd->Sca_id_set, sizeof(tagBio2Bytecode::tagSca_id_set));
		break;
		case 0x3A:	// Sce_espr_on
			ValidOpcode = YES;
			Read(_File, _Offset, &Scd15->Sce_espr_on, sizeof(tagBio2BytecodeP::tagSce_espr_on));
			Scd->Sce_espr_on.Opcode = Scd->Opcode = 0x3A;
			Scd->Sce_espr_on.zAlign = NULL;
			Scd->Sce_espr_on.data0 = Scd15->Sce_espr_on.data0;
			Scd->Sce_espr_on.data1 = Scd15->Sce_espr_on.data1;
			Scd->Sce_espr_on.data2 = Scd15->Sce_espr_on.data2;
			Scd->Sce_espr_on.X = Scd15->Sce_espr_on.X;
			Scd->Sce_espr_on.Y = Scd15->Sce_espr_on.Y;
			Scd->Sce_espr_on.Z = Scd15->Sce_espr_on.Z;
			Scd->Sce_espr_on.DirY = Scd15->Sce_espr_on.DirY;
			Write(Output, Pointer, &Scd->Sce_espr_on, sizeof(tagBio2Bytecode::tagSce_espr_on));
		break;
		case 0x3B:	// Door_aot_set
			ValidOpcode = YES;
			UpdateOffset = NO;
			Read(_File, _Offset, &Scd15->Door_aot_set, sizeof(tagBio2BytecodeP::tagDoor_aot_set));
			if (Scd15->Door_aot_set.SAT & 0x80) {	// 4P
				Read(_File, _Offset, &Scd15->Door_aot_set_4p, sizeof(tagBio2BytecodeP::tagDoor_aot_set_4p));
				Scd->Door_aot_set_4p.Opcode = Scd->Opcode = 0x68; // DO NOT CHANGE
				Scd->Door_aot_set_4p.Aot = Scd15->Door_aot_set_4p.Aot;
				Scd->Door_aot_set_4p.SCE = GetSceTypeProto(Scd15->Door_aot_set_4p.SCE);
				Scd->Door_aot_set_4p.SAT = Scd15->Door_aot_set_4p.SAT;
				Scd->Door_aot_set_4p.nFloor = Scd15->Door_aot_set_4p.nFloor;
				Scd->Door_aot_set_4p.Super = Scd15->Door_aot_set_4p.Super;
				Scd->Door_aot_set_4p.X0 = Scd15->Door_aot_set_4p.X0;
				Scd->Door_aot_set_4p.X1 = Scd15->Door_aot_set_4p.X1;
				Scd->Door_aot_set_4p.X2 = Scd15->Door_aot_set_4p.X2;
				Scd->Door_aot_set_4p.X3 = Scd15->Door_aot_set_4p.X3;
				Scd->Door_aot_set_4p.Z0 = Scd15->Door_aot_set_4p.Z0;
				Scd->Door_aot_set_4p.Z1 = Scd15->Door_aot_set_4p.Z1;
				Scd->Door_aot_set_4p.Z2 = Scd15->Door_aot_set_4p.Z2;
				Scd->Door_aot_set_4p.Z3 = Scd15->Door_aot_set_4p.Z3;
				Scd->Door_aot_set_4p.Next_pos_x = Scd15->Door_aot_set_4p.PosX;
				Scd->Door_aot_set_4p.Next_pos_y = Scd15->Door_aot_set_4p.PosY;
				Scd->Door_aot_set_4p.Next_pos_z = Scd15->Door_aot_set_4p.PosZ;
				Scd->Door_aot_set_4p.Next_cdir_y = Scd15->Door_aot_set_4p.DirY;
				Scd->Door_aot_set_4p.Next_stage = Scd15->Door_aot_set_4p.Stage;
				Scd->Door_aot_set_4p.Next_room = Scd15->Door_aot_set_4p.Room;
				Scd->Door_aot_set_4p.Next_cut = Scd15->Door_aot_set_4p.Cut;
				Scd->Door_aot_set_4p.Next_nfloor = Scd15->Door_aot_set_4p.nFloorNxt;
				Scd->Door_aot_set_4p.Dtex_type = Scd15->Door_aot_set_4p.DO2;
				Scd->Door_aot_set_4p.Door_type = Scd15->Door_aot_set_4p.Animation;
				Scd->Door_aot_set_4p.Knock_type = Scd15->Door_aot_set_4p.Sound;
				Scd->Door_aot_set_4p.Key_id = Scd15->Door_aot_set_4p.KeyId;
				Scd->Door_aot_set_4p.Key_type = Scd15->Door_aot_set_4p.KeyType;
				Scd->Door_aot_set_4p.Free = Scd15->Door_aot_set_4p.Free;
				Write(Output, Pointer, &Scd->Door_aot_set_4p, sizeof(tagBio2Bytecode::tagDoor_aot_set_4p));
				_Offset += sizeof(tagBio2Bytecode::tagDoor_aot_set_4p);
			} else {	// STANDARD
				Scd->Door_aot_set.Opcode = Scd->Opcode = 0x3B;
				Scd->Door_aot_set.Aot = Scd15->Door_aot_set.Aot;
				Scd->Door_aot_set.SCE = GetSceTypeProto(Scd15->Door_aot_set.SCE);
				Scd->Door_aot_set.SAT = Scd15->Door_aot_set.SAT;
				Scd->Door_aot_set.nFloor = Scd15->Door_aot_set.nFloor;
				Scd->Door_aot_set.Super = Scd15->Door_aot_set.Super;
				Scd->Door_aot_set.X = Scd15->Door_aot_set.X;
				Scd->Door_aot_set.Z = Scd15->Door_aot_set.Z;
				Scd->Door_aot_set.W = Scd15->Door_aot_set.W;
				Scd->Door_aot_set.D = Scd15->Door_aot_set.D;
				Scd->Door_aot_set.Next_pos_x = Scd15->Door_aot_set.Next_pos_x;
				Scd->Door_aot_set.Next_pos_y = Scd15->Door_aot_set.Next_pos_y;
				Scd->Door_aot_set.Next_pos_z = Scd15->Door_aot_set.Next_pos_z;
				Scd->Door_aot_set.Next_cdir_y = Scd15->Door_aot_set.Next_cdir_y;
				Scd->Door_aot_set.Next_stage = Scd15->Door_aot_set.Next_stage;
				Scd->Door_aot_set.Next_room = Scd15->Door_aot_set.Next_room;
				Scd->Door_aot_set.Next_cut = Scd15->Door_aot_set.Next_cut;
				Scd->Door_aot_set.Next_nfloor = Scd15->Door_aot_set.Next_nfloor;
				Scd->Door_aot_set.Dtex_type = Scd15->Door_aot_set.Dtex_type;
				Scd->Door_aot_set.Door_type = Scd15->Door_aot_set.Door_type;
				Scd->Door_aot_set.Knock_type = Scd15->Door_aot_set.Knock_type;
				Scd->Door_aot_set.Key_id = Scd15->Door_aot_set.Key_id;
				Scd->Door_aot_set.Key_type = Scd15->Door_aot_set.Key_type;
				Scd->Door_aot_set.Free = Scd15->Door_aot_set.Free;
				Write(Output, Pointer, &Scd->Door_aot_set, sizeof(tagBio2Bytecode::tagDoor_aot_set));
				_Offset += sizeof(tagBio2Bytecode::tagDoor_aot_set);
			}
		break;
		case 0x3C:	// Cut_auto
			ValidOpcode = YES;
			Read(_File, _Offset, &Scd15->Cut_auto, sizeof(tagBio2BytecodeP::tagCut_auto));
			Scd->Cut_auto.Opcode = Scd->Opcode = 0x3C;
			Scd->Cut_auto.OnOff = Scd15->Cut_auto.OnOff;
			Write(Output, Pointer, &Scd->Cut_auto, sizeof(tagBio2Bytecode::tagCut_auto));
		break;
		case 0x3D:	// Member_copy
			ValidOpcode = YES;
			Read(_File, _Offset, &Scd15->Member_copy, sizeof(tagBio2BytecodeP::tagMember_copy));
			Scd->Member_copy.Opcode = Scd->Opcode = 0x3D;
			Scd->Member_copy.Destination = Scd15->Member_copy.Destination;
			Scd->Member_copy.Source = Scd15->Member_copy.Source;
			Write(Output, Pointer, &Scd->Member_copy, sizeof(tagBio2Bytecode::tagMember_copy));
		break;
		case 0x3E:	// Member_cmp
			ValidOpcode = YES;
			Read(_File, _Offset, &Scd15->Member_cmp, sizeof(tagBio2BytecodeP::tagMember_cmp));
			Scd->Member_cmp.Opcode = Scd->Opcode = 0x3E;
			Scd->Member_cmp.zAlign = NULL;
			Scd->Member_cmp.Flag = Scd15->Member_cmp.Flag;
			Scd->Member_cmp.Operator = Scd15->Member_cmp.Operator;
			Scd->Member_cmp.Value = Scd15->Member_cmp.Value;
			Write(Output, Pointer, &Scd->Member_cmp, sizeof(tagBio2Bytecode::tagMember_cmp));
		break;
		case 0x3F:	// Plc_motion
			ValidOpcode = YES;
			Read(_File, _Offset, &Scd15->Plc_motion, sizeof(tagBio2BytecodeP::tagPlc_motion));
			Scd->Plc_motion.Opcode = Scd->Opcode = 0x3F;
			Scd->Plc_motion.Animation = Scd15->Plc_motion.Animation;
			Scd->Plc_motion.data0 = Scd15->Plc_motion.data0;
			Scd->Plc_motion.data1 = Scd15->Plc_motion.data1;
			Write(Output, Pointer, &Scd->Plc_motion, sizeof(tagBio2Bytecode::tagPlc_motion));
		break;
		case 0x40:	// Plc_dest
			ValidOpcode = YES;
			Read(_File, _Offset, &Scd15->Plc_dest, sizeof(tagBio2BytecodeP::tagPlc_dest));
			Scd->Plc_dest.Opcode = Scd->Opcode = 0x40;
			Scd->Plc_dest.zAlign = NULL;
			Scd->Plc_dest.Animation = Scd15->Plc_dest.Animation;
			Scd->Plc_dest.Bit = Scd15->Plc_dest.Bit;
			Scd->Plc_dest.X = Scd15->Plc_dest.X;
			Scd->Plc_dest.Z = Scd15->Plc_dest.Z;
			Write(Output, Pointer, &Scd->Plc_dest, sizeof(tagBio2Bytecode::tagPlc_dest));
		break;
		case 0x41:	// Plc_neck
			ValidOpcode = YES;
			Read(_File, _Offset, &Scd15->Plc_neck, sizeof(tagBio2BytecodeP::tagPlc_neck));
			Scd->Plc_neck.Opcode = Scd->Opcode = 0x41;
			Scd->Plc_neck.Op = Scd15->Plc_neck.Op;
			Scd->Plc_neck.X = Scd15->Plc_neck.X;
			Scd->Plc_neck.Y = Scd15->Plc_neck.Y;
			Scd->Plc_neck.Z = Scd15->Plc_neck.Z;
			Scd->Plc_neck.SpeedX = Scd15->Plc_neck.SpeedX;
			Scd->Plc_neck.SpeedZ = Scd15->Plc_neck.SpeedZ;
			Write(Output, Pointer, &Scd->Plc_neck, sizeof(tagBio2Bytecode::tagPlc_neck));
		break;
		case 0x42:	// Plc_ret
			ValidOpcode = YES;
			Read(_File, _Offset, &Scd15->Plc_ret, sizeof(tagBio2BytecodeP::tagPlc_ret));
			Scd->Plc_ret.Opcode = Scd->Opcode = 0x42;
			Write(Output, Pointer, &Scd->Plc_ret, sizeof(tagBio2Bytecode::tagPlc_ret));
		break;
		case 0x43:	// Plc_flg
			ValidOpcode = YES;
			Read(_File, _Offset, &Scd15->Plc_flg, sizeof(tagBio2BytecodeP::tagPlc_flg));
			Scd->Plc_flg.Opcode = Scd->Opcode = 0x43;
			Scd->Plc_flg.Type = Scd15->Plc_flg.Type;
			Scd->Plc_flg.Flag = Scd15->Plc_flg.Flag;
			Write(Output, Pointer, &Scd->Plc_flg, sizeof(tagBio2Bytecode::tagPlc_flg));
		break;
		case 0x44:	// Sce_em_set
			ValidOpcode = YES;
			Read(_File, _Offset, &Scd15->Sce_em_set, sizeof(tagBio2BytecodeP::tagSce_em_set));
			Scd->Sce_em_set.Opcode = Scd->Opcode = 0x44;
			Scd->Sce_em_set.Nop = NULL;
			Scd->Sce_em_set.Em_no = Scd15->Sce_em_set.Em_no;
			Scd->Sce_em_set.Id = Scd15->Sce_em_set.Id;
			Scd->Sce_em_set.Type = Scd15->Sce_em_set.Type;
			Scd->Sce_em_set.nFloor = Scd15->Sce_em_set.nFloor;
			Scd->Sce_em_set.Sound_flg = Scd15->Sce_em_set.Sound_flg;
			Scd->Sce_em_set.Model_type = Scd15->Sce_em_set.Model_type;
			Scd->Sce_em_set.Em_set_flg = Scd15->Sce_em_set.Em_set_flg;
			Scd->Sce_em_set.Pos_x = Scd15->Sce_em_set.Pos_x;
			Scd->Sce_em_set.Pos_y = Scd15->Sce_em_set.Pos_y;
			Scd->Sce_em_set.Pos_z = Scd15->Sce_em_set.Pos_z;
			Scd->Sce_em_set.Cdir_y = Scd15->Sce_em_set.Cdir_y;
			Scd->Sce_em_set.Motion = Scd15->Sce_em_set.Motion;
			Scd->Sce_em_set.Ctr_flg = Scd15->Sce_em_set.Ctr_flg;
			Write(Output, Pointer, &Scd->Sce_em_set, sizeof(tagBio2Bytecode::tagSce_em_set));
		break;
		case 0x45:	// UNKNOWN OPCODE
		break;
		case 0x46:	// Aot_reset
			ValidOpcode = YES;
			Read(_File, _Offset, &Scd15->Aot_reset, sizeof(tagBio2BytecodeP::tagAot_reset));
			Scd->Aot_reset.Opcode = Scd->Opcode = 0x46;
			Scd->Aot_reset.Aot = Scd15->Aot_reset.Aot;
			Scd->Aot_reset.SCE = GetSceTypeProto(Scd15->Aot_reset.SCE);
			Scd->Aot_reset.SAT = Scd15->Aot_reset.SAT;
			Scd->Aot_reset.Data0 = Scd15->Aot_reset.Data0;
			Scd->Aot_reset.Data1 = Scd15->Aot_reset.Data1;
			Scd->Aot_reset.Data2 = Scd15->Aot_reset.Data2;
			Write(Output, Pointer, &Scd->Aot_reset, sizeof(tagBio2Bytecode::tagAot_reset));
		break;
		case 0x47:	// Aot_on
			ValidOpcode = YES;
			Read(_File, _Offset, &Scd15->Aot_on, sizeof(tagBio2BytecodeP::tagAot_on));
			Scd->Aot_on.Opcode = Scd->Opcode = 0x47;
			Scd->Aot_on.Aot = Scd15->Aot_on.Aot;
			Write(Output, Pointer, &Scd->Aot_on, sizeof(tagBio2Bytecode::tagAot_on));
		break;
		case 0x48:	// Super_set
			ValidOpcode = YES;
			Read(_File, _Offset, &Scd15->Super_set, sizeof(tagBio2BytecodeP::tagSuper_set));
			Scd->Super_set.Opcode = Scd->Opcode = 0x48;
			Scd->Super_set.zAlign = NULL;
			Scd->Super_set.Work = Scd15->Super_set.Work;
			Scd->Super_set.Id = Scd15->Super_set.Id;
			Scd->Super_set.pX = Scd15->Super_set.pX;
			Scd->Super_set.pY = Scd15->Super_set.pY;
			Scd->Super_set.pZ = Scd15->Super_set.pZ;
			Scd->Super_set.dX = Scd15->Super_set.dX;
			Scd->Super_set.dY = Scd15->Super_set.dY;
			Scd->Super_set.dZ = Scd15->Super_set.dZ;
			Write(Output, Pointer, &Scd->Super_set, sizeof(tagBio2Bytecode::tagSuper_set));
		break;
		case 0x49:	// Super_reset
			ValidOpcode = YES;
			Read(_File, _Offset, &Scd15->Super_reset, sizeof(tagBio2BytecodeP::tagSuper_reset));
			Scd->Super_reset.Opcode = Scd->Opcode = 0x49;
			Scd->Super_reset.zAlign = NULL;
			Scd->Super_reset.dX = Scd15->Super_reset.dX;
			Scd->Super_reset.dY = Scd15->Super_reset.dY;
			Scd->Super_reset.dZ = Scd15->Super_reset.dZ;
			Write(Output, Pointer, &Scd->Super_reset, sizeof(tagBio2Bytecode::tagSuper_reset));
		break;
		case 0x4A:	// Plc_gun
			ValidOpcode = YES;
			Read(_File, _Offset, &Scd15->Plc_gun, sizeof(tagBio2BytecodeP::tagPlc_gun));
			Scd->Plc_gun.Opcode = Scd->Opcode = 0x4A;
			Scd->Plc_gun.Animation = Scd15->Plc_gun.Animation;
			Write(Output, Pointer, &Scd->Plc_gun, sizeof(tagBio2Bytecode::tagPlc_gun));
		break;
		case 0x4B:	// Cut_replace
			ValidOpcode = YES;
			Read(_File, _Offset, &Scd15->Cut_replace, sizeof(tagBio2BytecodeP::tagCut_replace));
			Scd->Cut_replace.Opcode = Scd->Opcode = 0x4B;
			Scd->Cut_replace.Id = Scd15->Cut_replace.Id;
			Scd->Cut_replace.Value = Scd15->Cut_replace.Value;
			Write(Output, Pointer, &Scd->Cut_replace, sizeof(tagBio2Bytecode::tagCut_replace));
		break;
		case 0x4C:	// UNKNOWN OPCODE
		break;
		case 0x4D:	// UNKNOWN OPCODE
		break;
		case 0x4E:	// Sce_espr_kill
			ValidOpcode = YES;
			Read(_File, _Offset, &Scd15->Sce_espr_kill, sizeof(tagBio2BytecodeP::tagSce_espr_kill));
			Scd->Sce_espr_kill.Opcode = Scd->Opcode = 0x4C; // DO NOT CHANGE
			Scd->Sce_espr_kill.id = Scd15->Sce_espr_kill.id;
			Scd->Sce_espr_kill.tp = Scd15->Sce_espr_kill.tp;
			Scd->Sce_espr_kill.WorkKind = Scd15->Sce_espr_kill.WorkKind;
			Scd->Sce_espr_kill.WorkNo = Scd15->Sce_espr_kill.WorkNo;
			Write(Output, Pointer, &Scd->Sce_espr_kill, sizeof(tagBio2Bytecode::tagSce_espr_kill));
		break;
		case 0x4F:	// Door_model_set
			ValidOpcode = YES;
			Read(_File, _Offset, &Scd15->Door_model_set, sizeof(tagBio2BytecodeP::tagDoor_model_set));
			Scd->Door_model_set.Opcode = Scd->Opcode = 0x4D; // DO NOT CHANGE
			Scd->Door_model_set.data0 = Scd15->Door_model_set.data0;
			Scd->Door_model_set.Id = Scd15->Door_model_set.Id;
			Scd->Door_model_set.OfsY = Scd15->Door_model_set.OfsY;
			Scd->Door_model_set.BeFlg = Scd15->Door_model_set.BeFlg;
			Scd->Door_model_set.data5 = Scd15->Door_model_set.data5;
			Scd->Door_model_set.data6 = Scd15->Door_model_set.data6;
			Scd->Door_model_set.X = Scd15->Door_model_set.X;
			Scd->Door_model_set.Y = Scd15->Door_model_set.Y;
			Scd->Door_model_set.Z = Scd15->Door_model_set.Z;
			Scd->Door_model_set.DirY = Scd15->Door_model_set.DirY;
			Scd->Door_model_set.data10 = Scd15->Door_model_set.data10;
			Scd->Door_model_set.data11 = Scd15->Door_model_set.data11;
			Scd->Door_model_set.data12 = Scd15->Door_model_set.data12;
			Write(Output, Pointer, &Scd->Door_model_set, sizeof(tagBio2Bytecode::tagDoor_model_set));
		break;
		case 0x50:	// Item_aot_set
			ValidOpcode = YES;
			UpdateOffset = NO;
			Read(_File, _Offset, &Scd15->Item_aot_set, sizeof(tagBio2BytecodeP::tagItem_aot_set));
			if (Scd15->Item_aot_set.SAT & 0x80) {	// 4P
				Read(_File, _Offset, &Scd15->Item_aot_set_4p, sizeof(tagBio2BytecodeP::tagItem_aot_set_4p));
				Scd->Item_aot_set_4p.Opcode = Scd->Opcode = 0x69; // DO NOT CHANGE
				Scd->Item_aot_set_4p.Aot = Scd15->Item_aot_set_4p.Aot;
				Scd->Item_aot_set_4p.SCE = GetSceTypeProto(Scd15->Item_aot_set_4p.SCE);
				Scd->Item_aot_set_4p.SAT = Scd15->Item_aot_set_4p.SAT;
				Scd->Item_aot_set_4p.nFloor = Scd15->Item_aot_set_4p.nFloor;
				Scd->Item_aot_set_4p.Super = Scd15->Item_aot_set_4p.Super;
				Scd->Item_aot_set_4p.X0 = Scd15->Item_aot_set_4p.X0;
				Scd->Item_aot_set_4p.Z0 = Scd15->Item_aot_set_4p.Z0;
				Scd->Item_aot_set_4p.X1 = Scd15->Item_aot_set_4p.X1;
				Scd->Item_aot_set_4p.Z1 = Scd15->Item_aot_set_4p.Z1;
				Scd->Item_aot_set_4p.X2 = Scd15->Item_aot_set_4p.X2;
				Scd->Item_aot_set_4p.Z2 = Scd15->Item_aot_set_4p.Z2;
				Scd->Item_aot_set_4p.X3 = Scd15->Item_aot_set_4p.X3;
				Scd->Item_aot_set_4p.Z3 = Scd15->Item_aot_set_4p.Z3;
				Scd->Item_aot_set_4p.iItem = Scd15->Item_aot_set_4p.iItem;
				Scd->Item_aot_set_4p.nItem = Scd15->Item_aot_set_4p.nItem;
				Scd->Item_aot_set_4p.Flag = Scd15->Item_aot_set_4p.Flag;
				Scd->Item_aot_set_4p.MD1 = Scd15->Item_aot_set_4p.MD1;
				Scd->Item_aot_set_4p.Action = Scd15->Item_aot_set_4p.Action;
				Write(Output, Pointer, &Scd->Item_aot_set_4p, sizeof(tagBio2Bytecode::tagItem_aot_set_4p));
				_Offset += sizeof(tagBio2Bytecode::tagItem_aot_set_4p);
			} else {	// STANDARD
				Scd->Item_aot_set.Opcode = Scd->Opcode = 0x4E; // DO NOT CHANGE
				Scd->Item_aot_set.Aot = Scd15->Item_aot_set.Aot;
				Scd->Item_aot_set.SCE = GetSceTypeProto(Scd15->Item_aot_set.SCE);
				Scd->Item_aot_set.SAT = Scd15->Item_aot_set.SAT;
				Scd->Item_aot_set.nFloor = Scd15->Item_aot_set.nFloor;
				Scd->Item_aot_set.Super = Scd15->Item_aot_set.Super;
				Scd->Item_aot_set.X = Scd15->Item_aot_set.X;
				Scd->Item_aot_set.Z = Scd15->Item_aot_set.Z;
				Scd->Item_aot_set.W = Scd15->Item_aot_set.W;
				Scd->Item_aot_set.D = Scd15->Item_aot_set.D;
				Scd->Item_aot_set.iItem = Scd15->Item_aot_set.iItem;
				Scd->Item_aot_set.nItem = Scd15->Item_aot_set.nItem;
				Scd->Item_aot_set.Flag = Scd15->Item_aot_set.Flag;
				Scd->Item_aot_set.MD1 = Scd15->Item_aot_set.MD1;
				Scd->Item_aot_set.Action = Scd15->Item_aot_set.Action;
				Write(Output, Pointer, &Scd->Item_aot_set, sizeof(tagBio2Bytecode::tagItem_aot_set));
				_Offset += sizeof(tagBio2Bytecode::tagItem_aot_set);
			}
		break;
		case 0x51:	// Sce_key_ck
			ValidOpcode = YES;
			Read(_File, _Offset, &Scd15->Sce_key_ck, sizeof(tagBio2BytecodeP::tagSce_key_ck));
			Scd->Sce_key_ck.Opcode = Scd->Opcode = 0x4F; // DO NOT CHANGE
			Scd->Sce_key_ck.Flag = Scd15->Sce_key_ck.Flag;
			Scd->Sce_key_ck.Value = Scd15->Sce_key_ck.Value;
			Write(Output, Pointer, &Scd->Sce_key_ck, sizeof(tagBio2Bytecode::tagSce_key_ck));
		break;
		case 0x52:	// Sce_trg_ck
			ValidOpcode = YES;
			Read(_File, _Offset, &Scd15->Sce_trg_ck, sizeof(tagBio2BytecodeP::tagSce_trg_ck));
			Scd->Sce_trg_ck.Opcode = Scd->Opcode = 0x50; // DO NOT CHANGE
			Scd->Sce_trg_ck.Flag = Scd15->Sce_trg_ck.Flag;
			Scd->Sce_trg_ck.Value = Scd15->Sce_trg_ck.Value;
			Write(Output, Pointer, &Scd->Sce_trg_ck, sizeof(tagBio2Bytecode::tagSce_trg_ck));
		break;
		case 0x53:	// Work_set2
			ValidOpcode = YES;
			Read(_File, _Offset, &Scd15->Work_set2, sizeof(tagBio2BytecodeP::tagWork_set2));
			Scd->Work_set.Opcode = Scd->Opcode = 0x2E; // DO NOT CHANGE
			Scd->Work_set.Type = Scd15->Work_set2.Type;
			Scd->Work_set.Aot = Scd15->Work_set2.Aot;
			Write(Output, Pointer, &Scd->Work_set, sizeof(tagBio2Bytecode::tagWork_set));
		break;
		case 0x54:	// Sce_bgm_control
			ValidOpcode = YES;
			Read(_File, _Offset, &Scd15->Sce_bgm_control, sizeof(tagBio2BytecodeP::tagSce_bgm_control));
			Scd->Sce_bgm_control.Opcode = Scd->Opcode = 0x51; // DO NOT CHANGE
			Scd->Sce_bgm_control.Id = Scd15->Sce_bgm_control.Id;
			Scd->Sce_bgm_control.Op = Scd15->Sce_bgm_control.Op;
			Scd->Sce_bgm_control.Type = Scd15->Sce_bgm_control.Type;
			Scd->Sce_bgm_control.VolL = Scd15->Sce_bgm_control.VolL;
			Scd->Sce_bgm_control.VolR = Scd15->Sce_bgm_control.VolR;
			Write(Output, Pointer, &Scd->Sce_bgm_control, sizeof(tagBio2Bytecode::tagSce_bgm_control));
		break;
		case 0x55:	// Sce_espr_control
			ValidOpcode = YES;
			Read(_File, _Offset, &Scd15->Sce_espr_control, sizeof(tagBio2BytecodeP::tagSce_espr_control));
			Scd->Sce_espr_control.Opcode = Scd->Opcode = 0x52; // DO NOT CHANGE
			Scd->Sce_espr_control.Id = Scd15->Sce_espr_control.Id;
			Scd->Sce_espr_control.Type = Scd15->Sce_espr_control.Type;
			Scd->Sce_espr_control.Return = Scd15->Sce_espr_control.Return;
			Scd->Sce_espr_control.WorkKind = Scd15->Sce_espr_control.WorkKind;
			Scd->Sce_espr_control.WorkNo = Scd15->Sce_espr_control.WorkNo;
			Write(Output, Pointer, &Scd->Sce_espr_control, sizeof(tagBio2Bytecode::tagSce_espr_control));
		break;
		case 0x56:	// Sce_fade_set
			ValidOpcode = YES;
			Read(_File, _Offset, &Scd15->Sce_fade_set, sizeof(tagBio2BytecodeP::tagSce_fade_set));
			Scd->Sce_fade_set.Opcode = Scd->Opcode = 0x53; // DO NOT CHANGE
			Scd->Sce_fade_set.data0 = Scd15->Sce_fade_set.data0;
			Scd->Sce_fade_set.data1 = Scd15->Sce_fade_set.data1;
			Scd->Sce_fade_set.data2 = Scd15->Sce_fade_set.data2;
			Scd->Sce_fade_set.data3 = Scd15->Sce_fade_set.data3;
			Write(Output, Pointer, &Scd->Sce_fade_set, sizeof(tagBio2Bytecode::tagSce_fade_set));
		break;
		case 0x57:	// Sce_fade_adjust
			ValidOpcode = YES;
			Read(_File, _Offset, &Scd15->Sce_fade_adjust, sizeof(tagBio2BytecodeP::tagSce_fade_adjust));
			Scd->Sce_fade_adjust.Opcode = Scd->Opcode = 0x74; // DO NOT CHANGE
			Scd->Sce_fade_adjust.data0 = Scd15->Sce_fade_adjust.data0;
			Scd->Sce_fade_adjust.data1 = Scd15->Sce_fade_adjust.data1;
			Write(Output, Pointer, &Scd->Sce_fade_adjust, sizeof(tagBio2Bytecode::tagSce_fade_adjust));
		break;
		case 0x58:	// Ck2 (...probably not compatible)
			ValidOpcode = YES;
			Read(_File, _Offset, &Scd15->Ck2, sizeof(tagBio2BytecodeP::tagCk2));
			Scd->Ck.Opcode = Scd->Opcode = 0x21; // DO NOT CHANGE
			Scd->Ck.Flag = Scd15->Ck2.Flag;
			Scd->Ck.Id = Scd15->Ck2.Id;
			Scd->Ck.OnOff = Scd15->Ck2.OnOff;
			Write(Output, Pointer, &Scd->Ck, sizeof(tagBio2Bytecode::tagCk));
		break;
		case 0x59:	// Set2 (...probably not compatible)
			ValidOpcode = YES;
			Read(_File, _Offset, &Scd15->Set2, sizeof(tagBio2BytecodeP::tagSet2));
			Scd->Set.Opcode = Scd->Opcode = 0x22; // DO NOT CHANGE
			Scd->Set.Flag = Scd15->Set2.Flag;
			Scd->Set.Id = Scd15->Set2.Id;
			Scd->Set.OnOff = Scd15->Set2.OnOff;
			Write(Output, Pointer, &Scd->Set, sizeof(tagBio2Bytecode::tagSet));
		break;
		case 0x5A:	// Member_calc
			ValidOpcode = YES;
			Read(_File, _Offset, &Scd15->Member_calc, sizeof(tagBio2BytecodeP::tagMember_calc));
			Scd->Member_calc.Opcode = Scd->Opcode = 0x55; // DO NOT CHANGE
			Scd->Member_calc.Operator = Scd15->Member_calc.Operator;
			Scd->Member_calc.Flag = Scd15->Member_calc.Flag;
			Scd->Member_calc.Value = Scd15->Member_calc.Value;
			Write(Output, Pointer, &Scd->Member_calc, sizeof(tagBio2Bytecode::tagMember_calc));
		break;
		case 0x5B:	// Member_calc2
			ValidOpcode = YES;
			Read(_File, _Offset, &Scd15->Member_calc2, sizeof(tagBio2BytecodeP::tagMember_calc2));
			Scd->Member_calc2.Opcode = Scd->Opcode = 0x56; // DO NOT CHANGE
			Scd->Member_calc2.Operator = Scd15->Member_calc2.Operator;
			Scd->Member_calc2.Flag = Scd15->Member_calc2.Flag;
			Scd->Member_calc2.Value = Scd15->Member_calc2.Value;
			Write(Output, Pointer, &Scd->Member_calc2, sizeof(tagBio2Bytecode::tagMember_calc2));
		break;
		case 0x5C:	// Sce_bgmtbl_set
			ValidOpcode = YES;
			Read(_File, _Offset, &Scd15->Sce_bgmtbl_set, sizeof(tagBio2BytecodeP::tagSce_bgmtbl_set));
			Scd->Sce_bgmtbl_set.Opcode = Scd->Opcode = 0x58; // DO NOT CHANGE
			Scd->Sce_bgmtbl_set.Stage = Scd15->Sce_bgmtbl_set.Stage;
			Scd->Sce_bgmtbl_set.Room = Scd15->Sce_bgmtbl_set.Room;
			Scd->Sce_bgmtbl_set.data1 = Scd15->Sce_bgmtbl_set.data1;
			Write(Output, Pointer, &Scd->Sce_bgmtbl_set, sizeof(tagBio2Bytecode::tagSce_bgmtbl_set));
		break;
		case 0x5D:	// Plc_rot
			ValidOpcode = YES;
			Read(_File, _Offset, &Scd15->Plc_rot, sizeof(tagBio2BytecodeP::tagPlc_rot));
			Scd->Plc_rot.Opcode = Scd->Opcode = 0x58; // DO NOT CHANGE
			Scd->Plc_rot.Id = Scd15->Plc_rot.Id;
			Scd->Plc_rot.Sce_free0 = Scd15->Plc_rot.Sce_free0;
			Write(Output, Pointer, &Scd->Plc_rot, sizeof(tagBio2Bytecode::tagPlc_rot));
		break;
		case 0x5E:	// Xa_on
			ValidOpcode = YES;
			Read(_File, _Offset, &Scd15->Xa_on, sizeof(tagBio2BytecodeP::tagXa_on));
			Scd->Xa_on.Opcode = Scd->Opcode = 0x59; // DO NOT CHANGE
			Scd->Xa_on.Mode = Scd15->Xa_on.Mode;
			Scd->Xa_on.Number = Scd15->Xa_on.Number;
			Write(Output, Pointer, &Scd->Xa_on, sizeof(tagBio2Bytecode::tagXa_on));
		break;
		}

		// Update
		if (UpdateOffset) { _Offset += Bio_Hazard_2_Proto_Script_Bytecode_Size[Scd15->Opcode]; }
		if (ValidOpcode) { Pointer += Bio_Hazard_2_Script_Bytecode_Size[Scd->Opcode]; }
	}

	// Cleanup
	delete[] Scd15;
	delete[] Scd;
	delete[] FileName;
	fclose(Output);
	fclose(_File);

	// Complete
	Disassemble((CHAR*)"%s\\_%s.scd", Directory, NameBase);
	delete[] NameBase;
	delete[] Directory;

	// Terminate
	return TRUE;
}