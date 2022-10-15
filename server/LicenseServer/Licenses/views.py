"""
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
"""

from django.shortcuts import render, redirect, get_object_or_404
from django.http import HttpResponse
from django.views.decorators.csrf import csrf_exempt

from .models import Version
import os
import base64
from xml.dom import minidom

# Create your views here.

def index(request):
    return redirect(os.environ.get('PARENT_HOSTNAME'))


# This checks the database for a valid license, demo or if demo is available
@csrf_exempt
def license(request):
    version = get_object_or_404(Version, pk=request.POST["version"])
    data = base64.b64decode(request.POST["payload"])

    return HttpResponse("License test for:" + str(version.product) + "\n" + str(data))


# This creates a cpp file for the developer to pu in their product to unlock
def license_data(request, version_id):
    version = get_object_or_404(Version, pk=version_id)

    source = """
/*
  ==============================================================================

    license_data.cpp

    This file is auto generated by the license server

  ==============================================================================
*/

#pragma once

namespace licensing {
namespace Data {

"""

    source += 'const char* server      = "https://' + os.environ.get('HEROKU_HOSTNAME') + '/";\n'
    source += 'const char* productPage = "' + version.product.website + '";\n'
    source += 'const char* productUuid = "' + str(version.id) + '";\n'
    source += 'const char* publicKey   = "' + version.public_key + '";\n'
    source += 'long        hash        = ' + str(version.public_key_hash) + ';\n'
    allowed = 'true' if version.product.allowDismissPopup else 'false'
    source += 'bool        closingPopupAllowed = ' + allowed + ';\n'

    source += """
} // namespace Data
} // namespace licensing
    
"""

    return HttpResponse(source, headers={
        'Content-Type': 'text/plain',
        'Content-Disposition': 'attachment; filename="license_data.cpp"',
    })
