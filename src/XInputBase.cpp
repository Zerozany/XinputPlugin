#include "XInputBase.h"

#include <functional>
#include <iostream>
#include <map>
#include <ranges>
#include <vector>

XInputBase::XInputBase()
{
    std::invoke(&XInputBase::initXinput, this);
}

XInputBase::~XInputBase() noexcept
{
    m_inputHandle.store(false);
    m_cv.notify_all();
    for (auto& t : m_inputPool)
    {
        if (t.joinable())
        {
            t.join();
        }
    }
}

void XInputBase::pressedEventA()
{
    std::cerr << "A Button Pressed!" << std::endl;
}

void XInputBase::stilledEventA()
{
    std::cerr << "A Button Still Pressed!" << std::endl;
}

void XInputBase::releasedEventA()
{
    std::cout << "A Button Released!" << std::endl;
}

void XInputBase::pressedEventB()
{
    std::cerr << "B Button Pressed!" << std::endl;
}

void XInputBase::stilledEventB()
{
    std::cerr << "B Button Still Pressed!" << std::endl;
}

void XInputBase::releasedEventB()
{
    std::cout << "B Button Released!" << std::endl;
}

void XInputBase::pressedEventX()
{
    std::cerr << "X Button Pressed!" << std::endl;
}

void XInputBase::stilledEventX()
{
    std::cerr << "X Button Still Pressed!" << std::endl;
}

void XInputBase::releasedEventX()
{
    std::cout << "X Button Released!" << std::endl;
}

void XInputBase::pressedEventY()
{
    std::cerr << "Y Button Pressed!" << std::endl;
}

void XInputBase::stilledEventY()
{
    std::cerr << "Y Button Still Pressed!" << std::endl;
}

void XInputBase::releasedEventY()
{
    std::cout << "Y Button Released!" << std::endl;
}

void XInputBase::pressedEventUp()
{
    std::cerr << "up Button Pressed!" << std::endl;
}

void XInputBase::stilledEventUp()
{
    std::cerr << "up Button Still Pressed!" << std::endl;
}

void XInputBase::releasedEventUp()
{
    std::cout << "up Button Released!" << std::endl;
}

void XInputBase::pressedEventDown()
{
    std::cerr << "down Button Pressed!" << std::endl;
}

void XInputBase::stilledEventDown()
{
    std::cerr << "down Button Still Pressed!" << std::endl;
}

void XInputBase::releasedEventDown()
{
    std::cout << "down Button Released!" << std::endl;
}

void XInputBase::pressedEventLeft()
{
    std::cerr << "left Button Pressed!" << std::endl;
}

void XInputBase::stilledEventLeft()
{
    std::cerr << "left Button Still Pressed!" << std::endl;
}

void XInputBase::releasedEventLeft()
{
    std::cout << "left Button Released!" << std::endl;
}

void XInputBase::pressedEventRight()
{
    std::cerr << "right Button Pressed!" << std::endl;
}

void XInputBase::stilledEventRight()
{
    std::cerr << "right Button Still Pressed!" << std::endl;
}

void XInputBase::releasedEventRight()
{
    std::cout << "right Button Released!" << std::endl;
}

void XInputBase::pressedEventStart()
{
    std::cerr << "start Button Pressed!" << std::endl;
}

void XInputBase::stilledEventStart()
{
    std::cerr << "start Button Still Pressed!" << std::endl;
}

void XInputBase::releasedEventStart()
{
    std::cout << "start Button Released!" << std::endl;
}

void XInputBase::pressedEventBack()
{
    std::cerr << "back Button Pressed!" << std::endl;
}

void XInputBase::stilledEventBack()
{
    std::cerr << "back Button Still Pressed!" << std::endl;
}

void XInputBase::releasedEventBack()
{
    std::cout << "back Button Released!" << std::endl;
}

void XInputBase::pressedShoulderLeft()
{
    std::cerr << "left shoulder Button Pressed!" << std::endl;
}

void XInputBase::stilledShoulderLeft()
{
    std::cerr << "left shoulder Button Still Pressed!" << std::endl;
}

void XInputBase::releasedShoulderLeft()
{
    std::cout << "left shoulder Button Released!" << std::endl;
}

void XInputBase::pressedShoulderRight()
{
    std::cerr << "right shoulder Button Pressed!" << std::endl;
}

