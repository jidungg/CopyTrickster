#include "stdafx.h"
#include "RythmNoteSpawner.h"
#include "Define.h"
#include "SoundMgr.h"

CRythmNoteSpawner::CRythmNoteSpawner()
{
}

void CRythmNoteSpawner::Initialize()
{

	m_qNoteBeats.push({NOTE_TYPE::NORMAL, EIGHT, 0});
	m_qNoteBeats.push({ NOTE_TYPE::NORMAL,	EIGHT,3	});
	m_qNoteBeats.push({ NOTE_TYPE::REST, EIGHT, 0}	);
	m_qNoteBeats.push({ NOTE_TYPE::NORMAL,EIGHT,1});
	m_qNoteBeats.push({ NOTE_TYPE::REST,EIGHT,0});
	m_qNoteBeats.push({ NOTE_TYPE::NORMAL,EIGHT,2});
	m_qNoteBeats.push({ NOTE_TYPE::NORMAL,FOUR,1});

	m_qNoteBeats.push({NOTE_TYPE::NORMAL,FOUR, 1});
	m_qNoteBeats.push({ NOTE_TYPE::REST ,FOUR, 1}) ;
	m_qNoteBeats.push({ NOTE_TYPE::NORMAL,FOUR,1 });
	m_qNoteBeats.push({ NOTE_TYPE::REST ,FOUR, 1}) ;

	m_qNoteBeats.push({NOTE_TYPE::NORMAL,	FOUR		, 2 });
	m_qNoteBeats.push({NOTE_TYPE::REST	,	EIGHT		, 2 });
	m_qNoteBeats.push({NOTE_TYPE::NORMAL,	FOUR		, 2 });
	m_qNoteBeats.push({NOTE_TYPE::REST	,	EIGHT		, 2 });
	m_qNoteBeats.push({NOTE_TYPE::NORMAL,	FOUR		, 2});

	m_qNoteBeats.push({ NOTE_TYPE::REST,		EIGHT,			3 });
	m_qNoteBeats.push({ NOTE_TYPE::NORMAL,		FOUR,			3 });
	m_qNoteBeats.push({ NOTE_TYPE::NORMAL,		FOUR,			3 });
	m_qNoteBeats.push({ NOTE_TYPE::NORMAL,		EIGHT,			3});
	m_qNoteBeats.push({ NOTE_TYPE::NORMAL,		FOUR,			2 });

	m_qNoteBeats.push({ NOTE_TYPE::NORMAL	,	TRIPLET	,	0 });
	m_qNoteBeats.push({ NOTE_TYPE::NORMAL	,	TRIPLET	,	1 });
	m_qNoteBeats.push({ NOTE_TYPE::NORMAL	,	TRIPLET	,	2 });
	m_qNoteBeats.push({ NOTE_TYPE::NORMAL	,	FOUR	,	3 });
	m_qNoteBeats.push({ NOTE_TYPE::NORMAL	,	EIGHT	,	0 });
	m_qNoteBeats.push({ NOTE_TYPE::NORMAL	,	EIGHT	,	1});

	m_qNoteBeats.push({NOTE_TYPE::REST		,EIGHT,	1});
	m_qNoteBeats.push({NOTE_TYPE::NORMAL	,FOUR,	1});
	m_qNoteBeats.push({NOTE_TYPE::NORMAL	,EIGHT,	1});
	m_qNoteBeats.push({NOTE_TYPE::NORMAL	,EIGHT,	2});
	m_qNoteBeats.push({NOTE_TYPE::NORMAL	,FOUR,	1});
	m_qNoteBeats.push({NOTE_TYPE::REST		,EIGHT,	1});

	//1줄 반복
	m_qNoteBeats.push({ NOTE_TYPE::NORMAL,	FOUR			, 2 });
	m_qNoteBeats.push({ NOTE_TYPE::REST	,	EIGHT		, 2 });
	m_qNoteBeats.push({ NOTE_TYPE::NORMAL,	FOUR			, 2 });
	m_qNoteBeats.push({ NOTE_TYPE::REST	,	EIGHT		, 2 });
	m_qNoteBeats.push({ NOTE_TYPE::NORMAL,	FOUR			, 2 });

	m_qNoteBeats.push({ NOTE_TYPE::REST,		EIGHT,			3 });
	m_qNoteBeats.push({ NOTE_TYPE::NORMAL,		FOUR,			3 });
	m_qNoteBeats.push({ NOTE_TYPE::NORMAL,		FOUR,			3 });
	m_qNoteBeats.push({ NOTE_TYPE::NORMAL,		EIGHT,			3 });
	m_qNoteBeats.push({ NOTE_TYPE::NORMAL,		FOUR,			2 });

	m_qNoteBeats.push({ NOTE_TYPE::NORMAL	,	TRIPLET	,	0 });
	m_qNoteBeats.push({ NOTE_TYPE::NORMAL	,	TRIPLET	,	1 });
	m_qNoteBeats.push({ NOTE_TYPE::NORMAL	,	TRIPLET	,	2 });
	m_qNoteBeats.push({ NOTE_TYPE::NORMAL	,	FOUR	,	3 });
	m_qNoteBeats.push({ NOTE_TYPE::NORMAL	,	EIGHT	,	0 });
	m_qNoteBeats.push({ NOTE_TYPE::NORMAL	,	EIGHT	,	1 });

	m_qNoteBeats.push({ NOTE_TYPE::REST		,EIGHT,	1 });
	m_qNoteBeats.push({ NOTE_TYPE::NORMAL	,FOUR,	1 });
	m_qNoteBeats.push({ NOTE_TYPE::NORMAL	,EIGHT,	1 });
	m_qNoteBeats.push({ NOTE_TYPE::NORMAL	,EIGHT,	2 });
	m_qNoteBeats.push({ NOTE_TYPE::NORMAL	,FOUR,	1 });
	m_qNoteBeats.push({ NOTE_TYPE::REST		,EIGHT,	1 });

	//2줄
	m_qNoteBeats.push({NOTE_TYPE::REST		,FOUR,	2});
	m_qNoteBeats.push({NOTE_TYPE::NORMAL	,EIGHT,	3});
	m_qNoteBeats.push({NOTE_TYPE::NORMAL	,EIGHT,	2});
	m_qNoteBeats.push({NOTE_TYPE::NORMAL	,EIGHT,	1});
	m_qNoteBeats.push({NOTE_TYPE::NORMAL	,FOUR,	0});
	m_qNoteBeats.push({NOTE_TYPE::NORMAL	,EIGHT,	1});


	m_qNoteBeats.push({NOTE_TYPE::REST		,EIGHT,	1});
	m_qNoteBeats.push({NOTE_TYPE::NORMAL	,EIGHT,	1});
	m_qNoteBeats.push({NOTE_TYPE::NORMAL	,EIGHT,	2});
	m_qNoteBeats.push({NOTE_TYPE::NORMAL	,EIGHT,	3});
	m_qNoteBeats.push({NOTE_TYPE::REST		,EIGHT,	1});
	m_qNoteBeats.push({NOTE_TYPE::NORMAL	,EIGHT,	1});
	m_qNoteBeats.push({NOTE_TYPE::NORMAL	,EIGHT,	2});
	m_qNoteBeats.push({NOTE_TYPE::NORMAL	,EIGHT,	3});

	m_qNoteBeats.push({NOTE_TYPE::REST			,FOUR	,	3});
	m_qNoteBeats.push({NOTE_TYPE::NORMAL		,EIGHT	,	3});
	m_qNoteBeats.push({NOTE_TYPE::NORMAL		,EIGHT	,	2});
	m_qNoteBeats.push({NOTE_TYPE::NORMAL		,EIGHT	,	1});
	m_qNoteBeats.push({NOTE_TYPE::NORMAL		,FOUR	,	0});
	m_qNoteBeats.push({NOTE_TYPE::NORMAL		,EIGHT	,	1});

	m_qNoteBeats.push({NOTE_TYPE::REST			,EIGHT	,	1});
	m_qNoteBeats.push({NOTE_TYPE::NORMAL		,FOUR	,	2});
	m_qNoteBeats.push({NOTE_TYPE::NORMAL		,EIGHT	,	2});
	m_qNoteBeats.push({NOTE_TYPE::NORMAL		,FOUR	,	3});
	m_qNoteBeats.push({NOTE_TYPE::REST			,FOUR	,	2});

	m_qNoteBeats.push({NOTE_TYPE::REST			,FOUR	,	1});
	m_qNoteBeats.push({NOTE_TYPE::NORMAL		,EIGHT	,	3});
	m_qNoteBeats.push({NOTE_TYPE::NORMAL		,EIGHT	,	2});
	m_qNoteBeats.push({NOTE_TYPE::NORMAL		,EIGHT	,	1});
	m_qNoteBeats.push({NOTE_TYPE::NORMAL		,FOUR	,	0});
	m_qNoteBeats.push({NOTE_TYPE::NORMAL		,EIGHT	,	1});

	//3줄
	m_qNoteBeats.push({NOTE_TYPE::REST			,EIGHT	,	1});
	m_qNoteBeats.push({NOTE_TYPE::NORMAL		,EIGHT	,	0});
	m_qNoteBeats.push({NOTE_TYPE::NORMAL		,EIGHT	,	1});
	m_qNoteBeats.push({NOTE_TYPE::NORMAL		,EIGHT	,	2});
	m_qNoteBeats.push({NOTE_TYPE::REST			,EIGHT	,	1});
	m_qNoteBeats.push({ NOTE_TYPE::NORMAL		,EIGHT	,	1 });
	m_qNoteBeats.push({ NOTE_TYPE::NORMAL		,EIGHT	,	2 });
	m_qNoteBeats.push({ NOTE_TYPE::NORMAL		,EIGHT	,	3 });

	m_qNoteBeats.push({ NOTE_TYPE::REST		,FOUR	,	3 });
	m_qNoteBeats.push({ NOTE_TYPE::NORMAL		,FOUR	,	3 });
	m_qNoteBeats.push({NOTE_TYPE::REST			,EIGHT	,	1});
	m_qNoteBeats.push({ NOTE_TYPE::NORMAL		,FOUR	,	3 });
	m_qNoteBeats.push({NOTE_TYPE::REST			,EIGHT	,	1});

	m_qNoteBeats.push({ NOTE_TYPE::NORMAL		,FOUR	,	3 });
	m_qNoteBeats.push({ NOTE_TYPE::REST		,FOUR	,	3 });
	m_qNoteBeats.push({ NOTE_TYPE::REST		,TWO	,	3 });

	//2줄 반복
	m_qNoteBeats.push({ NOTE_TYPE::REST		,FOUR,	2 });
	m_qNoteBeats.push({ NOTE_TYPE::NORMAL	,EIGHT,	3 });
	m_qNoteBeats.push({ NOTE_TYPE::NORMAL	,EIGHT,	2 });
	m_qNoteBeats.push({ NOTE_TYPE::NORMAL	,EIGHT,	1 });
	m_qNoteBeats.push({ NOTE_TYPE::NORMAL	,FOUR,	0 });
	m_qNoteBeats.push({ NOTE_TYPE::NORMAL	,EIGHT,	1 });


	m_qNoteBeats.push({ NOTE_TYPE::REST		,EIGHT,	1 });
	m_qNoteBeats.push({ NOTE_TYPE::NORMAL	,EIGHT,	1 });
	m_qNoteBeats.push({ NOTE_TYPE::NORMAL	,EIGHT,	2 });
	m_qNoteBeats.push({ NOTE_TYPE::NORMAL	,EIGHT,	3 });
	m_qNoteBeats.push({ NOTE_TYPE::REST		,EIGHT,	1 });
	m_qNoteBeats.push({ NOTE_TYPE::NORMAL	,EIGHT,	1 });
	m_qNoteBeats.push({ NOTE_TYPE::NORMAL	,EIGHT,	2 });
	m_qNoteBeats.push({ NOTE_TYPE::NORMAL	,EIGHT,	3 });

	m_qNoteBeats.push({ NOTE_TYPE::REST			,FOUR	,	3 });
	m_qNoteBeats.push({ NOTE_TYPE::NORMAL		,EIGHT	,	3 });
	m_qNoteBeats.push({ NOTE_TYPE::NORMAL		,EIGHT	,	2 });
	m_qNoteBeats.push({ NOTE_TYPE::NORMAL		,EIGHT	,	1 });
	m_qNoteBeats.push({ NOTE_TYPE::NORMAL		,FOUR	,	0 });
	m_qNoteBeats.push({ NOTE_TYPE::NORMAL		,EIGHT	,	1 });

	m_qNoteBeats.push({ NOTE_TYPE::REST			,EIGHT	,	1 });
	m_qNoteBeats.push({ NOTE_TYPE::NORMAL		,FOUR	,	2 });
	m_qNoteBeats.push({ NOTE_TYPE::NORMAL		,EIGHT	,	2 });
	m_qNoteBeats.push({ NOTE_TYPE::NORMAL		,FOUR	,	3 });
	m_qNoteBeats.push({ NOTE_TYPE::REST			,FOUR	,	2 });

	m_qNoteBeats.push({ NOTE_TYPE::REST			,FOUR	,	1 });
	m_qNoteBeats.push({ NOTE_TYPE::NORMAL		,EIGHT	,	3 });
	m_qNoteBeats.push({ NOTE_TYPE::NORMAL		,EIGHT	,	2 });
	m_qNoteBeats.push({ NOTE_TYPE::NORMAL		,EIGHT	,	1 });
	m_qNoteBeats.push({ NOTE_TYPE::NORMAL		,FOUR	,	0 });
	m_qNoteBeats.push({ NOTE_TYPE::NORMAL		,EIGHT	,	1 });

	//3줄
	m_qNoteBeats.push({ NOTE_TYPE::REST			,EIGHT	,	1 });
	m_qNoteBeats.push({ NOTE_TYPE::NORMAL		,EIGHT	,	0 });
	m_qNoteBeats.push({ NOTE_TYPE::NORMAL		,EIGHT	,	1 });
	m_qNoteBeats.push({ NOTE_TYPE::NORMAL		,EIGHT	,	2 });
	m_qNoteBeats.push({ NOTE_TYPE::REST			,EIGHT	,	1 });
	m_qNoteBeats.push({ NOTE_TYPE::NORMAL		,EIGHT	,	1 });
	m_qNoteBeats.push({ NOTE_TYPE::NORMAL		,EIGHT	,	2 });
	m_qNoteBeats.push({ NOTE_TYPE::NORMAL		,EIGHT	,	3 });

	m_qNoteBeats.push({ NOTE_TYPE::REST		,FOUR	,	3 });
	m_qNoteBeats.push({ NOTE_TYPE::NORMAL		,FOUR	,	3 });
	m_qNoteBeats.push({ NOTE_TYPE::REST			,EIGHT	,	1 });
	m_qNoteBeats.push({ NOTE_TYPE::NORMAL		,FOUR	,	3 });
	m_qNoteBeats.push({ NOTE_TYPE::REST			,EIGHT	,	1 });

	m_qNoteBeats.push({ NOTE_TYPE::NORMAL		,FOUR	,	3 });
	m_qNoteBeats.push({ NOTE_TYPE::REST		,FOUR	,	3 });
	m_qNoteBeats.push({ NOTE_TYPE::REST		,TWO	,	3 });

	m_qNoteBeats.push({ NOTE_TYPE::NORMAL		,EIGHT	,	1 });
	m_qNoteBeats.push({ NOTE_TYPE::NORMAL		,EIGHT	,	2 });
	m_qNoteBeats.push({ NOTE_TYPE::REST		,EIGHT	,	1 });
	m_qNoteBeats.push({ NOTE_TYPE::NORMAL		,EIGHT	,	1 });
	m_qNoteBeats.push({ NOTE_TYPE::REST		,EIGHT	,	1 });
	m_qNoteBeats.push({ NOTE_TYPE::NORMAL		,EIGHT	,	1 });
	m_qNoteBeats.push({ NOTE_TYPE::NORMAL		,FOUR	,	2 });

	m_qNoteBeats.push({ NOTE_TYPE::NORMAL		,EIGHT	,	3 });
	m_qNoteBeats.push({ NOTE_TYPE::NORMAL		,EIGHT	,	2 });
	m_qNoteBeats.push({ NOTE_TYPE::REST		,EIGHT	,	2 });
	m_qNoteBeats.push({ NOTE_TYPE::NORMAL		,EIGHT	,	1 });
	m_qNoteBeats.push({ NOTE_TYPE::NORMAL		,TWO	,	0 });

	m_qNoteBeats.push({ NOTE_TYPE::NORMAL		,EIGHT	,	1 });
	m_qNoteBeats.push({ NOTE_TYPE::NORMAL		,EIGHT	,	2 });
	m_qNoteBeats.push({ NOTE_TYPE::REST		,EIGHT	,	1 });
	m_qNoteBeats.push({ NOTE_TYPE::NORMAL		,EIGHT	,	1 });
	m_qNoteBeats.push({ NOTE_TYPE::REST		,EIGHT	,	2 });
	m_qNoteBeats.push({ NOTE_TYPE::NORMAL		,EIGHT	,	1 });
	m_qNoteBeats.push({ NOTE_TYPE::NORMAL		,EIGHT	,	2 });
	m_qNoteBeats.push({ NOTE_TYPE::NORMAL		,EIGHT	,	3 });

	//4줄
	m_qNoteBeats.push({ NOTE_TYPE::REST		,ONE	,	2 });

	m_qNoteBeats.push({ NOTE_TYPE::NORMAL		,EIGHT	,	1 });
	m_qNoteBeats.push({ NOTE_TYPE::NORMAL		,EIGHT	,	2 });
	m_qNoteBeats.push({ NOTE_TYPE::REST		,EIGHT	,	2 });
	m_qNoteBeats.push({ NOTE_TYPE::NORMAL		,EIGHT	,	2 });
	m_qNoteBeats.push({ NOTE_TYPE::REST		,EIGHT	,	2 });
	m_qNoteBeats.push({ NOTE_TYPE::NORMAL		,EIGHT	,	2 });
	m_qNoteBeats.push({ NOTE_TYPE::NORMAL		,FOUR	,	3 });

	m_qNoteBeats.push({ NOTE_TYPE::NORMAL		,EIGHT	,	3 });
	m_qNoteBeats.push({ NOTE_TYPE::NORMAL		,EIGHT	,	2 });
	m_qNoteBeats.push({ NOTE_TYPE::REST		,EIGHT	,	3 });
	m_qNoteBeats.push({ NOTE_TYPE::NORMAL		,EIGHT	,	1 });
	m_qNoteBeats.push({ NOTE_TYPE::NORMAL		,TWO	,	0 });

	m_qNoteBeats.push({ NOTE_TYPE::NORMAL		,EIGHT	,	1 });
	m_qNoteBeats.push({ NOTE_TYPE::NORMAL		,EIGHT	,	0 });
	m_qNoteBeats.push({ NOTE_TYPE::REST		,EIGHT	,	1 });
	m_qNoteBeats.push({ NOTE_TYPE::NORMAL		,EIGHT	,	0 });
	m_qNoteBeats.push({ NOTE_TYPE::REST		,EIGHT	,	0 });
	m_qNoteBeats.push({ NOTE_TYPE::NORMAL		,EIGHT	,	1 });
	m_qNoteBeats.push({ NOTE_TYPE::NORMAL		,FOUR	,	0 });

	m_qNoteBeats.push({ NOTE_TYPE::NORMAL		,FOUR	,	0 });
	m_qNoteBeats.push({ NOTE_TYPE::REST		,FOUR	,	1 });
	m_qNoteBeats.push({ NOTE_TYPE::NORMAL		,FOUR	,	2 });
	m_qNoteBeats.push({ NOTE_TYPE::REST		,FOUR	,	3 });

	m_qNoteBeats.push({ NOTE_TYPE::GAME_OVER		,FOUR	, 1 });

	DWORD dwTime = m_qNoteBeats.front().dwTime;

	while (m_qNoteBeats.empty() == false)
	{
		NOTE_SPAWN tData = m_qNoteBeats.front();
		tData.dwTime = dwTime;
		m_qNoteTimes.push(tData);
		m_qNoteBeats.pop();
		if (m_qNoteBeats.empty())
			break;
		dwTime += m_qNoteBeats.front().dwTime;
	}
}

NOTE_SPAWN CRythmNoteSpawner::Update()
{
	if (m_bStartSpawn == false)
		return NOTE_SPAWN();
	if (m_qNoteTimes.empty())
		return NOTE_SPAWN(NOTE_TYPE::END);
	if ((m_dwStartTiime + m_dwMusicStarTime) < GetTickCount() && m_bMusicStarted == false)
	{
		SOUND_INST->PlayBGM(L"Super Mario Bross - Theme Song.mp3", 1);
		m_bMusicStarted = true;
	}

	m_dwElapsedTime = GetTickCount() - m_dwStartTiime;
	if (m_dwPrevNoteLen < m_dwElapsedTime)
	{
 		auto data = m_qNoteTimes.front();
		m_qNoteTimes.pop();
		m_dwPrevNoteLen = data.dwTime;

		return data;
	}
	else
		return NOTE_SPAWN();
}

void CRythmNoteSpawner::Late_Update()
{

}

void CRythmNoteSpawner::Release()
{
}
