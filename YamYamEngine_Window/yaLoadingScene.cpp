#include "yaLoadingScene.h"
#include "yaRenderer.h"
#include "yaSceneManager.h"
#include "yaResources.h"
#include "yaTexture.h"


namespace ya
{
	ya::LoadingScene::LoadingScene() : mbLoadCompleted(false), mMutexExclusion(), mResourcesLoadThread()
	{
	}
	LoadingScene::~LoadingScene()
	{
		delete mResourcesLoadThread;
		mResourcesLoadThread = nullptr;
	}
	void LoadingScene::Initialize()
	{
		mResourcesLoadThread = new std::thread(&LoadingScene::ResourceLoad, this, std::ref(mMutexExclusion));
	}
	void LoadingScene::Update()
	{
		if (mbLoadCompleted)
		{
			// ���� ���� �����尡 ����Ǵµ� �ڽľ����尡 �����ִٸ�
			// �ڽ� �����带 ���ξ����忡 ���Խ��� ���ξ����尡 ����Ǳ� ������ block
			mResourcesLoadThread->join();

			// ���ξ������ ���� �и� ���� �������� ������ �����
			// mResourcesLoad->detach();

			SceneManager::LoadScene(L"PlayScene");
		}
	}
	void LoadingScene::LateUpdate()
	{
	}
	void LoadingScene::Render(HDC hdc)
	{
	}
	void LoadingScene::OnEnter()
	{
	}
	void LoadingScene::OnExit()
	{
	}
	void LoadingScene::ResourceLoad(std::mutex& m)
	{
		m.lock();
		{
			Resources::Load<graphics::Texture>(L"Cat", L"..\\Resources\\ChickenAlpha.bmp");
			Resources::Load<graphics::Texture>(L"Player", L"..\\Resources\\Player.bmp");
			Resources::Load<graphics::Texture>(L"SpringFloor", L"..\\Resources\\SpringFloor.bmp");
			Resources::Load<graphics::Texture>(L"HPBAR", L"..\\Resources\\HPBAR.bmp");
			Resources::Load<graphics::Texture>(L"PixelMap", L"..\\Resources\\pixelMap.bmp");
		}
		m.unlock();

		mbLoadCompleted = true;
	}
}