void XInputBase::stilledShoulderRight()
{
    std::cerr << "right shoulder Button Still Pressed!" << std::endl;
}

void XInputBase::releasedShoulderRight()
{
    std::cout << "right shoulder Button Released!" << std::endl;
}

void XInputBase::pressedThumbLeft()
{
    std::cerr << "left thumb Button Pressed!" << std::endl;
}

void XInputBase::stilledThumbLeft()
{
    std::cerr << "left thumb Button Still Pressed!" << std::endl;
}

void XInputBase::releasedThumbLeft()
{
    std::cout << "left thumb Button Released!" << std::endl;
}

void XInputBase::pressedThumbRight()
{
    std::cerr << "right thumb Button Pressed!" << std::endl;
}

void XInputBase::stilledThumbRight()
{
    std::cerr << "right thumb Button Still Pressed!" << std::endl;
}

void XInputBase::releasedThumbRight()
{
    std::cout << "right thumb Button Released!" << std::endl;
}

void XInputBase::pressedTriggerLeft()
{
    std::cerr << "left trigger Button Pressed!" << std::endl;
}

void XInputBase::stilledTriggerLeft()
{
    std::cerr << "left trigger Button Still Pressed!" << std::endl;
}

void XInputBase::releasedTriggerLeft()
{
    std::cout << "left trigger Button Released!" << std::endl;
}

void XInputBase::pressedTriggerRight()
{
    std::cerr << "right trigger Button Pressed!" << std::endl;
}

void XInputBase::stilledTriggeRight()
{
    std::cerr << "right trigger Button Still Pressed!" << std::endl;
}

void XInputBase::releasedTriggerRight()
{
    std::cerr << "right trigger Button Released!" << std::endl;
}

void XInputBase::turnThumbLeft(const short _lx, const short _ly)
{
    std::cout << "Left Thumb Stick X: " << _lx << ", Y: " << _ly << std::endl;
}

void XInputBase::turnThumbRight(const short _rx, const short _ry)
{
    std::cout << "Right Thumb Stick X: " << _rx << ", Y: " << _ry << std::endl;
}

auto XInputBase::initXinput() noexcept -> void
{
    ZeroMemory(&m_state, sizeof(XINPUT_STATE));
    std::cout << "Package Number: " << m_state.dwPacketNumber << std::endl;
}

auto XInputBase::checkInput() noexcept -> void
{
    while (true)
    {
        {
            std::unique_lock<std::mutex> lock{m_stateMtx};
            m_cv.wait(lock, [this] { return m_inputHandle.load(); });
        }
        std::invoke(&XInputBase::listenInputEvent, this);
        std::invoke(&XInputBase::handleTriggerLeft, this);
        std::invoke(&XInputBase::handleTriggerRight, this);
        std::invoke(&XInputBase::handleThumbLeft, this);
        std::invoke(&XInputBase::handleThumbRight, this);
        if (XInputGetState(m_userIndex, &m_state) != ERROR_SUCCESS)
        {
            m_inputHandle.store(false);
            m_cv.notify_one();
        }
    }
}

auto XInputBase::checkInputState() noexcept -> void
{
    while (true)
    {
        {
            std::unique_lock<std::mutex> lock{m_stateMtx};
            m_cv.wait(lock, [this] { return !m_inputHandle.load(); });
        }
        DWORD result{XInputGetState(m_userIndex, &m_state)};
        if (result == ERROR_SUCCESS) [[likely]]
        {
            m_inputHandle.store(true);
        }
        else if (result == ERROR_DEVICE_NOT_CONNECTED)
        {
            m_inputHandle.store(false);
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            std::cerr << "Waitting connect ..." << std::endl;
        }
        m_cv.notify_one();
    }
}

auto XInputBase::xinputStart() noexcept -> void
{
    m_inputPool[0] = std::thread{&XInputBase::checkInputState, this};
    m_inputPool[1] = std::thread{&XInputBase::checkInput, this};
}

