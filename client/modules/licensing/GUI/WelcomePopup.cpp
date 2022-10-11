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

 The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

 ==============================================================================
 */

#include "WelcomePopup.h"
#include "LicensingGUI.h"

namespace licensing
{

WelcomePopup::WelcomePopup (Unlocker& unlockerToUse, LicensingGUI& gui)
  : unlocker (unlockerToUse),
    licensingGUI (gui)
{
    demo.onClick = [&]{ unlocker.requestDemo(); };
    buy.onClick = [&]{ unlocker.launchProductPage(); };
    addAndMakeVisible (demo);
    addAndMakeVisible (buy);

    if (Data::closingPopupAllowed)
    {
        close.onClick = [&]{ licensingGUI.closePopup(); };
        addAndMakeVisible (close);
    }
}

void WelcomePopup::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colours::black.withAlpha (0.7f));

    // Display according to the unlocker's status
    
    g.setColour (juce::Colours::silver);
    g.drawFittedText (TRANS ("If you have a license file drag it here"), 10, 40, getWidth() - 20, getHeight() - 90, juce::Justification::topLeft, 10);
}

void WelcomePopup::resized()
{
    close.setBounds(getWidth() - 30, 10, 20, 20);

    auto footer = getLocalBounds().removeFromBottom (50);
    demo.setBounds (footer.removeFromLeft (footer.getWidth() / 2).reduced (10));
    buy.setBounds (footer.reduced (10));
}

bool WelcomePopup::isInterestedInFileDrag (const juce::StringArray& files)
{
    for (const auto& f : files)
        if (f.endsWithIgnoreCase (".lic"))
            return true;

    return false;
}

void WelcomePopup::filesDropped (const juce::StringArray& files, int, int)
{
    for (const auto& f : files)
        if (f.endsWithIgnoreCase (".lic"))
            unlocker.validateLicenseFile (f);
}

} // namespace licensing
