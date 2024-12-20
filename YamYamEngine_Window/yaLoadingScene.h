#pragma once
#include "..\YamYamEngine_SOURCE\yaScene.h"


namespace ya
{
	class LoadingScene : public Scene
	{
	public:
		LoadingScene();
		~LoadingScene();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC hdc) override;

		void OnEnter() override;
		void OnExit() override;

	private:
		void ResourceLoad(std::mutex& m);

	private:
		bool mbLoadCompleted;
		std::thread* mResourcesLoadThread;
		std::mutex mMutexExclusion;
	};
}