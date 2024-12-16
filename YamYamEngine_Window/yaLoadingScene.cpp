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
			// 만약 메인 쓰레드가 종료되는데 자식쓰레드가 남아있다면
			// 자식 쓰레드를 메인쓰레드에 편입시켜 메인쓰레드가 종료되기 전까지 block
			mResourcesLoadThread->join();

			// 메인쓰레드와 완전 분리 시켜 독립적인 쓰레드 운영가능
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