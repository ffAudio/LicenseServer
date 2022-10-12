from django.db import models

# Create your models here.


class Product(models.Model):
    name = models.CharField(max_length=256)
    website = models.URLField(blank=True)
    allowDismissPopup = models.BooleanField()


class Version(models.Model):
    product = models.ForeignKey(Product, on_delete=models.CASCADE)
    version_string = models.CharField(max_length=64)
    uuid = models.UUIDField()
    private_key = models.TextField()
    public_key = models.TextField()
    public_key_hash = models.BigIntegerField()
    created = models.DateTimeField(auto_now_add=True)


class Customer(models.Model):
    name = models.CharField(max_length=256)
    email = models.EmailField(blank=True)
    created = models.DateTimeField(auto_now_add=True)


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

