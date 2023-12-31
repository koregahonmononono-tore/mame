#include "AudioManager.h"

void AudioManager::LoadAudio()
{
    // 音楽読み込み
    {
        // BGM読み込み
        {
            //bgm_[static_cast<int>(BGM::Title)           ] = std::make_unique<Audio>(xAudio2.Get(), L"./resources/audio/BGM/Title.wav");
        }

        // SE読み込み
        {
            //se_[static_cast<int>(SE::Select)      ] = std::make_unique<Audio>(xAudio2.Get(), L"./resources/audio/SE/Select/Select.wav");
        }
    }

    // 音量調整
    {    
        // BGM音量調整
        {
            //bgm_[static_cast<int>(BGM::Title)           ]->Volume(0.75f);
        }

        // SE音量調整
        {
            //se_[static_cast<int>(SE::PL_Walk)     ]->Volume(0.6f);
        }
    }

}


void AudioManager::PlayBGM(const BGM& bgm, const bool isLoop, const bool isIgnoreQueue)
{
    bgm_[static_cast<int>(bgm)]->Play(isLoop, isIgnoreQueue);
}

void AudioManager::PlaySE(const SE& se, const bool isLoop, const bool isIgnoreQueue)
{
    se_[static_cast<int>(se)]->Play(isLoop, isIgnoreQueue);
}


void AudioManager::StopBGM(const BGM& bgm)
{
    bgm_[static_cast<int>(bgm)]->Stop();
}

void AudioManager::StopSE(const SE& se)
{
    se_[static_cast<int>(se)]->Stop();
}


std::unique_ptr<Audio>& AudioManager::GetBGM(const BGM& bgmIndex)
{
    return bgm_[static_cast<int>(bgmIndex)];
}

std::unique_ptr<Audio>& AudioManager::GetSE(const SE& seIndex)
{
    return se_[static_cast<int>(seIndex)];
}


void AudioManager::StopAllBGM()
{
    for (std::unique_ptr<Audio>& bgm :bgm_)
    {
        bgm->Stop();
    }
}

void AudioManager::StopAllSE()
{
    for (std::unique_ptr<Audio>& se : se_)
    {
        se->Stop();
    }
}

void AudioManager::StopAllAudio()
{
    for (std::unique_ptr<Audio>& bgm : bgm_)
    {
        bgm->Stop();
    }
    for (std::unique_ptr<Audio>& se : se_)
    {
        se->Stop();
    }
}
