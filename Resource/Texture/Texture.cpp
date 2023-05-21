
#include "Texture.h"
#include "../../PathManager.h"
#include "../../GameManager.h"

CTexture::CTexture() :
	m_Type(ETexture_Type::Sprite)
{
}

CTexture::~CTexture()
{
	size_t	Size = m_vecImageInfo.size();

	for (size_t i = 0; i < Size; ++i)
	{
		SAFE_DELETE(m_vecImageInfo[i]);
	}
}

bool CTexture::LoadTexture(const TCHAR* FileName, 
	const std::string& PathName)
{
	const PathInfo* Path = CPathManager::GetInst()->FindPath(PathName);

	TCHAR	FullPath[MAX_PATH] = {};

	if (Path)
		lstrcpy(FullPath, Path->Path);

	lstrcat(FullPath, FileName);

	return LoadTextureFullPath(FullPath);

}

bool CTexture::LoadTextureFullPath(const TCHAR* FullPath)
{
	// memDC�� ����� ���� �Լ�
	// ȭ�� DC�� �ְ� �޸� DC�� ��´�.
	HDC hDC = CreateCompatibleDC(CGameManager::GetInst()->GetWindowDC());

	// ��Ʈ���� �ε��Ѵ�.
	// 2��°���� : ���(�� ��ο� �ִ� �̹����� �ҷ��Ͷ�)
	// 3��° ���� : �̹��� Ÿ��
	// 4,5��° ���� : �̹��� ũ��. 0���� �ϸ� �ȴ�.
	// 6��° ���� : �ε带 ��� �� ������. LR_LOADFROMFILE:���Ϸκ��� �ҷ��ð��̴�.
	HBITMAP hBmp = (HBITMAP)LoadImage(CGameManager::GetInst()->GetWindowInstance(),
		FullPath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	if (!hBmp)
		return false;

	// �о�� ��Ʈ���� �޸� DC�� �����Ѵ�.

	HBITMAP hPrevBmp = (HBITMAP)SelectObject(hDC, hBmp); //m_hMemDC���ٰ� m_hBmp�������ϰڴ�.

	BITMAP	BmpInfo;

	GetObject(hBmp, sizeof(BITMAP), &BmpInfo);

	ImageInfo* Info = new ImageInfo;

	Info->hMemDC = hDC;
	Info->hBmp = hBmp;
	Info->hPrevBmp = hPrevBmp;
	Info->BmpInfo = BmpInfo;

	m_vecImageInfo.push_back(Info);

	return true;
}

#ifdef UNICODE

bool CTexture::LoadTexture(const std::vector<std::wstring>& vecFileName,
	const std::string& PathName)
{
	m_Type = ETexture_Type::Frame;

	const PathInfo* Path = CPathManager::GetInst()->FindPath(PathName);

	std::vector<std::wstring>	vecFullPath;

	size_t	Size = vecFileName.size();

	// �̸� ������ŭ push �س��� ȿ���̴�.
	vecFullPath.resize(Size);

	// �̸� �迭 ������ Ȯ���Ͽ� �� á���� ���� ���Ҵ��� �Ͼ�°��� �������ִ�
	// ������ �Ҷ� ����Ѵ�.
	//vecFullPath.reserve(Size);

	for (size_t i = 0; i < Size; ++i)
	{
		if (Path)
			vecFullPath[i] = Path->Path;

		vecFullPath[i] += vecFileName[i];
	}

	return LoadTextureFullPath(vecFullPath);
}

bool CTexture::LoadTextureFullPath(const std::vector<std::wstring>& vecFullPath)
{
	m_Type = ETexture_Type::Frame;

	size_t	Size = vecFullPath.size();

	for (size_t i = 0; i < Size; ++i)
	{
		// ȭ��DC�� �ְ� �޸� DC�� ��´�.
		HDC	hDC = CreateCompatibleDC(CGameManager::GetInst()->GetWindowDC());

		// ��Ʈ���� �ε��Ѵ�.
		// string �̳� wstring Ŭ������ c_str() �Լ��� ���ڿ� �����͸� ���´�.
		HBITMAP	hBmp = (HBITMAP)LoadImage(CGameManager::GetInst()->GetWindowInstance(),
			vecFullPath[i].c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

		if (!hBmp)
			return false;

		// �о�� ��Ʈ���� �޸� DC�� �����Ѵ�.
		// ������ DC�� ������ �ִ� ������ ��ȯ�Ѵ�.
		HBITMAP hPrevBmp = (HBITMAP)SelectObject(hDC, hBmp);

		BITMAP	BmpInfo;

		GetObject(hBmp, sizeof(BITMAP), &BmpInfo);

		ImageInfo* Info = new ImageInfo;

		Info->hMemDC = hDC;
		Info->hBmp = hBmp;
		Info->hPrevBmp = hPrevBmp;
		Info->BmpInfo = BmpInfo;

		m_vecImageInfo.push_back(Info);
	}

	return true;
}

#else

bool CTexture::LoadTexture(const std::vector<std::string>& vecFileName,
	const std::string& PathName)
{
	m_Type = ETexture_Type::Frame;

	const PathInfo* Path = CPathManager::GetInst()->FindPath(PathName);

	std::vector<std::string>	vecFullPath;

	size_t	Size = vecFileName.size();

	// �̸� ������ŭ push �س��� ȿ���̴�.
	vecFullPath.resize(Size);

	// �̸� �迭 ������ Ȯ���Ͽ� �� á���� ���� ���Ҵ��� �Ͼ�°��� �������ִ�
	// ������ �Ҷ� ����Ѵ�.
	//vecFullPath.reserve(Size);

	for (size_t i = 0; i < Size; ++i)
	{
		if (Path)
			vecFullPath[i] = Path->Path;

		vecFullPath[i] += vecFileName[i];
	}

	return LoadTextureFullPath(vecFullPath);
}

bool CTexture::LoadTextureFullPath(const std::vector<std::string>& vecFullPath)
{
	m_Type = ETexture_Type::Frame;

	size_t	Size = vecFullPath.size();

	for (size_t i = 0; i < Size; ++i)
	{
		// ȭ��DC�� �ְ� �޸� DC�� ��´�.
		HDC	hDC = CreateCompatibleDC(CGameManager::GetInst()->GetWindowDC());

		// ��Ʈ���� �ε��Ѵ�.
		// string �̳� wstring Ŭ������ c_str() �Լ��� ���ڿ� �����͸� ���´�.
		HBITMAP	hBmp = (HBITMAP)LoadImage(CGameManager::GetInst()->GetWindowInstance(),
			vecFullPath[i].c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

		if (!hBmp)
			return false;

		// �о�� ��Ʈ���� �޸� DC�� �����Ѵ�.
		// ������ DC�� ������ �ִ� ������ ��ȯ�Ѵ�.
		HBITMAP hPrevBmp = (HBITMAP)SelectObject(hDC, hBmp);

		BITMAP	BmpInfo;

		GetObject(hBmp, sizeof(BITMAP), &BmpInfo);

		ImageInfo* Info = new ImageInfo;

		Info->hMemDC = hDC;
		Info->hBmp = hBmp;
		Info->hPrevBmp = hPrevBmp;
		Info->BmpInfo = BmpInfo;

		m_vecImageInfo.push_back(Info);
	}

	return true;
}

#endif // UNICODE
