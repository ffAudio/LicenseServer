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

from django.db import models
import uuid


# Create your models here.


class Product(models.Model):
    name = models.CharField(max_length=256)
    website = models.URLField(blank=True)
    allowDismissPopup = models.BooleanField()

    def __str__(self):
        return self.name


class Version(models.Model):
    id = models.UUIDField(primary_key=True, default=uuid.uuid4, editable=False)
    product = models.ForeignKey(Product, on_delete=models.CASCADE)
    version_string = models.CharField(max_length=64)
    private_key = models.TextField()
    public_key = models.TextField()
    public_key_hash = models.BigIntegerField()
    created = models.DateTimeField(auto_now_add=True)


class Customer(models.Model):
    id = models.UUIDField(primary_key=True, default=uuid.uuid4, editable=False)
    name = models.CharField(max_length=256)
    email = models.EmailField(blank=True)
    created = models.DateTimeField(auto_now_add=True)

    def __str__(self):
        return self.name + " (" + self.email + ")"


class License(models.Model):
    customer = models.ForeignKey(Customer, on_delete=models.PROTECT)
    product = models.ForeignKey(Product, on_delete=models.PROTECT)
    created = models.DateTimeField(auto_now_add=True)


class Activation(models.Model):
    version = models.ForeignKey(Version, on_delete=models.CASCADE)
    customer = models.ForeignKey(Customer, on_delete=models.CASCADE, blank=True)
    hardware_id = models.CharField(max_length=256)
    hardware_name = models.CharField(max_length=256)
    demo_expires = models.DateTimeField(blank=True)
    created = models.DateTimeField(auto_now_add=True)
