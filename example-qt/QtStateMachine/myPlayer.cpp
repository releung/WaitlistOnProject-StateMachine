#include "myPlayer.h"
#include <iostream>
#include <map>

Player::Player() :
	StateMachine(ST_MAX_STATES)
{
}

void Player::OpenClose()
{
    auto key = std::make_pair(Player::Event::OpenClose, (Player::States)GetCurrentState());
    try {
        ExternalEvent((BYTE)transitions.at(key), NULL);
    } catch (const std::out_of_range& e) {
        // 键不存在于 map 中的处理逻辑
    }
}

void Player::Play(const std::string& fileName) 
{
    PlayEventData* pData = new PlayEventData(fileName);
    auto key = std::make_pair(Player::Event::Play, (Player::States)GetCurrentState());
    try {
        ExternalEvent(transitions.at(key), pData);
    } catch (const std::out_of_range& e) {
        // 键不存在于 map 中的处理逻辑
    }
}

void Player::Stop()
{
    auto key = std::make_pair(Player::Event::Stop, (Player::States)GetCurrentState());
    try {
        ExternalEvent(transitions.at(key), NULL);
    } catch (const std::out_of_range& e) {
        // 键不存在于 map 中的处理逻辑
    }
}

void Player::Pause()
{
    auto key = std::make_pair(Player::Event::Pause, (Player::States)GetCurrentState());
    try {
        ExternalEvent(transitions.at(key), NULL);
    } catch (const std::out_of_range& e) {
        // 键不存在于 map 中的处理逻辑
    }
}

void Player::EndPause()
{
    auto key = std::make_pair(Player::Event::EndPause, (Player::States)GetCurrentState());
    try {
        ExternalEvent((BYTE)transitions.at(key), NULL);
    } catch (const std::out_of_range& e) {
        // 键不存在于 map 中的处理逻辑
    }
}

void Player::STATE_DEFINE_DATA(Player, Empty, NoEventData)
{
	static BOOL CD_DetectedToggle = FALSE;
    CD_DetectedToggle = CD_DetectedToggle == FALSE ? TRUE : FALSE;

    std::cout << "Player::ST_Empty" << __PRETTY_FUNCTION__ << __LINE__ << std::endl;
    if (CD_DetectedToggle == TRUE)
        InternalEvent((BYTE)Player::States::ST_STOPPED);
}

void Player::STATE_DEFINE_DATA(Player, Open,	NoEventData)
{
    std::cout << "Player::ST_Open" << __PRETTY_FUNCTION__ << __LINE__ << std::endl;
}

void Player::STATE_DEFINE_DATA(Player, Stopped, NoEventData)
{
    std::cout << "Player::ST_Stopped" << __PRETTY_FUNCTION__ << __LINE__ << std::endl;
}

void Player::STATE_DEFINE_DATA(Player, Paused, NoEventData)
{
    std::cout << "Player::ST_Paused" << __PRETTY_FUNCTION__ << __LINE__ << std::endl;
}

void Player::STATE_DEFINE_DATA(Player, Playing, PlayEventData) {
    const std::string& fileName = data->GetFileName();
    std::cout << "Player::ST_Playing, playing file: " << __PRETTY_FUNCTION__ << __LINE__ << fileName << std::endl;
    // 这里添加播放逻辑
}
