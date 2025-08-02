_Pragma("once");
#include <Windows.h>
#include <Xinput.h>

#include <atomic>
#include <condition_variable>
#include <mutex>
#include <thread>

class XInputBase
{
public:
    explicit(true) XInputBase();
    XInputBase(const XInputBase& /*other */)            = delete;
    XInputBase& operator=(const XInputBase& /*other */) = delete;
    XInputBase(XInputBase&& /*other */)                 = delete;
    XInputBase& operator=(XInputBase&& /*other */)      = delete;
    ~XInputBase() noexcept;

public:
    auto xinputStart() noexcept -> void;

    virtual void pressedEventA();
    virtual void stilledEventA();
    virtual void releasedEventA();

    virtual void pressedEventB();
    virtual void stilledEventB();
    virtual void releasedEventB();

    virtual void pressedEventX();
    virtual void stilledEventX();
    virtual void releasedEventX();

    virtual void pressedEventY();
    virtual void stilledEventY();
    virtual void releasedEventY();

    virtual void pressedEventUp();
    virtual void stilledEventUp();
    virtual void releasedEventUp();

    virtual void pressedEventDown();
    virtual void stilledEventDown();
    virtual void releasedEventDown();

    virtual void pressedEventLeft();
    virtual void stilledEventLeft();
    virtual void releasedEventLeft();

    virtual void pressedEventRight();
    virtual void stilledEventRight();
    virtual void releasedEventRight();

    virtual void pressedShoulderLeft();
    virtual void stilledShoulderLeft();
    virtual void releasedShoulderLeft();

    virtual void pressedShoulderRight();
    virtual void stilledShoulderRight();
    virtual void releasedShoulderRight();

    virtual void pressedThumbLeft();
    virtual void stilledThumbLeft();
    virtual void releasedThumbLeft();

    virtual void pressedThumbRight();
    virtual void stilledThumbRight();
    virtual void releasedThumbRight();

    virtual void pressedTriggerLeft();
    virtual void stilledTriggerLeft();
    virtual void releasedTriggerLeft();

    virtual void pressedTriggerRight();
    virtual void stilledTriggeRight();
    virtual void releasedTriggerRight();

    virtual void pressedEventStart();
    virtual void stilledEventStart();
    virtual void releasedEventStart();

    virtual void pressedEventBack();
    virtual void stilledEventBack();
    virtual void releasedEventBack();

    virtual void turnThumbLeft(const short _lx, const short _ly);
    virtual void turnThumbRight(const short _rx, const short _ry);

private:
    auto initXinput() noexcept -> void;

    auto checkInput() noexcept -> void;

    auto checkInputState() noexcept -> void;

    auto listenInputEvent() noexcept -> void;

    void handleTriggerLeft() noexcept;

    void handleTriggerRight() noexcept;

    void handleThumbLeft() noexcept;

    void handleThumbRight() noexcept;

private:
    DWORD m_userIndex{};

    XINPUT_STATE m_state{};

    std::atomic<bool> m_inputHandle{false};

    std::thread m_inputPool[2]{};

    std::mutex m_stateMtx{};

    std::condition_variable m_cv{};

    constexpr static inline std::chrono::milliseconds m_pressedThreshold{500};
};
