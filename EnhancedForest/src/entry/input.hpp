//
//  input.hpp
//  EnhancedForest
//
//  Created by Admin on 31.07.2021.
//

#pragma once

#include "entry.hpp"

///
void inputInit();

///
void inputShutdown();

///
void inputSetKeyState(entry::Key::Enum _key, uint8_t _modifiers, bool _down);

///
bool inputGetKeyState(entry::Key::Enum _key, uint8_t *_modifiers = NULL);

///
uint8_t inputGetModifiersState();

/// Adds single UTF-8 encoded character into input buffer.
void inputChar(uint8_t _len, const uint8_t _char[4]);

/// Returns single UTF-8 encoded character from input buffer.
const uint8_t *inputGetChar();

/// Flush internal input buffer.
void inputCharFlush();

///
void inputSetMouseResolution(uint16_t _width, uint16_t _height);

///
void inputSetMousePos(int32_t _mx, int32_t _my, int32_t _mz);

///
void inputSetMouseButtonState(entry::MouseButton::Enum _button, uint8_t _state);

///
void inputSetMouseLock(bool _lock);

///
void inputGetMouse(float _mouse[3]);

///
bool inputIsMouseLocked();

///
void inputSetGamepadAxis(entry::GamepadHandle _handle, entry::GamepadAxis::Enum _axis, int32_t _value);

///
int32_t inputGetGamepadAxis(entry::GamepadHandle _handle, entry::GamepadAxis::Enum _axis);
