#ifndef _MYPLAYER_H
#define _MYPLAYER_H

#include "../../StateMachine.h"
#include <string>
#include <map>

// Macro for declaring a state that takes event data
#define STATE_DECLARE_DATA(stateMachine, stateName, eventData) \
    ST_##stateName(const eventData*); \
    StateAction<stateMachine, eventData, &stateMachine::ST_##stateName> stateName;

#define STATE_DEFINE_DATA(stateMachine, stateName, eventData) \
ST_##stateName(const eventData* data)

#define STATE_MAP_DEFINE(...) \
BEGIN_STATE_MAP \
    __VA_ARGS__ \
    END_STATE_MAP

class PlayEventData : public EventData {
public:
    PlayEventData(const std::string& fileName) : m_fileName(fileName) {}
    std::string GetFileName() const { return m_fileName; }

private:
    std::string m_fileName; // 播放事件需要的文件名
};

class Player : public StateMachine {
public:
    Player();

    void OpenClose();
    void Play(const std::string& fileName);
    void Stop();
    void Pause();
    void EndPause();

    enum States {
        ST_EMPTY,
        ST_OPEN,
        ST_STOPPED,
        ST_PAUSED,
        ST_PLAYING,
        ST_MAX_STATES,
        ST_EVENT_IGNORED = EVENT_IGNORED,  // 这里添加 EVENT_IGNORED
        ST_CANNOT_HAPPEN = CANNOT_HAPPEN   // 这里添加 CANNOT_HAPPEN
    };

    enum class Event {
        OpenClose,
        Play,
        Stop,
        Pause,
        EndPause
    };

private:
    std::map<std::pair<Player::Event, Player::States>, Player::States> transitions = {
        {std::make_pair(Player::Event::OpenClose, Player::ST_EMPTY),            Player::ST_OPEN},
        {std::make_pair(Player::Event::OpenClose, Player::ST_OPEN), 			Player::ST_EMPTY},
        {std::make_pair(Player::Event::OpenClose, Player::ST_STOPPED),          Player::ST_OPEN},
        {std::make_pair(Player::Event::OpenClose, Player::ST_PAUSED),			Player::ST_OPEN},
        {std::make_pair(Player::Event::OpenClose, Player::ST_PLAYING),          Player::ST_OPEN},

        {std::make_pair(Player::Event::Play, Player::ST_EMPTY),                 Player::ST_EVENT_IGNORED},
        {std::make_pair(Player::Event::Play, Player::ST_OPEN),                  Player::ST_EVENT_IGNORED},
        {std::make_pair(Player::Event::Play, Player::ST_STOPPED),			    Player::ST_PLAYING},
        {std::make_pair(Player::Event::Play, Player::ST_PAUSED),			    Player::ST_EVENT_IGNORED},
        {std::make_pair(Player::Event::Play, Player::ST_PLAYING),			    Player::ST_EVENT_IGNORED},

        {std::make_pair(Player::Event::Stop, Player::ST_EMPTY),				  Player::ST_EVENT_IGNORED},
        {std::make_pair(Player::Event::Stop, Player::ST_OPEN),				  Player::ST_EVENT_IGNORED},
        {std::make_pair(Player::Event::Stop, Player::ST_STOPPED),             Player::ST_STOPPED},
        {std::make_pair(Player::Event::Stop, Player::ST_PAUSED),              Player::ST_STOPPED},
        {std::make_pair(Player::Event::Stop, Player::ST_PLAYING),             Player::ST_STOPPED},

        {std::make_pair(Player::Event::Pause, Player::ST_EMPTY),              Player::ST_EVENT_IGNORED},
        {std::make_pair(Player::Event::Pause, Player::ST_OPEN),				  Player::ST_EVENT_IGNORED},
        {std::make_pair(Player::Event::Pause, Player::ST_STOPPED),            Player::ST_EVENT_IGNORED},
        {std::make_pair(Player::Event::Pause, Player::ST_PAUSED),             Player::ST_EVENT_IGNORED},
        {std::make_pair(Player::Event::Pause, Player::ST_PLAYING),            Player::ST_PAUSED},

        {std::make_pair(Player::Event::EndPause, Player::ST_EMPTY),			  Player::ST_EVENT_IGNORED},
        {std::make_pair(Player::Event::EndPause, Player::ST_OPEN),			  Player::ST_EVENT_IGNORED},
        {std::make_pair(Player::Event::EndPause, Player::ST_STOPPED),         Player::ST_EVENT_IGNORED},
        {std::make_pair(Player::Event::EndPause, Player::ST_PAUSED),          Player::ST_PLAYING},
        {std::make_pair(Player::Event::EndPause, Player::ST_PLAYING),         Player::ST_EVENT_IGNORED},
        };

    // 声明状态函数
    void STATE_DECLARE_DATA(Player, Empty, NoEventData);
    void STATE_DECLARE_DATA(Player, Open, NoEventData);
    void STATE_DECLARE_DATA(Player, Stopped, NoEventData);
    void STATE_DECLARE_DATA(Player, Paused, NoEventData);
    void STATE_DECLARE_DATA(Player, Playing, PlayEventData);

    // State map to define state object order. Each state map entry defines a
    // state object
    STATE_MAP_DEFINE(
        STATE_MAP_ENTRY(&Empty)
        STATE_MAP_ENTRY(&Open)
        STATE_MAP_ENTRY(&Stopped)
        STATE_MAP_ENTRY(&Paused)
        STATE_MAP_ENTRY(&Playing)
        )

};
#endif // _MYPLAYER_H

#if 0
有什么业务场景需要传递参数的么

在软件设计和架构中，有多种业务场景和用例，其中传递参数到状态机的状态处理函数是必要的。以下是一些典型的场景：

1. **动态数据处理**：
   - 场景：如果状态机代表一个网络连接，那么在处理如“接收数据”或“发送数据”等事件时，可能需要传递具体的数据包或消息。
   - 例子：`ReceiveData(EventData* data)` 函数可以接收包含实际网络数据的 `EventData`。

2. **用户交互**：
   - 场景：在用户界面（UI）驱动的应用中，用户的输入（如文本输入、选择项）可能需要传递给状态机。
   - 例子：在文本编辑器的状态机中，一个 `InsertText(EventData* textData)` 事件可能携带用户输入的文本。

3. **配置或设置更改**：
   - 场景：状态机在运行时可能需要根据外部配置或设置的更改来调整其行为。
   - 例子：在播放器状态机中，`SetPlaybackMode(EventData* modeData)` 可能根据用户选择的播放模式（如随机播放、循环播放）来改变状态逻辑。

4. **资源管理**：
   - 场景：在处理资源（如文件、数据库连接）时，状态机可能需要具体的资源标识符或句柄。
   - 例子：`OpenFile(EventData* fileData)` 可以接收一个包含文件路径的 `EventData`。

5. **多任务或并发控制**：
   - 场景：在多任务环境中，状态机可能需要知道哪个任务或线程触发了特定的状态转换。
   - 例子：`TaskComplete(EventData* taskData)` 事件可能包含完成任务的具体信息。

6. **错误和异常处理**：
   - 场景：当状态机需要处理错误或异常时，传递有关错误的详细信息变得重要。
   - 例子：`HandleError(EventData* errorData)` 可以传递错误代码和描述。

在这些场景中，将参数传递给状态机的状态处理函数允许更灵活、动态且上下文相关的状态管理。这样的设计提高了状态机的通用性和适应性，使其能够更好地满足复杂业务逻辑的需求。
#endif
