from django.contrib import admin

# Register your models here.

from .models import Product, Version, Customer, License, Activation

admin.site.register(Product)
admin.site.register(Version)
admin.site.register(Customer)
admin.site.register(License)
admin.site.register(Activation)