auto XInputBase::listenInputEvent() noexcept -> void
{
    struct ButtonState
    {
        uint16_t                              previousButton{};
        bool                                  buttonPressedHandle{false};
        std::chrono::steady_clock::time_point buttonPressTime{};
    };

    struct InputStateKit
    {
        std::function<void()> pressedType;
        std::function<void()> stillType;
        std::function<void()> releaseType;
        ButtonState           buttonState{};
    };

    static std::map<std::int32_t, InputStateKit> inputStateMap{
        {XINPUT_GAMEPAD_A, InputStateKit{std::bind(&XInputBase::pressedEventA, this), std::bind(&XInputBase::stilledEventA, this), std::bind(&XInputBase::releasedEventA, this), ButtonState{}}},
        {XINPUT_GAMEPAD_B, InputStateKit{std::bind(&XInputBase::pressedEventB, this), std::bind(&XInputBase::stilledEventB, this), std::bind(&XInputBase::releasedEventB, this), ButtonState{}}},
        {XINPUT_GAMEPAD_X, InputStateKit{std::bind(&XInputBase::pressedEventX, this), std::bind(&XInputBase::stilledEventX, this), std::bind(&XInputBase::releasedEventX, this), ButtonState{}}},
        {XINPUT_GAMEPAD_Y, InputStateKit{std::bind(&XInputBase::pressedEventY, this), std::bind(&XInputBase::stilledEventY, this), std::bind(&XInputBase::releasedEventY, this), ButtonState{}}},
        {XINPUT_GAMEPAD_DPAD_UP, InputStateKit{std::bind(&XInputBase::pressedEventUp, this), std::bind(&XInputBase::stilledEventUp, this), std::bind(&XInputBase::releasedEventUp, this), ButtonState{}}},
        {XINPUT_GAMEPAD_DPAD_DOWN, InputStateKit{std::bind(&XInputBase::pressedEventDown, this), std::bind(&XInputBase::stilledEventDown, this), std::bind(&XInputBase::releasedEventDown, this), ButtonState{}}},
        {XINPUT_GAMEPAD_DPAD_LEFT, InputStateKit{std::bind(&XInputBase::pressedEventLeft, this), std::bind(&XInputBase::stilledEventLeft, this), std::bind(&XInputBase::releasedEventLeft, this), ButtonState{}}},
        {XINPUT_GAMEPAD_DPAD_RIGHT, InputStateKit{std::bind(&XInputBase::pressedEventRight, this), std::bind(&XInputBase::stilledEventRight, this), std::bind(&XInputBase::releasedEventRight, this), ButtonState{}}},
        {XINPUT_GAMEPAD_LEFT_SHOULDER, InputStateKit{std::bind(&XInputBase::pressedShoulderLeft, this), std::bind(&XInputBase::stilledShoulderLeft, this), std::bind(&XInputBase::releasedShoulderLeft, this), ButtonState{}}},
        {XINPUT_GAMEPAD_RIGHT_SHOULDER, InputStateKit{std::bind(&XInputBase::pressedShoulderRight, this), std::bind(&XInputBase::stilledShoulderRight, this), std::bind(&XInputBase::releasedShoulderRight, this), ButtonState{}}},
        {XINPUT_GAMEPAD_LEFT_THUMB, InputStateKit{std::bind(&XInputBase::pressedThumbLeft, this), std::bind(&XInputBase::stilledTriggerLeft, this), std::bind(&XInputBase::releasedThumbLeft, this), ButtonState{}}},
        {XINPUT_GAMEPAD_RIGHT_THUMB, InputStateKit{std::bind(&XInputBase::pressedThumbRight, this), std::bind(&XInputBase::stilledTriggeRight, this), std::bind(&XInputBase::releasedThumbRight, this), ButtonState{}}},
        {XINPUT_GAMEPAD_START, InputStateKit{std::bind(&XInputBase::pressedEventStart, this), std::bind(&XInputBase::stilledEventStart, this), std::bind(&XInputBase::releasedEventStart, this), ButtonState{}}},
        {XINPUT_GAMEPAD_BACK, InputStateKit{std::bind(&XInputBase::pressedEventBack, this), std::bind(&XInputBase::stilledEventBack, this), std::bind(&XInputBase::releasedEventBack, this), ButtonState{}}},
    };

    auto listenLambda{[&, this](std::int32_t _inputType, std::function<void()>& _pressedEvent, std::function<void()>& _stillEvent, std::function<void()>& _releaseEvent, ButtonState& _buttonState) {
        if ((m_state.Gamepad.wButtons & _inputType) && !(_buttonState.previousButton & _inputType))
        {
            std::invoke(_pressedEvent);
            _buttonState.buttonPressedHandle = true;
            _buttonState.buttonPressTime     = std::chrono::steady_clock::now();
        }
        if ((m_state.Gamepad.wButtons & _inputType) && _buttonState.buttonPressedHandle)
        {
            auto duration{std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - _buttonState.buttonPressTime)};
            if (duration >= m_pressedThreshold)
            {
                std::invoke(_stillEvent);
            }
        }
        if (!(m_state.Gamepad.wButtons & _inputType) && (_buttonState.previousButton & _inputType))
        {
            std::invoke(_releaseEvent);
            _buttonState.buttonPressedHandle = false;
        }
        _buttonState.previousButton = m_state.Gamepad.wButtons;
    }};

    for (auto& [__type, __inputStateKit] : inputStateMap)
    {
        std::invoke(listenLambda, __type, __inputStateKit.pressedType, __inputStateKit.stillType, __inputStateKit.releaseType, __inputStateKit.buttonState);
    }
}

