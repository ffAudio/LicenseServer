/*
 ==============================================================================

 Copyright 2022 Foleys Finest Audio and the contributors

 MIT License
 ===========

 Permission is hereby granted, free of charge, to any person obtaining a copy of
 this software and associated documentation files (the "Software"), to deal in
 the Software without restriction, including without limitation the rights to
 use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
 of the Software, and to permit persons to whom the Software is furnished to do
 so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

 ==============================================================================
 */

#pragma once

namespace licensing
{

class LicensingGUI
{
public:
    LicensingGUI (licensing::Unlocker& unlocker, juce::Component* parent);
    ~LicensingGUI();

    /*!
     Show a welcome screen after delayMS miliseconds if not already licensed
     */
    void showWelcome (int delayMS);

    void closePopup();

private:
    licensing::Unlocker& unlocker;
    juce::Component::SafePointer<juce::Component> parent;

    std::unique_ptr<juce::Component> popup;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LicensingGUI)
    JUCE_DECLARE_WEAK_REFERENCEABLE (LicensingGUI)
};

} // namespace licensing
