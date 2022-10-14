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

#include "Connection.h"
#include "LicensingData.h"

namespace licensing
{

Connection::Connection()
{
    sendRequest (createPacket());
}

juce::ValueTree Connection::createPacket()
{
    return {"License",
        {
            {"hardware_id", juce::SystemStats::getDeviceIdentifiers().joinIntoString (";")},
            {"computer_name", juce::SystemStats::getComputerName()}
        }
    };
}

void Connection::sendRequest (juce::ValueTree payload)
{
    auto packet = juce::Base64::toBase64 (payload.toXmlString());

    auto url = juce::URL (juce::String (Data::server) + "license")
        .withParameter ("version", Data::productUuid)
        .withParameter ("payload", packet);

    auto result = url.readEntireTextStream (true);
    DBG (result);
}


} // namespace licensing
