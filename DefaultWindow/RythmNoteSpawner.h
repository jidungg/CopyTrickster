#pragma once
class CRythmNote;
enum class NOTE_TYPE
{
	NORMAL,
	REST,
	GAME_OVER,
	END
};
enum NOTE_BEAT
{
	SIXTEEN = 81,
	EIGHT = 162,
	FOUR = 324,
	DOT_FOUR = 486,
	TWO = 648,
	TRIPLET = 216,
	ONE = 1296,
	BEAT_END
};
typedef struct tagNoteSpawn
{
	tagNoteSpawn(NOTE_TYPE etype = NOTE_TYPE::END, NOTE_BEAT ebeat = BEAT_END,  int iCol = -1)
		:dwTime(ebeat), eType(etype), iCOl(iCol) {}
	DWORD dwTime;
	NOTE_TYPE eType;
	int iCOl = 0;
}NOTE_SPAWN;
class CRythmNoteSpawner
{
public:
	CRythmNoteSpawner();

	void Initialize();
	NOTE_SPAWN Update();
	void Late_Update();
	void Release();
	void Start_Spawn() { m_bStartSpawn = true; m_dwStartTiime = GetTickCount(); }
private:
	queue<NOTE_SPAWN> m_qNoteBeats;
	queue<NOTE_SPAWN> m_qNoteTimes;
	DWORD m_dwStartTiime = 0;
	DWORD m_dwElapsedTime = 0;
	DWORD m_dwPrevNoteLen=0;

	bool m_bStartSpawn = false;

	DWORD m_dwMusicStarTime = 2000;
	bool m_bMusicStarted = false;
};

