#pragma once
class CMouseMgr
{
private:
	CMouseMgr();
	~CMouseMgr();

public:
	static CMouseMgr* Get_Instance()
	{
		if (!m_pInstance)
			m_pInstance = new CMouseMgr;

		return m_pInstance;
	}

	static void		Destroy_Instance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}
private:
	static CMouseMgr* m_pInstance;

public:
	POINT Get_Mouse_Point();
};
#define MOUSE_INST CMouseMgr::Get_Instance()