void XInputBase::handleTriggerLeft() noexcept
{
    constinit static uint8_t                               previousTriggerLeft{0};
    constinit static bool                                  pressedTriggerHandleLeft{false};
    constinit static std::chrono::steady_clock::time_point pressedTriggerTimeLeft{};
    uint8_t                                                ValueTriggerLeft = m_state.Gamepad.bLeftTrigger;
    if (ValueTriggerLeft > 0 && previousTriggerLeft == 0)
    {
        std::invoke(&XInputBase::pressedTriggerLeft, this);
        pressedTriggerHandleLeft = true;
        pressedTriggerTimeLeft   = std::chrono::steady_clock::now();
    }
    if (ValueTriggerLeft > 0 && pressedTriggerHandleLeft)
    {
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - pressedTriggerTimeLeft);
        if (duration >= m_pressedThreshold)
        {
            std::invoke(&XInputBase::stilledTriggerLeft, this);
        }
    }
    if (ValueTriggerLeft == 0 && previousTriggerLeft > 0)
    {
        std::invoke(&XInputBase::releasedTriggerLeft, this);
        pressedTriggerHandleLeft = false;
    }
    previousTriggerLeft = ValueTriggerLeft;
}

void XInputBase::handleTriggerRight() noexcept
{
    constinit static uint8_t                               previousTriggerRight{0};
    constinit static bool                                  pressedTriggerHandleRight{false};
    constinit static std::chrono::steady_clock::time_point pressedTriggerTimeRight{};
    uint8_t                                                ValueTriggerRight = m_state.Gamepad.bRightTrigger;
    if (ValueTriggerRight > 0 && previousTriggerRight == 0)
    {
        std::invoke(&XInputBase::pressedTriggerRight, this);
        pressedTriggerHandleRight = true;
        pressedTriggerTimeRight   = std::chrono::steady_clock::now();
    }
    if (ValueTriggerRight > 0 && pressedTriggerHandleRight)
    {
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - pressedTriggerTimeRight);
        if (duration >= m_pressedThreshold)
        {
            std::invoke(&XInputBase::stilledTriggeRight, this);
        }
    }
    if (ValueTriggerRight == 0 && previousTriggerRight > 0)
    {
        std::invoke(&XInputBase::releasedTriggerRight, this);
        pressedTriggerHandleRight = false;
    }
    previousTriggerRight = ValueTriggerRight;
}

void XInputBase::handleThumbLeft() noexcept
{
    short           thumbLx{m_state.Gamepad.sThumbLX};
    short           thumbLy{m_state.Gamepad.sThumbLY};
    constexpr short deadzoneLeft{XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE};
    if (abs(thumbLx) > deadzoneLeft || abs(thumbLy) > deadzoneLeft)
    {
        std::invoke(&XInputBase::turnThumbLeft, this, thumbLx, thumbLy);
    }
    else
    {
        // std::cout << "Left Thumb Stick is in deadzone" << std::endl;
    }
}

void XInputBase::handleThumbRight() noexcept
{
    short           thumbRx{m_state.Gamepad.sThumbRX};
    short           thumbRy{m_state.Gamepad.sThumbRY};
    constexpr short deadzoneRight{XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE};
    if (abs(thumbRx) > deadzoneRight || abs(thumbRy) > deadzoneRight)
    {
        std::invoke(&XInputBase::turnThumbRight, this, thumbRx, thumbRy);
    }
    else
    {
        // std::cout << "Right Thumb Stick is in deadzone" << std::endl;
    }
}
